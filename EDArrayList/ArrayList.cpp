#include "ArrayList.h"


template <class T>
void ArrayList<T>::arrayCopy(unsigned int n, T** dest, T** src)
{
	// Copy directions of src[] to dest[]
	for (unsigned int i = 0; i < n; i++)
		if (src != nullptr)
			dest[i] = src[i];
		else
			dest[i] = nullptr;
}

template <class T>
ArrayList<T>::ArrayList(const T* t)
{
	size = sizeof(t) / sizeof(t[0]);
	array = new T*[size];
	for (unsigned int i = 0; i < size; ++i)
		*array[i] = t[i];
}

template <class T>
ArrayList<T>::ArrayList(unsigned int i)
{
	size = i;
	if (size == 0)
		throw;
	array = new T*[size];
	for (unsigned int j = 0; j < size; ++j)
		array[j] = nullptr;
}

template <class T>
ArrayList<T>::~ArrayList()
{
	clear();
}

template <class T>
void ArrayList<T>::add(const T t)
{
	int index = -1;
	for (unsigned int i = 0; i < size; ++i)
		if (!array[i])
		{
			index = i;
			break;
		}
	/* There's no more space, ensure at least 5 positions more,
	* since it may slow down performance, if you have idea of
	* how many items will be saved, it is recommended to use 
	* first ensureCapacity(int) or initialize the ArrayList
	* with the minimum capacity needed.
	*/
	if (index < 0)
	{
		ensureCapacity(size + 5);
		for (unsigned int i = 0; i < size; ++i)
			if (!array[i])
			{
				index = i;
				break;
			}
	}
	array[index] = new T;
	*array[index] = t;
}

template <class T>
void ArrayList<T>::add(unsigned int i, T t)
{
	// If the index is out of limit then expand the limit
	if (i > size - 1)
		ensureCapacity(i + 1);

	// If the position is empty put item there.
	if (!array[i])
	{
		array[i] = new T;
		*array[i] = t;
	}
	else
	{
		// Add an extra space for the new item
		ensureCapacity(size + 1);

		/* Calculate number of directions to be moved and
		* create new array for those directions.
		*/
		int size1 = size - 1 - i;
		T** backup = new T*[size1];

		// Copy directions to backup array.
		arrayCopy(size1, backup, &array[i]);

		/* Create new direction for item, replacing the other
		* and then put the 't' with its own direction in array.*/
		array[i] = new T;
		*array[i] = t;

		// Recover the rest from backup.
		arrayCopy(size1, &array[i + 1], backup);

		/* Set backup's pointers to null, so we
		* don't free data when we free the backup.*/
		backup = {nullptr};
		delete[] backup;
	}
}

template <class T>
void ArrayList<T>::clear()
{
	for (unsigned int i = 0; i < size; ++i)
		delete array[i];
	delete[] array;
	array = {nullptr};
	size = 0;
}

template <class T>
bool ArrayList<T>::contains(const T& t)
{
	for (unsigned int i = 0; i < size; ++i)
		if (*array[i] == t)
			return true;
	return false;
}

// Ensure minimum capacity of array.
template <class T>
void ArrayList<T>::ensureCapacity(unsigned int i)
{
	// Chech if we don't need to extend the capacity.
	if (i <= size)
		return;

	// Backup directions and number of items in array.
	T** backup = new T*[i];
	arrayCopy(size, backup, array);
	int size1 = size;

	/* Set array's pointers to null, so we
	* don't free data when we free the array.*/
	array = {nullptr};
	delete[] array;

	// Set new sizes.
	size = i;
	array = new T*[size];

	// Recover directions from backup.
	arrayCopy(size1, array, backup);

	// Set to null pointers not initialized with T
	arrayCopy(size - size1, &array[size1]);

	/* Set backup's pointers to null, so we
	* don't free data when we free the backup.*/
	backup = {nullptr};
	delete[] backup;
}

template <class T>
T ArrayList<T>::get(unsigned int i)
{
	return i > size - 1 ? NULL : *array[i];
}

template <class T>
unsigned int ArrayList<T>::getSize() const
{
	return size;
}

template <class T>
int ArrayList<T>::indexOf(const T& t)
{
	for (unsigned int i = 0; i < size; ++i)
		if (*array[i] == t)
			return i;
	return -1;
}

template <class T>
bool ArrayList<T>::isEmpty()
{
	for (unsigned int i = 0; i < size; ++i)
		if (array[i] != nullptr)
			return false;
	return true;
}

template <class T>
void ArrayList<T>::remove(unsigned int i)
{
	if (i > size - 1)
		return;
	delete array[i]; // Free item
	array[i] = nullptr; // Set pointer to null
}

// Replaces an item in 'i' position with 't'
template <class T>
void ArrayList<T>::set(unsigned int i, T t)
{
	if (i < 0 || i > size - 1)
		return;
	if (array[i])
		*array[i] = t;
	else
	{
		array[i] = new T;
		*array[i] = t;
	}
}

// Returns items of std::string or a native variable in a std::string
template <class T>
std::string ArrayList<T>::toString()
{
	std::stringstream s;
	for (unsigned int i = 0; i < size; ++i)
		if (array[i])
			s << '[' << i << "] " << *array[i] << std::endl;
	return s.str();
}

// Trims array to its last not null item
template <class T>
void ArrayList<T>::trimToSize()
{
	int emptySpaces = 0;

	// Count null pointers after last item
	for (unsigned int i = 0; i < size; ++i)
		if (array[i] == nullptr)
			++emptySpaces;
		else
			emptySpaces = 0;

	// If there's none then we don't need to trim array
	if (emptySpaces == 0)
		return;

	/* Create array with the trimmed size and 
	* then copy directions to backup.*/
	T** backup = new T*[size - emptySpaces];
	arrayCopy(size - emptySpaces, backup, array);

	/* Set array's pointers to null, so we 
	 * don't free data when we free the array.*/
	array = {nullptr};
	delete[] array;

	// Set new trimmed sizes.
	size -= emptySpaces;
	array = new T*[size];

	// Recover directions from backup to new array.
	arrayCopy(size, array, backup);

	/* Set backup's pointers to null, so we
	* don't free data when we free the backup.*/
	backup = {nullptr};
	delete[] backup;
}

template class ArrayList<int>;
