#include <iostream>

#include <thread>
#include <algorithm>


#include <random>

#include "FileReader.h"
#include "JsonCodert.h"
#include "JsonObject.h"

int main()
{
	//JsonObject job;
	//JsonObject t = job["aaa"];
	
	FileReader fr("test.csv");

	fr.test();



    //Standard radom engine.
//    std::uniform_real_distribution<double> rd;
//
//    std::default_random_engine e;
    //std::cout << rd(e) << std::endl;



	
	getchar();

	return 0;

}
