#pragma once

#include <iostream>

class URL
{
public:
	URL(std::string& str);
	std::string get_url();
	unsigned char* get_data(); // unmanaged memory, free yourself
private:
	std::string str;
};