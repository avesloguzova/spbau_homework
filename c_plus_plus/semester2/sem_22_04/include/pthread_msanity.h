#ifdef __cplusplus
extern "C" {
#endif
    
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex) throw();
int pthread_mutex_unlock(pthread_mutex_t *mutex) throw();

#ifdef __cplusplus
}
#endif