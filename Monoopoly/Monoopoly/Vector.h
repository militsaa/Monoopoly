#pragma once

template<typename T>
class Vector {
	size_t size;
	size_t capacity;
	T* data;
	void free();
	void copyFrom(const Vector<T>&);
	void resize(size_t);

public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector <T>&);
	Vector<T>& operator=(const Vector<T>&);
	~Vector();

	void push_back(const T&);
	bool empty() const;
	void clear();
	T* insert(int, const T&);
	void pop_back();
	T* erase(size_t);
	T* erase(size_t, size_t);
	size_t getSize() const;
	T& at(size_t);
	const T& at(size_t) const;

	T& operator[](size_t);
	const T& operator[](size_t) const;
};

#include <iostream>


template<typename T>
void Vector<T>::free()
{
	delete[] data;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	data = new T[other.capacity];
	size = other.size;
	capacity = other.capacity;
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::resize(size_t capacity)
{
	this->capacity = capacity;
	T* buff = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		if (capacity == i) {
			size = capacity;
			break;
		}
		buff[i] = data[i];
	}
	delete[] data;
	data = buff;
}

template<typename T>
Vector<T>::Vector()
{
	capacity = 8;
	size = 0;
	data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(size_t capacity)
{
	this->capacity = capacity;
	data = new T[capacity];
	size = 0;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::push_back(const T& element)
{
	if (size == capacity)
	{
		if (capacity == 0)
		{
			capacity = 4;
		}
		resize(capacity * 2);
	}
	data[size++] = element;
}

template<typename T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template<typename T>
void Vector<T>::clear()
{
	free();
}

template<typename T>
T* Vector<T>::insert(int index, const T& element)
{
	if (index >= size && size)
	{
		throw std::out_of_range("Out of range!");
	}
	if (size == capacity)
	{
		resize(capacity * 2);
	}
	for (int i = size; i > index; i--)
	{
		data[i] = data[i - 1];
	}
	data[index] = element;
	size++;
	return &data[index];
}

template<typename T>
void Vector<T>::pop_back()
{
	size--;
}

template<typename T>
T* Vector<T>::erase(size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Out of range!");
	}
	for (size_t i = index; i < size; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
	return &data[index];
}

template<typename T>
T* Vector<T>::erase(size_t from, size_t to)
{
	if (from >= size || to >= size || from > to)
	{
		throw std::out_of_range("Out of range!");
	}
	for (size_t i = 0; i < size - to; i++)
	{
		data[from + i] = data[to + 1 + i];
	}
	size -= (to - from + 1);
	return data;
}

template<typename T>
size_t Vector<T>::getSize() const
{
	return size;
}

template<typename T>
T& Vector<T>::at(size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Out of range!");
	}
	return data[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Out of range!");
	}
	return data[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
	return at(index);
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return at(index);
}


