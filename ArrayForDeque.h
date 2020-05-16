#ifndef ARRAYFORDEQUE_H_
#define ARRAYFORDEQUE_H_

#include "ArrayOptions.h"
#include "MyExceptions.h"
#include <iostream>

template <typename T>
class ArrayForDeque
{
public:
	ArrayForDeque() : arrayForDec{ nullptr }, sizeOfArr{ 0 } {}
	ArrayForDeque(unsigned long int);
	ArrayForDeque(const ArrayForDeque<T>&);
	~ArrayForDeque() { delete[] arrayForDec; };
	void pushFront(T);
	void pushBack(T);
	T getAndDelFromEnd();
	T getAndDelFromBeginning();
	T getFront();
	T getBack();
	bool isEmpty();
	unsigned long int len() { return sizeOfArr; }
	void deleteAll();
	void deleteByIndex(unsigned long int);
	T* getSubsequenceByIndexes(unsigned long int, unsigned long int);
	void Sort();
	ArrayForDeque<T>& operator+(ArrayForDeque<T>&);
	ArrayOptions<T>& operator[](unsigned long int);
	long int getIndexByValue(T);
	void setValueByIndex(T, unsigned long int );
	T &getValueByIndex(unsigned long int);
	bool operator==(const ArrayForDeque<T>&); 
	bool operator!=(const ArrayForDeque<T>&);
	ArrayForDeque<T>& operator=(const ArrayForDeque<T>&);
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, const ArrayForDeque<T>&);
private:
	ArrayOptions<T>* arrayForDec;
	unsigned long int sizeOfArr;
};

template <typename T>
ArrayForDeque<T>::ArrayForDeque(unsigned long int n)
{
	arrayForDec = new ArrayOptions<T>[n];
	sizeOfArr = n;
}

template <typename T>
ArrayForDeque<T>::ArrayForDeque(const ArrayForDeque<T>& arrayToCopy) {
	arrayForDec = new ArrayOptions<T>[arrayToCopy.sizeOfArr];
	for (unsigned long int i = 0; i < arrayToCopy.sizeOfArr; ++i) {
		arrayForDec[i] = arrayToCopy.arrayForDec[i];
	}
	sizeOfArr = arrayToCopy.sizeOfArr;
}

template <typename T>
void ArrayForDeque<T>::pushBack(T itemToAdd) {
	if (sizeOfArr == 0) {
		arrayForDec = new ArrayOptions<T>[1];
		arrayForDec[0] = itemToAdd;
		++sizeOfArr;
	}
	else {
		ArrayForDeque<T> temp(*this);
		delete[] arrayForDec;
		arrayForDec = new ArrayOptions<T>[sizeOfArr + 1];
		for (unsigned long int i = 0; i < sizeOfArr; ++i) {
			arrayForDec[i] = temp[i];
		}
		arrayForDec[sizeOfArr] = itemToAdd;
		++sizeOfArr;
	}
}

template <typename T>
void ArrayForDeque<T>::pushFront(T itemToAdd) {
	if (sizeOfArr == 0) {
		++sizeOfArr;
		arrayForDec = new ArrayOptions<T>[1];
		arrayForDec[0] = itemToAdd;
	}
	else {
		ArrayForDeque<T> temp(*this);
		delete[] arrayForDec;
		arrayForDec = new ArrayOptions<T>[sizeOfArr + 1];
		arrayForDec[0] = itemToAdd;
		for (unsigned long int i = 0; i < sizeOfArr; ++i) {
			arrayForDec[i + 1] = temp[i];
		}
		++sizeOfArr;
	}
}

template <typename T>
T ArrayForDeque<T>::getAndDelFromBeginning() {
	ArrayForDeque<T> temp(*this);
	delete[] arrayForDec;
	arrayForDec = new ArrayOptions<T>[sizeOfArr - 1];
	for (unsigned long int i = 0; i < sizeOfArr - 1; ++i) {
		arrayForDec[i] = temp[i + 1];
	}
	--sizeOfArr;
	return temp[0].getValue();
}

template <typename T>
T ArrayForDeque<T>::getAndDelFromEnd() {
	ArrayForDeque<T> temp(*this);
	delete[] arrayForDec;
	--sizeOfArr;
	arrayForDec = new ArrayOptions<T>[sizeOfArr];
	for (unsigned long int i = 0; i < sizeOfArr; ++i) {
		arrayForDec[i] = temp[i];
	}
	return temp[sizeOfArr].getValue();
}

template <typename T>
bool ArrayForDeque<T>::isEmpty() {
	if (sizeOfArr) {
		return false;
	}
	else {
		return true;
	}
}

template <typename T>
T ArrayForDeque<T>::getFront() {
	if (this->isEmpty()) {
		throw ArrayExcepton(R"(нельзя получить данные из пустого массива!)");
	}
	else {
		return arrayForDec[0].getValue();
	}
}

template <typename T>
T ArrayForDeque<T>::getBack() {
	if (this->isEmpty()) {
		throw ArrayExcepton(R"(нельзя получить данные из пустого массива!)");
	}
	else {
		return arrayForDec[sizeOfArr - 1].getValue();
	}
}

template <typename T>
void ArrayForDeque<T>::deleteAll() {
	if (!this->isEmpty()) {
		delete[] arrayForDec;
		sizeOfArr = 0;
	}
	else {
		throw ArrayExcepton(R"(невозможно удалить пустой массив!)");
	}
}

