
#ifndef PZVT_CLIENT_H
#define PZVT_CLIENT_H

/**
 @name pzvtinit
 */
/**
 @brief pzvt initialazation.
 @param server : the address of the pzs server.
 @param port : the port number of the pzvt module in pzs.
 @param changeflag: if changeflag==0, reference count++; else if changeflag==1, reference count--. When reference count is 0, the server and port will be changed to the given server ip and port.
 @return a reference pointer to this session of pzvt.
 */
BASE_API int pzvtInit(const char* server, const char* port, int changeflag);

/**
 @name getPzvtData
 */
/**
 @brief to achieve the virtual time data. To get the time offset between client and pzb, you should calculate it by firstStageOffsetData + remoteOffsetData. The unit is second.
 @param p : the reference pointer got returned from pzvtinit.
        firstStageOffsetData : the time offset between client and pzs.
        remoteOffsetData : the time offset between pzs and pzb.
        firstStageDelayData: the total transport delay between client and pzs.
 */
BASE_API int getPzvtData(double *firstStageOffsetData, double *remoteOffsetData, double *firstStageDelayData);


/**
 @name togglePzvtFrequency
 */
/**
 @brief change the pzvt request frequency.
 @param p : the reference pointer got returned from pzvtinit.
 frequencyChoice : 0 for pzvt frequency when pushing and receiving; 1 for pzvt frequency when no pushing or receiving; 2 for pzvt frequency when hibernating.
 */
BASE_API void togglePzvtFrequency(int frequencyChoice);

BASE_API void hibernatePzvt();

BASE_API void stopPzvt();

//0 for success, other for fail
BASE_API int resumePzvt();

BASE_API int getPzvtAddr(int ndselect, char* getAddr, int* getPort);

BASE_API int pzvtGlobalInit(int ndselect);

#define PZVTAVAILABLE   1
#define PZVTUNAVAILABLE 0
typedef void (*refreshPzvtCallback)(int ifPzvtAvailable, void* refcon);


#define PzvtRefreshFail         -1
#define PzvtRefreshProcessing   1
#define PzvtRefreshNoNeed       2

/*
 Discussion:
 callback should block for too long, because that will block pzvt inner thread.
 
 return value:
 
 PzvtRefreshFail: pzvt error or pzvt not inited yet, no pzvt data available.
 PzvtRefreshProcessing: pzvt is being updated, when finish, callback will be called in a different thread.
 PzvtRefreshNoNeed: pzvt update so frequently that no update is needed. callback will be called in current thread before function returns.
 
 */

BASE_API int refreshPzvt(int force, refreshPzvtCallback callback, void* refcon);

#endif
