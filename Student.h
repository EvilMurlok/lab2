#pragma once
#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <iostream>
class Student
{
public: 
	Student() : name{ "Someone" }, gender{ 'M' }, averageMark{ 0.0 } {};
	Student(std::string Name, char Gender, double AverageMark) : name{ Name }, gender{ Gender }, averageMark{ AverageMark } {};
	//Student(const Student& valToCopy) : name{valToCopy.name, } хахa компилятор сам сгенерирует конструктор копирования по полям(слишком изи)
	~Student() = default;
	std::string getName() { return name; };
	char getGender() { return gender; };
	double getAverageMark() { return averageMark; };
	void swapStudents(Student& val1) {
		std::string temp1 = name;
		char temp2 = gender;
		double temp3 = averageMark;
		name = val1.name;
		gender = val1.gender;
		averageMark = val1.averageMark;
		val1.averageMark = temp3;
		val1.name = temp1;
		val1.gender = temp2;
	}
	Student& operator=(const Student& valueToEqv) {
		if (this == &valueToEqv) {
			return *this;
		}
		else {
			name = valueToEqv.name;
			gender = valueToEqv.gender;
			averageMark = valueToEqv.averageMark;
		}
		return *this;
	}
	friend std::istream& operator>>(std::istream& is, Student& valToInput) {
		std::cout << "введите имя: ";
		std::getline(is, valToInput.name).get();
		std::cout << "введите пол(M, W): ";
		(is >> valToInput.gender).get();
		std::cout << "введите средний балл: ";
		(is >> valToInput.averageMark).get();
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const Student& valToOutput) {
		os << "(" << valToOutput.name << ' ' << valToOutput.gender << ' ' << valToOutput.averageMark << ')';
		return os;
	}
private:
	std::string name;
	char gender;
	double averageMark;
};
#endif // !STUDENT_H_
