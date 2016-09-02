//
// Created by steve on 16-8-31.
//

#include <iostream>

#include <memory>

#include <cstring>

template <class T>
class Matrix
{
public:


	Matrix<T>(){}

    Matrix<T>(int rows,int cols)
    {
        buf_=new T[rows*cols];
        rows_ = rows;
        cols_ = cols;
    }

	Matrix<T>(Matrix &m_matrix)
	{
		this->rows_ = m_matrix.rows_;
		this->cols_ = m_matrix.cols_;

		buf_ = new T[rows_*cols_];
		std::cout << "Before copy" << std::endl;
		memcpy(buf_, m_matrix.buf_, sizeof(T)*(rows_ + 1)*(cols_ + 1));
		std::cout << "After copy" << std::endl;
	}

	~Matrix<T>()
	{
		/*delete[] buf_;*/
	}

    void set_size(int rows,int cols)
    {
        buf_ = new T[rows*cols];
        rows_=rows;
        cols_ = cols;
    }

    virtual void SetValue(T *value);

    void test(){
        std::cout<< "second value is :" << *(buf_ + 2 ) << std::endl;
    }

	T* operator()(int a, int b);

	Matrix operator+(Matrix &b_matrix);

	Matrix operator=(Matrix tmp_matrix) {
		return Matrix<T>(tmp_matrix) ;
	}


	
    
protected:
int rows_=0;
    int cols_= 0;
	
	T* buf_;
    

private:

};
template <class T>
void Matrix<T>::SetValue(T *value) {
    if(rows_*cols_  == 0)
    {
        std::cout << "ERROR,matrix size is:" << rows_ << " * " << cols_ << std::endl;
    }
    memcpy(buf_,value,sizeof(T)*rows_*cols_);

}

template <class T>
T* Matrix<T>::operator()(int a, int b)
{
	return (buf_ + a*cols_ + b);
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix &b_matrix)
{
	if(cols_ == b_matrix.cols_ && rows_ == b_matrix.rows_)
	{
		Matrix<T> sum_matrix(cols_, rows_);
		//TODO:parallelization this function.
		for(int x(0);x<rows_;++x)
		{
			for(int y(0);y<cols_;++y)
			{
				*sum_matrix(x, y) = *b_matrix(x, y) + *(buf_ + x*cols_ +y);
			}
		}
		return sum_matrix;
	}
}
