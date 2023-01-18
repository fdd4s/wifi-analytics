#ifndef DS_H
#define DS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct ds_t {
	unsigned char *d;
	int used;
	int size;
};

int ds_init(struct ds_t **ds_ptr, int size);
void ds_free(struct ds_t *ds);

#endif
