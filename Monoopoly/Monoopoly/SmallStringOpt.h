#pragma once
#pragma warning(disable: 4996)
#include <iostream>

struct allocatedMemory {
	char* ptr = nullptr;
	size_t size;
};

const int BUFFER_SIZE = sizeof(allocatedMemory);

struct staticMemory {
	char buff[BUFFER_SIZE];
};

union Storage {
	allocatedMemory heap;
	staticMemory stack;

	Storage() :stack() {}
};

class String {
	Storage storage;
	void free();
	void copyFrom(const String&);
	void makeDynamic();
	void makeStatic();

public:
	size_t getLenght() const;
	String() = default;
	String(const String&);
	String(const char*);
	String& operator=(const String&);
	~String();


	const char* getData() const;
	char* getData();
	void saveData(const char*);
	int compare(const String&) const;
	int compare(const char*) const;
	const char* c_str() const;
	bool isDynamic() const;
	size_t getSize()const;

	const char operator[](size_t index) const;
	char operator[](size_t index);
	const char at(size_t index) const;
	char at(size_t index);

	String& operator+=(const char*);
	String& operator+=(const String&);

	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
};

String operator+(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
bool operator<(const String&, const String&);
bool operator<=(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator>(const String&, const String&);
