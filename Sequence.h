#ifndef SEQUENCE_H_
#define SEQUENCE_H_


template <typename T>
class Sequence
{
public:
	Sequence() = default;
	virtual ~Sequence() = default;
	virtual void pushFront(T) = 0;
	virtual void pushBack(T) = 0;
	virtual T getFront() = 0;
	virtual T getBack() = 0;
	virtual T getAndDelFromBeginning() = 0;
	virtual T getAndDelFromEnd() = 0;
	virtual bool isEmpty() = 0;
	virtual void deleteAll() = 0;
	virtual void deleteByIndex(unsigned long int) = 0;
	virtual unsigned long int len() = 0;
	virtual long int getIndexByValue(T) = 0;
	virtual void setValueByIndex(T, unsigned long int) = 0;
	virtual T &getValueByIndex(unsigned long int) = 0;
	virtual void Sort() = 0;
	virtual T* getSubsequenceByIndexes(unsigned long int, unsigned long int) = 0;
};
#endif // !SEQUENCE_H_

