#include "list.h"

int list_init(struct list_t **list_ptr, int size)
{
	struct list_t *list;
	list = malloc(sizeof(struct list_t));

	if (list==NULL) 
		return -1;

	*list_ptr = list;
	
	list->it = calloc(size, sizeof(void*));
	
	list->used = 0;
	list->size = size;
	list->index = 0;
			
	return 0;

}

void list_add(struct list_t *list, void* item)
{
	list->it[list->index] = item;
	(list->used)++;
	(list->index)++;
	if (list->index == list->size) list->index = 0;
	if (list->used > list->size) list->used = list->size;
}

void list_clear(struct list_t *list)
{
	list->used = 0;
	list->index = 0;
}

void list_fill(struct list_t *list)
{
	int i, imax;
	imax = list->size;
	struct item_t *item_new;
	int ret;
	for (i=0; i<imax; i++) {
		ret = item_init(&item_new);
		list->it[i] = (void*)item_new;
	}
}

int list_search(struct list_t *list, unsigned char *mac)
{
	int i, imax;
	imax = list->used;
	struct item_t *item;
	
	for (i=0; i<imax; i++) {
		item = (struct item_t *)(list->it[i]);
		if (mac_cmp(item->mac, mac)==0) return i;
	}

	return -1;
}

int list_add_mac(struct list_t *list, unsigned char *mac, int signal)
{
	struct item_t *item;
	int ret;
	ret = list_search(list, mac);

	if (ret>=0) {
		item = (struct item_t *)(list->it[ret]);
		if (signal > item->signal_max) {
			item->signal_max = signal;
			tiempo_get(item->tiempo_max);
		}

		item->signal_last = signal;
		tiempo_get(item->tiempo_last);

		if (item->sent==0) {
			item->sent = 1;
			item_send(item, 'f');
		}

		return 1;
	} else {
		item = (struct item_t*)(list->it[list->index]);
		(list->used)++;
		(list->index)++;
		if (list->index == list->size) list->index = 0;
		if (list->used > list->size) list->used = list->size;
		
		memcpy(item->mac, mac, 6);
		item->signal_first = signal;
		item->signal_max = signal;
		item->signal_last = signal;
		tiempo_get(item->tiempo_first);
		tiempo_get(item->tiempo_max);
		tiempo_get(item->tiempo_last);
		item->sent = 0;

		return 0;
	}
	return -1;
}

void list_send_last(struct list_t *list)
{
	int i, imax;
	imax = list->used;
	struct item_t *item;
	
	for(i=0; i<imax; i++) {
		item = (struct item_t *)(list->it[i]);
		if (item->tiempo_first->sec != item->tiempo_max->sec) {
			item_send(item, 'm');
		}
		if ((item->tiempo_max->sec != item->tiempo_last->sec) && (item->tiempo_first->sec != item->tiempo_last->sec )) {
			item_send(item, 'l');
		}

	}
}

void list_def_send_last()
{
	list_send_last(list_def);
}

int list_def_add_mac(unsigned char *mac, int signal)
{
	return list_add_mac(list_def, mac, signal);
}

int list_def_search(unsigned char *mac)
{
	return list_search(list_def, mac);
}

void list_def_fill()
{
	list_fill(list_def);
}

void list_def_clear()
{
	list_clear(list_def);
}

int list_def_init(int size)
{
	return list_init(&list_def, size);
}

void list_def_add(void* item)
{
	list_add(list_def, item);
}

