#pragma once

#include "JsonObject.h"

class AutoJsonDecoder:public JsonCoder
{
public:
	AutoJsonDecoder(std::string str)
	{
		s_buf_ = str;
	}


protected:
	


};