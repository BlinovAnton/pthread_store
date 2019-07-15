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

int *gl_shops = NULL, status = 0;
pthread_mutex_t * gl_mutex = NULL;

void kekich (void *arg) {
    printf("loader end his job\n");
}

void * purchases_n_loading (void *arg) {
    int * thread_num;
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

int main () {
    srand(time(NULL));
    int i = 0;
    int *j_status = calloc(NUM_OF_BUYERS + 1, sizeof(int));
    int *personal_val = calloc(NUM_OF_BUYERS + 1, sizeof(int));
    pthread_t *thread = malloc((NUM_OF_BUYERS + 1) * sizeof(pthread_t));
    gl_shops = calloc(NUM_OF_SHOPS, sizeof(int));
    gl_mutex = malloc(NUM_OF_SHOPS * sizeof(pthread_mutex_t));
    for (i = 0; i < NUM_OF_SHOPS; i++) {
	pthread_mutex_init(&gl_mutex[i], NULL);
    }
    for (i = 0; i <= NUM_OF_BUYERS; i++) {
	personal_val[i] = i;
	status = pthread_create(&thread[i], NULL, purchases_n_loading, &personal_val[i]);
	if (status) {
	    perror("pthread_create error\n");
	    return 0;
	}
    }
    for (i = NUM_OF_BUYERS; i > 0; i--) {
	status = pthread_join(thread[i], (void **)&j_status[i]);
	if (!status) {
	    printf("thread %d joined with %d\n", personal_val[i], j_status[i]);
	}
    }
    status = pthread_cancel(thread[0]);
    if (!status) {
	for (i = 0; i < NUM_OF_SHOPS; i++)
	    pthread_mutex_destroy(&gl_mutex[i]);
	status = pthread_join(thread[0], (void **)&j_status[0]);
	if (status) {
	    perror("pthread_join() fault");
	} else {
	    printf("thread %d joined with %d\n", personal_val[0], j_status[0]);
	}
    } else {
	perror("pthread_cancel() fault");
    }
    free(j_status);
    free(personal_val);
    free(thread);
    free(gl_shops);
    free(gl_mutex);
    return 0;
}