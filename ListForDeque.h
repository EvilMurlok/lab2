#ifndef LISTFORDEQUE_H_
#define LISTFORDEQUE_H_

#include "MyExceptions.h"
#include "ListOptions.h"
#include <iostream>

template <typename T>
class ListForDeque
{
public:
	ListForDeque() : head{ nullptr }, tail{ nullptr }, sizeOfList{ 0 } {}
	ListForDeque(const ListForDeque<T>&);
	unsigned long int len() { return sizeOfList; }
	void pushFront(T);
	void pushBack(T);
	bool isEmpty();
	T getFront();
	T getBack();
	T getAndDelFromEnd();
	T getAndDelFromBeginning();
	void deleteByIndex(unsigned long int);
	void deleteAll();
	long int getIndexByValue(T);
	T &getValueByIndex(unsigned long int);
	void setValueByIndex(T, unsigned long int);
	T* getSubsequenceByIndexes(unsigned long int, unsigned long int);
	void Sort();
	bool operator==(const ListForDeque<T>&);
	bool operator!=(const ListForDeque<T>&);
	ListForDeque<T>& operator=(ListForDeque<T>&);
	ListForDeque<T>& operator[](const unsigned long int);
	ListForDeque<T>& operator+(const ListForDeque<T>&);
	~ListForDeque() = default;
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, const ListForDeque<T>&);
private:
	ListOptions<T>* head;
	ListOptions<T>* tail;
	unsigned long int sizeOfList;
};
//конструктор копирования
template <typename T>
ListForDeque<T>::ListForDeque(const ListForDeque<T>& listToCopy){
	ListOptions<T>* temp1 = listToCopy.head;
	ListOptions<T>* temp2 = new ListOptions<T>;
	temp2->setValue(temp1->getValue());
	temp2->setPrev(nullptr);
	temp2->setNext(nullptr);
	while (temp1->getNext()) {
		temp1 = temp1->getNext();
		temp2->setNext(new ListOptions<T>);
		ListOptions<T>* temp3 = temp2;
		temp2 = temp2->getNext();
		temp2->setPrev(temp3);
		temp2->setValue(temp1->getValue());
		temp2->setNext(nullptr);
	}
	sizeOfList = listToCopy.sizeOfList;
}

template <typename T>
void ListForDeque<T>::pushFront(T itemToAdd) {
	if (!this->isEmpty()) {
		head->setPrev(new ListOptions<T>);
		ListOptions<T>* temp1 = head;
		head = head->getPrev();
		head->setValue(itemToAdd);
		head->setPrev(nullptr);
		head->setNext(temp1);
	}
	else {
		ListOptions<T>* temp = new ListOptions<T>;
		temp->setNext(nullptr);
		temp->setPrev(nullptr);
		temp->setValue(itemToAdd);
		head = temp;
		tail = temp;
	}
	++sizeOfList;
}

template <typename T>
void ListForDeque<T>::pushBack(T itemToAdd) {
	if (!this->isEmpty()) {
		tail->setNext(new ListOptions<T>);
		ListOptions<T>* temp1 = tail;
		tail = tail->getNext();
		tail->setValue(itemToAdd);
		tail->setNext(nullptr);
		tail->setPrev(temp1);
	}
	else {
		ListOptions<T>* temp = new ListOptions<T>;
		temp->setNext(nullptr);
		temp->setPrev(nullptr);
		temp->setValue(itemToAdd);
		head = temp;
		tail = temp;
	}
	++sizeOfList;
}

template <typename T>
bool ListForDeque<T>::isEmpty() {
	if (sizeOfList) {
		return false;
	}
	else {
		return true;
	}
}

template <typename T>
T ListForDeque<T>::getFront() {
	if (this->isEmpty()) {
		throw DualListExceptions("нельзя получить данные из пустого списка!");
	}
	else {
		return head->getValue();
	}
}

template <typename T>
T ListForDeque<T>::getBack() {
	if (this->isEmpty()) {
		throw DualListExceptions("нельзя получить данные из пустого списка!");
	}
	else {
		return tail->getValue();
	}
}

template <typename T>
T ListForDeque<T>::getAndDelFromEnd() {
	if (!this->isEmpty()) {
		T temp = tail->getValue();
		ListOptions<T>* temp1 = tail;
		tail = tail->getPrev();
		tail->setNext(nullptr);
		delete temp1;
		--sizeOfList;
		return temp;
	}
	else {
		throw DualListExceptions("список уже пуст!");
	}
}