template<typename T>
void ArrayForDeque<T>::deleteByIndex(unsigned long int index){
	if (index == 0 && sizeOfArr == 1) {
		delete [] arrayForDec;
		sizeOfArr = 0;
		return;
	}
	if (index < sizeOfArr && index >= 0) {
		ArrayForDeque<T> temp(*this);
		delete[] arrayForDec;
		--sizeOfArr;
		arrayForDec = new ArrayOptions<T>[sizeOfArr];
		for (size_t i = 0; i < sizeOfArr; ++i) {
			if (i < index) {
				arrayForDec[i] = temp[i];
			}
			else {
				arrayForDec[i] = temp[i + 1];
			}
		}
	}
	else {
		throw ArrayExcepton("Индекс находился за границей массива");
	}
}

template <typename T>
long int ArrayForDeque<T>::getIndexByValue(T item) {
	for (unsigned long int i = 0; i < sizeOfArr; ++i) {
		if (arrayForDec[i].getValue() == item) {
			return i;
		}
	}
	return -1;
}

template <typename T>
T &ArrayForDeque<T>::getValueByIndex(unsigned long int index) {
	if (index >= 0 && index < sizeOfArr) {
		return arrayForDec[index].getValue();
	}
	else {
		throw ArrayExcepton(R"(индекс находился за границами массива)");
	}
}

template <typename T>
ArrayForDeque<T>& ArrayForDeque<T>::operator+(ArrayForDeque<T>& arrToSumm) {
	ArrayForDeque<T> temp(*this);
	for (unsigned long int i = 0; i < arrToSumm.sizeOfArr; ++i) {
		temp.pushBack(arrToSumm.arrayForDec[i].getValue());
		
	}
}

template <typename T>
void ArrayForDeque<T>::setValueByIndex(T itemToAdd, unsigned long int index) {
	if (index < sizeOfArr && index >= 0) {
		if (index == 0) {
			this->pushFront(itemToAdd);
		}
		else if (index == sizeOfArr - 1) {
			this->pushBack(itemToAdd);
		}
		else {
			ArrayForDeque<T> temp(*this);
			delete[] arrayForDec;
			arrayForDec = new ArrayOptions<T>[sizeOfArr + 1];
			++sizeOfArr;
			for (unsigned long int i = 0; i < sizeOfArr; ++i) {
				if (i < index) {
					arrayForDec[i] = temp[i];
				}
				else if (i == index) {
					arrayForDec[i].setValue(itemToAdd);
				}
				else {
					arrayForDec[i] = temp[i - 1];
				}
			}
		}
	}
	else {
		throw ArrayExcepton(R"(индекс находился за границами массива)");
	}
}

//если введены допустим 2, 2, то выведется элемент с индексом 2
//то есть второй индекс включается
template <typename T>
T* ArrayForDeque<T>::getSubsequenceByIndexes(unsigned long int begin, unsigned long int end) {
	if (end >= begin && end < sizeOfArr && begin >= 0) {
		T* temp = new T[end - begin + 1];
		unsigned long int newIndex = 0;
		//std::cout << "последовательность: " << std::endl;
		for (unsigned long int i = begin; i <= end; ++i) {
			temp[newIndex] = arrayForDec[i].getValue();
			//std::cout << temp[i] << "  ";
			++newIndex;
		}
		return temp;
	}
	else {
		throw ArrayExcepton(R"(индексы находились за границами массива)");
	}
}

//сортировка пузырьком по возрастанию
template <typename T>
void ArrayForDeque<T>::Sort() {
	bool flag = true;
	while (flag) {
		flag = false;
		for (unsigned long int i = 0; i < sizeOfArr - 1; ++i) {
			if (arrayForDec[i].getValue() > arrayForDec[i + 1].getValue()) {
				T temp = arrayForDec[i].getValue();
				arrayForDec[i].setValue(arrayForDec[i + 1].getValue());
				arrayForDec[i + 1].setValue(temp);
				flag = true;
			}
		}
	}
}

template <typename T>
ArrayOptions<T>& ArrayForDeque<T>::operator[](unsigned long int i) {
	if (i >= 0 && i < sizeOfArr) {
		return arrayForDec[i];
	}
	else {
		throw ArrayExcepton(R"(индекс находился за границей массива)");
	}
}

template <typename T>
bool ArrayForDeque<T>::operator==(const ArrayForDeque& arrToCompare) {
	if (sizeOfArr == arrToCompare.sizeOfArr) {
		for (unsigned long int i = 0; i < arrToCompare.sizeOfArr; ++i) {
			if (arrToCompare.arrayForDec[i] != arrayForDec[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		throw ArrayExcepton(R"(массивы имели разную длину)");
	}
}

template <typename T>
bool ArrayForDeque<T>::operator!=(const ArrayForDeque<T>& arrayToCompare) {
	return !(*this == arrayToCompare);
}

template <typename T>
ArrayForDeque<T>& ArrayForDeque<T>::operator=(const ArrayForDeque<T>& arrayToCopy) {
	if (this == &arrayToCopy) {
		return *this;
	}
	else {
		sizeOfArr = arrayToCopy.sizeOfArr;
		delete[] arrayForDec;
		arrayForDec = new ArrayOptions<T>[sizeOfArr];
		for (unsigned long int i = 0; i < sizeOfArr; ++i) {
			arrayForDec[i] = arrayToCopy.arrayForDec[i];
		}
		return *this;
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArrayForDeque<T>& arrToOutput) {
	if (arrToOutput.sizeOfArr) {
		for (unsigned long int i = 0; i < arrToOutput.sizeOfArr; ++i) {
			if (i != arrToOutput.sizeOfArr - 1) {
				os << arrToOutput.arrayForDec[i] << "; ";
			}
			else {
				os << arrToOutput.arrayForDec[i] << std::endl;
			}
		}
		return os;
	}
	else {
		throw ArrayExcepton(R"(невозможно вывести пустой массив!)");
	}
}
#endif // !ARRAYFORDEQUE_H_
