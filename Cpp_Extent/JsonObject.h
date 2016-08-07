#pragma once


#include <string>
#include <map>

#include <chrono>

#include "JsonCodert.h"


enum ValueType
{
	EMPTY = -1,
	OBJECT = 0,
	INT = 1,
	DOUBLE = 2,
	STRING = 3,
	
};

class JsonObject
{
public:
	ValueType value_type_ = EMPTY;
	
	JsonObject &value_;




};