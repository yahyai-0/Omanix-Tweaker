// Ahmed Al-Yahyai
// blackheart10001@gmail.com

#ifndef _STRING_FORMAT_H_
#define  _STRING_FORMAT_H_

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

template <typename T>
		string StringFrom(const T& val)
		{
			stringstream ss;
			ss << val;
			return ss.str();
		}

#endif