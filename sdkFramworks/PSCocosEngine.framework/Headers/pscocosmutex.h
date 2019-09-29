/*****************************************************************************
 * pscocosmutex.h
 *****************************************************************************
 */

#ifndef PSCOCOS_MUTEX_H
#define PSCOCOS_MUTEX_H



#include <stdint.h>
#include <pthread.h>

#define PSCOCOS_MUTEX_TIMEDOUT  1
#define PSCOCOS_MUTEX_MAXWAIT   (~(uint32_t)0)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PSDL_mutex {
    pthread_mutex_t id;
} PSDL_mutex;

PSDL_mutex  *PSDL_CreateMutex(void);
void        PSDL_DestroyMutex(PSDL_mutex *mutex);
int         PSDL_LockMutex(PSDL_mutex *mutex);
int         PSDL_UnlockMutex(PSDL_mutex *mutex);

typedef struct PSDL_cond {
    pthread_cond_t id;
} PSDL_cond;

PSDL_cond   *PSDL_CreateCond(void);
void        PSDL_DestroyCond(PSDL_cond *cond);
int         PSDL_CondSignal(PSDL_cond *cond);
int         PSDL_CondBroadcast(PSDL_cond *cond);
int         PSDL_CondWaitTimeout(PSDL_cond *cond, PSDL_mutex *mutex, uint32_t ms);
int         PSDL_CondWait(PSDL_cond *cond, PSDL_mutex *mutex);
    
#ifdef __cplusplus
}
#endif

#endif
