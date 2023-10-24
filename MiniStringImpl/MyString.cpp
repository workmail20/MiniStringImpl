#include "MyString.h"

myString::myString()
{
	length = 0;
	mem_struct = mem_get(length + 1);
	data = mem_struct.pointer;
	if (data != NULL)data[0] = '\0';
}

myString::myString(char c)
{
	length = 0;
	mem_struct = mem_get(length + 2);
	data = mem_struct.pointer;
	if (data != NULL) {
		length = 1;
		data[0] = c;
		data[length] = '\0';
	}
}



myString::myString(const char* c)
{
	length = 0;
	if (c != NULL) {
		unsigned n = 0;
		while (c[n] != '\0') n++;
		mem_struct = mem_get(n + 1);
		data = mem_struct.pointer;
		if (data != NULL) {
			for (unsigned j = 0; j < n; j++)
				data[j] = c[j];
			length = n;
			data[length] = '\0';
		}
	}
	else {
		mem_struct = mem_get(length + 1);
		data = mem_struct.pointer;
		if (data != NULL)data[0] = '\0';
	}
}

myString::myString(const myString& s)
{
	length = 0;
	int n = s.len();
	mem_struct = mem_get(n + 1);
	data = mem_struct.pointer;
	if (data != NULL) {
		for (unsigned j = 0; j < n; j++)
			data[j] = s[j];
		length = n;
		data[length] = '\0';
	}
}



myString::~myString()
{
	length = 0;
	mem_free(mem_struct);
	data = NULL;
}

bool myString::resize(DWORD size) {
	if (size <= length) {
		length = size;
		data[length] = '\0';
		return true;
	}
	else {
		length = 0;
		data = NULL;

		mem_struct = mem_get(size + 1, &mem_struct);
		data = mem_struct.pointer;
		if (data != NULL) {
			length = size;
			data[length] = '\0';
			return true;
		}
	}
	return false;
}


void myString::assign(const char* c, int size)
{
	length = 0;
	if (c != NULL) {
		if (size > -1) {
			unsigned n = size;
			mem_struct = mem_get(n + 1, &mem_struct);
			data = mem_struct.pointer;
			if (data != NULL) {
				for (unsigned j = 0; j < n; j++)
					data[j] = c[j];
				length = n;
				data[length] = '\0';
			}
		}
		else {
			unsigned n = 0;
			while (c[n] != '\0') n++;
			mem_struct = mem_get(n + 1, &mem_struct);
			data = mem_struct.pointer;
			if (data != NULL) {
				for (unsigned j = 0; j < n; j++)
					data[j] = c[j];
				length = n;
				data[length] = '\0';
			}
		}

	}
	else {
		length = 0;
		mem_struct = mem_get(length + 1, &mem_struct);
		data = mem_struct.pointer;
		if (data != NULL)data[length] = '\0';
	}
}

int myString::find(const myString& s) {
	int res = -1;
	int LenSubStr = s.len();
	if ((LenSubStr > 0) && (length > 0)) {
		int Len = length - LenSubStr;
		int I = 0;
		int X;
		while (I <= Len) {
			if (data[I] == s[0]) {
				X = 1;
				while ((X < LenSubStr) && (data[I + X] == s[X]))X++;
				if (X == LenSubStr) {
					res = I;
					return res;
				}
			}
			I++;
		}
	}
	return res;
}

int myString::find(const char* c) {
	int res = -1;
	if (c != NULL) {
		int LenSubStr = 0;
		while (c[LenSubStr] != '\0') LenSubStr++;
		if ((LenSubStr > 0) && (length > 0)) {
			int Len = length - LenSubStr;
			int I = 0;
			int X;
			while (I <= Len) {
				if (data[I] == c[0]) {
					X = 1;
					while ((X < LenSubStr) && (data[I + X] == c[X]))X++;
					if (X == LenSubStr) {
						res = I;
						return res;
					}
				}
				I++;
			}
		}
	}
	return res;
}

unsigned myString::len() const
{
	return length;
}

char myString::operator[] (unsigned j) const
{
	if (j >= length) return 0;
	return data[j];
}

myString& myString::operator= (const myString& s)
{
	if (this == &s) return *this;
	length = 0;
	int n = s.len();
	if (n > 0) {
		mem_struct = mem_get(n + 1, &mem_struct);
		data = mem_struct.pointer;
		if (data != NULL) {
			for (unsigned j = 0; j < n; j++)
				data[j] = s[j];
			length = n;
			data[length] = '\0';
		}
	}
	return *this;
}



