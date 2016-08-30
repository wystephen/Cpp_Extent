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
	
	FileReader fr("jsontest.txt");

	fr.test();

    std::ofstream of("test.csv");

    std::uniform_real_distribution<double> rd;

    std::default_random_engine e;

    int rows(100);
    int cols(100);

    for(int i_x(0);i_x < rows;++i_x)
    {
        for(int i_y(0);i_y < cols;++i_y)
        {
            of << rd(e) ;
            if(i_y != cols-1)
            {
                of<<",";
            }else{
                if(i_x != rows-1)
                {
                    of<<std::endl;
                }

            }
        }
    }

    of.close();

	
	getchar();

	return 0;

}
