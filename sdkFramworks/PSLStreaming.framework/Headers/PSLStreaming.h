#ifndef __PSLSTREAMING_HEADER_INCLUDED__
#define __PSLSTREAMING_HEADER_INCLUDED__

#define PSLSTREAMING_VERSION    "1.9.2.0-20190919R01-dev"

/**
 *  PSLStreaming lib interface return value define and status define
 **/
#define PSLRET_SUCCESS                      0

#define PSLRET_ERR_START_FAILED             -1
#define PSLRET_ERR_NO_MEDIA_ACTIVE          -2
#define PSLRET_ERR_GET_PUSHMODE_FAILED      -3
#define PSLRET_ERR_NULL_POINT               -4
#define PSLRET_ERR_NOT_INIT                 -5
#define PSLRET_ERR_INIT_PACKER_FAILED       -6
#define PSLRET_ERR_DEPRECATED_API           -201
#define PSLRET_ERR_PSLSTREAMING_NOT_INIT    -100

#define PSLRET_ERR_PARAMS                   -10
#define PSLRET_ERR_PACKER_PARAMS            -11
#define PSLRET_ERR_AUDIO_PARAMS             -12
#define PSLRET_ERR_VIDEO_PARAMS             -13

#define PSLRET_ERR_MODE_NOT_EXIST           -30
#define PSLRET_ERR_TYPE_NOT_EXIST           -31
#define PSLRET_ERR_TRACK_NOT_EXIST          -32

#define PSLRET_ERR_NOT_RECORDING            -40
#define PSLRET_ERR_RECORDFAIL               -41
#define PSLRET_ERR_RECFILE_FAIL             -42

#define PSLSTATUS_NETWORK_FAILED            21
#define PSLSTATUS_DELAY_TOO_LARGE           22
#define PSLSTATUS_NO_VIDEO_DATA             23
#define PSLSTATUS_NO_AUDIO_DATA             24
#define PSLSTATUS_NO_AV_DATA                25
#define PSLSTATUS_PERFORMANCE_NOT_ENOUGH    26

#define PSLTYPE_VIDEO_CAPTURE_QUEUE         31
#define PSLTYPE_VIDEO_ENCODE_QUEUE          32
#define PSLTYPE_AUDIO_CAPTURE_QUEUE         33
#define PSLTYPE_AUDIO_ENCODE_QUEUE          34

#define PSL_STOPREASON_EOS                  1
#define PSL_STOPREASON_SYSTEMINTERRUPT      0


typedef int (* CONTROLPROC)( void* pVOID, int index, int ctltype, void* INTERFACE_PARAM, void* orig_INTERFACE_PARAM);
typedef int (* HANDLERFN)( int handler, int cmd, int data, void*param);

class PSLSTREAMING_API PSLStreaming {
    
public:
	int     m_index;
    int     m_runningstat;
    bool    m_running_cpucheck;
    bool    m_running_check;
	void	*m_pTcsConfig;
	void	*m_pStreamInfo;
	void	*m_pINTERFACE_PARAM;
    void    *m_pINTERFACE_PARAM_Alloc;
	void    * m_pencoder;
	CONTROLPROC	m_pfnControl;
    
    int64_t m_lastdatatime;
    int64_t m_lastvideostamp;
    int64_t m_lastdatastamp;
    int64_t m_lastaudiostamp[16];
    
    int     m_largedelaywarning_count;
    int     m_packernull_count;
    
    int    m_ipvxflag;
    uint32_t     m_pzbcstop;

public:
	PSLStreaming();
	~PSLStreaming();

    static void PreLoadUrl(char *url);
    
    /**
     * called this function when network changed, such as, network changed from wifi to 4G and vice versa, and from wifi to another wifi.
     
     * param reconnect
     *       notify pslstreaming to :  1  reconnect immediately. 0 no network, stop push streaming.
     */
    static void OnNetworkChanged(int reconnect);
    
    /**
     * called when stream is mute or unmute.
     */
    int OnStreamingMute(int bMute);
    
