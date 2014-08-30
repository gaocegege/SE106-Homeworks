/**
* Homework 2: Using Template
* Assigned: September 13
* Due: September 23 24:00
**/

// [TODO]
// Student ID: 5120379091
// Name: GaoCe
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstdlib>

template <typename T>
class Vector {
private:
  // [TODO] Add private variables and methods here
  T *elements;
  int number;
  int able;

  void deepCopy(const Vector & x);

  void expandCapacity();

public:
  // Do NOT modify following interfaces
  Vector();
  Vector(int size, const T& val = T());
  Vector(const Vector& x);
  ~Vector();
  Vector<T>& operator=(const Vector<T>& x);
  int size() const;
  bool empty() const;
  T& operator [](int pos) const;
  void resize(size_t n, T val = T());
  void push_back(const T& val);
};

template <typename T>
void Vector<T>::deepCopy(const Vector &x)
{
  number = x.size();
  able = number;
  T *array = new T[able];
  if (number == 0)
    elements = NULL;
  else
  {
    for (unsigned i = 0; i < number; i++)
      array[i] = x.elements[i];
  }
  delete[] elements;
  elements = array;
}

template <typename T>
void Vector<T>::expandCapacity()
{
  if (able * 2 > 1)
    able = able * 2;
  else
    able = 1;
  T *array = new T[able];
  for (unsigned i = 0; i < number; i++)
    array[i] = elements[i];
  if (elements != NULL)
    delete[] elements;
  elements = array;
}

// (default constructor)
// Constructs an empty container, with no elements.
template <typename T>
Vector<T>::Vector() {
// [TODO]
  number = 0;
  able = 0;
  elements = NULL;
}

// (fill constructor)
// Constructs a container with n elements.
// Each element is a copy of val.
template <typename T>
Vector<T>::Vector(int size, const T& val) {
// [TODO]
  able = size;
  number = size;
  if (size == 0)
  {
    elements = NULL;
  }
  else
  {
    elements = new T[size];
    for (unsigned i = 0; i <size; i++)
      elements[i] = val;
  }
}

// (copy constructor)
// Constructs a container with a copy of each of the
// elements in x, in the same order.
template <typename T>
Vector<T>::Vector(const Vector& x) {
// [TODO]
  number = x.size();
  able = number;
  T *array = new T[number];
  for (unsigned i = 0; i < number; i++)
    array[i] = x[i];
  delete[] elements;
  elements = array;
}

// (destructor)
// Destroys the container object.
template <typename T>
Vector<T>::~Vector() {
// [TODO]
  if (elements != NULL) 
    delete[] elements;
}

// operator=
// Assigns new contents to the container, replacing its
// current contents, and modifying its size accordingly.
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x) {
// [TODO]
  if (this != &x)
  {
      deepCopy(x);
  }
  return *this;
}

// size
// Returns the number of elements in the vector.
// This is the number of actual objects held in the
// vector, which is not necessarily equal to its
// storage capacity.
template <typename T>
int Vector<T>::size() const {
// [TODO]
  return number;
}

// empty
// Returns whether the vector is empty
template <typename T>
bool Vector<T>::empty() const {
// [TODO]
  return (number == 0);
}

// operator[]
// Returns a reference to the element at position n
// in the vector container.
// if the requested position is out of range, the
// behavior is undefined
template <typename T>
T& Vector<T>::operator[](int pos) const {
// [TODO]
  return elements[pos];
}

// resize
// Resizes the container so that it contains n elements.
// If n is smaller than the current container size, the 
// content is reduced to its first n elements, removing 
// those beyond (and destroying them).
// If n is greater than the current container size, the 
// content is expanded by inserting at the end as many 
// elements as needed to reach a size of n. If val is 
// specified, the new elements are initialized as copies 
// of val, otherwise, they are value-initialized.
template <typename T>
void Vector<T>::resize(size_t n, T val) {
// [TODO]
  T *array = new T[n];
  if (n < number)
    for (unsigned i = 0; i < n; i++)
      array[i] = elements[i];
  else if (n > number)
  {
    while (n > able)
      expandCapacity();
    for (unsigned i = 0; i < n; i++)
      array[i] = elements[i];
  }
  delete[] elements;
  elements = array;
  number = able = n;
}

// push_back
// Adds a new element at the end of the vector, after its
// current last element. The content of val is copied (or
// moved) to the new element.
template <typename T>
void Vector<T>::push_back(const T& val) {
// [TODO]
  if (able == number)
    expandCapacity();
  elements[number] = val;
  number++;
}

#endif

