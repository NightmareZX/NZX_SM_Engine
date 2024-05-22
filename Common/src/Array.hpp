#pragma once
#include <utility>
#include "IntTypes.h"
/// <summary>
/// A wrapper class around primitive arrays
/// </summary>
template<class T>
class Array
{
private:
	T* mArray;
	size mArrayLength;
public:
	Array();
	Array(size length);
	Array(const Array<T>& other);
	Array(Array<T>&& other);
	//Takes ownership of the array
	Array(T* array, size length);
	~Array();

	bool IsEmpty() { return mArray == nullptr; }
	size GetLength() { return mArrayLength; }
	T* GetRawArray() { return mArray; }
	Array<T>&& Move() { return std::move(*this); }

	T& operator[](size index);
	void Dispose();
	void New(size length);
	Array<T>&& Subsect(size offset, size length);

	Array<T>& operator=(Array<T> other)
	{
		std::swap(mArray, other.mArray);
		return *this;
	}
};

#include "Array.inl"

