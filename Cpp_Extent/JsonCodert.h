#pragma once

#include <string>

#include <map>

class JsonCoder
{
public:
	JsonCoder();

	JsonCoder(std::string str);

	~JsonCoder();

private:
	std::string s_buf_;

protected:
	std::map<std::string, std::string> content_map_;

	


};

inline JsonCoder::JsonCoder()
{

}

inline JsonCoder::JsonCoder(std::string str)
{
	s_buf_ = str;
}

inline JsonCoder::~JsonCoder()
{

}
