#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "iface.h"
#include "ds.h"

#include "list.h"
#include "tiempo.h"
#include "item.h"

unsigned char macdis1[6];
unsigned char macdis2[6];

void mac_blacklist_init();
int packet_new(unsigned char *d, int size);
int mac_blacklist_check(unsigned char *mac);
void signal_new(unsigned char *mac_src, unsigned char *mac_des, int signal);
int packet_new(unsigned char *d, int size);

int main(int argc, char** argv)
{		
	printf("wifi-analytics monitor 1.0\n");

	if (argc!=2) {
		printf("wamon <iface>\n");
		return 0;
	}

	timeblock_init(60);
	mac_blacklist_init();
	list_def_init(10000);
	list_def_fill();
	
	struct iface_t *iface;
        if (iface_init(&iface, argv[1]) < 0) {
		printf("error opening iface\n");
		return -1;
	}

	struct ds_t *ds;
	int ret;
	
	ret = ds_init(&ds, 2048);
	if (ret<0) { printf("ds init error\n"); return 0; }
	
	for (;;) {
		iface_read_ds(iface, ds);
		if (ds->used < 1) continue;
	
		packet_new(ds->d, ds->used);
	}
	
	return 0;
}

void mac_blacklist_init()
{
	memset(macdis1, 0xff, 6);
	memset(macdis2, 0, 6);
}

int mac_blacklist_check(unsigned char *mac)
{
	if (mac_cmp(mac, macdis1)==0) return -1;
	if (mac_cmp(mac, macdis2)==0) return -1;
	return 0;
}

void signal_new(unsigned char *mac_src, unsigned char *mac_des, int signal)
{
	int ret;

	if (mac_blacklist_check(mac_src)==-1) return;

	if (timeblock_check()==0) {
		list_def_send_last();

		list_def_clear();
	}

	ret  = list_def_add_mac(mac_src, signal);
}

int packet_new(unsigned char *d, int size)
{
	if (size < 10) return -1;

	if (d[0] != 0 || d[1] != 0) return -1;
	
	int radiotap_size;
	radiotap_size = d[2] + d[3] * 256;
	
	unsigned char signal;
	signal = d[34];
	int signal2;
	signal2 = (int)(char)signal;
	
	unsigned char *wlan_d;
	wlan_d = d + radiotap_size;

	int wlan_size;
	wlan_size = size - radiotap_size;

	if (wlan_size < 18) return 0;
	if (wlan_d[0] == 0xc4 || wlan_d[0] == 0xd4) return 0;
	
	unsigned char *mac_des;
	unsigned char *mac_src;
	
	mac_des = wlan_d + 4;
	mac_src = mac_des + 6;

	signal_new(mac_src, mac_des, signal2);

	return 0;	
}