myString& myString::operator+= (const myString& s)
{

	int len = length + s.len();
	if (len > 0) {
		if (len + 1 < mem_struct.size) {
			for (unsigned i = 0; i < s.len(); i++)
				mem_struct.pointer[length + i] = s[i];

			length = len;
			data = mem_struct.pointer;
			data[length] = '\0';
			return *this;
		}
		else {
			mem_alloc tmp_mem = mem_get(len + 1);

			if (tmp_mem.pointer != NULL) {
				for (unsigned j = 0; j < length; j++)
					tmp_mem.pointer[j] = data[j];

				for (unsigned i = 0; i < s.len(); i++)
					tmp_mem.pointer[length + i] = s[i];

				mem_free(mem_struct);
				data = NULL;

				mem_struct = tmp_mem;
				length = len;
				data = tmp_mem.pointer;
				data[length] = '\0';
			}
		}
	}
	return *this;
}



myString operator+ (const myString& lhs, const myString& rhs)
{
	return myString(lhs) += rhs;
}

myString operator+ (const myString& lhs, char rhs)
{
	return myString(lhs) += myString(rhs);
}

myString operator+ (const myString& lhs, const char* rhs)
{
	return myString(lhs) += myString(rhs);
}

myString operator+ (char lhs, const myString& rhs)
{
	return myString(lhs) += rhs;
}
myString operator+ (const char* lhs, const myString& rhs)
{
	return myString(lhs) += rhs;
}


bool operator== (const myString& lhs, const myString& rhs)
{
	if (lhs.len() != rhs.len()) return false;

	int cap = lhs.len();
	int   n = 0;
	while ((n < cap) && (lhs[n] == rhs[n])) n++;
	return (n == cap);
}

bool operator== (const myString& lhs, char rhs)
{
	return (lhs == myString(rhs));
}

bool operator== (const myString& lhs, const char* rhs)
{
	return (lhs == myString(rhs));
}

bool operator== (char lhs, const myString& rhs)
{
	return (myString(lhs) == rhs);
}

bool operator== (const char* lhs, const myString& rhs)
{
	return (myString(lhs) == rhs);
}



myWString::myWString()
{
	length = 0;
	mem_struct = mem_get(length + 2);
	data = (PWCHAR)mem_struct.pointer;
	if (data != NULL)data[0] = L'\0';
}

myWString::myWString(WCHAR c)
{
	length = 0;
	mem_struct = mem_get(length + 4);
	data = (PWCHAR)mem_struct.pointer;
	if (data != NULL) {
		length = 1;
		data[0] = c;
		data[length] = L'\0';
	}
}

myWString::myWString(const WCHAR* c)
{
	length = 0;
	if (c != NULL) {
		unsigned n = 0;
		while (c[n] != L'\0') n++;
		mem_struct = mem_get(n * 2 + 2);
		data = (PWCHAR)mem_struct.pointer;
		if (data != NULL) {
			for (unsigned j = 0; j < n; j++)
				data[j] = c[j];
			length = n;
			data[length] = L'\0';
		}
	}
	else {
		mem_struct = mem_get(length + 2);
		data = (PWCHAR)mem_struct.pointer;
		if (data != NULL)data[0] = L'\0';
	}
}

myWString::myWString(const myWString& s)
{
	length = 0;
	int n = s.len();
	mem_struct = mem_get(n * 2 + 2);
	data = (PWCHAR)mem_struct.pointer;
	if (data != NULL) {
		for (unsigned j = 0; j < n; j++)
			data[j] = s[j];
		length = n;
		data[length] = L'\0';
	}
}



myWString::~myWString()
{
	length = 0;
	mem_free(mem_struct);
	data = NULL;
}

bool myWString::resize(DWORD size) {
	if (size <= length) {
		length = size;
		data[length] = L'\0';
		return true;
	}
	else {
		length = 0;
		data = NULL;

		mem_struct = mem_get(size * 2 + 2, &mem_struct);
		data = (PWCHAR)mem_struct.pointer;
		if (data != NULL) {
			length = size;
			data[length] = L'\0';
			return true;
		}
	}
	return false;
}

void myWString::assign(const WCHAR* c, int size)
{
	length = 0;
	if (c != NULL) {
		if (size > -1) {
			unsigned n = size;
			mem_struct = mem_get(n * 2 + 2, &mem_struct);
			data = (PWCHAR)mem_struct.pointer;
			if (data != NULL) {
				for (unsigned j = 0; j < n; j++)
					data[j] = c[j];
				length = n;
				data[length] = L'\0';
			}
		}
		else {
			unsigned n = 0;
			while (c[n] != L'\0') n++;
			mem_struct = mem_get(n * 2 + 2, &mem_struct);
			data = (PWCHAR)mem_struct.pointer;
			if (data != NULL) {
				for (unsigned j = 0; j < n; j++)
					data[j] = c[j];
				length = n;
				data[length] = L'\0';
			}
		}

	}
	else {
		length = 0;
		mem_struct = mem_get(length + 2, &mem_struct);
		data = (PWCHAR)mem_struct.pointer;
		if (data != NULL)data[length] = L'\0';
	}
}

