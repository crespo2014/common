/*
 * formatstring.h
 * This is a on fly formated string object.
 *
 *  Created on: 29 Mar 2015
 *      Author: lester
 */

#ifndef FORMATSTRING_H_
#define FORMATSTRING_H_

/**
 * A object to create a formatted string on fly
 */
class FormatString: public std::ostringstream
{
public:
	FormatString()
	{
	}
	template<class T>
	FormatString& operator<<(const T& t)
	{
		static_cast<std::ostringstream&>(*this) << t;
		return *this;
	}
	operator std::string()
	{
		return std::ostringstream::str();
	}
};

#define TYPE_NAME(x) #x

#endif /* FORMATSTRING_H_ */
