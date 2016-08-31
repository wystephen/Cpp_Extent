//
// Created by steve on 16-8-30.
//

#include <iostream>
#include "FileReader.h"



class CSVReader: public FileReader
{
public:

    CSVReader() = default;
    CSVReader(std::string file_name):FileReader(file_name){}


    int rows_ = 0;
    int cols_ = 0;

    void test1();

private:

protected:
    bool MatSize();
    std::vector<double> array;

};

bool CSVReader::MatSize() {

    int len_first_line(0);
    int line_number(0);
    int index(0);
    int line_elements(0);
    while(true)
    {
        if(file_buf_[index] == '\n')
        {
            ++ line_number;
        }
        if(line_number == 0)
        {
            if(file_buf_[index]==',')
            {
                ++ line_elements;
            }
        }
        if(index > file_size_-2)
        {
            break;
        }else{
            ++ index;
        }
    }

    rows_ = line_number;
    cols_ = line_elements +1;


    return false;
}

void CSVReader::test1() {
    MatSize();
    std::cout << " rows : " << rows_ << "  cols : " << rows_ << std::endl;

}

