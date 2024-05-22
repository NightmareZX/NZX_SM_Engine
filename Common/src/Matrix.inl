#pragma once

template<class T>
Matrix<T>::Matrix()
{
	mMatrix = nullptr;
	mMatrixSize = 0;
	mColumnLength = 0;
	mRowLength = 0;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	mRowLength = other.mRowLength;
	mColumnLength = other.mColumnLength;
	mMatrixSize = other.mMatrixSize;
	mMatrix = new T[mMatrixSize];

	//for (Size i = 0; i < mMatrixSize; i++)
	//{
	//	mMatrix[i] = other.mMatrix[i];
	//}
	std::memcpy(mMatrix, other.mMatrix, mMatrixSize * sizeof(T));
}

template<class T>
Matrix<T>::Matrix(Matrix<T>&& other)
{
	mRowLength = other.mRowLength;
	mColumnLength = other.mColumnLength;
	mMatrixSize = other.mMatrixSize;
	mMatrix = other.mMatrix;

	other.mMatrix = nullptr;
	other.mMatrixSize = 0;
	other.mRowLength = 0;
	other.mColumnLength = 0;
}

template<class T>
Matrix<T>::Matrix(size rowLength, size columnLength)
{
	mMatrixSize = rowLength * columnLength;
	mRowLength = rowLength;
	mColumnLength = columnLength;
	mMatrix = new T[mMatrixSize]();
}

template<class T>
Matrix<T>::Matrix(T* matrix, size rowLength, size columnLength)
{
	mMatrixSize = rowLength * columnLength;
	mRowLength = rowLength;
	mColumnLength = columnLength;
	mMatrix = matrix;
}

template<class T>
Matrix<T>::~Matrix()
{
	Dispose();
}

template<class T>
T& Matrix<T>::operator()(size rowIndex, size columnIndex)
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
template<class T>
void Matrix<T>::Dispose()
{
	if (mMatrix == nullptr) return;
	delete[] mMatrix;
	mMatrix = nullptr;
	mMatrixSize = 0;
	mRowLength = 0;
	mColumnLength = 0;
}

template<class T>
void Matrix<T>::New(size rowLength, size columnLength)
{
	Dispose();
	mMatrixSize = rowLength * columnLength;
	mRowLength = rowLength;
	mColumnLength = columnLength;
	mMatrix = new T[mMatrixSize]();
}

template<class T>
void Matrix<T>::Resize(size newRowLength, size newColumnLength)
{
	if (newRowLength < 1 || newColumnLength < 1) return;
	if (IsNull())
	{
		New(newRowLength, newColumnLength);
		return;
	}

	T* temp = new T[newRowLength * newColumnLength]();

	size nrow = (mRowLength > newRowLength) ? newRowLength : mRowLength;
	size ncol = (mColumnLength > newColumnLength) ? newColumnLength : mColumnLength;

	for (size row = 0; row < nrow; row++)
	{
		for (size column = 0; column < ncol; column++)
		{
			temp[row * newColumnLength + column] = mMatrix[row * newColumnLength + column];
		}
	}
	Dispose();
	mMatrix = temp;
	mRowLength = newRowLength;
	mColumnLength = newColumnLength;
	mMatrixSize = newColumnLength * newRowLength;
}

template<class T>
Matrix<T>&& Matrix<T>::Subsect(size rowOffset, size rowSubLength, size columnOffset, size columnSubLength)
{
	if (rowOffset + rowSubLength > mRowLength || columnOffset + columnSubLength > mColumnLength)
	{
		throw "Subsection indices out of bounds!";
	}

	T* subsectMatrix = new T[rowSubLength * columnSubLength];

	for (size row = 0; row < rowSubLength; row++)
	{
		for (size column = 0; column < columnSubLength; column++)
		{
			subsectMatrix[row * columnSubLength + column] = mMatrix[(row + rowOffset) * mColumnLength + (column + columnOffset)];
		}
	}

	return Matrix<T>(subsectMatrix, rowSubLength, columnSubLength).Move();
}

template<class T>
Array<T>&& Matrix<T>::SubsectByColumns(size columnOffset, size columnSubLength, size rowIndex)
{
	if (columnOffset + columnSubLength > mColumnLength || rowIndex >= mRowLength)
	{
		throw "Index out of bounds";
	}

	T* subsectArray = new T[columnSubLength];

	//for (Size i = 0; i < columnSubLength; i++)
	//{
	//	subsectArray[i] = mMatrix[rowIndex * mColumnLength + (i + columnOffset)];
	//}
	std::memcpy(subsectArray, mMatrix + rowIndex * mColumnLength + columnOffset, columnSubLength * sizeof(T));


	return Array<T>(subsectArray, columnSubLength).Move();
}

template<class T>
Array<T>&& Matrix<T>::SubsectByRows(size rowOffset, size rowSubLength, size columnIndex)
{
	if (rowOffset + rowSubLength > mColumnLength || columnIndex >= mRowLength)
	{
		throw "Index out of bounds";
	}

	T* subsectArray = new T[rowSubLength];

	for (size i = 0; i < rowSubLength; i++)
	{
		subsectArray[i] = mMatrix[(rowOffset + i) * mColumnLength + columnIndex];
	}
	//std::memcpy(subsectArray, mMatrix + rowOffset * mColumnLength + columnIndex, rowSubLength * sizeof(T));

	return Array<T>(subsectArray, rowSubLength).Move();
}