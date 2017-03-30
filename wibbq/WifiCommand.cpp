#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "WifiCommand.h"

namespace wibbq
{

WifiCommand::WifiCommand()
{
}

WifiCommand::WifiCommand(wifi_cmd_type_t type, String name, String content)
{
}

WifiCommand::~WifiCommand()
{
}

bool WifiCommand::unpackJson()
{
	return false;
}

String WifiCommand::packJson()
{
	return 0;
}
}  // namespace wibbq
