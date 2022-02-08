#ifndef DS_BUFFER_H_
#define DS_BUFFER_H_

#include <stdlib.h>

typedef struct {
	char *string;
	size_t string_length;
	size_t buffer_length;
	size_t internal_length;
} ds_buffer_t;

ds_buffer_t *ds_buffer_initialize(const size_t buffer_length);
void ds_buffer_insert_char(ds_buffer_t *buffer, const char c);
void ds_buffer_insert_string(ds_buffer_t *buffer, const char *string);
ds_buffer_t *ds_buffer_deinitialize(ds_buffer_t *buffer);
void ds_buffer_print_all(ds_buffer_t *buffer);
void ds_buffer_print_string(ds_buffer_t *buffer);

#endif /* DS_BUFFER_H_ */