    /**
     *  init PSLStreaming
     *  @param index
     *      set 0 if you only used one PSLStreaming point, or if you have a PSLStreaming point array, set array num
     *  @param inf_param
     *      set the point of struct INTERFACE_PARAMS, before this, init INTERFACE_PARAMS with your param
     *  @param logdir
     *      not used now
     *  @param lognum
     *      not used now
     *  @param extrainfo
     *      TODO
     *  @return
     *      PSLRET_SUCCESS for success
     *      PSLRET_ERR_PACKER_PARAMS for PSLStreaming struct params error
     *      PSLRET_ERR_AUDIO_PARAMS for audio params error
     *      PSLRET_ERR_VIDEO_PARAMS for video params error
     *      PSLRET_ERR_NO_MEDIA_ACTIVE  for no media need to push
     *      PSLRET_ERR_GET_PUSHMODE_FAILED for get push mode failed
     *      PSLRET_ERR_NULL_POINT for inf_param is NULL
     *      PSLRET_ERR_INIT_PACKER_FAILED for init output failed
     **/
	int Init(int index, void*inf_param, void*logdir, void*lognum, void *extrainfo);

    int ResetConfig(int index, void *inf_param,  void *extrainfo);
    /**
     *  start PSLStreaming
     *  @return
     *      PSLRET_SUCCESS for success
     *      PSLRET_ERR_START_FAILED for start failed, mostly it's caused by init function failed
     **/
	int Start();
    
    /**
     *  stop PSLStreaming
     *  @param
     *      reason:     PSL_STOPREASON_EOS: End of Streaming, means "APP workflow close it".
     *                  PSL_STOPREASON_SYSTEMINTERRUPT: interrupt by system or something
     *  @return
     *      PSLRET_SUCCESS for success
     **/
	int Stop(int reason);
    
    int PreStop();
    
    int Pause(int enable);
    
    int NetworkReconnect(int status);
    
    int CheckPushParam(void *param);
    
    int EnableVideoPush(int enable);
    
    int US_Enable(int state);
    
    int US_SelfCtrl(int enable);
    
    int EnableAVDeltaCorrection(int enable);
    
    int RecoveryUSState();
    /**
     *  app switch to background
     **/
    //void    PLtoBackground();
    
    /**
     *  app switch to foreground
     **/
    //void    PLtoForeground();
    
    /**
     *  only used in IOS_VERSION
     *  @param encoder
     *      if used videotoolbox for encoder, transfer VTCompressionSessionRef* to PSLStreaming,
     *      if not, transfer null
     **/
#ifndef NT_VERSION
    __attribute__((deprecated))
#endif
    int SetEncoderPoint(int index, void* encoder);
    
    int SetEncoderPoint2(void* encoder, int new_bitrate);
    
    /**
     *
     * call getEncodeProperty before encode frame. get the property struct for encode.
     * for IOS version, property is CFDictionaryRef
     *
     **/
#ifndef NT_VERSION
    __attribute__((deprecated))
#endif
    int getEncodeProperty(void **property);
    
    /**
     *  set callback function
     *  @return
     *      PSLRET_SUCCESS for success
     *      PSLRET_ERR_PARAMS for tcs is not NULL, this Err used by iOS
     **/
	int SetControlFunc(void*tcs, CONTROLPROC pFUNC);
    
    /**
     *  Insert audio/video data to push
     *  @param buf
     *      audio/video data point
     *  @param SAMPLE
     *      BUFFER_INFO struct point, info for audio/video data
     *  @param extime
     *      _EXTTIME_INFO struct, info for timestamp and pzvt
     *
     *  @return
     *      PSLRET_SUCCESS for success
     *      PSLRET_ERR_PARAMS for params error
     *      PSLRET_ERR_NULL_POINT for some point is NULL
     *      PSLRET_ERR_START_FAILED for PSLStreaming not started
     *      PSLSTATUS_NO_AUDIO_DATA for no audio data
     *      PSLSTATUS_NO_VIDEO_DATA for no video data
     *      PSLSTATUS_DELAY_TOO_LARGE for delay is large than set
     *      PSLSTATUS_NETWORK_FAILED for push failed
     **/
	int InsertSample(unsigned char*buf, void*SAMPLE, struct ExtendTime exttime);
    
    
    //  push_config is not NULL when meta changed at
    //      video codec changed
    //      audio codec changed
    //  exactly at inserting sample of new codec encoded frame.
    //  otherwise push_config is NULL, same as InsertSample
    int InsertSample_with_metachanged(unsigned char*buf, void*SAMPLE, struct ExtendTime exttime, void*push_config);
    
    //main check
    void RunCheck();
    
    /**
     *  @return
     *      PSLRET_SUCCESS for normal
     *      PSLSTATUS_NO_AV_DATA     for input haven't audio and video data
     **/
    int     getdatastatus();
    
