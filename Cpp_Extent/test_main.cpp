#include <iostream>

#include <thread>
#include <algorithm>


#include <random>

#include "FileReader.h"
#include "JsonCodert.h"
#include "JsonObject.h"
#include "CSVReader.h"



int main()
{
	//JsonObject job;
	//JsonObject t = job["aaa"];
	
	CSVReader fr(std::string("u1.csv"));

	fr.test1();

	CSVReader magic(std::string("magicmatrix.csv"));
	Matrix<double> src_m(magic.GetMatrix());

	CSVReader inv(std::string("pinv.csv"));
	Matrix<double> inv_m(inv.GetMatrix());




	
	getchar();

	return 0;

}
