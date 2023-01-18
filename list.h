#ifndef LIST_H
#define LIST_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "item.h"
#include "tiempo.h"


struct list_t {
	void **it;
	int used;
	int size;
	int index;
};


int list_init(struct list_t **list_ptr, int size);
void list_add(struct list_t *list, void* item);

struct list_t *list_def;
int list_def_init(int size);
void list_def_add(void* item);


void list_clear(struct list_t *list);
void list_def_clear();

void list_fill(struct list_t *list);
void list_def_fill();

int list_search(struct list_t *list, unsigned char *mac);
int list_def_search(unsigned char *mac);

int list_add_mac(struct list_t *list, unsigned char *mac, int signal);
int list_def_add_mac(unsigned char *mac, int signal);

void list_send_last(struct list_t *list);
void list_def_send_last();

#endif
