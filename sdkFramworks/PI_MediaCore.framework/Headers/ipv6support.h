
#ifndef ipconverter_hpp
#define ipconverter_hpp

#define PSL_IPV4_ONLY 1
#define PSL_IPV6_ONLY 2
#define PSL_IPV4_AND_IPV6 3

/**
 @param type 1 for ip point is &(int), it's network byte order
             2 for ip point is char*
 @param ipv4 see type
 @param ipv6 char array, length of array should larger than 128
 @param sizeofipv6 size of char array `ipv6`
 @return error return -1
         success return 0
 */
BASE_API int converter_ipv4_to_ipv6(int type, void *ipv4, char* ipv6, int sizeofipv6);

/**
 @param type 1 for ip point is &(int), it's network byte order
             2 for ip point is char*
 @param ipv4 see type
 @param ipv6 char array, length of array should not less than 128
 @param sizeofipv4 size of char array `ipv4` if `ipv4` type is 1, length of array should not less than 128
 @return error return -1
 success return 0
 */
BASE_API int converter_ipv6_to_ipv4(int type, char* ipv6, void *ipv4, int sizeofipv4);

/**
 @return if ipv4-only, return PSL_IPV4_ONLY
         if ipv6-only, return PSL_IPV6_ONLY
         if PSL_IPV4_AND_IPV6, return PSL_IPV4_AND_IPV6
         failed, return -1
 */
BASE_API int checknetwork_ipv4_ipv6();

/**
 
 */
BASE_API int checknetworkipvx_setflush();

/**
 @return    if ipv4-only, return PSL_IPV4_ONLY
            if ipv6-only, return PSL_IPV6_ONLY
            if PSL_IPV4_AND_IPV6, return PSL_IPV4_AND_IPV6
            failed, return -1
 */
BASE_API int getnetwork_ipv4_ipv6();

BASE_API void setnetwork_ipv4_ipv6(int ipvx);

// 1 for force ipv6, 0 for no force ipv6
void forceNetworkIpv6NoIpv4(int enable);

#endif
