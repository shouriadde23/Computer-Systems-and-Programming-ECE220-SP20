#include "acc.h"
#include <pthread.h>

int main() {
    pthread_mutex_init(&lock_for_result, NULL);

    int i = 0;
    int j = 0;
    pthread_t threads[NUM_THREADS];
    int memory_store[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; i++) {
      memory_store[i] = i;
        pthread_create(&threads[i], NULL, *parallel_acc_wrapper, (void*) &memory_store[i]);
    }

    for(j = 0; j < NUM_THREADS; j++) {
        pthread_join(threads[j], NULL);
    }

    FILE *out = fopen("parallel_output.txt", "w");
    fprintf(out, "%llu\n", result);
    fclose(out);
    return 0;

}
