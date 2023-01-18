#include "item.h"

int item_init(struct item_t **item_ptr)
{
	struct item_t *item;
	item = malloc(sizeof(struct item_t));

	if (item==NULL) 
		return -1;

	*item_ptr = item;
	
	item->mac = malloc(6);
	item->signal = -1000;

	int ret;
	ret = tiempo_init(&(item->tiempo_first));
	ret = tiempo_init(&(item->tiempo_max));
	ret = tiempo_init(&(item->tiempo_last));

	item->sent = 0;
	
	return 0;
}

int mac_cmp(unsigned char *mac1, unsigned char *mac)
{
	if (mac1[0]==mac[0] && mac1[1]==mac[1] && mac1[2]==mac[2] && mac1[3]==mac[3] && mac1[4]==mac[4] && mac1[5]==mac[5])
		return 0;
	return -1;
}

void mac_print(unsigned char *d)
{
	printf("%02X:%02X:%02X:%02X:%02X:%02X", d[0], d[1], d[2], d[3], d[4], d[5]);
}

void item_print(struct item_t *item)
{
	tiempo_print(item->tiempo_first);
	printf(" ");
	mac_print(item->mac);
	printf(" signal %d\n", item->signal_first);
}

void item_send(struct item_t *item, unsigned char type)
{
	item_print(item);
}


