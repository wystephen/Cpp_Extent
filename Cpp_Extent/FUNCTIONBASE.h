#pragma once

template <class ValueType,class FuncValueType,class DrivativeValueType,int VecLen>
class FUNCTIONBASE
{
public:
	FUNCTIONBASE()
	{}

	/*
	This function will return a value according to the function value.
	*/
	virtual FuncValueType operator ()(ValueType val) = 0;


	virtual DrivativeValueType derivative(ValueType val) = 0;

	DrivativeValueType d(ValueType val)
	{
		return derivative(val);
	}

protected:

private:


};