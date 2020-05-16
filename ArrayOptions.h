#ifndef ARRAYOPTIONS_H_
#define ARRAYOPTIONS_H_

#include "MyExceptions.h"
#include <iostream>

template <typename T>
class ArrayOptions
{
public:
	ArrayOptions() : hasValue{ false } {};
	ArrayOptions(T valueToAdd) : value{ valueToAdd }, hasValue{ true } {}
	ArrayOptions(ArrayOptions<T>& itemToAdd) : value{ itemToAdd.value }, hasValue{ itemToAdd.hasValue } {}
	~ArrayOptions() = default;
	void setValue(T valueToAdd) { value = valueToAdd; hasValue = true; }
	T &getValue();
	bool checkValue() { return hasValue; }
	template <typename T> 
	friend std::ostream& operator<<(std::ostream&, const ArrayOptions<T>&);
	ArrayOptions<T>& operator=(const ArrayOptions<T>&);
	ArrayOptions<T>& operator=(T);
	bool operator==(ArrayOptions<T>& arrToCompare) { return (hasValue && arrToCompare.hasValue && value == arrToCompare.value) || (arrToCompare.hasValue == hasValue); }
	bool operator!=(ArrayOptions<T>& arrToCompare) { return !(*this == arrToCompare); }
private:
	T value;
	bool hasValue;
};

template <typename T>
T &ArrayOptions<T>::getValue() {
	if (hasValue) {
		return value;
	}
	else {
		throw ArrayOptionsExceptions("Элемент не имеет никакого значения");
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArrayOptions<T>& arr) {
	if (arr.hasValue) {
		os << arr.value;
		return os;
	}
	else {
		throw ArrayOptionsExceptions("Элемент не имеет никакого значения");
	}
}

template <typename T>
ArrayOptions<T>& ArrayOptions<T>::operator=(T itemToAdd) {
	if (value == itemToAdd) {
		return *this;
	}
	else {
		hasValue = true;
		value = itemToAdd;
		return *this;
	}
}

template <typename T>
ArrayOptions<T>& ArrayOptions<T>::operator=(const ArrayOptions<T>& arr) {
	if (value == arr.value && hasValue == arr.hasValue) {
		return *this;
	}
	else {
		value = arr.value;
		hasValue = arr.hasValue;
		return *this;
	}
}

#endif // !ARRAYOPTIONS_H_

