
#ifndef _LIB_PS_GLOBAL_STATUS_H_
#define _LIB_PS_GLOBAL_STATUS_H_

#ifdef UNIX_VERSION
#include <pthread.h>
#endif

#define PSPULL_STATUS_TERMINATED    -1
#define PSPULL_STATUS_STOP      0
#define PSPULL_STATUS_REQUEST   2
#define PSPULL_STATUS_WAIT      4
#define PSPULL_STATUS_START     6
#define PSPULL_STATUS_PROBE     8
#define PSPULL_STATUS_PROBEOK   10
#define PSPULL_STATUS_RUN       100

#define MAX_PS_PULL_NUMBER 9
#define MAX_PS_PULL_BITRATE_COUNT 8
#define SINGLE_LOG_LENGTH 12560
#define MAX_SAVED_LOG_COUNT 10

#define MAX_ERROR_LOG_COUNT 10
#define MAX_ERROR_LOG_DOMAIN_LENGTH 2048
#define MAX_ERROR_LOG_CONTENT_LENGTH 4096

class PSPullStatus;
class PSPushStatus;

struct PullDataRecord{
    int32_t    lastFlux;
    int32_t    lastDuration;
    int32_t    lastFreeze_Count;
    int32_t    lastFreeze;
    
    int32_t    lastBitrate[MAX_PS_PULL_BITRATE_COUNT];
    
    long long   LastLogTick;
};

class BASE_API PSGlobalStatus
{
public:
    static PSGlobalStatus *GetInstance() {
        if (!m_pInstance) {
            m_pInstance = new PSGlobalStatus;
            printf("new m_pInstance");
        }
        
        return m_pInstance;
    }
    
    virtual void destructor();
    
    // mutex
	PI_iLiveBase_Mutex mutex;
#ifdef NT_VERSION
	PI_iLiveBase_Cond  m_sleepcond;
#endif
#ifdef UNIX_VERSION
	PI_iLiveBase_Mutex m_sleepmutex;
	PI_iLiveBase_Cond  m_sleepcond;
#endif
    // Pull Status
    int m_iStatus;  // 0-stop, 1-started, 2-running
    int pull_number;
    int flushInterval;
    PSPullStatus *pull_status[MAX_PS_PULL_NUMBER];
    PullDataRecord *pull_data_record[MAX_PS_PULL_NUMBER];
    
    int64_t lastFlushTick;
    
    // Push Status
    PSPushStatus *push_status;
    
    void uploadProc();
    
    int start();   //start upload thread
    void stop();    //stop upload thread
    int getSinglePullLog(int no, int64_t current_time, char* returnlog);
    
    void freshPullStatus();
    
    int savedLogCount;
    char* savedLog[MAX_SAVED_LOG_COUNT];
    size_t savedLogLength[MAX_SAVED_LOG_COUNT];
    
    int errorLogCount;
    char* errorLogURI[MAX_ERROR_LOG_COUNT];
    char* errorLogContent[MAX_ERROR_LOG_COUNT];
    
    
    char global_user_ip[32];
    
    int findAvailablePullStatus(PSPullStatus* pullstatus, int* found);
    void clearPullRecord(int no);
    
private:
    PSGlobalStatus();
    PSGlobalStatus(PSGlobalStatus const &);
    PSGlobalStatus & operator=(PSGlobalStatus const &);
    ~PSGlobalStatus();
    
    int sleepInterval; //ms
    int m_iStopFlag;  // 0-do nothing, 1-stop running
    void *m_uploadThread;
    
    int getPzlogAddr(void* pzbcPtr, int ndselect, char* getAddr, int* getPort);
    int getLog(char* log);
    int upload(char* log);
    void updatePullRecord(int no, int64_t current_time);
    int Http_Connect(DWORD sockfd, struct sockaddr*dstaddr, int addrlen, int timeout_ms);
    int zlibcompress(char* ori_str, char* dst_str, unsigned long* dst_size);
    int zlibdecompress(char* ori_str, char* dst_str, unsigned long ori_size);
    void clearSavedLog();
    void clearSavedErrorLog();
    int findOldestPullStatus();
    
    void *statusPzbcPtr;
    
    static PSGlobalStatus *m_pInstance;
};

class BASE_API PSPullStatus {
    
public:
    PSPullStatus();
    ~PSPullStatus();
    
    void clearDataInside();//do not use outside base
    void clearDataOutside();//reset all data within the class
    
    int64_t initialtime;
    
    void *psdemux;
    int stream_id;
    
//    char pull_url[2048];        //split
    
    char pull_cdn_ip[64];   //server ip
    int pull_protocol;  //pdp and so on
    int pull_status;    //1 for pulling, 0 for finished pulling
    int pull_cbuffer;   //ms
    int pull_freeze;        //Freeze_Count
    
    
    
    long long   pull_start_time;  //Begin_Time
    char        User_IP[16];        //pzb return
    uint32_t    ResponseCode;
    uint32_t    Flux;   //bytes
//    uint32_t    Duration;   //ms
    int64_t     duration_starttime;
    int64_t     freeze_starttime;   //-1 for not freezing
    uint32_t    Freeze;
    char        Domain[256];
    uint32_t    Port;
    char        URI[2048];
    char        UserAgent[32];
    
    long long   bitrate_starttime;
    int         current_bitrate;    //if current_bitrate==-1, no bitrate
    uint32_t    bitrate[MAX_PS_PULL_BITRATE_COUNT];
    char        bitrate_name[MAX_PS_PULL_BITRATE_COUNT][32];
    
    int32_t     cpu_usage;  //n%
    int64_t     mem_used;  //byte
    int64_t     mem_total;  //byte
    
    int32_t     first_time;
    int32_t     audio_cache;
    int32_t     video_cache;
    
    char        reserved[10240];
};

class BASE_API PSPushStatus {
    
public:
    PSPushStatus();
    ~PSPushStatus();
    
    char push_url[2048];
    char push_cdn_ip[64];
    
    int push_protocol;
    int push_status;
    int push_cbuffer;
    int push_freeze;
    
    long long push_start_time;
    
};

BASE_API int updatepullstatus(PSPullStatus* pullstatus);
BASE_API int updateflush(int force);//force==1 will force upload log to server

#endif
