#include <iostream>

#include <thread>
#include <algorithm>


#include "FileReader.h"

int main()
{
	FileReader fr("jsontest.txt");

	fr.test();

	getchar();

}
