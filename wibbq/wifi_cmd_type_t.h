#ifndef WIBBQ_WIFI_CMD_TYPE_T_H
#define WIBBQ_WIFI_CMD_TYPE_T_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace wibbq
{
typedef enum 
{
	WIFICMD_REQUEST,
	WIFICMD_RESPONSE,
	WIFICMD_EVENT

} wifi_cmd_type_t;

}  // namespace wibbq
#endif
