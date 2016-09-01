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

	~Matrix<T>()
	{
		delete[] buf_;
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
