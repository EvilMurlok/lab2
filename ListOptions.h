#ifndef LISTOPTIONS_H_
#define LISTOPTIONS_H_

#include "MyExceptions.h"
#include <iostream>

template <typename T>
class ListOptions
{
public:
	ListOptions() :  hasValue { false }, next{ nullptr }, prev{ nullptr } {}
	ListOptions(T itemToAdd) : value{ itemToAdd }, hasValue{ true }, next{ nullptr }, prev{ nullptr } {}
	ListOptions(const ListOptions<T>&);
	void setValue(T valueToAdd);
	T &getValue();
	bool checkValue() { return hasValue; }
	void setNext(ListOptions<T>* nextPointer) { next = nextPointer; }
	void setPrev(ListOptions<T>* prevPointer) { prev = prevPointer; }
	ListOptions<T>* getNext() { return next; }
	ListOptions<T>* getPrev() { return prev; }
	ListOptions<T>& operator=(T);
	ListOptions<T>& operator=(const ListOptions<T>&);
	template <typename T>
	friend std::ostream& operator<<(const std::ostream&, const ListOptions<T>&);
	bool operator==(ListOptions<T>& listToCompare) { return (hasValue && listToCompare.hasValue && value == listToCompare.value) || (listToCompare.hasValue == hasValue); }
	~ListOptions() = default;
private:
	T value;
	bool hasValue;
	ListOptions<T> *next;
	ListOptions<T>* prev;
	
};

template <typename T>
ListOptions<T>::ListOptions(const ListOptions<T> &listToAdd)
{
	if (listToAdd.checkValue) {
		value = listToAdd.value;
		hasValue = true;
		next = listToAdd.next;
		prev = listToAdd.prev;
	}
	else {
		throw DualListOptionsExceptions("Элемент не содержит никакого значения");
	}
}

template<typename T>
void ListOptions<T>::setValue(T valueToAdd) {
	value = valueToAdd;
	hasValue = true;
}

template<typename T>
T &ListOptions<T>::getValue() {
	if (hasValue) {
		return value;
	}
	else {
		throw DualListOptionsExceptions("Element has not value!");
	}
}

template <typename T>
ListOptions<T>& ListOptions<T>::operator=(T itemToAdd) {
	value = itemToAdd;
	hasValue = true;
	return *this;
}

template <typename T>
ListOptions<T>& ListOptions<T>::operator=(const ListOptions<T>& listToAdd) {
	if (listToAdd.hasValue == hasValue && listToAdd.value == value) {
		return *this;
	}
	else {
		value = listToAdd.value;
		hasValue = true;
		next = listToAdd.next;
		prev = listToAdd.prev;
		return *this;
	}
}

template <typename T>
std::ostream& operator<<(const std::ostream& os, const ListOptions<T>& listToOutput) {
	if (listToOutput.checkValue()) {
		os << listToOutput.value;
		return os;
	}
	else {
		throw DualListExceptions("элемент не содержит значения");
	}
}

#endif // !LISTOPTIONS_H_
