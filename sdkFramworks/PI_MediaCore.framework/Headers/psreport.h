
#ifndef _LIB_PS_REPORT_H_
#define _LIB_PS_REPORT_H_

class PSReport
{
public:
    static PSReport *GetInstance() {
        if (!m_pInstance) {
            m_pInstance = new PSReport;
        }
        
        return m_pInstance;
    }
    
    virtual void destructor();
    
    int     SetReportInterval(int report_interval);
    int     SetReportInfo(const char *info);
    
    void    ReportProc();
    
private:
    PSReport();
    PSReport(PSReport const &);
    PSReport & operator=(PSReport const &);
    ~PSReport();
    
    int HttpConnect(int timeout_ms);
    int HttpPost(const char *buf);
    
    static PSReport     *m_pInstance;
    pthread_mutex_t     mutex;
    
    int     m_iReportInterval;
    int     m_iStopFlag;
    int     m_iStatus;
    char    *m_pInfo;
    
    char            m_pDomain[64];
    int             m_iPort;
    SOCKET          m_sockfd;
    PSNDSelector    *m_pSelector;
};

#endif
