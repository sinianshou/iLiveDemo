
#ifndef BASE64_H
#define BASE64_H

BASE_API unsigned char Which(unsigned char sr);
BASE_API unsigned long Base64Encode(char *sr, unsigned int dwSrcSize, char *dest);
BASE_API unsigned long Base64Decode(char *InputStr, unsigned int dwLen, char *OutputStr);

#endif
