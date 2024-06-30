#ifndef UTILS_H
#define UTILS_H

#include <iostream>


class Error
{
	enum { msg_size = 512 };

public:
	
	static int set(int code, const char* format, ...);
	static const int code();
	static const char* msg();

private:
	Error() : _code(0) {};

	static Error& get();

	int _code;
	char _msg[msg_size] = {0};
};


#ifndef DEBUG
	#define THISLOG(msg)
	#define LOG(msg)
#else
	#define THISLOG(msg) std::cout << "[" << this << "] " << (msg) << "\n";
	#define LOG(msg) std::cout << (msg) << "\n";
#endif


#endif