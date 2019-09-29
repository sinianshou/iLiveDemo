
#ifndef PI_ILIVEBASESTRUCT_HPP
#define PI_ILIVEBASESTRUCT_HPP

#include "PI_iLiveBaseVersion.h"


#ifdef NT_VERSION
#include <stdint.h>
#include <windows.h>
#define PI_iLiveBase_Mutex          CRITICAL_SECTION
#define PI_iLiveBase_Cond            HANDLE
#endif

#ifdef NT_VERSION
#if defined(SELF_BASE_DLL)
#define BASE_API __declspec(dllexport)
#else
#define BASE_API __declspec(dllimport)
#endif
#else
#define BASE_API
#endif

#ifdef UNIX_VERSION
#define INFINITE                    0xFFFFFFFF
#define PI_iLiveBase_Mutex          pthread_mutex_t
#define PI_iLiveBase_Cond           pthread_cond_t
#endif

#ifndef NT_VERSION
typedef uint32_t                    DWORD;
typedef void                        *(*LPTHREAD_START_ROUTINE)(void *);
#endif

typedef	unsigned int                SOCKET;

#endif
