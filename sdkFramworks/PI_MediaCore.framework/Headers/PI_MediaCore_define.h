
#ifndef PIMEDIACORE_VERSION

#define PIMEDIACORE_VERSION "1.9.2.0-20190925R02-dev"


#ifdef NT_VERSION
#if defined(SELF_MEDIACORE_DLL)
#define MEDIACORE_API __declspec(dllexport)
#else
#define MEDIACORE_API __declspec(dllimport)
#endif
#else
#define MEDIACORE_API
#endif

#define PSL_CHANNEL_MAX     8

union ptcp_sockstore {
    struct sockaddr_in sin;
    struct sockaddr_in6 sin6;
    struct sockaddr sa;
};

extern "C" void ptcp_print_address_string(struct sockaddr *sa,char *string);

struct PTCP_SockStat
{
    uint32_t NetNum;
    uint64_t RTTArr[8];
    uint32_t CWndArr[8];
    uint32_t OnFlightArr[8];
    uint64_t RetransPacket, TotalSent, TotalRecv, TotalAcked;
    uint32_t TotalSentPackets, TotalRecvPackets, TotalAckedPackets;
    uint16_t Throughput;
    int32_t  FWD_Serial_MaxDelay;
    uint32_t reserved[125];
};

struct PUSHDATA_STAT
{
    int64_t     m_delay_audio_avg;  //input audio avg delay
    int64_t     m_delay_video_avg;  //input video avg delay
    
    int64_t     QAdelay, QVdelay;   //A/V delay of queue before packer
    int64_t     memcache_buf, memcache_delay;   // after packer, before send:  buf_size and delay
    
    int64_t     unsent_delay,sent_delay;        //socket
    int64_t     sockbuf;                        //socket buf
    
    int32_t     reserved[128];
    
};

#define RC_POLICY_WORST             1       // satisfy worst person
#define RC_POLICY_AVERAGE           2       // satisfy avg persons
#define RC_POLICY_SECOND_TO_WORST   3       // satisfy the second_to_worst person


typedef struct _POST_URL_PARAM
{
    int         txmd;
    int         limit;
    int         delay;
    int         linkmd;
    int         quality;
    int         rc;
    int         dropmd;
    uint64_t    droptime;
    int         peeraddrnum;
    char        peeraddr[2048];
    int         ndselect;
    int         pdp_mode;
    int         eth_mode;
    uint32_t    sid;
    
    int         ld_target;
    int         ld_min;
    int         ld_max;
    int         ld_jump;
    int         ld_fix;
    int         ld_dm;
    int         ld_fg;
    int         ld_st;
    
    int         changeres;          //0 -- disable      1 -- auto change res
    int         cellusage;          //percent
    
    int         usmd;
    int         rc_policy;
    int         arrc_flag;
    
    int         lowpower_mode;
    int16_t     us_selfctrl;    //  0 -- enable A50, not self ctrl nstest, not change bitrate when switching among Ax and normal.
                                //  1 -- enable A50, self ctrl nstest, change bitrate when switching among Ax and normal.
    
    int16_t     us_submode;
    
    int16_t     txmd_adaptive;
    
    int16_t     fec_type;
    int16_t     fec_k;
    int16_t     fec_m;
    
    int         reserved[252];
    
} POST_URL_PARAM;

typedef struct _PSL_CHANNEL {

    int             stat_interval;
    char            reserved_str[512];
    char            extrainfo[128];
    char            pzb_fwddata[1024];
    
    class psl_adjust      *adjust;
    pthread_mutex_t       pzb_lock;
    DWORD           dwpzb_Port;
    DWORD           dwpzb_IP;
    in6_addr        addrpzb_IPV6;
    bool            bIPV6UsableFlag;
    
    int             pzb_ndmode;
    int             pzb_ownermode;
    char            streamdomain[1024];
    DWORD           stream_port;
    char            stream_uri[1024];
    char            pzb_domainfrom[1024];
    char            pzb_domain[256];
    char            pzb_domain_actual[256];
    unsigned char   url_md5[64];
    int             pzb_innermode;
    
    DWORD           bRTMP_output;
    
    int             enable_video_push;
    int             pzs_support_relay;
    char            pzs_pstoken[64];
        
    POST_URL_PARAM  urlparam;
    
    int16_t         camera_facing;
    int16_t         reserved_short;
    int             reserved[255];
    void            *reserved_ptr[32];
} PSL_CHANNEL;

#define PIMC_CAMERA_FACING_UNKNOWN      0
#define PIMC_CAMERA_FACING_FRONT        1
#define PIMC_CAMERA_FACING_BACK         2

struct PushConfigInternal_AudioEncParam {
    int32_t a_datasource;
    int32_t a_format;
    int32_t a_sample_rate;
    int32_t a_channel_num;
    int32_t a_element_size;
    int32_t a_bitrate;
    int32_t a_samples_per_frame;
};

