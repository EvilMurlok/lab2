#include <cstdlib>
#include <iostream>
#include <string>
#include "MyDeque.h"
#include <chrono>
#include "Student.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;

void testArray();
void testList();

const unsigned long AMOUNT = 200;

template <typename T>
void testTimeFunctions(MyDeque<T>&, MyDeque<T>&);

Student* getRandStudent() {
	int a = 0,
		b = 0;
	do {
		a = rand() % 5 + 1;
		b = rand() % 5 + 1;
	} while (a <= b);
	auto h = new Student("Ilya", 'M', (double)a / b);
	return h;
}

template <typename TypeOfSeq, typename fcn>
void map(TypeOfSeq& seq, fcn func) {
	for (size_t i = 0; i < seq.len(); ++i) {
		func(seq.getValueByIndex(i));
	}
}


template <typename TypeOfSeq, typename T, typename fcn>
T reduce(TypeOfSeq inputSequence, T startVal, fcn f) {
	T temp = f(startVal, inputSequence.getValueByIndex(0));
	for (size_t i = 1; i < inputSequence.len(); ++i) {
		temp = f(temp, inputSequence.getValueByIndex(i));
	}
	return temp;
}


template <typename TypeOfSeq, typename TypeOfSubsequence, typename fcn>
TypeOfSubsequence where(TypeOfSeq inputSequence, fcn f) {
	TypeOfSubsequence temp;
	for (size_t i = 0; i < inputSequence.len(); i++) {
		if (f(inputSequence.getValueByIndex(i))) {
			temp.pushBack(inputSequence.getValueByIndex(i));
		}
	}
	return temp;
}

//сортировка независимо от типа
template <typename TypeOfSeq, typename fcn1, typename fcn2>
void sort(TypeOfSeq& inputSequence, fcn1 f, fcn2 swap) {
	for (size_t i = 0; i < inputSequence.len() - 1; i++) {
		for (size_t j = i + 1; j < inputSequence.len(); j++) {
			auto& temp1 = inputSequence.getValueByIndex(i);
			auto& temp2 = inputSequence.getValueByIndex(j);
			if (f(temp1, temp2)) {
				swap(temp1, temp2);
			}
		}
	}
}

template <typename TypeOfSeq, typename fcn1>
long binarySearch(TypeOfSeq inputSequence, fcn1 search) {
	return search(inputSequence);
}



