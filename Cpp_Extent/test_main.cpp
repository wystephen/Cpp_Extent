#include <iostream>

#include <thread>
#include <algorithm>


#include "FileReader.h"
#include "JsonCodert.h"

int main()
{
	
	FileReader fr("jsontest.txt");

	fr.test();

	
	
	//JsonCoder jc("{\"number\":1,\"rray\":[],\"null\":null,\"string\":\"leo108\",\"boolean\":true,\"obj\":{},\"level1\":{\"level2\":{\"level3\":{\"level4\":{\"level5\":{\"level6\":{\"level7\":{\"level8\":{}}}}}}}}}");

	JsonCoder jc(fr.GetString());
	std::cout << fr.GetString() << std::endl;
	jc.test();
	

	getchar();
	return 0;

}
