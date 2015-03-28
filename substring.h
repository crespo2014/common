/*
 * substring.h
 *
 *  Created on: 26 Mar 2015
 *      Author: lester
 */

#ifndef SUBSTRING_H_
#define SUBSTRING_H_

#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <stdarg.h>
#include <map>
#include <exception>
#include <stdexcept>

#include <vector>
#include <iostream>

/**
 * SubString is a object to manage a const string
 * It is useful for getting substrings inside const string, allowing easier string comparison.
 * members of class are char pointer and size,
 * pointer can be null.
 * size being zero inidcated that string is zero end
 */
class SubString
{
	const char* start;    //!< pointer to first character of string
	size_t len;         //!< size of string
public:
	//! Copy constructor
	SubString(const SubString &str) :
			start(str.start), len(str.len)
	{

	}
	//!Copy assignment
	SubString& operator=(const SubString& n_s)
	{
		start = n_s.start;
		len = n_s.len;
		return *this;
//        new (this) SubString(n_s);
//        return *this;
	}
	/** Constructor specifying start and end positions of string to get the substring.
	 * @param [in] start - the pointer to the starting position of the const string
	 * @param [in] end - the past-the-last pointer for the sub string
	 */
	SubString(const char* start, const char* end) :
			start(start), len(end - start)
	{

	}
	/** Constructor from a null terminated string
	 * @param [in] start - the pointer to the starting position of the null terminated string
	 */
	SubString(const char* start) :
			start(start), len(strlen(start))
	{

	}
	/** Constructor using start char and len
	 * @param [in] start - the pointer to the starting position of the string
	 * @param [in] len - the size in bytes for the sub string
	 */
	SubString(const char* start, size_t len) :
			start(start), len(len)
	{

	}
	/** Implicit conversion to std::string
	 */
	operator std::string() const
	{
		return getString();
	}
	/// len will be calculate when it needed if it is zero
	size_t length() const
	{
		return len;
	}
	// get a std::string representation
	std::string getString() const
	{
		return
		{	start,len};
	}
	 /// destructor nothing to clear
	~SubString()
	{
	}
	/** Equal-to operator for a null terminated string
	 * @param str - a null terminated string
	 * @return bool - true if equal, else false.
	 */
	bool operator ==(const char* str) const
	{
		return str && (strncmp(str, start, len) == 0) && str[len] == 0;
	}
	/// Compare again string
	bool operator ==(const std::string str) const
	{
		return len == str.length() && str.compare(0,len,start);
	}

	/** Equal-to operator SubString object
	 * @param str - a SubString object
	 * @return bool - true if equal, else false.
	 */
	bool operator ==(const SubString & str) const
	{
		return len == str.len && strncmp(str.start, start, len) == 0;
	}
	/** Not-Equal-to operator for a null terminated string
	 * @param str - a null terminated string
	 * @return bool - true if not equal, else false.
	 */
	bool operator !=(const char* str) const
	{
		return !(operator ==(str));
	}
	/**Get the len of the string contained in the class
	 * @return size_t - the size of the SubString in bytes
	 */
	size_t size() const
	{
		return len;
	}
	/** Get a pointer to the first character in the SubString
	 * @return char* - the pointer to the first char
	 */
	const char* begin() const
	{
		return start;
	}
	/** Get a pointer to the past-the-last character in the SubString
	 * @return char* - the pointer to the past-the-last char
	 */
	const char* end() const
	{
		return start + len;
	}
	/**
	 * Insertion operator implementation
	 */
	friend std::ostream& operator<<(std::ostream &out, const SubString &str)
	{
		return out.write(str.start, str.len);
	}
};

#endif /* SUBSTRING_H_ */
