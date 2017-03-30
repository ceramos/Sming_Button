#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif

void print_hex_arr(void *arr, int length) {
   int i;
   unsigned char *pch = (unsigned char *)arr;
   for (i = 0; i < length; ++i) {
      m_printf("%02X ", pch[i]);
   }
}

#ifdef __cplusplus
}
#endif