    /**
     * get the current delay,  unit: ms
     * @return
     *      PSLRET_SUCCESS for ok
     **/
    int     get_status_delay(unsigned int *delay);
    
    /**
     * get the current data bitrate,  unit: kbps
     * @return
     *      PSLRET_SUCCESS for ok
     **/
    int     get_status_data_br(unsigned int *databr);
    
    /**
     * get the current network bitrate,  unit: kbps
     * @return
     *      PSLRET_SUCCESS for ok
     **/
    int     get_status_network_br(unsigned int *networkbr);
    
    /**
     * get the current network total sent data,  unit: bytes
     * @return
     *      PSLRET_SUCCESS for ok
     **/
    int     get_status_total_sent(uint64_t *totalsize);
    
    /**
     * get the current network packet loss rate,  stat per 2 seconds.
     * @return
     *      PSLRET_SUCCESS for ok
     **/
    int     get_status_PLR(double *PLR_packets);
    
    /**
     * get the current network usage for every path,  unit: bytes
     * @return
     *      PSLRET_SUCCESS for ok
     **/
    int     get_status_mpath_usage(uint64_t *totalsize, unsigned int *mpathn, uint64_t *mpath_usage, char *mpath_name);
    /**
     * get the current server node ip that stream pushing to
     * @param size should not less than 128
     * @return
            PSLRET_SUCCESS for ok
            other for error
     */
    int     get_node_ip(char *nodeip, int size);
    
    int     get_status_fps_target_and_real(int *target_fps, int *real_fps);
    
    int     get_us_state(int *state);
    /**
     * set IntraRefresh to let encoder output key frame
     * @return
     PSLRET_SUCCESS for ok
     other for error
     */
    int     setIntraRefresh(bool flag);
	
	/**
     * set capture queue max and encoder queue max to pslstreaming
     * @param type 
                PSLTYPE_AUDIO_CAPTURE_QUEUE for audio capture
                PSLTYPE_AUDIO_ENCODE_QUEUE for audio encoder
                PSLTYPE_VIDEO_CAPTURE_QUEUE for video capture
                PSLTYPE_VIDEO_ENCODE_QUEUE for video encoder
     * @param queuelength the num of frame in queue
     **/
#ifndef NT_VERSION
    __attribute__((deprecated))
#endif
    void     setQueueLength(int type, int queuelength);
    
    /**
     *   set MSC server to start or stop stitching the substream into mosaic stream.
     *   @input
     *      userno                 assist broadcaster index
     *      userserial  			assist broadcaster serialno
     *      flag					0: invisible  1: visible
     *
     *   @remark
     *          assist broadcaster push stream url:
     *              http://......./publish/trans/{group-id}/mlinks{$userno$}_{$userserial$}/{stream-id}
     *   @return
     *      PSLRET_SUCCESS      success
     *      others				failed
     */
#ifndef NT_VERSION
    __attribute__((deprecated))
#endif
    int ControlUserVisible(unsigned int userno, unsigned int userserial, unsigned int flag);
    
    int SetHandlerFunc(HANDLERFN func);
    int     m_changebr_bps;
    
    int SetTargetDelay(int delay);
    int SetCameraFacing(int facing);
    
    int PostEventIA(int eventid, char *eventbody, int eventsize, int64_t stamp);
    
    int NSTestRule(char *str);
    int NTGetCapability(char *str);
    int InsertEventTrackingData(int type, int64_t data);
    int SetMasterSlave(int state);
    int GetSampleInfoStats(int type, unsigned int*seq, int*calcount, int64_t*avg, int64_t*maxv, int64_t*minv);
    int UpdateStreamParam(int recover, char*paramstr);
    
private:
    int InitOutput();
    int StartOutput();
    int StopAndReleaseOutput();
    
    int updateStreamConfig(void *_params, void *_pcfg,
                           int video, int audio, int data, int *hasvideo, int *hasaudio);
    
    int stat_fps(int64_t videostamp);
    int log_insertsample(int64_t data_delay, int64_t nowtick, void*SAMPLE, ExtendTime *exttime);
    
    int     m_pid;
    void    *hThread;
    
    pthread_mutex_t m_packermutex;
    
    void    *cThread;
    void 	*m_pPacker;
    void    *m_adjust;
    
    int     m_adatacount;
    int     m_vdatacount;
    int     m_current_pushmode;
    bool    m_bwaitI;
    int     m_avdelta_correction;
    
