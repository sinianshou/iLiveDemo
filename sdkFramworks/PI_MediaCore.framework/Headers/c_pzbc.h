
#ifndef C_PZBC_HPP
#define C_PZBC_HPP

typedef struct PI_NSTestResult {
    sockaddr    targetAddr;
    double      lossRate;
    double      rttMin;
    double      rttMax;
    double      rttAvg;
    double      rttStd;
    char        reserved[32];
} PI_NSTestResult;

BASE_API void* C_PZBC_Init(void* pNDSelector);

BASE_API DWORD C_PZBC_Get(void* pzbcptr, char *domain, DWORD port, char *uri, DWORD mode, DWORD owner, char *get_addr, DWORD* get_port, DWORD* get_protocol, char *desired_domain, char *actual_domain, DWORD *stopflag, DWORD *rpi);

BASE_API DWORD C_PZBC_Preload(void* pzbcptr, char *domain, DWORD port, char *uri, DWORD mode, DWORD owner, DWORD *network_type);

BASE_API DWORD C_PZBC_AddInfoToPZB(void* pzbcptr, char* content, char* domain, char* uri, DWORD port, DWORD mode, DWORD owner);

BASE_API DWORD C_Get_Info_From_PZB_With_Stopflag(void* pzbcptr, DWORD owner, char* pURI, char* User_Agent, DWORD* pContent_Length,char* pContent, DWORD Time_Out, DWORD *stopflag);

//Room_Server_Post should be deprecated.
BASE_API DWORD Room_Server_Post(DWORD ndselect, const char* url, const char* requestBody, char* returnedContent, DWORD* contentLength, DWORD Timeout_ms);

BASE_API DWORD Room_Server_Post2(DWORD ndselect, const char* url, const char* requestBody, char** returnedContent, DWORD* contentLength, DWORD Timeout_ms);

BASE_API DWORD Room_Server_Post_With_Header(DWORD ndselect, const char* url, const char* requestBody, const char* requestUserHeader, char** returnedContent, DWORD* contentLength, DWORD Timeout_ms);

//DeleteReturnedContent should be used once the result returnedContent is used.
BASE_API void DeleteReturnedContent(char* returnedContent);

BASE_API DWORD AddRSDomain(int ndselect);

BASE_API DWORD BaseGlobalInit(int ndselect, int rsPort=80, int pisPort=81);

BASE_API void BaseSetDomain(char* domain);

BASE_API void C_psSetForegroundStatus(int status);

BASE_API int C_psGetForegroundStatus();

// 0 for available, others for not available
// source: 0 for roomserver return, 1 for long connection
#define PZBDataSourceRoomserver 0
#define PZBDataSourceLongConnection 1
BASE_API int checkPZBDataAvailability(const char* pzbdata, int source);

BASE_API void forceNetworkIpv6(int enableForceIpv6);

BASE_API void PI_StartNSTest();

BASE_API void PI_StopNSTest();

BASE_API int PI_GetNSTestResult(void *result);

BASE_API void PI_GetSDKVersion(char *version);

#endif