int main()
{
	srand(time(NULL));
	system("chcp 1251 > nul");
	cout << R"(приветсвую вас в консольном приложении по работе с деком!)" << endl;
	//замеры времени
	auto begin = std::chrono::steady_clock::now();
	MyDeque<double> arrayObject("arraySequence");
	int a = 0, b = 0;
	for (unsigned long i = 0; i < AMOUNT; ++i) {
		a = rand() % 10000 - 5000;
		b = rand() % 10000 - 5000;
		double c = (double)a / b;
		if (i % 2) {
			arrayObject.pushFront(c);
		}
		else {
			arrayObject.pushBack(c);
		}
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время создания массива длиной " << AMOUNT << ": " << elapsed_ms.count() << " mcs\n";

	auto begin1 = std::chrono::steady_clock::now();
	MyDeque<double> listObject("listSequence");
	a = 0;
	b = 0;
	for (unsigned long i = 0; i < AMOUNT; ++i) {
		a = rand() % 10000 - 5000;
		b = rand() % 10000 - 5000;
		double c = (double)a / b;
		if (i % 2) {
			listObject.pushFront(c);
		}
		else {
			listObject.pushBack(c);
		}
	}
	auto end1 = std::chrono::steady_clock::now();
	auto elapsed1_ms = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
	cout << "время создания списка длиной " << AMOUNT << ": " << elapsed1_ms.count() << " mcs\n";
	testTimeFunctions(listObject, arrayObject);

	//два теста, которые показывают работоспособность дека как на массиве, так и на списке двусвязном
	testList();
	testArray();
	//-----------------------------------------------------------------------------------------------


	//тут продемонстрирована работа функций map, where, reduce
	MyDeque<double> d("arraySequence");
	for (long i = 10; i >= 1; --i) {
		d.pushBack(i);
	}

	cout << d;

	double valueFromReduce = reduce<MyDeque<double>, double>(d, 6, [](double valueToChange, double valueFromDeque) {
		return valueToChange + valueFromDeque;
		});

	cout << valueFromReduce << endl;

	map(d, [](double& valueToChange) {
		valueToChange = 3 * valueToChange;
		});

	cout << d;


	MyDeque<double> sd = where<MyDeque<double>, MyDeque<double>>(d, [](double valueToChange) {
		return valueToChange > 10;
		});

	sort(sd, [](double a, double b) {
		return a > b;
		}, [](double& a, double& b) {
			double temp = a;
			a = b;
			b = temp;
		});

	cout << sd;

	//реализованный класс сложной структуры(ввод и добавление, а потом сортировка)
	MyDeque<Student*> ddd("listSequence");
	for (size_t i = 0; i < 10; i++)
	{
		Student h;
		cin >> h;
		Student* hh = new Student(h.getName(), h.getGender(), h.getAverageMark());
		ddd.pushBack(hh);
		ddd.pushBack(getRandStudent());
	}
	sort(ddd, [](Student* a, Student* b) {
		return a->getAverageMark() > b->getAverageMark();
		}, [](Student* a, Student* b) {
			a->swapStudents(*b);
		});

	map(ddd, [](Student* h) {
		cout << *h;
		});
	//некоторые методы со сложной структурой
	cout << endl << *ddd.getValueByIndex(3) << endl;
	Student** arr = ddd.getSubsequence(1, 8);
	for (unsigned i = 0; i < 8; ++i) {
		cout << *arr[i] << ' ';
	}

	cout << endl;

	double ser = 3;
	long index = binarySearch(ddd, [&ser](MyDeque<Student*> ddd) {
		long l = 0;
		long r = ddd.len() - 1;
		while (l <= r) {
			long middle = (l + r) / 2;
			if (ser < ddd.getValueByIndex(middle)->getAverageMark()) {
				r = middle - 1;
			}
			else if (ser > ddd.getValueByIndex(middle)->getAverageMark()) {
				l = middle + 1;
			}
			else {
				return middle;
			}
		}
		return (long)-1;
		});

	if (index > -1) {
		cout << *ddd.getValueByIndex(index) << endl;
	}
	else {
		cout << "студента с таким средним баллом нет!(" << ser << ")" << endl;
	}

	ser = 18;
	index = binarySearch(sd, [&ser](MyDeque<double> sd) {
		long l = 0;
		long r = sd.len() - 1;
		while (l <= r) {
			long middle = (l + r) / 2;
			if (ser < sd.getValueByIndex(middle)) {
				r = middle - 1;
			}
			else if (ser > sd.getValueByIndex(middle)) {
				l = middle + 1;
			}
			else {
				return middle;
			}
		}
		return (long)-1;
		});

	if (index > -1) {
		cout << index << endl;
	}
	else {
		cout << "такого значения нет!" << endl;
	}
	return EXIT_SUCCESS;
}



//работает так, как надо!
void testArray() {
	srand(time(0));
	MyDeque<double> firstObject("arraySequence");
	cout << "сейчас будут протестированы основные методы класса MyDeque, когда за основу взят МАССИВ" << endl;
	cout << "для начала нагенерируем случайных чисел и добавим их в дек(протестировав добавление в конец и в начало) и посмотрим на наш дек, к которому мы будем обращаться: " << endl << endl;
	cout << "заодно и убедимся, что вывод объекта MyDeque работает нормально" << endl;
	int a = 0, b = 0;
	for (unsigned int i = 0; i < 12; ++i) {
		a = rand() % 10000 - 5000;
		b = rand() % 10000 - 5000;
		double c = (double)a / b;
		if (i % 2) {
			firstObject.pushFront(c);
		}
		else {
			firstObject.pushBack(c);
		}
	}
	cout << firstObject << endl << endl;
	cout << "теперь продемострируем каждый метод класса MyDeque" << endl;
	cout << "длина дека: " << firstObject.len() << "  пуст ли дек? " << firstObject.isEmpt() << endl << endl;
	cout << "последний элемент дека: " << firstObject.outBack() << "  первый элемент списка: " << firstObject.outFront() << endl << endl;
	unsigned long int index = rand() % 12;
	cout << "элемент с индексом " << index << ": " << firstObject.getValueByIndex(index) << endl << endl;
	index = rand() % 12;
	cout << "индекс элемента " << firstObject.getValueByIndex(index) << ":  " << firstObject.getIndex(firstObject.getValueByIndex(index)) << endl << endl;
	unsigned long int first = 0, second = 0;
	do {
		first = rand() % 12;
		second = rand() % 12;
	} while (first > second);
	//бесят срезы в питоне тем, что не выводится крайний элемент, поэтому будут выделены элементы с индексами 4, 5, 6, 7
	cout << "левая граница: " << first << " правая граница: " << second << endl;
	double* subSeq = firstObject.getSubsequence(first, second);
	for (unsigned long int i = 0; i <= second - first; ++i) {
		cout << subSeq[i] << ' ';
	}
	cout << endl << endl;
	cout << "теперь протестрируем удаление и возращение элементов из конца дека" << endl << endl;
	double fromBeginnind = firstObject.popFront(), fromEnd = firstObject.popBack();
	cout << "начало: " << fromBeginnind << " конец: " << fromEnd << endl << endl;
	cout << "длина дека после удаления: " << firstObject.len() << endl << endl;
	cout << "конструктор копирования работает нормально: " << endl;
	MyDeque<double> secondObject(firstObject);
	cout << secondObject << endl << endl;
	cout << "добавим два элемента в произвольные места дека(хотя в адекватный дек можно добавить только в начало или в конец...)" << endl;
	for (unsigned long int i = 0; i < 2; ++i) {
		index = rand() % 10;
		a = rand() % 10000 - 5000;
		b = rand() % 10000 - 5000;
		double c = (double)a / b;
		cout << "индекс: " << index << " элемент: " << c << endl;
		secondObject.insertIn(c, index);
		cout << secondObject << endl;
	}
	cout << "длина дека после добавления: " << secondObject.len() << endl << endl;
	cout << "теперь проверим сортировку по возрастанию: " << endl;
	secondObject.Sorting();
	cout << secondObject << endl << endl;
	cout << "проверим конкатенацию: сложим деки firstObject + secondObject" << endl;
	cout << "заодно проверим как работает оператор присвания одного объекта класса MyDeque  другому" << endl;
	firstObject = firstObject + secondObject;
	cout << firstObject << endl;
	cout << "длина дека после добавления: " << firstObject.len() << endl << endl;
	cout << firstObject << endl << endl;
	a = rand() % 20;
	cout << "удалим элемент с индексом " << a << endl;
	firstObject.deleteByIndex(a);
	cout << firstObject << endl << endl;
	secondObject.cleanAll();
	firstObject.cleanAll();
	cout << "длины деков после удаления: " << firstObject.len() << "  " << secondObject.len() << endl << endl;
}

//и тут работает на ура!
void testList() {
	srand(time(0));
	MyDeque<double> firstObject("listSequence");
	cout << "сейчас будут протестированы основные методы класса MyDeque, когда за основу взят Двунаправленный Список" << endl;
	cout << "для начала нагенерируем случайных чисел и добавим их в дек(протестировав добавление в конец и в начало) и посмотрим на наш дек: " << endl;
	cout << "заодно и убедимся, что вывод объекта MyDeque работает нормально" << endl;
	int a = 0, b = 0;
	for (unsigned int i = 0; i < 12; ++i) {
		a = rand() % 10000 - 5000;
		b = rand() % 10000 - 5000;
		double c = (double)a / b;
		if (i % 2) {
			firstObject.pushFront(c);
		}
		else {
			firstObject.pushBack(c);
		}
	}
	cout << firstObject << endl << endl;
	cout << "теперь продемострируем каждый метод класса MyDeque" << endl;
	cout << "длина дека: " << firstObject.len() << "пуст ли дек? " << firstObject.isEmpt() << endl << endl;
	cout << "последний элемент дека: " << firstObject.outBack() << "первый элемент списка: " << firstObject.outFront() << endl << endl;
	unsigned long int index = rand() % 12;
	cout << "элемент с индексом " << index << ": " << firstObject.getValueByIndex(index) << endl << endl;
	index = rand() % 12;
	cout << "индекс элемента " << firstObject.getValueByIndex(index) << ":  " << firstObject.getIndex(firstObject.getValueByIndex(index)) << endl << endl;
	unsigned long int first = 0, second = 0;
	do {
		first = rand() % 12;
		second = rand() % 12;
	} while (first > second);
	//бесят срезы в питоне тем, что не выводится крайний элемент, поэтому будут выделены элементы с индексами 4, 5, 6, 7
	cout << "левая граница: " << first << " правая граница: " << second << endl;
	double* subSeq = firstObject.getSubsequence(first, second);
	for (unsigned long int i = 0; i <= second - first; ++i) {
		cout << subSeq[i] << ' ';
	}
	cout << endl << endl;
	cout << "теперь протестрируем удаление и возращение элементов из конца дека" << endl << endl;
	double fromBeginnind = firstObject.popFront(), fromEnd = firstObject.popBack();
	cout << "начало: " << fromBeginnind << " конец: " << fromEnd << endl << endl;
	cout << "длина дека после удаления: " << firstObject.len() << endl << endl;
	cout << "конструктор копирования работает нормально: " << endl;
	MyDeque<double> secondObject(firstObject);
	cout << secondObject << endl;
	cout << secondObject.len() << endl << endl;
	cout << "добавим два элемента в произвольные места дека(хотя в адекватный дек можно добавить только в начало или в конец...)" << endl;
	for (unsigned long int i = 0; i < 2; ++i) {
		index = rand() % 10;
		a = rand() % 10000 - 5000;
		b = rand() % 10000 - 5000;
		double c = (double)a / b;
		cout << "индекс: " << index << " элемент: " << c << endl;
		secondObject.insertIn(c, index);
		cout << secondObject << endl;
	}
	cout << "длина дека после добавления: " << secondObject.len() << endl << endl;
	cout << "теперь проверим сортировку по возрастанию: " << endl;
	secondObject.Sorting();
	cout << secondObject << endl << endl;
	cout << "проверим конкатенацию: сложим деки firstObject + secondObject" << endl;
	cout << "заодно проверим как работает оператор присвания одного обьекта класса MyDeque  другому" << endl;
	firstObject = firstObject + secondObject;
	cout << firstObject << endl;
	cout << "длина дека после добавления: " << firstObject.len() << endl << endl;
	a = rand() % 20;
	cout << "удалим элемент с индексом " << a << endl;
	firstObject.deleteByIndex(a);
	cout << firstObject << endl << endl;
	secondObject.cleanAll();
	firstObject.cleanAll();
	cout << "длины деков после удаления: " << firstObject.len() << "  " << secondObject.len() << endl << endl;
}


//функция для замера времени работы методов
template<typename T>
void testTimeFunctions(MyDeque<T>& listDeque, MyDeque<T>& arrayDeque)
{
	auto begin = std::chrono::steady_clock::now();
	sort(listDeque, [](double a, double b) {
		return a > b;
		}, [](double& a, double& b) {
			double temp = a;
			a = b;
			b = temp;
		});
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "время сортировки списка: " << elapsed_ms.count() << " ms\n";

	begin = std::chrono::steady_clock::now();
	sort(arrayDeque, [](double a, double b) {
		return a > b;
		}, [](double& a, double& b) {
			double temp = a;
			a = b;
			b = temp;
		});
	end = std::chrono::steady_clock::now();
	auto elapsed2_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "время сортировки массива: " << elapsed2_ms.count() << " ms\n";

	begin = std::chrono::steady_clock::now();
	listDeque.deleteByIndex(67);
	end = std::chrono::steady_clock::now();
	auto elapsed3_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время удаления элемента с индексом 67 из списка: " << elapsed3_ms.count() << " mcs\n";

	begin = std::chrono::steady_clock::now();
	arrayDeque.deleteByIndex(67);
	end = std::chrono::steady_clock::now();
	auto elapsed4_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время удаления элемента с индексом 67 из массива: " << elapsed4_ms.count() << " mcs\n";

	begin = std::chrono::steady_clock::now();
	listDeque.pushBack(389.328);
	end = std::chrono::steady_clock::now();
	auto elapsed5_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время добавления элемента в конец в список: " << elapsed5_ms.count() << " mcs\n";

	begin = std::chrono::steady_clock::now();
	arrayDeque.pushBack(389.328);
	end = std::chrono::steady_clock::now();
	auto elapsed6_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время добавления элемента в конец в массив: " << elapsed6_ms.count() << " mcs\n";

	begin = std::chrono::steady_clock::now();
	listDeque.insertIn(423.42, 89);
	end = std::chrono::steady_clock::now();
	auto elapsed7_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время добавления элемента в позицию под номером 89 в список: " << elapsed7_ms.count() << " mcs\n";

	begin = std::chrono::steady_clock::now();
	arrayDeque.insertIn(423.42, 89);
	end = std::chrono::steady_clock::now();
	auto elapsed8_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "время добавления элемента в позицию под номером 89 в массив: " << elapsed8_ms.count() << " mcs\n";
}
