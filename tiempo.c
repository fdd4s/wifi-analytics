#include "tiempo.h"

void timeblock_init(unsigned long secs)
{
	timeblock_start = timeblock_now();
	timeblock_block = secs;
}

int timeblock_check()
{
	unsigned long dife;
	dife = timeblock_now() - timeblock_start;
	if (dife > timeblock_block) {
		timeblock_start = timeblock_now();
		return 0;
	}
	return -1;
}

unsigned long timeblock_now()
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	return (unsigned long)timeval.tv_sec;
}

int tiempo_init(struct tiempo_t **tiempo_ptr)
{
	struct tiempo_t *tiempo;
	tiempo = malloc(sizeof(struct tiempo_t));

	if (tiempo==NULL) 
		return -1;

	*tiempo_ptr = tiempo;
	
	return 0;
}

void tiempo_get(struct tiempo_t *tiempo)
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	tiempo->sec = timeval.tv_sec;
	tiempo->usec = timeval.tv_usec;
}

void 	 tiempo_print(struct tiempo_t *tiempo)
{
	tiempo_print_hour_usec(tiempo);
}

void tiempo_print_date(struct tiempo_t *tiempo)
{
	time_t t = tiempo->sec;
	struct tm tm = *localtime(&t);

	printf("%02d:%02d:%02d %02d/%02d/%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900); 
}

void tiempo_print_hour_usec(struct tiempo_t *tiempo)
{
	time_t t = tiempo->sec;
	struct tm tm = *localtime(&t);

	printf("%02d:%02d:%02d.%06d", tm.tm_hour, tm.tm_min, tm.tm_sec, tiempo->usec); 
}

void tiempo_resta(struct tiempo_t *tiempo_des, struct tiempo_t *tiempo1, struct tiempo_t *tiempo2)
{
	tiempo_des->sec = tiempo1->sec - tiempo2->sec;
	if (tiempo_des->sec == 0) {
		tiempo_des->usec = tiempo1->usec - tiempo2->usec;
	} else {
		if (tiempo1->usec >= tiempo2->usec) {
			tiempo_des->usec = tiempo1->usec - tiempo2->usec;
		} else {
			tiempo_des->sec -= 1;
			tiempo_des->usec = (1000000 - tiempo2->usec) + tiempo1->usec;
		}
	}
}

void tiempo_add(struct tiempo_t *tiempo_des, struct tiempo_t *tiempo_add)
{
	tiempo_des->sec = tiempo_des->sec + tiempo_add->sec;
	tiempo_des->usec = tiempo_des->usec + tiempo_add->usec;

	if (tiempo_des->usec >= 1000000) {
		(tiempo_des->sec)++;
		tiempo_des->usec = 1000000 - tiempo_des->usec;
	}


}

void tiempo_copy(struct tiempo_t *tiempo_des, struct tiempo_t *tiempo_src)
{
	tiempo_des->sec = tiempo_src->sec;
	tiempo_des->usec = tiempo_src->usec;
}

void crono_init()
{
	crono_block = 40000;
	tiempo_get(&crono_t1);
}

int crono_set()
{
	int diferencia;

	tiempo_get(&crono_t2);
	tiempo_resta(&crono_resta, &crono_t2, &crono_t1);
	if (  (crono_resta.sec > 0 )  || (crono_resta.usec > crono_block) ) {
		tiempo_copy(&crono_t1, &crono_t2);
		return 0;
	}
	diferencia = crono_block - crono_resta.usec;
	usleep(diferencia);
	return -1; 
}

void cronoabs_init()
{
	cronoabs_block = 40000;
	cronoabs_tblock.sec = 0;
	cronoabs_tblock.usec = cronoabs_block;
	tiempo_get(&cronoabs_t0);
	tiempo_get(&cronoabs_t1);
}

int cronoabs_set()
{
	int diferencia;

	tiempo_get(&cronoabs_t2);
	tiempo_resta(&cronoabs_resta, &cronoabs_t2, &cronoabs_t1);
	if (  (cronoabs_resta.sec > 0 )  || (cronoabs_resta.usec > cronoabs_block) ) {
		//tiempo_copy(&cronoabs_t1, &cronoabs_t2);
		tiempo_add(&cronoabs_t1, &cronoabs_tblock);
		return 0;
	}
	diferencia = cronoabs_block - cronoabs_resta.usec;
	usleep(diferencia);
	return -1; 
}

