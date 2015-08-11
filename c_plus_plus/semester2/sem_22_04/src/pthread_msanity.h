#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

#ifdef __cplusplus
}
#endif