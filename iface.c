#include "iface.h"

static int iface_bind(int fd, int ifindex) {
	struct sockaddr_ll	sll;
	int			err;
	socklen_t		errlen = sizeof(err);

	memset(&sll, 0, sizeof(sll));
	sll.sll_family		= AF_PACKET;
	sll.sll_ifindex		= ifindex;
	sll.sll_protocol	= htons(ETH_P_ALL);

	if (bind(fd, (struct sockaddr *) &sll, sizeof(sll)) == -1) return -1;
	
	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) return -1;
	
	if (err > 0) return -1;

	return 0;
}

int iface_get_index(char *if_name, int fd) {
	int ret;
	struct ifreq ifr;
	size_t if_name_len;
	
	ret = -1;
	
	if_name_len = strlen(if_name);
	memcpy(ifr.ifr_name, if_name, if_name_len);
	ifr.ifr_name[if_name_len] = 0;
		
	if (fd == -1) return ret;
    	if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) return ret;
	
	ret = ifr.ifr_ifindex;
	
	return ret;
}

static int iface_get_id(int fd, const char *device) {
	struct ifreq	ifr;

	memset(&ifr, 0, sizeof(ifr));
	memcpy(ifr.ifr_name, device, sizeof(ifr.ifr_name));

	if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) {
		
		return -1;
	}

	return ifr.ifr_ifindex;
}

static int iface_fd_new(struct iface_t *iface, char *dev) {
	int so;
	int ifindex;

	so = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	
	ifindex = iface_get_id(so, (const char*)dev);
	iface->addr->sll_ifindex = ifindex;
	
	iface_bind(so, ifindex);

	return so;
}

int iface_init(struct iface_t **iface_ptr, char *name) {
	struct iface_t *iface;
	iface = malloc(sizeof(struct iface_t));

	if (iface==NULL) 
		return -1;

	*iface_ptr = iface;
	
	struct sockaddr_ll *addr;
	addr = malloc(sizeof(struct sockaddr_ll));
	if (addr==NULL)
		return -1;
	
	iface->addr = addr;
	
	memset(addr, 0, sizeof(struct sockaddr_ll));
	iface->addrlen = sizeof(struct sockaddr_ll);
	
	const unsigned char ether_broadcast_addr[] = {0xff,0xff,0xff,0xff,0xff,0xff};
	addr->sll_family = AF_PACKET;
	addr->sll_halen = ETHER_ADDR_LEN;
	addr->sll_protocol = htons(ETH_P_ARP);
	memcpy(addr->sll_addr, ether_broadcast_addr, ETHER_ADDR_LEN);

	int fd;
	fd = iface_fd_new(iface, name);
	if (fd==-1) {
		free(iface);
		return -1;
	}
	
	iface->fd = fd;
	
	return 0;
}

void iface_close(struct iface_t *iface) {
	close(iface->fd);
}

void iface_read_ds(struct iface_t *iface, struct ds_t *ds) {
	ds->used = read(iface->fd, ds->d, ds->size);
	if (ds->used < 0) ds->used = 0;
}

int iface_read_data(struct iface_t *iface, unsigned char *data, int size)
{
	return read(iface->fd, data, size);
}
