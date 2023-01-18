#ifndef IFACE_H
#define IFACE_H

#include <poll.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ds.h"

struct iface_t {
	int fd;
	struct sockaddr_ll *addr;
	socklen_t addrlen;
};

#define IFACE_DATA_LEN 2048

int iface_init(struct iface_t **iface_ptr, char *name);
void iface_close(struct iface_t *iface);
void iface_read_ds(struct iface_t *iface, struct ds_t *ds);
int iface_read_data(struct iface_t *iface, unsigned char *data, int size);

#endif
