//
// Created by steve on 16-8-30.
//

#include <iostream>
#include "FileReader.h"

#include "Matrix.h"

#include "MyError.h"

class CSVReader : public FileReader {
public:

    CSVReader() = default;

	~CSVReader()
	{

	}

    CSVReader(std::string file_name) : FileReader(file_name) {}


    int rows_ = 0;
    int cols_ = 0;

    void test1();

private:

protected:
    bool MatSize();

    Matrix<double> m_;

    bool LoadData();

};

bool CSVReader::MatSize() {

    int line_number(0);
    int index(0);
    int line_elements(0);

    while (true) {
        if (line_number == 0) {
            if (file_buf_[index] == ',') {
                ++line_elements;
            }
        }
        if (file_buf_[index] == '\n') {
            ++line_number;
        }

        if (index > file_size_ - 1) {

            break;
        } else {
            ++index;
        }
    }

    rows_ = line_number+1;
    cols_ = line_elements + 1;


    return false;
}

//Just for test.
void CSVReader::test1() {
    MatSize();
    std::cout << " rows : " << rows_ << "  cols : " << rows_ << std::endl;
	
	m_.set_size(rows_, cols_);

	*m_(1, 2) = 2;
	std::cout << " ok " << *m_(1, 2) << std::endl;
	LoadData();
	std::cout << " ok ::" << *m_(1, 2) << std::endl;
	
	Matrix<double> tmp_m1(m_),sum_m(m_);
	std::cout << "sss" << std::endl;
	sum_m = tmp_m1 * m_;

	int xx(1), yy(2);
	std::cout << *m_(xx, yy) << "  "<< *tmp_m1(xx, yy) << "  " << *sum_m(xx, yy) << std::endl;

	std::cout << *m_(99, 99) << std::endl;
	sum_m = tmp_m1 * m_ * 2.0 + 10.0;

	std::cout << *m_(xx, yy) << "  " << *tmp_m1(xx, yy) << "  " << *sum_m(xx, yy) << std::endl;
	
}

bool CSVReader::LoadData() {

	if(rows_*cols_ == 0)
	{
		MatSize();
	}
	if(file_size_ == 0)
	{
		MYERROR("FILE IS EMPTY!")
	}
	std::string tmp_str(file_buf_);

	int the_row(0), the_col(0);

	int l_index(0), r_index(0);

	for(int index(0);index < tmp_str.size();++index)
	{
		if(tmp_str[index]==',' || tmp_str[index] == '\n')
		{
			r_index = index;
			*m_(the_row, the_col) = atof(tmp_str.substr(l_index, r_index - l_index).c_str());
			if(tmp_str[index] == '\n')
			{
				++the_row;
				the_col = 0;
			}else
			{
				++the_col;
			}
			if(the_row == rows_-1 && the_col == cols_ -1)
			{
				*m_(the_row, the_col ) = atof(tmp_str.substr(r_index + 1, file_size_ - r_index - 1).c_str());
				break;
			}
			l_index = r_index + 1;
		}
	}
	
    return false;
}

