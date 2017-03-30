#ifndef WIBBQ_WIFI_COMMAND_H
#define WIBBQ_WIFI_COMMAND_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "common.h"
#include <SmingCore/SmingCore.h>
#include "wibbq/wifi_cmd_type_t.h"

namespace wibbq
{
class WifiCommand
{
protected:
	wifi_cmd_type_t type;

	String name;

	String content;


public:
	/**
	 * WifiCommand constructor. Create an object of WifiCommand with default properties.
	 *
 *
	 */
	WifiCommand();

	/**
	 * Create an object of WifiCommand with given parameters.
	 *
 *
	 */
	WifiCommand(wifi_cmd_type_t type, String name, String content);

	~WifiCommand();

	/**
	 * Unpacking data from JSON string into object properties
	 *
 *
	 */
	virtual bool unpackJson();

	/**
	 * Pack data from object properties into JSON string
	 *
 *
	 */
	virtual String packJson();

};

}  // namespace wibbq
#endif
