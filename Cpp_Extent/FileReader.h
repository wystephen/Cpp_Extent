#pragma once

#include <stdio.h>

#include <fstream>
#include <string>




class FileReader
{
public:
	FileReader();
	FileReader(std::string file_name);
	~FileReader();

	bool test();

private:
	std::string file_name_;

	long GetSize();

	bool LoadFile();
protected:
	long file_size_;

	char *file_buf_;

	
};

inline FileReader::FileReader()
{
	file_name_ = std::string("");
}

inline FileReader::FileReader(std::string file_name)
{
	file_name_ = file_name;

	GetSize();

	LoadFile();
}

inline FileReader::~FileReader()
{
	delete[]file_buf_;
}

inline bool FileReader::test()
{
	GetSize();
	return true;
}

inline long FileReader::GetSize()
{
	try
	{
		std::ifstream tmp_f(file_name_);


		tmp_f.seekg(0, std::ios::end);
		std::streampos ps = tmp_f.tellg();

		file_size_ = ps;

		std::cout << "file_size :" << file_size_ << std::endl;

		return ps;
	}
	catch (...)
	{
		std::cerr << "Error in open file." << std::endl;
	}
}

inline bool FileReader::LoadFile()
{
	try
	{
		if( file_size_ == 0)
		{
			if(GetSize()==0)
			{
				std::cerr << "File" << file_name_ << " is empty !" << std::endl;
			}

		}

		file_buf_ = new char[file_size_];

		FILE *file;
		file = fopen(file_name_.c_str(), "r");

	

		fread(file_buf_, file_size_, 1, file);

		fclose(file);

		return true;

	}catch(...)
	{
		
	}
}
