#ifndef MYEXCEPTIONS_H_
#define MYEXCEPTIONS_H_

#include <exception>
#include <string>

class ArrayOptionsExceptions : public std::exception
{
public:
	ArrayOptionsExceptions(std::string error) : m_error{ error } {}
	~ArrayOptionsExceptions() = default;
	const char* what() const noexcept { return m_error.c_str(); }
private:
	std::string m_error;
};

class DualListOptionsExceptions : public std::exception
{
public:
	DualListOptionsExceptions(std::string error) : m_error{ error } {}
	~DualListOptionsExceptions() = default;
	const char* what() const noexcept { return m_error.c_str(); }
private:
	std::string m_error;
};

class ArrayExcepton : public std::exception
{
public:
	ArrayExcepton(std::string error) : m_error(error) {}
	~ArrayExcepton() = default;
	const char* what() const noexcept { return m_error.c_str(); }
private:
	std::string m_error;
};

class DualListExceptions
{
public:
	DualListExceptions(std::string error) : m_error{ error } {}
	~DualListExceptions() = default;
	const char* what() const noexcept { return m_error.c_str(); }
private:
	std::string m_error;
};

class DequeExceptions
{
public:
	DequeExceptions(std::string error) : m_error{ error } {}
	~DequeExceptions() = default;
	const char* what() const noexcept { return m_error.c_str(); }
private:
	std::string m_error;
};



#endif //MYEXCEPTIONS_H_