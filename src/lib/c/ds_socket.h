#ifndef DS_SOCKET_H_
#define DS_SOCKET_H_

#define DS_SOCKET_VERSION "0.0.2"
#define DS_SOCKET_NAME    "ds_socket"
#define DS_SOCKET_AUTHOR  "Thorsten Geppert (thorsten@tgeppert.de)"

#ifdef __WINDOWS__
	#include <winsock.h>
#else
	#include <netinet/in.h>
#endif

#define TRUE  1
#define FALSE 0

#define DS_SCS_OK                  0
#define DS_SCS_ERROR_GETHOSTBYNAME 1

typedef char ds_bool_t;

typedef struct ds_socket_connection {
	int connection;
	char *host;
	unsigned short port;
	struct sockaddr_in address;
	short family;
	int protocol;
	int type;
	ds_bool_t options_setted;
	int timeout_seconds;
	int timeout_microseconds;
	ds_bool_t timeout_setted;
} ds_socket_connection_t;

ds_socket_connection_t *ds_socket_create_connection(
	const char *host,
	unsigned short port,
	unsigned int *error
);
ds_socket_connection_t *ds_socket_copy_connection(ds_socket_connection_t *connection);

ds_socket_connection_t *ds_socket_destroy_connection(ds_socket_connection_t *connection);

void ds_socket_set_family(ds_socket_connection_t *connection, short family);
void ds_socket_set_protocol(ds_socket_connection_t *connection, int protocol);
void ds_socket_set_type(ds_socket_connection_t *connection, int type);
ds_bool_t ds_socket_set_options(ds_socket_connection_t *connection, int level, int name, void *value, int length);
ds_bool_t ds_socket_set_default_options(ds_socket_connection_t *connection);
void ds_socket_set_timeout(ds_socket_connection_t *connection, long seconds, long mircoseconds);

ds_bool_t ds_socket_connect(ds_socket_connection_t *connection);
ds_bool_t ds_socket_bind(ds_socket_connection_t *connection);
ds_bool_t ds_socket_listen(ds_socket_connection_t *connection, int tries);
ds_bool_t ds_socket_disconnect(ds_socket_connection_t *connection);
ds_socket_connection_t *ds_socket_acceppt(ds_socket_connection_t *connection);
ds_bool_t ds_socket_timeout(ds_socket_connection_t *connection);

int ds_socket_receive(ds_socket_connection_t *connection, void *buffer, int length, int flags);
int ds_socket_send(ds_socket_connection_t *connection, void *buffer, int length, int flags);

#endif /* DS_SOCKET_H_ */
