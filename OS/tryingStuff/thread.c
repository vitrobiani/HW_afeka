#include <pthread.h>
#include <stdio.h>
#include <threads.h>

static int counter = 0;
pthread_mutex_t lock;

void *mythread(void *arg) {
    printf("begin: %s\n", (char *)arg);

    pthread_mutex_lock(&lock);
    for (int i = 0; i < 1e7; i++) {
        counter = counter + 1;
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t p1, p2;
    printf("main begin: counter = %d \n", counter);
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main done: counter = %d\n", counter);
    return 0;
}