template <typename T>
T ListForDeque<T>::getAndDelFromBeginning() {
	if (!this->isEmpty()) {
		T temp = head->getValue();
		ListOptions<T>* temp1 = head;
		head = head->getNext();
		head->setPrev(nullptr);
		delete temp1;
		--sizeOfList;
		return temp;
	}
	else {
		throw DualListExceptions("список уже пуст!");
	}
}

template<typename T>
void ListForDeque<T>::deleteByIndex(unsigned long int index)
{
	if (sizeOfList == 1 && index == 0) {
		delete head;
		sizeOfList = 0;
		return;
	}
	else if (index == 0) {
		ListOptions<T>* temp = head;
		head = temp->getNext();
		delete temp;
		head->setPrev(nullptr);
		--sizeOfList;
		return;
	}
	else if (index == sizeOfList - 1){
		ListOptions<T>* temp = tail;
		tail = tail->getPrev();
		delete temp;
		tail->setNext(nullptr);
		--sizeOfList;
		return;
	}
	if (index < sizeOfList && index >= 0) {
		ListOptions<T>* temp = head;
		size_t i = 0;
		while (temp && i < index) {
			temp = temp->getNext();
			++i;
		}
		temp->getNext()->setPrev(temp->getPrev());
		temp->getPrev()->setNext(temp->getNext());
		delete temp;
		--sizeOfList;
	}
	else {
		throw DualListExceptions("Индекс находился за границей массива");
	}
}

template <typename T>
void ListForDeque<T>::deleteAll() {
	if (!this->isEmpty()) {
		ListOptions<T>* temp = head;
		while (temp)
		{
			ListOptions<T>* temp2 = temp;
			temp = temp->getNext();
			delete temp2;
		}
		sizeOfList = 0;
	}
	else {
		throw DualListExceptions("невозможно удалить и так несуществующий список!");
	}
}

template <typename T>
long int ListForDeque<T>::getIndexByValue(T item) {
	ListOptions<T>* temp = head;
	unsigned long int index = 0;
	while (temp) {
		if (temp->getValue() == item) {
			return index;
		}
		++index;
		temp = temp->getNext();
	}
	return -1;
}

template <typename T>
T &ListForDeque<T>::getValueByIndex(unsigned long int index) {
	if (index >= 0 && index < sizeOfList) {
		ListOptions<T>* temp1 = head;
		for (unsigned long int i = 0; i < index; ++i) {
			temp1 = temp1->getNext();
		}
		return temp1->getValue();
	}
	else {
		throw DualListExceptions("индекс находился за границей  массива!");
	}
}

template <typename T>
void ListForDeque<T>::setValueByIndex(T value, unsigned long int index) {
	if (index < sizeOfList && index >= 0) {
		if (index == 0) {
			pushFront(value);
		}
		else if (index == sizeOfList) {
			pushBack(value);
		}
		else {
			ListOptions<T>* temp1 = head;
			for (unsigned long int i = 0; i < index - 1 ; ++i) {
				temp1 = temp1->getNext();
			}
			ListOptions<T>* temp2 = new ListOptions<T>;
			ListOptions<T>* temp3 = temp1->getNext();
			temp1->setNext(temp2);
			temp2->setPrev(temp1);
			temp2->setValue(value);
			temp2->setNext(temp3);
			temp3->setPrev(temp2);
			++sizeOfList;
		}
	}
	else {
		throw DualListExceptions("индекс находился за границей массива!");
	}
}

template <typename T>
T* ListForDeque<T>::getSubsequenceByIndexes(unsigned long int begin, unsigned long int end) {
	if (end >= begin && end < sizeOfList && begin >= 0) {
		T* temp = new T[end - begin + 1];
		ListOptions<T>* temp1 = head;
		unsigned long int index = 0;
		//std::cout << "подпоследовтельность: " << std::endl;
		while (index < begin) {
			temp1 = temp1->getNext();
			++index;
		}
		while (index <= end)
		{
			temp[index - begin] = temp1->getValue();
			//std::cout << temp[index - begin] << "  ";
			++index;
			temp1 = temp1->getNext();
		}
		return temp;
	}
	else {
		throw DualListExceptions("индексы находились за границами массива");
	}
}