struct PushConfigInternal_VideoEncParam {
    int32_t v_datasource;
    int32_t v_format;
    int32_t v_width;
    int32_t v_height;
    int32_t v_ratio_width;
    int32_t v_ratio_height;
    int32_t v_bitrate;
    int32_t v_fps;
    float   v_keyinterval_sec;
    int32_t v_enc_profile;
    int32_t v_enc_bframe_flag;
    int32_t v_enc_bitrate_mode;
    int32_t v_enc_input_yuv_format;
    
    int32_t adjust_br_min_ratio;
    int32_t adjust_br_max_ratio;
    int32_t adjust_fps_min_ratio;
    int32_t adjust_quality_ratio;
};

struct PushConfigInternal_DataEncParam {
    int32_t d_datasource;
    int32_t d_format;
    int32_t d_width;
    int32_t d_height;
    int32_t d_fps;
    float   d_keyinterval_sec;
    int32_t d_adjust_fps_min_ratio;
};

struct PushConfigInternal {
    int32_t pid;
    int32_t type;
    int32_t tx_type;
    int32_t delay_ms;
    int32_t adjust_rc_mode;
    
    int32_t ae_param_num;
    PushConfigInternal_AudioEncParam ae_param[16];
    
    int32_t ve_param_num;
    PushConfigInternal_VideoEncParam ve_param[16];
    
    int32_t de_param_num;
    PushConfigInternal_DataEncParam de_param[16];
    
    char url[1024];
    char extra_info[1024];
    
    //status set by PSLPusherController
    int             enable_video_push;
    int             pause_push;
    
    int             us_lasterror;
    int             us_laststate;
    
    int32_t         us_targetdelayms;
    int32_t         us_adjust_fps_min_ratio;
    int32_t         us_fps;
    int32_t         us_v_bitrate;
};

typedef void (* PSLCONTROLLERFUNC)( int index, int cmd, int data, void*param);
typedef void (* PSLCONTROLLER_CALLPSLFUNC)( int index, int cmd, int intvalue, PushConfigInternal *configInternal);

enum CALLPSLFUNC_CMD
{
        CMD_RESET,
        CMD_ENABLEVIDEO,
        CMD_RESETTARGETDELAY,
        CMD_PAUSEPUSH,
        CMD_US_ENABLE
};

typedef struct _PSL_CONFIG {
    
    char            cpuinfo_str[512];
    double          OSVersion;
    char            devicemodel[32];
    void*           om_device;
    char            psl_version[32];
    DWORD           dwSEND_TIME_TODISCONNECT;
    DWORD           refresh_interval;
    
    class PSNDSelector    *pP31_PSNDSelector;
    PSLCONTROLLERFUNC      pControlFunc;
    PSLCONTROLLER_CALLPSLFUNC  pCallPSLFunc;
    class PSLPusherController *pPusherController;
    
    PSL_CHANNEL     pslchannel[PSL_CHANNEL_MAX];
    
    int16_t         fps_limit;//newve
    int16_t         brmode;//0-invalid
    int16_t         keyintms_limit;
    int16_t         reserve_i16;
    int             reserved_int[510];
    
    class PZBC          *pPZBC;
    void*           reserved_ptr[127];
    
} PSL_CONFIG;

#define PSL_CALLBACK_MAGICID    (-1)
#define PSL_CMD_CONNECT_SUCCEED     1
#define PSL_CMD_POSTOK              2
#define PSL_CMD_RECORD_RESET        3
#define PSL_CMD_ENCODE_KEYFRAME     4
#define PSL_CMD_CHANGE_ENCODE_PARAM    5
#define PSL_CMD_FOUND_KEYFRAME      6
#define PSL_CMD_EXT_JSON           7
#define PSL_CMD_CAP_JSON            8
#define PSL_CMD_MSC_STATUS          9
#define PSL_CMD_CONNECT_START       10
#define PSL_CMD_USER_MESSAGE        11
#define PSL_CMD_CORE_STATUS         12

#define PI_CORESTATUS_NETRESULT     1

#define US_CAP_DISABLE  100
#define US_CAP_UNKNOWN  200
#define US_CAP_A1       300
#define US_CAP_A2       400
#define US_CAP_A3       500
#define US_CAP_A4       600
#define US_CAP_A5       700

typedef struct _PSL_STREAMING_CALLBACK_PARAM {
    int _int;
    char _str[512];
} PSL_STREAMING_CALLBACK_PARAM;

#define DEVICE_NET_TYPE_MOBILE     0
#define DEVICE_NET_TYPE_WIFI       1
#define DEVICE_NET_TYPE_WIMAX      6
#define DEVICE_NET_TYPE_ETHERNET   9
#define DEVICE_NET_TYPE_UNKNOWN    -2

extern MEDIACORE_API PSL_CONFIG * g_PSLConfig;

//ctltype
#define CP_CTLTYPE_CHANGESTATE  1   //value = CP_STATE_XXX

//value
#define CP_STATE_STOP       0
#define CP_STATE_START      10      //param=desc_str
#define CP_STATE_OPERATING  20
#define CP_STATE_RUN        100     //param=request_str when toid==local_id 
#define CP_STATE_FAIL       200
#define CP_STATE_TERMINATE  201
#define CP_STATE_TIMEOUT    202

