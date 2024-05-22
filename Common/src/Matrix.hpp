#pragma once
#include <utility>
#include "IntTypes.h"
#include "Array.hpp"
/// <summary>
/// A wrapper class around primitive arrays, represents a 2D matrix within a 1D array
/// </summary>
template<class T>
class Matrix
{
public:
	Matrix();
	Matrix(const Matrix<T>& other);
	Matrix(Matrix<T>&& other);
	Matrix(size rowLength, size columnLength);
	Matrix(T* matrix, size rowLength, size columnLength);
	~Matrix();
	
	inline size GetRowLength() { return mRowLength; }
	inline size GetColumnLength() { return mColumnLength; }
	inline size GetMatrixSize() { return mMatrixSize; }
	inline bool IsNull() { return mMatrix == nullptr; }
	inline T* GetRawArray() { return mMatrix; }
	inline Matrix<T>&& Move() { return std::move(*this); }

	//cant use [] with multiple arguments in msvc
	T& operator()(size rowIndex, size columnIndex);
	void Dispose();
	void New(size rowLength, size columnLength);
	//Resizes the matrix while keeping its members;
	void Resize(size newRowLength, size newColumnLength);
	Matrix<T>&& Subsect(size rowOffset, size rowSubLength, size columnOffset, size columnSubLength);
	Array<T>&& SubsectByColumns(size columnOffset, size columnSubLength, size rowIndex);
	Array<T>&& SubsectByRows(size rowOffset, size rowSubLength, size columnIndex);

	Matrix<T>& operator=(Matrix<T> other)
	{
		std::swap(mMatrix, other.mMatrix);
		return *this;
	}

	const T& operator()(size rowIndex, size columnIndex) const
	{
		if (mMatrix == nullptr)
		{
			throw "Matrix is empty!";
		}
		if (rowIndex >= mRowLength || columnIndex >= mColumnLength)
		{
			throw "Index out of bounds!";
		}

		return mMatrix[rowIndex * mColumnLength + columnIndex];
	}
private:
	T* mMatrix;
	size mMatrixSize;
	size mColumnLength;
	size mRowLength;
};

#include "Matrix.inl"