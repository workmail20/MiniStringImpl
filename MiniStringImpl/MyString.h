#ifndef MYSTRING_H
#define MYSTRING_H
#include "windows.h"
#include "mem_manager.h"

class myString
{
	int length;  /*!< The number of characters allocated in data */
public:
	PCHAR    data;    /*!< The ASCII characters that comprise the String */
	mem_alloc	mem_struct;

	myString();

	myString(char c);

	
	myString(const char* c);
	myString(const myString& s);
	~myString();

	unsigned len() const;

	int find(const myString& s);
	int find(const char* c);
	void assign(const char* c, int size = -1);

	bool resize(DWORD size);
	char  operator[] (unsigned j) const;

	myString& operator= (const myString& s);

	myString& operator+= (const myString& s);

	friend myString operator+ (const myString& lhs, const myString& rhs);
	friend myString operator+ (const myString& lhs, char          rhs);
	friend myString operator+ (const myString& lhs, const char* rhs);
	friend myString operator+ (char          lhs, const myString& rhs);
	friend myString operator+ (const char* lhs, const myString& rhs);

	friend bool operator== (const myString& lhs, const myString& rhs);
	friend bool operator== (const myString& lhs, char          rhs);
	friend bool operator== (const myString& lhs, const char* rhs);
	friend bool operator== (char          lhs, const myString& rhs);
	friend bool operator== (const char* lhs, const myString& rhs);

};

typedef myString* PmyString;

class myWString
{
	int length;  

public:
	PWCHAR    data;  
	mem_alloc	mem_struct;

	myWString();

	myWString(WCHAR c);

	myWString(const WCHAR* c);

	myWString(const myWString& s);

	~myWString();

	unsigned len() const;

	int find(const myWString& s);
	int find(const WCHAR* c);
	void assign(const WCHAR* c, int  size = -1);

	bool resize(DWORD size);

	WCHAR  operator[] (unsigned j) const;

	myWString& operator= (const myWString& s);

	myWString& operator+= (const myWString& s);

	friend myWString operator+ (const myWString& lhs, const myWString& rhs);
	friend myWString operator+ (const myWString& lhs, WCHAR          rhs);
	friend myWString operator+ (const myWString& lhs, const WCHAR* rhs);
	friend myWString operator+ (WCHAR          lhs, const myWString& rhs);
	friend myWString operator+ (const WCHAR* lhs, const myWString& rhs);

	friend bool operator== (const myWString& lhs, const myWString& rhs);
	friend bool operator== (const myWString& lhs, WCHAR          rhs);
	friend bool operator== (const myWString& lhs, const WCHAR* rhs);
	friend bool operator== (WCHAR          lhs, const myWString& rhs);
	friend bool operator== (const WCHAR* lhs, const myWString& rhs);
};
typedef myWString* PmyWString;

#endif