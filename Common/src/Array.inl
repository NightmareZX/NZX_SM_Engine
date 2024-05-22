#pragma once
#include <cstring>

template<class T>
Array<T>::Array()
{
	mArray = nullptr;
	mArrayLength = 0;
}

template<class T>
Array<T>::Array(size length)
{
	mArray = new T[length]();
	mArrayLength = length;
}

template<class T>
Array<T>::Array(const Array& other)
{
	mArrayLength = other.mArrayLength;
	mArray = new T[mArrayLength];
	//for (Size i = 0; i < mArrayLength; i++)
	//{
	//	mArray[i] = other.mArray[i];
	//}
	std::memcpy(mArray, other.mArray, mArrayLength * sizeof(T));
}

template<class T>
Array<T>::Array(Array<T>&& other)
{
	mArray = other.mArray;
	mArrayLength = other.mArrayLength;
	other.mArray = nullptr;
	other.mArrayLength = 0;
}

template<class T>
Array<T>::Array(T* array, size length)
{
	mArray = array;
	mArrayLength = length;
}

template<class T>
Array<T>::~Array()
{
	Dispose();
}

template<class T>
void Array<T>::Dispose()
{
	if (mArray == nullptr) return;
	delete[] mArray;
	mArray = nullptr;
	mArrayLength = 0;
}

template<class T>
void Array<T>::New(size length)
{
	Dispose();
	mArray = new T[length]();
	mArrayLength = length;
}

template<class T>
Array<T>&& Array<T>::Subsect(size offset, size length)
{
	if (offset >= mArrayLength || offset + length >= mArrayLength) { throw "Index out of bounds"; }

	T* subsectArray = new T[length];

	//for (Size i = 0; i < length; i++)
	//{
	//	subsectArray[i] = mArray[i + offset];
	//}
	std::memcpy(subsectArray, mArray + offset, length * sizeof(T));

	return Array<T>(subsectArray, length).Move();
}

template<class T>
T& Array<T>::operator[](size index)
{
	if (index >= mArrayLength) { throw "Index out of bounds!"; }
	if (mArray == nullptr) { throw "Array is empty!"; }
	return mArray[index];
}