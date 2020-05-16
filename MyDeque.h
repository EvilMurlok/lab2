#ifndef MYDEQUE_H_
#define MYDEQUE_H_

#include "arraySequence.h"
#include "ListSequence.h"
#include "MyExceptions.h"
#include <string>
#include <typeinfo>

template <typename T>
class MyDeque
{
public:
	MyDeque();
	MyDeque(std::string);
	MyDeque(const MyDeque<T>&);
	~MyDeque() = default;
	std::string getType() { return typeOfSequence; }
	void pushBack(T); //it works
	void pushFront(T); //it works
	bool isEmpt(); //it works
	T outFront(); //it works
	T outBack(); //it works
	//get and delete an element from the end
	T popBack(); //it works
	//get and delete an element from the beginning
	T popFront(); //it works
	void cleanAll(); //it works
	void deleteByIndex(unsigned long int);
	unsigned long int len(); //it works
	long int getIndex(T); //it works
	void insertIn(T, unsigned long int); //it works
	T &getValueByIndex(unsigned long int); //it works
	void Sorting(); //it works
	T* getSubsequence(unsigned long int, unsigned long int); //it works
	MyDeque<T> operator+(const MyDeque<T>&); //it works
	MyDeque<T>& operator=(const MyDeque<T>&); //it workss
	T operator[](unsigned long int);
	template <typename T>
	friend std::istream& operator>>(std::istream& , MyDeque<T>&);
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, MyDeque<T>&); 
private:
	Sequence<T>* DequeData;
	unsigned long int sizeOfDeque;
	std::string typeOfSequence;
};

template<typename T>
inline MyDeque<T>::MyDeque() {
	DequeData = new ArraySequence<T>;
	sizeOfDeque = DequeData->len();
	typeOfSequence = "arraySequence";
}

template <typename T>
MyDeque<T>::MyDeque(std::string tpOfSeq){
	typeOfSequence  = tpOfSeq;
	if (tpOfSeq == "arraySequence") {
		DequeData = new ArraySequence<T>;
		sizeOfDeque = DequeData->len();
	}
	else if (tpOfSeq == "listSequence") {
		DequeData = new ListSequence<T>;
		sizeOfDeque = DequeData->len();
	}
	else {
		throw DequeExceptions(R"(такого типа не существует!)");
	}
}

template <typename T>
void MyDeque<T>::pushBack(T valueToAdd) {
	DequeData->pushBack(valueToAdd);
	++sizeOfDeque;
}

template <typename T>
void MyDeque<T>::pushFront(T valueToAdd) {
	DequeData->pushFront(valueToAdd);
	++sizeOfDeque;
}

template <typename T>
bool MyDeque<T>::isEmpt() {
	return DequeData->isEmpty();
}

template <typename T>
T MyDeque<T>::outBack() {
	if (this->isEmpt()) {
		throw DequeExceptions(R"(дек пуст!)");
	}
	else {
		return DequeData->getBack();
	}
}

template <typename T>
T MyDeque<T>::outFront() {
	if (this->isEmpt()) {
		throw DequeExceptions(R"(дек пуст!)");
	}
	else {
		return DequeData->getFront();
	}
}

template <typename T>
T MyDeque<T>::popBack() {
	--sizeOfDeque;
	return DequeData->getAndDelFromEnd();
}

template <typename T>
T MyDeque<T>::popFront() {
	--sizeOfDeque;
	return DequeData->getAndDelFromBeginning();
}

template <typename T>
unsigned long int MyDeque<T>::len() {
	return DequeData->len();
}

template <typename T>
void MyDeque<T>::cleanAll() {
	if (this->isEmpt()) {
		throw DequeExceptions(R"(дек пуст!)");
	}
	else
	{
		DequeData->deleteAll();
	}
}

template<typename T>
void MyDeque<T>::deleteByIndex(unsigned long int index) {
	++sizeOfDeque;
	DequeData->deleteByIndex(index);
}

template <typename T>
long int MyDeque<T>::getIndex(T valueToCheck) {
	if (this->isEmpt()) {
		throw DequeExceptions(R"(дек пуст!)");
	}
	else {
		return DequeData->getIndexByValue(valueToCheck);
	}
}

