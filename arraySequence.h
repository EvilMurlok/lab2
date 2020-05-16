#ifndef ARRAYSEQUENCE_H_
#define ARRAYSEQUENCE_H_
#include "ArrayForDeque.h"
#include "Sequence.h"


template <typename T>
class ArraySequence : public Sequence<T>
{
public:
	ArraySequence();
	~ArraySequence() = default;
	void pushFront(T) override;
	void pushBack(T) override;
	T getFront() override;
	T getBack() override;
	T getAndDelFromBeginning() override;
	T getAndDelFromEnd() override;
	T &getValueByIndex(unsigned long int) override;
	void setValueByIndex(T, unsigned long int) override;
	long int getIndexByValue(T) override;
	bool isEmpty() override;
	void deleteAll() override;
	unsigned long int len() override;
	void Sort() override;
	T* getSubsequenceByIndexes(unsigned long int, unsigned long int) override;
	ArrayForDeque<T>& operator+(ArrayForDeque<T>&);
	void deleteByIndex(unsigned long int);
	T operator[](unsigned long int);
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, const ArraySequence<T>&);
private:
	ArrayForDeque<T> arrayForDec;
	unsigned long int sizeOfArr;
};

template <typename T>
ArraySequence<T>::ArraySequence() : Sequence<T>() {
	sizeOfArr = 0;
}


template <typename T>
void ArraySequence<T>::deleteAll() {
	arrayForDec.deleteAll();
	sizeOfArr = 0;
}

template <typename T>
void ArraySequence<T>::pushFront(T itemToAdd) {
	return arrayForDec.pushFront(itemToAdd);
}

template <typename T>
void ArraySequence<T>::pushBack(T itemToAdd) {
	return arrayForDec.pushBack(itemToAdd);
}

template <typename T>
bool ArraySequence<T>::isEmpty() {
	return arrayForDec.isEmpty();
}

template <typename T>
T ArraySequence<T>::getBack() {
	return arrayForDec.getBack();
}

template <typename T>
T ArraySequence<T>::getFront() {
	return arrayForDec.getFront();
}

template <typename T>
unsigned long int ArraySequence<T>::len() {
	return arrayForDec.len();
}

template <typename T>
T ArraySequence<T>::getAndDelFromEnd() {
	--sizeOfArr;
	return arrayForDec.getAndDelFromEnd();
}

template <typename T>
T ArraySequence<T>::getAndDelFromBeginning() {
	--sizeOfArr;
	return arrayForDec.getAndDelFromBeginning();
}

template <typename T>
T &ArraySequence<T>::getValueByIndex(unsigned long int index) {
	return arrayForDec.getValueByIndex(index);
}

template <typename T>
long int ArraySequence<T>::getIndexByValue(T value) {
	return arrayForDec.getIndexByValue(value);
}

template <typename T>
void ArraySequence<T>::setValueByIndex(T itemToAdd, unsigned long int index) {
	arrayForDec.setValueByIndex(itemToAdd, index);
}

template <typename T>
void ArraySequence<T>::Sort() {
	arrayForDec.Sort();
}

template <typename T>
T* ArraySequence<T>::getSubsequenceByIndexes(unsigned long int begin, unsigned long int end) {
	return arrayForDec.getSubsequenceByIndexes(begin, end);
}


template <typename T>
ArrayForDeque<T>& ArraySequence<T>::operator+(ArrayForDeque<T>& arrToSumm) {
	return *this + arrToSumm;
}

template<typename T>
void ArraySequence<T>::deleteByIndex(unsigned long int index)
{
	arrayForDec.deleteByIndex(index);
	--sizeOfArr;
}

template<typename T>
T ArraySequence<T>::operator[](unsigned long int index)
{
	return arrayForDec[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArraySequence<T>& arrToOutput) {
	os << arrToOutput.arrayForDec;
	return os;
}
#endif // !ARRAYSEQUENCE_H_
