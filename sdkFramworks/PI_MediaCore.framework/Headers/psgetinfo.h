
#ifndef PS_GETINFO_H
#define PS_GETINFO_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#define SUBSTREAM_MAX       16
#define SUBSTREAM_URL_SIZE  1024

#define PS_MSC_SET_CHANNEL_VISIBLE  101
#define PS_MSC_GET_WT_AUTH          102

#define PS_PIS_NODE_DEFAULT     3
#define PS_PIS_NODE_JP          5
#define PS_PIS_NODE_SG          6
#define PS_PIS_NODE_IN          20

struct PI_progam_info
{
    DWORD   port;
    char    domain[128];
    char    group_id[128];
    char    stream_id[128];
};

struct PI_MSC_CMD
{
    char    cid[32];
    char    cver[32];
    char    token[32];
    char    info[2048];
    int     op;
    int     pis_node;
};

struct PI_MSC_RESPONSE
{
    int     http_code;
    int     error_code;
    char    info[4096];
};

BASE_API int PI_get_ip(const char *url);

#ifdef __cplusplus
extern "C" {
#endif
	BASE_API int PI_get_wt_auth(struct PI_MSC_CMD *info, struct PI_MSC_RESPONSE *response, int timeout_ms);
#ifdef __cplusplus
}
#endif

// Device info function
#define PI_DEVICE_INFO_MAX  1024
#define PI_DEVICE_APP_ID_MAX 1024
#define PI_DEVICE_SDK_VERSION_MAX 1024

// Set device info
BASE_API int PI_set_device_info(const char *device_info, const char *device_app_id, const char *device_sdk_version);

BASE_API int PI_set_device_info2(const char *device_info, const char *device_app_id, const char *device_sdk_version, int os_version);

// Get device info
BASE_API int PI_get_device_info(char *device_info, int len);

// Get audio process delay
//int PI_get_audio_delay(int pis_node, int timeout_ms, int *delay);
BASE_API int PI_get_audio_delay(int pis_node, int timeout_ms, int *delay, DWORD* enable);

BASE_API int PI_get_audio_delay_with_rotation(int pis_node, int timeout_ms, int *delay, DWORD* enable, int *rotation);

BASE_API int PI_get_audio_delay2(int pis_node, int timeout_ms, int *delay, DWORD* enable, int *rotation, int *affinity_policy);

int PI_get_audio_delay_with_rotation(int pis_node, int timeout_ms, int *delay, DWORD* enable, int *rotation);

int checkSoundCardSupport(const char *m, const char *p, int pis_node, int timeout_ms);

int latencyReport(const char *device_id, const char *card_m, const char* card_p, int latency, int pis_node, int timeout_ms);

// Parse push url
BASE_API int PI_push_urlparse(const char *url, struct PI_progam_info *info);

// Push msc control
BASE_API int PI_push_msccontrol(struct PI_MSC_CMD *info, struct PI_MSC_RESPONSE *response, int timeout_ms);

// Parse url
BASE_API int PI_urlparse(const char *url, struct PI_progam_info *info);

// Get child stream info
BASE_API int PI_get_childstream_info(int ip, const char *url, int *childstream_num, char *childstream_url[SUBSTREAM_MAX]);
BASE_API int PI_get_childstream_info(int ip, const char *url, int *childstream_num, char *childstream_url[SUBSTREAM_MAX], int * ifMainStream);

// Get child stream info for new room server
BASE_API int PI_get_childstream_info2(int ip, struct PI_progam_info* pisInfo, int *childstream_num, char *childstream_url[SUBSTREAM_MAX], int * ifMainStream);
    
//#ifdef __cplusplus
//}
//#endif

#endif