//EventTracking
#define EVENTTRACKING_PUSH_REPEAT_DATASOURCE_FPS   1
#define EVENTTRACKING_PUSH_REPEAT_ENCODED_FPS      2
#define EVENTTRACKING_PUSH_TICK_JOINROOM           11
#define EVENTTRACKING_PUSH_TICK_FIRSTVIDEO         12
#define EVENTTRACKING_PUSH_TICK_FIRSTAUDIO         13
#define EVENTTRACKING_PUSH_PING_FROM_APP_TO_AGENT  20
#define EVENTTRACKING_PUSH_PATH_STAT               21
#define EVENTTRACKING_PUSH_PUSHING_STAT            22


//callmode
#define CP_CALLMODE_PSP      1
#define CP_CALLMODE_PDP_D    2
#define CP_CALLMODE_PDP_RB   3  //new mode

typedef int (*STATECBFUNC)(void*pvoid, int conn_index, int64_t fromid, int64_t toid, int sessionid, int conn_sequence, int ctltype, int value, void*param);

extern "C" {
    
MEDIACORE_API int PIMC_GlobalInit(unsigned short tcp_svrport, unsigned short ptcp_svrport, unsigned short ptcp_svrphyport,char* logpath);
MEDIACORE_API int PIMC_GetLocalAddr(char *netdevice, int family, char *addrstring);
MEDIACORE_API int PIMC_GetPublicAddr(char *netdevice, int family, char *addrstring);
MEDIACORE_API int PIMC_GetLocalAddr_By_Type(int devicetype, int family, char *addrstring);
MEDIACORE_API int PIMC_GetPublicAddr_By_Type(int devicetype, int family, char *addrstring);
    
MEDIACORE_API int PIMC_GetLocalPhyPort(unsigned short *phyport);


MEDIACORE_API int PIMC_GetNetworkDeviceStatus(uint32_t device_type, int32_t *device_on,
                                              char *local_addr, char *public_addr);

/*
 0  --   device is on, and local ip and public ip is available.
 -1 --   device is off.
 -2 --   device is on, but local ip is unavailable.
 -3 --   device is on, but public ip is unavailable.
 */
MEDIACORE_API int PIMC_GetNetworkDeviceAvailable(int device_type);

MEDIACORE_API int PIMC_StartProxy();
MEDIACORE_API int PIMC_StopProxy();

/* 0 -- stopped
   1 -- running
   2 -- running but not start proxy properly, will retry until status is running.
 */
MEDIACORE_API int PIMC_GetProxyRunning();

MEDIACORE_API int PIMC_set_mpath_agent_addr(struct sockaddr *addr);
MEDIACORE_API int PIMC_get_mpath_agent_serviced_clientip(int Max_ClientNum, int *pClientNum, char *pClientIP);
MEDIACORE_API int PIMC_get_mpath_agent_traffic(int64_t *pTrafficSend, int64_t *pTrafficRecv);

MEDIACORE_API int PIMC_SetAndroidFeature(unsigned char *buf, unsigned int bufsize);
MEDIACORE_API int PIMC_limit_refreshinterval();
MEDIACORE_API int PIMC_IODuration(int state, double *duration);
MEDIACORE_API int PIMC_parse_pushurl_param(char *url, POST_URL_PARAM *param);
MEDIACORE_API int PIMC_update_pushurl_param(char *url, int recover, POST_URL_PARAM *param);

MEDIACORE_API int PIMC_SetAndroidA50PushEnable(int enable);
//set localid
MEDIACORE_API int PIMC_SetConnID(int64_t localid);
//set callmode
MEDIACORE_API int PIMC_SetCallMode(int callmode);
//set supernode ip_str & port (for CP_CALLMODE_PDP_RB)
MEDIACORE_API int PIMC_SetConnNode(char*nodeaddr, int port);
//set callback function
MEDIACORE_API void* PIMC_SetConnCallback(void*pvoid, STATECBFUNC fnCallback);
//create push connection (non-block)
//connid - receiver_id, sid - session_id, desc - desc_str to receiver, urlparam - string for parse params
//return conn_index, <0 for fail; push_url append "&conn_index=%d" when success
MEDIACORE_API int PIMC_CreatePushConn(int64_t connid, char*desc, char*urlparam);
//not ready
MEDIACORE_API int PIMC_CloseConn(int64_t id_a, int64_t id_b, int sessionid, int dir);

MEDIACORE_API void PIMC_Print_Address_String(struct sockaddr *sa,char *string);
MEDIACORE_API int PIMC_AppKeyEncode(char*jsonstr, char*appkeystr, int size);
MEDIACORE_API int PIMC_AppKeyDecode(char*appkey, char*jsonstr, int size);
    
MEDIACORE_API void* PIMC_GetPushCtrlPtr();

MEDIACORE_API int PIMC_Set_MPC_Callback(void *MPCHandle, void *fnMPCSendCallback, void *fnMPCRecvCallback);

MEDIACORE_API int PIMC_GetVersion(char*versionstr, int size);
    
}

#endif


