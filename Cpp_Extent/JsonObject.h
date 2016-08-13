#pragma once


#include <string>
#include <map>

#include <chrono>

#include "JsonCodert.h"

#include <stdio.h>
#include <stdlib.h>


enum ValueType
{
	EMPTY = -1,
	OBJECT = 0,
	INT = 1,
	DOUBLE = 2,
	STRING = 3,
	ARRAY = 4,
	ISNULL = 5,
	BOOL = 6,
};

class JsonObject:public JsonCoder
{
public:

	JsonObject(): int_value_(0), double_value_(0)
	{
	}

	JsonObject(std::string value_str);

	~JsonObject()
	{
	}

	ValueType value_type_ = EMPTY;

	std::map<std::string, JsonObject> map_;
	std::string str_value_;
	int int_value_;
	double double_value_;
	std::vector<JsonObject> array_value_;
	bool bool_value_;

	std::string str_debug_;


	std::string AsString() const;

	int AsInt() const;

	double AsDouble() const;

	JsonObject operator[](std::string key);

	JsonObject operator[](int index);
};

inline JsonObject::JsonObject(std::string value_str)
{
	str_debug_ = value_str;
	if (-1 != value_str.find('{') && (value_str.find("{") < value_str.find('[') || value_str.find("[") < 0))
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

		size_t begin_index(value_str.find("[")), last_index(value_str.find_last_of("]"));
		int l_index = begin_index + 1, r_index = begin_index;

		bool is_object(false);
		bool is_array(false);

		bool is_end(false);

		while (true)
		{
			r_index = value_str.find(",", l_index + 1);
			if (r_index == -1)
			{
				r_index = last_index;
				is_end = true;
			}


			if (!is_object && !is_array)
			{
				if (-1 < value_str.find("[", l_index) && -1 < value_str.find("{", l_index))
				{
					//TODO:ADD function to element which value type is object or array.
					if (value_str.find("[", l_index) < value_str.find("{", l_index))
					{
						is_array = true;
					}
					else
					{
						is_object = true;
					}
				}
				else if (-1 < value_str.find("[", l_index) && !(-1 < value_str.find("{", l_index)))
				{
					is_array = true;
				}
				else if (!(-1 < value_str.find("[", l_index)) && -1 < value_str.find("{", l_index))
				{
					is_object = true;
				}
			}


			if (is_array)
			{
				l_index = value_str.find('[', l_index);

				int tmp_index(l_index + 1);
				std::vector<int> tmp_stack;
				tmp_stack.push_back(tmp_index);

				while (true)
				{
					if (value_str.at(tmp_index) == '[')
					{
						tmp_stack.push_back(tmp_index);
					}
					else if (value_str.at(tmp_index) == ']')
					{
						tmp_stack.pop_back();
					}
					if (tmp_stack.size() == 0)
					{
						r_index = tmp_index;
						break;
					}
					++tmp_index;
				}
				array_value_.push_back(JsonObject(value_str.substr(l_index, r_index)));
				last_index = r_index;
			}
			else if (is_object)
			{
				l_index = value_str.find('{', l_index+1);
			

				int tmp_index(l_index +1);
				std::vector<int> tmp_stack;
				tmp_stack.push_back(tmp_index);

				while (true)
				{
					if (tmp_index >= value_str.size())
					{
						std::cout << "ERROR :index is out of range!" << std::endl;
					}
					if (value_str.at(tmp_index) == '{')
					{
						tmp_stack.push_back(tmp_index);
					}
					else if (value_str.at(tmp_index) == '}')
					{
						tmp_stack.pop_back();
					}
					if (tmp_stack.size() == 0)
					{
						r_index = tmp_index;
						break;
					}
					++tmp_index;
				}
				array_value_.push_back(JsonObject(value_str.substr(l_index, r_index)));
				last_index = r_index;
			}
			else
			{
				array_value_.push_back(JsonObject(value_str.substr(l_index, r_index)));
				last_index = r_index;
			}

			l_index = r_index;
			if (is_end)
			{
				break;
			}
		}
	}
	else if (-1 != value_str.find("\""))
	{
		//value type is string , save value delete "\"".
		value_type_ = ValueType::STRING;
		size_t begin_index = value_str.find("\"");
		size_t end_index(value_str.find_last_of("\""));


		str_value_ = value_str.substr(begin_index + 1, end_index - 1);
	}
	else if (-1 != value_str.find("true"))
	{
		value_type_ = ValueType::BOOL;

		bool_value_ = true;
	}
	else if (-1 != value_str.find("false"))
	{
		value_type_ = ValueType::BOOL;

		bool_value_ = false;
	}
	else if (-1 != value_str.find("null"))
	{
		value_type_ = ValueType::ISNULL;
	}
	else if (-1 != value_str.find("."))
	{
		value_type_ = ValueType::DOUBLE;
		double_value_ = atof(value_str.c_str());
	}
	else if (-1 != value_str.find("e"))
	{
		value_type_ = ValueType::DOUBLE;
		double_value_ = atof(value_str.c_str());
	}
	else
	{
		value_type_ = ValueType::INT;
		int_value_ = atoi(value_str.c_str());
	}
}

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

inline JsonObject JsonObject::operator[](int index)
{
	if (value_type_ == ValueType::ARRAY)
	{
		if (index > array_value_.size())
		{
			std::cout << "Index : " << index << " is out of range 0-" << array_value_.size() << std::endl;
			return JsonObject();
		}
		else
		{
			return array_value_.at(index);
		}
	}
	else
	{
		std::cout << " This value is not a array!" << std::endl;
		return JsonObject();
	}
}
