#pragma once
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <sstream>

template <class T>

class ArrayList
{
private:
	T** array;
	unsigned int size;
	static void arrayCopy(unsigned int, T**, T** = nullptr);
public:
	explicit ArrayList(const T*);
	explicit ArrayList(unsigned int);
	~ArrayList();
	void add(const T);
	void add(unsigned int, T);
	void clear();
	bool contains(const T&);
	void ensureCapacity(unsigned int);
	T get(unsigned int);
	unsigned int getSize() const;
	int indexOf(const T&);
	bool isEmpty();
	void remove(unsigned int);
	void set(unsigned int, T);
	std::string toString();
	void trimToSize();
};
#endif
