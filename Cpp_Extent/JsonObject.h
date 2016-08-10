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
	ARRAY = 4,
};

class JsonObject:public JsonCoder
{
public:

	JsonObject(): int_value_(0), double_value_(0)
	{
	}

	JsonObject(std::string value_str)
	{
		if (-1 != value_str.find('{'))
		{
			value_type_ = ValueType::OBJECT;
			s_buf_ = value_str;

			ClearString();
			Decoder();

			for (std::map<std::string, std::string>::iterator it = content_map_.begin();
			     it != content_map_.end(); ++it)
			{
				JsonObject tmp_value(it->second);

				map_.insert(std::map<std::string, JsonObject>::value_type(it->first.substr(1, it->first.size() - 2), tmp_value));
			}
		}
		else if (-1 != value_str.find('['))
		{
			value_type_ = ValueType::ARRAY;
		}
		else if (-1 != value_str.find("\""))
		{
			value_type_ = ValueType::STRING;
		}
		else if (-1 != value_str.find("."))
		{
			value_type_ = ValueType::DOUBLE;
		}
		else if (-1 != value_str.find("e"))
		{
			value_type_ = ValueType::DOUBLE;
		}
		else
		{
			value_type_ = ValueType::INT;
		}
	}

	~JsonObject()
	{
	}

	ValueType value_type_ = EMPTY;

	std::map<std::string, JsonObject> map_;

	std::string str_value_;
	int int_value_;
	double double_value_;


	std::string AsString() const;

	int AsInt() const;

	double AsDouble() const;

	JsonObject operator[](std::string key);
};

inline std::string JsonObject::AsString() const
{
	if (value_type_ == ValueType::STRING)
	{
		return str_value_;
	}
	else
	{
		//TODO:ADD transform between diffirent value type.
		return std::string("");
	}
}

inline int JsonObject::AsInt() const
{
	if (value_type_ == ValueType::INT)
	{
		return int_value_;
	}
	else
	{
		return 0;
	}
}

inline double JsonObject::AsDouble() const
{
	if (value_type_ == ValueType::DOUBLE)
	{
		return double_value_;
	}
	else
	{
		return 0;
	}
}

inline JsonObject JsonObject::operator[](std::string key)
{
	std::map<std::string, JsonObject>::iterator ite;
	ite = map_.find(key);
	if (ite != map_.end())
	{
		return ite->second;
	}
	else
	{
		std::cout << "There are not a key : " << key << " in json document." << std::endl;
		return JsonObject();
	}
}