template <typename T>
void MyDeque<T>::insertIn(T valueToInsert, unsigned long int index) {
	DequeData->setValueByIndex(valueToInsert, index);
	++sizeOfDeque;
}

template <typename T>
T &MyDeque<T>::getValueByIndex(unsigned long int index) {
	return DequeData->getValueByIndex(index);
}

template <typename T>
void MyDeque<T>::Sorting() {
	DequeData->Sort();
}

template <typename T>
T* MyDeque<T>::getSubsequence(unsigned long int begin, unsigned long int end) {
	return DequeData->getSubsequenceByIndexes(begin, end);
}

template <typename T>
MyDeque<T>::MyDeque(const MyDeque<T>& dequeToCopy) {
	sizeOfDeque = dequeToCopy.sizeOfDeque;
	typeOfSequence = dequeToCopy.typeOfSequence;
	if (dequeToCopy.typeOfSequence == "arraySequence") {
		DequeData = new ArraySequence<T>;
		for (unsigned long int i = 0; i < sizeOfDeque; ++i) {
			DequeData->pushBack(dequeToCopy.DequeData->getValueByIndex(i));
		}
	}
	else if (dequeToCopy.typeOfSequence == "listSequence") {
		DequeData = new ListSequence<T>;
		for (unsigned long int i = 0; i < sizeOfDeque; ++i) {
			DequeData->pushBack(dequeToCopy.DequeData->getValueByIndex(i));
		}
	}
	else {
		throw DequeExceptions(R"(недопустимый тип последовательности!)");
	}
	
}

template <typename T>
MyDeque<T> MyDeque<T>::operator+(const MyDeque<T>& dequeToAdd) {
	MyDeque<T> temp(*this);
	for (unsigned long int i = 0; i < dequeToAdd.sizeOfDeque; ++i) {
		temp.pushBack(dequeToAdd.DequeData->getValueByIndex(i));
	}
	return temp;
}

template<typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque<T>& dequeToAssign)
{
	delete DequeData;
	typeOfSequence = dequeToAssign.typeOfSequence;
	sizeOfDeque = dequeToAssign.sizeOfDeque;
	if (dequeToAssign.typeOfSequence == "arraySequence") {
		DequeData = new ArraySequence<T>;
		for (unsigned long int i = 0; i < sizeOfDeque; ++i) {
			DequeData->pushBack(dequeToAssign.DequeData->getValueByIndex(i));
		}
	}
	else {
		DequeData = new ListSequence<T>;
		for (unsigned long int i = 0; i < dequeToAssign.sizeOfDeque; ++i) {
			DequeData->pushBack(dequeToAssign.DequeData->getValueByIndex(i));
		}		
	}
	return *this;
}

template<typename T>
T MyDeque<T>::operator[](unsigned long int index)
{
	return this->getValueByIndex(index);
}

template <typename T>
std::istream& operator>>(std::istream& is, MyDeque<T>& dequeToInput) {
	if (typeid(T) == typeid(std::string)) {
		std::cout << "вводите строки, если хотите прекратить ввод, введите q или Q" << std::endl;
		std::string input = "";
		while (getline(is, input)) {
			if (input == "q" || input == "Q") {
				break;
			}
			dequeToInput.pushBack(input);
		}
	}
	else {
		T input;
		while (is >> input) {
			if (!is.get()) {
				break;
			}
			dequeToInput.pushBack(input);
		}
	}
	return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, MyDeque<T>& dequeToOutput) {
	if (dequeToOutput.typeOfSequence == "arraySequence") {
		os << *dynamic_cast<ArraySequence<T>*>(dequeToOutput.DequeData);
	}
	else if (dequeToOutput.typeOfSequence == "listSequence") {
		os << *dynamic_cast<ListSequence<T>*>(dequeToOutput.DequeData);
	}
	else {
		throw DequeExceptions(R"(такого типа не существует!)");
	}
	return os;
}

#endif // !MYDEQUE_H_

