#include <iostream>

#include <thread>
#include <algorithm>


#include "FileReader.h"
#include "JsonCodert.h"
#include "JsonObject.h"

int main()
{
	JsonObject job;
	JsonObject t = job["aaa"];
	
	FileReader fr("jsontest.txt");

	fr.test();

	
	
	//JsonCoder jc("{\"number\":1,\"rray\":[],\"null\":null,\"string\":\"leo108\",\"boolean\":true,\"obj\":{},\"level1\":{\"level2\":{\"level3\":{\"level4\":{\"level5\":{\"level6\":{\"level7\":{\"level8\":{}}}}}}}}}");

	JsonCoder
		jc(fr.GetString());

	jc.test();
	

	getchar();
	return 0;

}
