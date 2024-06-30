#include "Utils.h"

#include <cstdarg>
#include <cstdlib>


Error& Error::get()
{
	static Error err;
	return err;
}


int Error::set(int code, const char* format, ...)
{
	Error& err = get();
	err._code = code;

	if (!format)
		return 0;

	va_list ap;
	va_start(ap, format);
	vsnprintf(err._msg, msg_size, format, ap);
	va_end(ap);

	return 0;
}


const int Error::code()
{
	return get()._code;
}


const char* Error::msg()
{
	return get()._msg;
}