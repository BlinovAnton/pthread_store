#include "../include/pt_store_head.h"

extern int *gl_shops;
extern pthread_mutex_t * gl_mutex;

void kekich (void *arg) {
    printf("loader end his job\n");
}

void *purchases_n_loading (void *arg) {
    int *thread_num;
    int i;
    thread_num = (int *)arg;
    if (!(*thread_num)) {
	//loader_code
	int load = 0;
	pthread_cleanup_push(kekich, NULL);
	while (1) {
	    i = (double)rand() / RAND_MAX * NUM_OF_SHOPS; //0...NUM_OF_SHOPS-1
	    pthread_mutex_lock(&gl_mutex[i]);

	    load = 100 * (COND_MIN_OF_LOAD + (rand() % COND_MAX_OF_LOAD));
	    gl_shops[i] += load;

	    printf("%d loaded %d products to shop_%d\n", *thread_num, load, i);

	    pthread_mutex_unlock(&gl_mutex[i]);
	}
	pthread_cleanup_pop(0);
    } else {
	//buyer_code
	int purchase = 0;
	while (purchase < BUYER_NEED) {
	    i = (double)rand() / RAND_MAX * NUM_OF_SHOPS; //0...NUM_OF_SHOPS-1
	    pthread_mutex_lock(&gl_mutex[i]);

	    purchase += gl_shops[i];

	    printf("%d bought %d products from shop_%d\n", *thread_num, gl_shops[i], i);
	    printf("\tneed: %d/%d\n", purchase, BUYER_NEED);

	    pthread_mutex_unlock(&gl_mutex[i]);
	}
	printf("!%d leave sales!\n", *thread_num);
	pthread_exit(0);
    }
}