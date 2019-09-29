
#ifndef xdns_h
#define xdns_h

typedef void (*XDNS_LOG_FUNC)(int32_t level, const char *str, ...);

extern XDNS_LOG_FUNC dns_log_to_file;

BASE_API void xdns_setlogfunc(XDNS_LOG_FUNC logfunc);

BASE_API int xdns_init();

/**
 * @return 0 for success, -1 for failed, -2 for timeout
 *
 */
BASE_API int xdns_gethostbyname(const char *name, DWORD *ip, void *p, int timeout_ms);

BASE_API int xdns_gethostbyname(const char *name, DWORD *ip, void *p, int timeout_ms, DWORD *stopflag);

BASE_API int xdns_addDNSServer(const char *dnsServerIP);

BASE_API int xdns_removeDNSServer(const char *dnsServerIP);

//ifabroad==0 means within China, others means abroad
BASE_API int xdns_setIfAbroad(int ifabroad);

BASE_API int xdns_release();

#endif /* xdns_h */