    int         m_usState;
    int64_t     m_fcount;
    int         m_fps_stat;						//add
    int         m_fps_count;					//add
    uint64_t    m_fps_stattick;					//add
    //bool    m_brestartPackerFlag;
    int         m_check_framesize;
    int         m_cons_largeframe;
    void        *m_msg_cache[10];
    
    int         m_reserved[512];
    void        *m_reserved_ptr[128];
    
public:											//add
    int         m_fps_real;						//add
    
    int             Init2(int index, void*push_config);
    static void     PushConfigToInterfaceParams(void*pcfg, void*ip);
    static void     PushConfigInternalToInterfaceParams(void *pcfg, void *ip);
    
    int         m_reserved_pub[256];
    void        *m_reserved_pubptr[64];
    
};

class PSLSTREAMING_API PSLRecorder {
public:
    PSLRecorder();
    ~PSLRecorder();
    
    int InsertSample(unsigned char*buf, void*SAMPLE, ExtendTime extinfo);
    int StartWriteFile(char*filename, int reset_size, void*inf_param);
    int StopWriteFile();
    
    int     m_runningstat;
    void    *m_pFilePacker;
    void    *m_pFileConfig;
    pthread_mutex_t m_packermutex;
};


extern "C"{
/**
 *  preload url, for start streaming faster.
 */
PSLSTREAMING_API void    PLGlobalInit(unsigned short tcp_svrport=8000, unsigned short ptcp_svrport=7788, unsigned short ptcp_svrphyport=12345,
                     char* logpath=NULL, char*devstr=NULL, char*appidstr=NULL, char*sdkstr=NULL, int updateinfo=0);
PSLSTREAMING_API void    PLSetAndroidFeature(unsigned char *buf, unsigned int bufsize);
PSLSTREAMING_API void    PLSetDevicePoint(void* Device);
PSLSTREAMING_API void    PLSetLogOnoff(int onoff);

PSLSTREAMING_API int     PLGetDeviceLatency();
PSLSTREAMING_API int     PLGetDeviceEnable();
PSLSTREAMING_API void    PLSetNDSelect(int ndselect);
PSLSTREAMING_API void    PLPZBCInfo(char*url, char*content);
    

/**
 *  used berore create PSLStreaming, preload push url
 **/
void     PSLStreamingPreLoad(char* url);

/**
 *  create PSLStreaming
 *  @return
 *      PSLStreaming Point
 **/
void*    PSLStreamingCreate();

/**
 *  init PSLStreaming
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @param index
 *      set 0 if you only used one PSLStreaming point, or if you have a PSLStreaming point array, set array num
 *  @param inf_param
 *      set the point of struct INTERFACE_PARAMS, before this, init INTERFACE_PARAMS with your param
 *  @param logdir
 *      not used now
 *  @param lognum
 *      not used now
 *  @param extrainfo
 *      TODO
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for success
 *      PSLRET_ERR_PACKER_PARAMS for PSLStreaming struct params error
 *      PSLRET_ERR_AUDIO_PARAMS for audio params error
 *      PSLRET_ERR_VIDEO_PARAMS for video params error
 *      PSLRET_ERR_NO_MEDIA_ACTIVE  for no media need to push
 *      PSLRET_ERR_GET_PUSHMODE_FAILED for get push mode failed
 *      PSLRET_ERR_NULL_POINT for inf_param is NULL
 *      PSLRET_ERR_INIT_PACKER_FAILED for init output failed
 **/
int      PSLStreamingInit(void* pPSLStreaming, int index, void*inf_param, void*logdir, void*lognum, void *extrainfo);

/**
 *  start PSLStreaming
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for success
 *      PSLRET_ERR_START_FAILED for start failed, mostly it's caused by init function failed
 **/
int      PSLStreamingStart(void* pPSLStreaming);

/**
 *  stop PSLStreaming
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @param
 *      reason:     PSL_STOPREASON_EOS: End of Streaming, means "APP workflow close it".
 *                  PSL_STOPREASON_SYSTEMINTERRUPT: interrupt by system or something
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for success
 **/
int      PSLStreamingStop(void* pPSLStreaming, int reason);

/**
 *  app switch to background
 **/
void    PSLStreamingtoBackground(void* pPSLStreaming);

/**
 *  app switch to foreground
 *  called PSLStreamingInit before this
 **/
void    PSLStreamingtoForeground(void* pPSLStreaming);

/**
 *  app recovery US state
 *      when switch AEC mode, restart Audio capture , etc...
 **/
int    PSLStreamingRecoveryUSState(void* pPSLStreaming);

/**
 *  only used in IOS_VERSION
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @param encoder
 *      if used videotoolbox for encoder, transfer VTCompressionSessionRef* to PSLStreaming,
 *      if not, transfer null
 **/
#ifndef NT_VERSION
__attribute__((deprecated))
#endif
int     PSLStreamingSetEncoderPoint(void* pPSLStreaming, int index, void* encoder);
    
int     PSLStreamingSetEncoderPoint2(void* pPSLStreaming, void* encoder, int new_bitrate);

/**
 * @brief call getEncodeProperty before encode frame. get the property struct for encode.
 * @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 * @param property for IOS version, property is (void**)(&CFDictionaryRef)
 * @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_ERR_NOT_INIT for packer is not created
        PSLRET_SUCCESS for success
 **/
#ifndef NT_VERSION
__attribute__((deprecated))
#endif
int      PSLStreamingGetEncodeProperty(void* pPSLStreaming, void **property);

/**
 *  set callback function
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for success
 *      PSLRET_ERR_PARAMS for tcs is not NULL, this Err used by iOS
 **/
int     PSLStreamingSetControlFunc(void* pPSLStreaming, void*tcs, CONTROLPROC pFUNC);

/**
 *  set camera facing
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for success
 **/
int     PSLStreamingSetCameraFacing(void* pPSLStreaming, int facing);

    
/**
 *  Insert audio/video data to push
 *  @param pPSLStreaming PSLStreaming Point get from PSLStreamingCreate
 *  @param buf
 *      audio/video data point
 *  @param SAMPLE
 *      BUFFER_INFO struct point, info for audio/video data
 *
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for success
 *      PSLRET_ERR_PARAMS for params error
 *      PSLRET_ERR_NULL_POINT for some point is NULL
 *      PSLRET_ERR_START_FAILED for PSLStreaming not started
 *      PSLSTATUS_NO_AUDIO_DATA for no audio data
 *      PSLSTATUS_NO_VIDEO_DATA for no video data
 *      PSLSTATUS_DELAY_TOO_LARGE for delay is large than set
 *      PSLSTATUS_NETWORK_FAILED for push failed
 **/
int     PSLStreamingInsertSample(void* pPSLStreaming, unsigned char*buf, void*SAMPLE, ExtendTime exttime);

/**
 *  @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for normal
 *      PSLSTATUS_NO_AV_DATA     for input haven't audio and video data
 **/
int     PSLStreamingGetdatastatus(void* pPSLStreaming);

/**
 * get the current delay,  unit: ms
 * @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for ok
 **/
int     PSLStreamingGet_status_delay(void* pPSLStreaming, unsigned int *delay);

/**
 * get the current data bitrate,  unit: kbps
 * @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for ok
 **/
int     PSLStreamingGet_status_data_br(void* pPSLStreaming, unsigned int *databr);

/**
 * get the current network bitrate,  unit: kbps
 * @return
 *      PSLRET_ERR_PSLSTREAMING_NOT_INIT for PSLStreaming not created
 *      PSLRET_SUCCESS for ok
 **/
int     PSLStreamingGet_status_network_br(void* pPSLStreaming, unsigned int *networkbr);

/**
 *   set MSC server to start or stop stitching the substream into mosaic stream.
 *   @input
 *      pPSLStreaming		PSLStreaming object pointer, returned by PSLStreamingCreate
 *      userno                 assist broadcaster index
 *      userserial  			assist broadcaster serialno
 *      flag					0: invisible  1: visible
 *
 *   @remark
 *          assist broadcaster push stream url:
 *              http://......./publish/trans/{group-id}/mlinks{$userno$}_{$userserial$}/{stream-id}
 *   @return
 *      PSLRET_SUCCESS      success
 *      others				failed
 */
#ifndef NT_VERSION
__attribute__((deprecated))
#endif
int PSLStreamingControlUserVisible(void* pPSLStreaming, unsigned int userno, unsigned int userserial, unsigned int flag);
    
/**
 * release PSLStreaming
 **/
void    PSLStreamingRelease(void* pPSLStreaming);
    
int     PL_GetVersion(char*versionstr, int size);

};

#endif
