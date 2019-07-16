#ifndef __PT_STORE_HEAD_H__
#define __PT_STORE_HEAD_H__

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <malloc.h>

#define NUM_OF_SHOPS 5
#define NUM_OF_BUYERS 3
#define BUYER_NEED 2500
#define COND_MIN_OF_LOAD 1 //condition number of products for one loading
#define COND_MAX_OF_LOAD 6 //condition number of products for one loading

void kekich (void *);
void *purchases_n_loading (void *);

#endif