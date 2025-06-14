#include "SmallStringOpt.h"
#include <iostream>

void String::free() {
	if (isDynamic())
	{
		delete[] storage.heap.ptr;
	}
	storage.heap.ptr = nullptr;
	storage.heap.size = 0;
}

size_t String::getLenght() const {
	if (isDynamic())
	{
		return storage.heap.size << 1 >> 1;
	}
	return strlen(storage.stack.buff);
}

const char* String::getData() const
{
	if (isDynamic())
	{
		return storage.heap.ptr;
	}
	return storage.stack.buff;
}
char* String::getData()
{
	if (isDynamic())
	{
		return storage.heap.ptr;
	}
	return storage.stack.buff;
}

int String::compare(const String& str) const
{
	return compare(str.getData());
}

int String::compare(const char* str) const
{
	return strcmp(getData(), str);
}

const char* String::c_str() const
{
	if (isDynamic())
		return storage.heap.ptr;
	else
		return storage.stack.buff;
}

void String::copyFrom(const String& other) {
	if (other.isDynamic())
	{
		storage.heap.size = other.storage.heap.size;
		storage.heap.ptr = new char[other.getLenght() + 1];
		strcpy(storage.heap.ptr, other.storage.heap.ptr);
		makeDynamic();
	}
	else
	{
		strcpy(storage.stack.buff, other.storage.stack.buff);
		makeStatic();
	}
}

String::String(const String& other)
{
	free();
	copyFrom(other);
}

String::String(const char* str) {
	saveData(str);
}

String& String::operator=(const String& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

String::~String() {
	free();
}

void String::saveData(const char* str) {
	if (!str)
	{
		throw;
	}
	free();
	size_t len = strlen(str);
	if (len < BUFFER_SIZE)
	{
		strcpy(storage.stack.buff, str);
		makeStatic();
	}
	else {
		storage.heap.ptr = new char[len + 1];
		storage.heap.size = len;
		strcpy(storage.heap.ptr, str);
		makeDynamic();
	}
}

bool String::isDynamic() const {
	return (storage.stack.buff[BUFFER_SIZE - 1] & (1 << 7));
}

size_t String::getSize() const
{
	if (isDynamic())
	{
		return strlen(storage.heap.ptr);
	}
	else {
		return strlen(storage.stack.buff);
	}
}

const char String::operator[](size_t index) const
{
	return at(index);
}

char String::operator[](size_t index)
{
	return at(index);
}

const char String::at(size_t index) const
{
	if (index >= getLenght())
	{
		throw std::out_of_range("Out of range!");
	}
	return getData()[index];
}

char String::at(size_t index)
{
	if (index >= getLenght())
	{
		throw std::out_of_range("Out of range!");
	}
	return getData()[index];
}

String& String::operator+=(const char* rhs)
{
	char* concat = new char[getLenght() + strlen(rhs) + 1];
	strcpy(concat, getData());
	strcat(concat, rhs);
	saveData(concat);
	delete[] concat;
	return *this;
}

String& String::operator+=(const String& rhs)
{
	return operator+=(rhs.getData());
}

void String::makeDynamic() {
	storage.stack.buff[BUFFER_SIZE - 1] |= (1 << 7);
}

void String::makeStatic() {
	storage.stack.buff[BUFFER_SIZE - 1] = '\0';
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.getData();
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[1024];
	is >> buff;
	str.saveData(buff);
	return is;
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs);
	result += rhs;
	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !operator==(lhs, rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) < 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return lhs < rhs || lhs == rhs;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return lhs > rhs || lhs == rhs;
}

bool operator>(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) > 0;
}