template <typename T>
void ListForDeque<T>::Sort() {
	if (sizeOfList == 1) {
		return;
	}
	else if (sizeOfList == 2) {
		//ListOptions<T>* temp1 = tail;
		tail->setNext(head);
		head->setPrev(tail);
		head->setNext(nullptr);
		tail->setPrev(nullptr);
		ListOptions<T>* temp = head;
		head = tail;
		tail = temp;
	}
	else {
		ListOptions<T>* temp1 = head;
		while (temp1) {
			ListOptions<T>* temp2 = head;
			while (temp2->getNext()) {
				if (temp2->getValue() > temp2->getNext()->getValue()) {
					ListOptions<T>* temp3 = temp2->getNext();
					if (!temp2->getPrev()) {
						temp3->getNext()->setPrev(temp2);
						temp3->setPrev(nullptr);
						temp2->setNext(temp3->getNext());
						temp3->setNext(temp2);
						temp2->setPrev(temp3);
						head = temp3;
					}
					else if (!temp3->getNext()) {
						temp2->getPrev()->setNext(temp3);
						temp2->setNext(nullptr);
						temp3->setPrev(temp2->getPrev());
						temp3->setNext(temp2);
						temp2->setPrev(temp3);
						break;
					}
					else {
						temp2->getPrev()->setNext(temp3);
						temp3->getNext()->setPrev(temp2);
						temp2->setNext(temp3->getNext());
						temp3->setPrev(temp2->getPrev());
						temp2->setPrev(temp3);
						temp3->setNext(temp2);
					}
				}
				temp2 = temp2->getNext();
			}
			if (!temp1->getNext()) {
				tail = temp1;
				break;
			}
			temp1 = temp1->getNext();

		}
	}
}

template <typename T>
bool ListForDeque<T>::operator==(const ListForDeque<T>& listToCompare) {
	if (sizeOfList == listToCompare.sizeOfList) {
		ListOptions<T>* temp1 = listToCompare.head;
		ListOptions<T>* temp2 = head;
		while (temp1) {
			if (temp1->getValue() != temp2->getValue()) {
				return false;
			}
			else {
				temp1 = temp1->getNext();
				temp2 = temp2->getNext();
			}
		}
		return true;
	}
	else {
		throw DualListExceptions("невозможно сравнить списки разной длины!");
	}
}

template <typename T>
bool ListForDeque<T>::operator!=(const ListForDeque<T>& listToCompare) {
	return !(*this == listToCompare);
}

template <typename T>
ListForDeque<T>& ListForDeque<T>::operator=(ListForDeque<T>& arrToCopy) {
	if (this == &arrToCopy) {
		return *this;
	}
	else {
		ListOptions<T>* temp1 = arrToCopy.head;
		if (arrToCopy.sizeOfList == sizeOfList) {
			ListOptions<T>* temp = head;
			while (temp1) {
				temp->setValue(temp1->getValue());
				temp = temp->getNext();
				temp1 = temp1->getNext();
			}
		}
		else {
			this->deleteAll();
			ListOptions<T>* temp = new ListOptions<T>;
			temp->setValue(temp1->getValue());
			temp->setNext(nullptr);
			temp->setPrev(nullptr);
			head = temp;
			temp1 = temp1->getNext();
			while (temp1) {
				temp->setNext(new ListOptions<T>);
				ListOptions<T>* temp2 = temp;
				temp = temp->getNext();
				temp->setValue(temp1->getValue());
				temp->setPrev(temp2);
				temp1 = temp1->getNext();
			}
		}
	}
}

template<typename T>
ListForDeque<T>& ListForDeque<T>::operator[](unsigned long int i) {
	if (i >= 0 && i < sizeOfList) {
		ListOptions<T>* temp = head;
		unsigned long int j = 0;
		while (temp != nullptr && j < i) {
			temp = temp->getNext();
			++j;
		}
		return *temp;
	}
	else {
		throw DualListExceptions("Индекс находился за границей массива!");
	}
}

template <typename T>
ListForDeque<T>& ListForDeque<T>::operator+(const ListForDeque<T>& listToConcat) {
	ListForDeque<T> temp(*this);
	ListOptions<T>* temp1 = listToConcat.head;
	while (temp1) {
		temp.pushBack(temp1->getValue());
		temp1 = temp1->getNext();
	}
	return temp;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ListForDeque<T>& listToOutput) {
	if (listToOutput.sizeOfList) {
		ListOptions<T>* temp = listToOutput.head;
		while (temp) {
			if (temp != listToOutput.tail) {
				os << temp->getValue() << ";  ";
			}
			else {
				os << temp->getValue() << std::endl;
			}
			temp = temp->getNext();
		}
		return os;
	}
	else {
		throw DualListExceptions("невозможно вывести пустой список");
	}
}

#endif // !LISTFORDEQUE_H_
