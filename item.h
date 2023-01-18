#ifndef ITEM_H
#define ITEM_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "tiempo.h"

struct item_t {
	//uint32_t id;
	unsigned char *mac;
	int signal;
	int signal_first;
	int signal_max;
	int signal_last;
	struct tiempo_t *tiempo_first;
	struct tiempo_t *tiempo_last;
	struct tiempo_t *tiempo_max;

	int sent;
};

int item_init(struct item_t **item_ptr);

int mac_cmp(unsigned char *mac1, unsigned char *mac);

void mac_print(unsigned char *d);

void item_print(struct item_t *item);

void item_send(struct item_t *item, unsigned char type);

#endif
