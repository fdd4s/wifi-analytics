#include "ds.h"

int ds_init(struct ds_t **ds_ptr, int size)
{
	struct ds_t *ds;
	ds = malloc(sizeof(struct ds_t));

	if (ds==NULL) 
		return -1;

	*ds_ptr = ds;
	
	if (size > 0) {
		ds->d = malloc(size);
		if (ds->d == NULL) {
			free(ds);
			return -1;
		}
	}
	
	ds->used = 0;
	ds->size = size;
	
	return 0;
}

void ds_free(struct ds_t *ds)
{
	if (ds->size > 0) free(ds->d);
	free(ds);
}


