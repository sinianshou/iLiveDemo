#ifndef __PZBC_HEADER_DEFINED__
#define __PZBC_HEADER_DEFINED__

#define PZB_PROTOCOL_TRANS_PTCP     1
#define PZB_PROTOCOL_FLV_HTTP       2
#define PZB_PROTOCOL_TCP_TRANS      3
#define PZB_PROTOCOL_FLV_RTMP       16

#define PZB_POWZAMEDIA_MODE       0
#define PZB_INKE_MODE             1
#define PZB_POWZAMEDIA_JP_MODE    2
#define PZB_POWZAMEDIA_TEST_MODE  3
#define PZB_POWZAMEDIA_SG_MODE    4
#define PZB_POWZAMEDIA_IN_MODE    20

#define	PZB_MAX_DOMAIN_COUNT	16
#define	PZB_MAX_ITEM_LIST		8
#define PZB_DOMAIN_LEN          64


#define PZBC_INPUT_DOMAIN_LEN   512
#define PZBC_INPUT_URI_LEN  1024
#define PZBC_INTERNAL_FWD_DATA_LEN  1024

class BASE_API PZBC_Item
{
public:
	char	Addr[256];
	DWORD	Port;
	DWORD	Protocol;
	DWORD	Retry;
	DWORD	Exec;
    DWORD   Err;
    DWORD   Networktype;    //1 for ipv4, 2 for ipv6
	char	Detail[256];
};

class BASE_API PZBC_Input
{
public:
    char    Domain[PZBC_INPUT_DOMAIN_LEN];
    char    URI[PZBC_INPUT_URI_LEN];
    DWORD   Port;
    DWORD   Mode;
    DWORD   Owner;
    DWORD   Timeout;
    DWORD   NewFlag;
    long long  RefreshTime;
};

class BASE_API PZBC_Internal
{
public:
    PZBC_Item  List_ipv4[PZB_MAX_ITEM_LIST];
    PZBC_Item  List_ipv6[PZB_MAX_ITEM_LIST];
    char   ActualDomain[PZB_DOMAIN_LEN];
    char   Fwd_Data[PZBC_INTERNAL_FWD_DATA_LEN];
    int    NowNo_ipv4;
    int    NowNo_ipv6;
    DWORD  PreloadFlag;
    DWORD  Count_ipv4;
    DWORD  Count_ipv6;
    DWORD  Loop;
    DWORD  RPI;
    
    int     Running;//chenhd
};

class BASE_API PZBC
{
private:
//	DWORD		PZBS_Port;
	char		CID[64];
//    int         m_ipvxflag;
//    void*       pPSNDSelector;
    PI_iLiveBase_Mutex		mutex;
    
    PZBC_Input      *m_input;
    PZBC_Internal   *m_internal;
    DWORD           m_saved;
    
    // Clear saved input and internal data
    int ClearSaved(int saved_no);
    
    // Save input data
    int SaveInput(int saved_no, char *domain, char *uri, DWORD port, DWORD mode, DWORD owner, DWORD timeout);
    
    // Find oldest saved input data
    int FindOldest();
    
    // Compare input params with saved params
    // Return value
    // 1, equal
    // 0, not equal
    int CompareInput(int saved_no, char *domain, char *uri, DWORD port, DWORD mode, DWORD owner);
    
    // Find available input space
    int FindAvailable(char *domain, char *uri, DWORD port, DWORD mode, DWORD owner, DWORD timeout);
    
    // Get ip address from node selector(do not update RefreshTime)
    int GetFromNDS(int no, char *ip, DWORD *port, DWORD *protocol, int *networktype);
    
    
    DWORD	Get_From_PZB_With_Stopflag(int no, DWORD *stopflag);
    DWORD	Get_Info_From_PZB_With_Stopflag(int no, char* Host,DWORD Host_Count,DWORD Port,char* pURI,char* User_Agent, DWORD* pContent_Length,char* pContent, DWORD Time_Out, DWORD *stopflag);
    
    DWORD parsePZBInfo(char* content, int i);

public:
    
    PZBC();
    ~PZBC();
	
    void*       pPSNDSelector;
    int         m_ipvxflag;
    DWORD		PZBS_Port;
    /**
     * Init with NDSelector object
     **/
    void	Init(void*	pNDSelector);
    
    DWORD	Set(char *Set_Domain,DWORD Set_Port,char *Set_URI,DWORD Set_Mode, DWORD	Set_Time_Out,DWORD PZBOwner_Mode);
    
    DWORD	Preload(char *domain, DWORD port, char *uri, DWORD mode, DWORD owner, DWORD *network_type);
    void*	Preload_Run(int no);
    
    /**
     * if the Domain in pzbc is same to your domain, return 0;
     * if difference, return -1;
     **/
    int     CheckDomain(char* domain);
    
    /**
     * Feedback error status
     **/
    int     Feedback(char *domain, DWORD port, char *uri, DWORD mode, DWORD owner, char *ip, int err);
    
    /**
     * Refresh all cache, force to make request again
     **/
    int     Refresh();
    
    /**
     @param get_addr the size of Addr should not less than 256
     **/
	DWORD	Get(char *domain, DWORD port, char *uri, DWORD mode, DWORD owner, char *get_addr, DWORD* get_port, DWORD* get_protocol, char *desired_domain, char *actual_domain, DWORD *stopflag, DWORD *network_type, DWORD *rpi = 0, char *get_fwd_data = NULL);	//sizeof(desiredDomain) and sizeof(actualDomain) should not less than 64
    
	DWORD	Reset(int no);

	DWORD	Get_From_PZB(int no);

    DWORD    Http_Connect_With_Stopflag(DWORD sockfd, struct sockaddr*dstaddr, int addrlen, int timeout_ms, DWORD *stopflag);
    
    DWORD    Http_Connect(DWORD sockfd, struct sockaddr*dstaddr, int addrlen, int timeout_ms);

	DWORD	Get_Info_From_PZB(int no, char* Host,DWORD Host_Count,DWORD Port,char* pURI,char* User_Agent, DWORD* pContent_Length,char* pContent, DWORD Time_Out);
    
    DWORD   addInfoToPZB(char* content, char* domain, char* uri, DWORD port, DWORD mode, DWORD owner, DWORD timeout=5000);
    
    
    // synchronize, do not modify
    int m_sync;
    
    // preload number, do not modify
    int m_preload;
    
    //chenhd
    int m_stopflag;

};

BASE_API DWORD	PZBC_Global_Init(void* pNDSelector);
BASE_API DWORD   NDSelector_Global_Init();
BASE_API DWORD   startPzlog();   //return 0 for success, -1 for fail, -2 for already started

//  status==0: set to background status; 1: set to foreground status
BASE_API void psSetForegroundStatus(int status);

//  if background status: return 0; if foreground status: return 1
BASE_API int psGetForegroundStatus();

#endif