int myWString::find(const myWString& s) {
	int res = -1;
	int LenSubStr = s.len();
	if ((LenSubStr > 0) && (length > 0)) {
		int Len = length - LenSubStr;
		int I = 0;
		int X;
		while (I <= Len) {
			if (data[I] == s[0]) {
				X = 1;
				while ((X < LenSubStr) && (data[I + X] == s[X]))X++;
				if (X == LenSubStr) {
					res = I;
					return res;
				}
			}
			I++;
		}
	}
	return res;
}

int myWString::find(const WCHAR* c) {
	int res = -1;
	if (c != NULL) {
		int LenSubStr = 0;
		while (c[LenSubStr] != L'\0') LenSubStr++;
		if ((LenSubStr > 0) && (length > 0)) {
			int Len = length - LenSubStr;
			int I = 0;
			int X;
			while (I <= Len) {
				if (data[I] == c[0]) {
					X = 1;
					while ((X < LenSubStr) && (data[I + X] == c[X]))X++;
					if (X == LenSubStr) {
						res = I;
						return res;
					}
				}
				I++;
			}
		}
	}
	return res;
}

unsigned myWString::len() const
{
	return length;
}

WCHAR myWString::operator[] (unsigned j) const
{
	if (j >= length) return 0;
	return data[j];
}

myWString& myWString::operator= (const myWString& s)
{
	if (this == &s) return *this;
	length = 0;
	int n = s.len();
	if (n > 0) {
		mem_struct = mem_get(n * 2 + 2, &mem_struct);
		data = (PWCHAR)mem_struct.pointer;
		if (data != NULL) {
			for (unsigned j = 0; j < n; j++)
				data[j] = s[j];
			length = n;
			data[length] = L'\0';
		}
	}
	return *this;
}



myWString& myWString::operator+= (const myWString& s)
{

	int len = length + s.len();
	if (len > 0) {
		if ((len * 2) + 2 < mem_struct.size) {
			for (unsigned i = 0; i < s.len(); i++)
				PWCHAR(mem_struct.pointer)[length + i] = s[i];

			length = len;
			data = (PWCHAR)mem_struct.pointer;
			data[length] = L'\0';
			return *this;
		}
		else {
			mem_alloc tmp_mem = mem_get(len * 2 + 2);

			if (tmp_mem.pointer != NULL) {
				for (unsigned j = 0; j < length; j++)
					PWCHAR(tmp_mem.pointer)[j] = data[j];

				for (unsigned i = 0; i < s.len(); i++)
					PWCHAR(tmp_mem.pointer)[length + i] = s[i];

				mem_free(mem_struct);
				data = NULL;

				mem_struct = tmp_mem;
				length = len;
				data = (PWCHAR)tmp_mem.pointer;
				data[length] = L'\0';
			}
		}
	}
	return *this;
}


myWString operator+ (const myWString& lhs, const myWString& rhs)
{
	return myWString(lhs) += rhs;
}

myWString operator+ (const myWString& lhs, WCHAR rhs)
{
	return myWString(lhs) += myWString(rhs);
}

myWString operator+ (const myWString& lhs, const WCHAR* rhs)
{
	return myWString(lhs) += myWString(rhs);
}

myWString operator+ (WCHAR lhs, const myWString& rhs)
{
	return myWString(lhs) += rhs;
}
myWString operator+ (const WCHAR* lhs, const myWString& rhs)
{
	return myWString(lhs) += rhs;
}


bool operator== (const myWString& lhs, const myWString& rhs)
{
	if (lhs.len() != rhs.len()) return false;

	int cap = lhs.len();
	int   n = 0;
	while ((n < cap) && (lhs[n] == rhs[n])) n++;
	return (n == cap);
}

bool operator== (const myWString& lhs, WCHAR rhs)
{
	return (lhs == myWString(rhs));
}

bool operator== (const myWString& lhs, const WCHAR* rhs)
{
	return (lhs == myWString(rhs));
}

bool operator== (WCHAR lhs, const myWString& rhs)
{
	return (myWString(lhs) == rhs);
}

bool operator== (const WCHAR* lhs, const myWString& rhs)
{
	return (myWString(lhs) == rhs);
}