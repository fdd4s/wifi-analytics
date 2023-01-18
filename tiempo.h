#ifndef TIEMPO_H
#define TIEMPO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

unsigned long timeblock_start;
unsigned long timeblock_block;

void timeblock_init(unsigned long secs);
int timeblock_check();
unsigned long 	timeblock_now();

struct tiempo_t {
	unsigned long sec;
	int usec;
};

int tiempo_init(struct tiempo_t **tiempo_ptr);
void tiempo_get(struct tiempo_t *tiempo);
void tiempo_resta(struct tiempo_t *tiempo_des, struct tiempo_t *tiempo1, struct tiempo_t *tiempo2);
void tiempo_print(struct tiempo_t *tiempo);
void tiempo_print_hour_usec(struct tiempo_t *tiempo);

struct tiempo_t crono_t1;
struct tiempo_t crono_t2;
struct tiempo_t crono_resta;
int crono_block;

void crono_init();
int crono_set();

void tiempo_add(struct tiempo_t *tiempo_des, struct tiempo_t *tiempo_add);
struct tiempo_t cronoabs_tblock;
struct tiempo_t cronoabs_t0;
struct tiempo_t cronoabs_t1;
struct tiempo_t cronoabs_t2;
struct tiempo_t cronoabs_resta;
int cronoabs_block;

void cronoabs_init();
int cronoabs_set();

#endif
