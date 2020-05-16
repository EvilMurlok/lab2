#ifndef LISTSEQUENCE_H_
#define LISTSEQUENCE_H_
#include "ListForDeque.h"
#include "Sequence.h"


template <typename T>
class ListSequence : public Sequence<T>
{
public:
	ListSequence();
	~ListSequence() = default;
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
	void deleteByIndex(unsigned long int);
	void Sort() override;
	T* getSubsequenceByIndexes(unsigned long int, unsigned long int) override;
	unsigned long int len() override;
	ListForDeque<T>& operator+(const ListForDeque<T>&);
	T operator[](unsigned long int);
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, const ListSequence<T>&);
private:
	ListForDeque<T> listForDec;
	unsigned long int sizeOfList;
};

template <typename T>
ListSequence<T>::ListSequence() : Sequence<T>()
{
	sizeOfList = 0;
}

template <typename T>
void ListSequence<T>::deleteAll() {
	listForDec.deleteAll();
	sizeOfList = 0;
}

template<typename T>
void ListSequence<T>::deleteByIndex(unsigned long int index)
{
	listForDec.deleteByIndex(index);
	--sizeOfList;
}

template <typename T>
void ListSequence<T>::pushFront(T itemToAdd) {
	listForDec.pushFront(itemToAdd);
	++sizeOfList;
}

template <typename T>
void ListSequence<T>::pushBack(T itemToAdd) {
	listForDec.pushBack(itemToAdd);
	++sizeOfList;
}

template <typename T>
bool ListSequence<T>::isEmpty() {
	return listForDec.isEmpty();
}

template <typename T>
T ListSequence<T>::getBack() {
	return listForDec.getBack();
}

template <typename T>
T ListSequence<T>::getFront() {
	return listForDec.getFront();
}

template <typename T>
unsigned long int ListSequence<T>::len() {
	return listForDec.len();
}

template <typename T>
T ListSequence<T>::getAndDelFromEnd() {
	--sizeOfList;
	return listForDec.getAndDelFromEnd();
}

template <typename T>
T ListSequence<T>::getAndDelFromBeginning() {
	--sizeOfList;
	return listForDec.getAndDelFromBeginning();
}

template <typename T>
T &ListSequence<T>::getValueByIndex(unsigned long int index) {
	return listForDec.getValueByIndex(index);
}

template <typename T>
long int ListSequence<T>::getIndexByValue(T value) {
	return listForDec.getIndexByValue(value);
}

template <typename T>
void ListSequence<T>::setValueByIndex(T itemToAdd, unsigned long int index) {
	listForDec.setValueByIndex(itemToAdd, index);
}

template <typename T>
void ListSequence<T>::Sort() {
	listForDec.Sort();
}

template <typename T>
T* ListSequence<T>::getSubsequenceByIndexes(unsigned long int begin, unsigned long int end) {
	return listForDec.getSubsequenceByIndexes(begin, end);
}

template <typename T>
ListForDeque<T>& ListSequence<T>::operator+(const ListForDeque<T>& listToConcat) {
	return *this + listToConcat;
}

template<typename T>
T ListSequence<T>::operator[](unsigned long int index)
{
	return listForDec.getValueByIndex(index);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ListSequence<T>& listToOutput) {
	os << listToOutput.listForDec;
	return os;
}
#endif // !LISTSEQUENCE_H_
