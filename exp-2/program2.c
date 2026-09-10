#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void *work(void *arg)
{
    int id = *(int *)arg;

    printf("Divit: thread %d is running on CPU core %d\n", id, sched_getcpu());

    return NULL;
}

int main()
{
    pthread_t threads[4];
    int ids[4];

    for (int i = 0; i < 4; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, work, &ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
