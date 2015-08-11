#include <pthread.h>

int main(){
    pthread_mutex_t test_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&test_mutex);
    pthread_mutex_unlock(&test_mutex);
}