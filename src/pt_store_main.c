#include "../include/pt_store_head.h"

int *gl_shops = NULL, status = 0;
pthread_mutex_t * gl_mutex = NULL;

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