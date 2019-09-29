
#include "pzbc.h"

#ifndef psndselector_h
#define psndselector_h

#define PSDEFAULT_TIMEOUT   60 * 60 * 1000
#define PSDNS_FAIL_TIMEOUT  5 * 60 * 1000

#define NODE_SELECT_RESERVED    0   // Reserved
#define NODE_SELECT_FASTWEB     1   // Fast DNS(Fast Web)
#define NODE_SELECT_NULL        2   // Normal DNS
#define NODE_SELECT_PZB         3   // PZB Default
#define NODE_SELECT_PZB_INKE    4   // PZB Inke
#define NODE_SELECT_PZB_JP      5   // PZB Japan
#define NODE_SELECT_PZB_SG      6   // PZB Singapore
#define NODE_SELECT_PZB_IN      20   // PZB India(not likely to be used)
#define NODE_SELECT_PZB_TEST    255 // PZB Test

#define NODE_SELECT_DEFAULT     NODE_SELECT_FASTWEB
#define NODE_SELECT_MAX         3
#define MAX_SOLID_IP            16

#define	PZB_SERVICE_MODE_AUTO				0
#define	PZB_SERVICE_MODE_PUBLISH_USER		1
#define	PZB_SERVICE_MODE_PULL_USER			2
#define	PZB_SERVICE_MODE_PUBLISH_LINKUSER	3
#define	PZB_SERVICE_MODE_PULL_LINKUSER		4

//class PZBC;

#define NDSELECT_DOMAIN_LEN 64

BASE_API int pzb_parseurl(const char* httpurl, char* domain, int domainlen, DWORD* port, char* uri, int urilen, int *mode, int keepparam);

int getndmodefromurl(char*url, const char* name, char* value, const int valuelen);

typedef struct PSDNSInfo
{
    char    domain[1024];
    int     request_type; // 0-invalid 1-fast dns, 2-basic dns, 3-pzb dns
    int     real_type;  // -1-invalid, 0-basic, 1-fast dns, 2-basic dns, 3-pzb dns
    DWORD   solid_ip[MAX_SOLID_IP];
    DWORD   basic_ip;
    in6_addr   solid_ipv6[MAX_SOLID_IP];
    in6_addr    basic_ipv6;
    int     number_solid_ip;
    int     number_solid_ipv6;
    bool    usableflag_solid_ip[MAX_SOLID_IP];
    bool    usableflag_solid_ipv6[MAX_SOLID_IP];
    int     usableflag_num;
    int     usableflag_num_ipv6;
    
    long long basic_refresh_time;
    long long solid_refresh_time;
    long long basic_fail_time;
    long long solid_fail_time;
} PSDNSInfo;

class BASE_API PSNDSelector
{
public:
    //PSNDSelector *getInstance();
    
    int start(int timeout_ms = PSDEFAULT_TIMEOUT);
    int stop();
    int addURL_domain(const char *domain, int type);
    int addURL(const char *url, int type);
    int getIP(const char *url, int type, int *ip, int *real_type, char* desiredDomain, char* acturalDomain);
    int getIP(const char *url, int type, sockaddr *addr, int *real_type, char* desiredDomain, char* acturalDomain, int *networktype);
    
    int getIP_with_stopflag(const char *url, int type, sockaddr *addr, int *real_type, char* desiredDomain, char* acturalDomain, int* networktype, DWORD *stopflag);
    
    int getIP_domain(const char *domain, int type, sockaddr *addr, int *real_type, char *desiredDomain, char *acturalDomain, int *networktype);
    
    int getIP_domain_with_stopflag(const char *domain, int type, sockaddr *addr, int *real_type, char *desiredDomain, char *acturalDomain, int *networktype, DWORD *stopflag);
    
    int getIP_domain(const char *domain, int type, int *ip, int *real_type, char* desiredDomain, char* acturalDomain);
    
    int getIP_domain(const char *domain, int type, int *ip, int *real_type, char* desiredDomain, char* acturalDomain, DWORD *stopflag);
    
    int getIPV6(const char *url, int type, in6_addr *ip, int *real_type, char* desiredDomain, char* acturalDomain);
    int getIPV6_domain(const char *domain, int type, in6_addr *ip, int *real_type, char* desiredDomain, char* acturalDomain);
    
    /**
     @param iptype if PSL_IPV6_ONLY, then the type of ip is in6_addr*
                   if PSL_IPV4_ONLY, then the type of ip is int*
     @param ip if ip type is PSL_IPV4_ONLY, ip is network byte order
     */
    int setSolidIPunUsable(const char *domain, void*ip, int iptype);
    
    void selectorProc();
    
    void refresh();
    
    // 1 for success, 2 for fail
    void feedBack(const char *domain, int networkType, sockaddr *addr, int ifSuccess);
    
    //private:
    PSNDSelector();
    ~PSNDSelector();
    
private:
    int basicIP(const char *domain, int *ip, int timeout_ms);
    int basicIP(const char *domain, int *ip, int timeout_ms, DWORD *stopflag);
    int basicIPV6(const char *domain, in6_addr *ip, int timeout_ms);
    int basicIPV6(const char *domain, in6_addr *ip, int timeout_ms, DWORD *stopflag);
    int solidIP(const char *domain, int *ip, int *ipnum, int timeout_ms);
    int solidIP(const char *domain, int *ip, int *ipnum, int timeout_ms, DWORD *stopflag);
    int getDomain(const char *url, char *domain);
    int addDomain(const char *domain, int type);
    int getDomainIP(const char *domain, int type, int *ip, int *real_type, in6_addr *ipv6, int *ipv6flag, char* desiredDomain, char* acturalDomain);
    int getDomainIPV4(const char *domain, int type, int *ip, int *real_type, char* desiredDomain, char* acturalDomain);
    
    int getDomainIPV4(const char *domain, int type, int *ip, int *real_type, char* desiredDomain, char* acturalDomain, DWORD *stopflag);
    
    int getDomainIPV6(const char *domain, int type, in6_addr *addr, int *real_type, char *desiredDomain, char *acturalDomain, DWORD *stopflag);
    
    //PSNDSelector *m_pInstance;
    PI_iLiveBase_Mutex m_Lock;
    
    PSDNSInfo *m_pInfo;
    void *m_pSelectorThread;
    
    int m_iStatus;  // 0-stop, 1-running
    int m_iStopFlag;  // 0-do nothing, 1-stop running
    int m_iDomainNumber;
    int m_iTimeout;  // ms
    int m_refreshflag;// -2: idle, -1: refresh last added record, positive number means refresh this record
    
    int m_ipvxflag;
    int m_iFastDNSIP;  // cache
    bool    m_bFastDNSIPV6Flag;
    char m_iFastDNSIPV6[128];
    long long m_llFastDNSIPRefreshTime;
};

#endif
