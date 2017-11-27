#pragma once
#include <string>
using namespace std;
class ProcessingRequest
{
public:

	ProcessingRequest();
	~ProcessingRequest();
	string getManager(string requestType);

};