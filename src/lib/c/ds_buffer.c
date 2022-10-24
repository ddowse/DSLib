#include "ds_buffer.h"

ds_buffer_t *ds_buffer_initialize(const size_t buffer_length) {
	if(buffer_length == 0)
		return NULL;

	ds_buffer_t *buffer = malloc(sizeof(ds_buffer_t));
	if(buffer) {
		buffer->string          = calloc(buffer_length, sizeof(char));
		buffer->string_length   = 0;
		buffer->buffer_length   = buffer_length;
		buffer->internal_length = buffer_length;
	}

	return buffer;
}

void ds_buffer_insert_char(ds_buffer_t *buffer, const char c) {
	if(buffer && buffer->buffer_length > 0) {
		if(buffer->string_length == buffer->internal_length - 1) {
			buffer->string           = realloc(buffer->string, sizeof(char) * (buffer->internal_length + buffer->buffer_length));
			buffer->internal_length += buffer->buffer_length;
		}

		buffer->string[buffer->string_length++] = c;
		buffer->string[buffer->string_length] = '\0';
	}
}

void ds_buffer_insert_string(ds_buffer_t *buffer, const char *string) {
	if(buffer && string) {
		while(*string != '\0')
			ds_buffer_insert_char(buffer, *string++);
	}
}

ds_buffer_t *ds_buffer_deinitialize(ds_buffer_t *buffer) {
	if(buffer) {
		free(buffer->string);
		free(buffer);
		buffer = NULL;
	}

	return buffer;
}

void ds_buffer_print_all(ds_buffer_t *buffer) {
	if(buffer && buffer->string) {
		printf(
			"  String length: %lu\n"
			"  Buffer length: %lu\n"
			"Internal length: %lu\n"
			"         String:\n\n%s\n",
			buffer->string_length,
			buffer->buffer_length,
			buffer->internal_length,
			buffer->string
		);
	} else {
		printf("Buffer or buffer string is NULL\n");
	}
}

void ds_buffer_print_string(ds_buffer_t *buffer) {
	if(buffer && buffer->string)
		printf("%s\n", buffer->string);
	else
		printf("Buffer or buffer string is NULL\n");
}
