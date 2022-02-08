#include "ds_socket.h"
#include <stdlib.h>
#include <string.h>

#ifdef __WINDOWS__
	#define socklen_t int
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
#endif

ds_socket_connection_t *ds_socket_create_connection(
	const char *host,
	unsigned short port,
	unsigned int *error
) {
	ds_socket_connection_t *connection = malloc(sizeof(ds_socket_connection_t));
	connection->connection           = -1;
	connection->host                 = NULL;
	connection->family               = AF_INET;
	connection->protocol             = 0;
	connection->type                 = SOCK_STREAM;
	connection->options_setted       = FALSE;
	connection->timeout_seconds      = 0;
	connection->timeout_microseconds = 0;
	connection->timeout_setted       = FALSE;

	bzero((char *)&connection->address, sizeof connection->address);

	size_t length = 0;
	if(host) {
		length = strlen(host);
		connection->host = calloc(length + 1, sizeof(char));
		strncpy(connection->host, host, length);

		struct hostent *hp = NULL;

		#ifndef __WINDOWS__
			if(!inet_aton(connection->host, &connection->address.sin_addr)) {
				hp = gethostbyname(connection->host);
				if(!hp && error)
					*error = DS_SCS_ERROR_GETHOSTBYNAME;
				connection->address.sin_addr = *(struct in_addr *) hp->h_addr;
			}
		#else
			WSADATA wsa;
			if(WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
				if(error)
					connection->address.sin_addr = *(struct in_addr *) hp->h_addr;

			hp = gethostbyname(connection->host);
			if(!hp && error)
				connection->address.sin_addr = *(struct in_addr *) hp->h_addr;

			connection->address.sin_addr = *((struct in_addr*) (hp->h_addr_list[0]));
		#endif

		connection->address.sin_family   = connection->family;
		connection->address.sin_port     = htons(port);
	}

	return connection;
}

ds_socket_connection_t *ds_socket_copy_connection(ds_socket_connection_t *connection) {
	if(!connection)
		return 0;
	
	ds_socket_connection_t *copy      = ds_socket_create_connection(connection->host, connection->port, NULL);
	copy->address              = connection->address;
	copy->family               = connection->family;
	copy->protocol             = connection->protocol;
	copy->type                 = connection->type;
	copy->options_setted       = connection->options_setted;
	copy->timeout_seconds      = connection->timeout_seconds;
	copy->timeout_microseconds = connection->timeout_microseconds;
	copy->timeout_setted       = connection->timeout_setted;

	return copy;
}

ds_socket_connection_t *ds_socket_destroy_connection(ds_socket_connection_t *connection) {
	if(connection) {
		if(connection->host)
			free(connection->host);
		free(connection);
	}

	return NULL;
}

void ds_socket_set_family(ds_socket_connection_t *connection, short family) {
	if(connection) {
		connection->family = family;
		connection->address.sin_family = family;
	}
}

void ds_socket_set_protocol(ds_socket_connection_t *connection, int protocol) {
	if(connection)
		connection->protocol = protocol;
}

void ds_socket_set_type(ds_socket_connection_t *connection, int type) {
	if(connection)
		connection->type = type;
}

ds_bool_t ds_socket_set_options(ds_socket_connection_t *connection, int level, int name, void *value, int length) {
	if(!connection)
		return FALSE;

	const int tmp = 1;

	connection->options_setted = setsockopt(
		connection->connection,
		level,
		name,
		#ifdef __WINDOWS__
			value == NULL ? (char *) &tmp : (char *) value,
		#else
			value == NULL ? (void *) &tmp : value,
		#endif
		value == NULL ? sizeof(tmp) : length
	) == 0 ? TRUE : FALSE;

	return connection->options_setted;
}

ds_bool_t ds_socket_set_default_options(ds_socket_connection_t *connection) {
	return ds_socket_set_options(connection, SOL_SOCKET, SO_REUSEADDR, NULL, 1);
}

void ds_socket_set_timeout(ds_socket_connection_t *connection, long seconds, long mircoseconds) {
	if(!connection)
		return;
		
	connection->timeout_seconds      = seconds;
	connection->timeout_microseconds = mircoseconds;
	connection->timeout_setted       = TRUE;
}

ds_bool_t ds_socket_connect(ds_socket_connection_t *connection) {
	connection->connection = socket(connection->family, connection->type, connection->protocol);
	if(connection->connection <= 0)
		return FALSE;

	if(connection->options_setted == FALSE)
		ds_socket_set_default_options(connection);

	return connect(
		connection->connection,
		(struct sockaddr *) &connection->address,
		sizeof(connection->address)
	) == 0 ? TRUE : FALSE;
}

ds_bool_t ds_socket_bind(ds_socket_connection_t *connection) {
	connection->connection = socket(connection->family, connection->type, connection->protocol);
	if(connection->connection <= 0) {
		return FALSE;
	}

	if(connection->options_setted == FALSE)
		ds_socket_set_default_options(connection);

	return bind(
		connection->connection,
		(struct sockaddr *) &connection->address,
		sizeof(connection->address)
	) == 0 ? TRUE : FALSE;
}

ds_bool_t ds_socket_listen(ds_socket_connection_t *connection, int tries) {
	return listen(connection->connection, tries) == 0 ? TRUE : FALSE;
}

ds_bool_t ds_socket_disconnect(ds_socket_connection_t *connection) {
	return close(connection->connection) == 0 ? TRUE : FALSE;
}

ds_socket_connection_t *ds_socket_acceppt(ds_socket_connection_t *connection) {
	socklen_t length = sizeof(struct sockaddr_in);
	ds_socket_connection_t *copy = ds_socket_copy_connection(connection);
	copy->connection = accept(
		connection->connection,
		(struct sockaddr *) &connection->address,
		&length
	);

	if(copy->connection > 0) {
		#ifdef __WINDOWS__
			memcpy((struct sockaddr *) &copy->address, &connection->address, length);
		#else
			bcopy(&connection->address, (struct sockaddr *) &copy->address, length);
		#endif
	} else {
		copy = ds_socket_destroy_connection(copy);
	}

	return copy;
}

ds_bool_t ds_socket_timeout(ds_socket_connection_t *connection) {
	if(!connection)
		return FALSE;

	if(connection->timeout_setted == FALSE)
		return FALSE;
	
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(connection->connection, &fds);

	struct timeval timeout;
	timeout.tv_sec  = connection->timeout_seconds;
	timeout.tv_usec = connection->timeout_microseconds;

	return select(connection->connection + 1, &fds, NULL, NULL, &timeout) <= 0 ? TRUE : FALSE;
}

int ds_socket_receive(ds_socket_connection_t *connection, void *buffer, int length, int flags) {
	#ifdef __WINDOWS__
		return recv(connection->connection, (char *) buffer, length, flags);
	#else
		return recv(connection->connection, buffer, length, flags);
	#endif
}

int ds_socket_send(ds_socket_connection_t *connection, void *buffer, int length, int flags) {
	#ifdef __WINDOWS__
		return send(connection->connection, (char *) buffer, length, flags);
	#else
		return send(connection->connection, buffer, length, flags);
	#endif
}
