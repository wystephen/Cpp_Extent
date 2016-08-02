#pragma once

#include <string>

#include <map>

#include <vector>

class JsonCoder
{
public:
	JsonCoder();

	JsonCoder(std::string str);

	~JsonCoder();

	bool test();

	bool Decoder();

	bool ClearString();

	

private:
	std::string s_buf_;

protected:
	std::map<std::string, std::string> content_map_;

	bool ValueDecoder(std::string value_str);
};

inline JsonCoder::JsonCoder()
{
	s_buf_ = "";
}

inline JsonCoder::JsonCoder(std::string str)
{
	
	s_buf_ = str;

	std::cout << "str size:" << str.length() << "s_buf_size:" << s_buf_.size();
	
	std::cout << str << std::endl << std::endl;

	ClearString();

	std::cout << s_buf_ << std::endl << std::endl;
	
	Decoder();
}

inline JsonCoder::~JsonCoder()
{

}

inline bool JsonCoder::test()
{
	for(std::map<std::string,std::string>::iterator it(content_map_.begin());it!=content_map_.end();it++)
	{
		std::cout << it->first << " : " << it->second << std::endl << std::endl<< std::endl;
	}

	return true;
}



inline bool JsonCoder::Decoder()
{
	try
	{
		if(s_buf_.empty())
		{
			std::cerr << "The value s_buf_ which is save the string is empty!" << std::endl;
			return false;
		}

		int tmp_comma_index(0);
		int colon_index(0);//冒号序号
		int comma_index(0);//逗号序号

		std::string tmp_key;
		std::string tmp_value;

		//std::cout << "size of buf:" << s_buf_.size() << std::endl;

		while(true)
		{
			tmp_comma_index = s_buf_.find(',', 1+comma_index);
			if(tmp_comma_index != std::string::npos)
			{
				//if(s_buf_.find('{',comma_index+1)<tmp_comma_index)//有子结构存在
				//{
				//	std::vector<int> pair_stack;
				//	pair_stack.push_back(s_buf_.find('{', comma_index + 1));
				//	int tmp_index(pair_stack[0]);
				//	while(true)
				//	{
				//		tmp_index++;
				//		if(s_buf_[tmp_index] == '{')
				//		{
				//			pair_stack.push_back(tmp_index);
				//		}else if(s_buf_[tmp_index] == '}')
				//		{
				//			pair_stack.pop_back();
				//		}

				//		if(pair_stack.size()==0)
				//		{
				//			tmp_comma_index = tmp_index + 1;
				//			break;
				//		}else
				//		{
				//			tmp_index++;
				//		}
				//	}
				//}
				
			}else
			{
				
				tmp_comma_index = s_buf_.find('}', comma_index + 1);
			}

			if (s_buf_.find('{', comma_index + 1)<tmp_comma_index)//有子结构存在
			{
				std::vector<int> pair_stack;
				pair_stack.push_back(s_buf_.find('{', comma_index + 1));
				int tmp_index(s_buf_.find('{', comma_index + 1));
				while (true)
				{
					tmp_index++;
					if (s_buf_[tmp_index] == '{')
					{
						pair_stack.push_back(tmp_index);
					}
					else if (s_buf_[tmp_index] == '}')
					{
						pair_stack.pop_back();
					}

					if (pair_stack.size() == 0)
					{
						tmp_comma_index = tmp_index + 1;
						break;
					}
					else
					{
						//tmp_index++;
					}
				}
			}

			colon_index = s_buf_.find(':', comma_index + 1);

			if (colon_index != std::string::npos && colon_index < tmp_comma_index)
			{
				tmp_key = s_buf_.substr(comma_index + 1, colon_index - comma_index-1);
				tmp_value = s_buf_.substr(colon_index + 1, tmp_comma_index - colon_index-1);
			}
			else
			{
				/*std::cerr << "Json format is error form index " << comma_index << " to index " << tmp_comma_index <<
					"str is:" << s_buf_.substr(comma_index, tmp_comma_index)  << std::endl;*/
				break;
			}

			content_map_.insert(std::map<std::string, std::string>::value_type(tmp_key, tmp_value));
			comma_index = tmp_comma_index;
			if(tmp_comma_index == s_buf_.size())
			{
				break;
			}
		}

	}catch(...)
	{
		
	}
}

inline bool JsonCoder::ClearString()
{
	std::string::iterator pos(s_buf_.begin());

	while (pos != s_buf_.end())
	{
		 if(*pos == '\n')
		 {
			 s_buf_.erase(pos);
		 }else if(*pos == ' ')
		 {
			 s_buf_.erase(pos);
		 }

		++pos;

	}
	return true;
}

inline bool JsonCoder::ValueDecoder(std::string value_str)
{
	try
	{
	
		if(value_str.size() >= 1)
		{
			std::cerr << "value is empty:" << std::endl;

		}


		

	}catch(double a)
	{
		if(a < 1.0)
		{
			std::cerr << "error:'" << a << std::endl;
		}
	}
}
