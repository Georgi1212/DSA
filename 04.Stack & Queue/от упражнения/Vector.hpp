#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
using namespace std;

template<typename T>
class Vector
{
	private: 
		T* vector;
		unsigned int capacity;
		unsigned int size;
		
		void copy(const Vector<T> &other);
		void destroy();
		void resize();
		
	public:
		Vector();
		Vector(const Vector<T>& other);
		Vector<T>& operator=(const Vector<T>& other);
		~Vector();
		
		unsigned int getSize() const;
		void push_back(const T& newElement);
		void pop_back();
		
		void deleteAt(unsigned int index);
		
		void print() const;

		T operator[](unsigned int index) const;
		T& operator[](unsigned int index);
		
		friend istream& operator>>(istream& in, Vector<T>& vect)
		{
		    in >> vect.size;
		    in >> vect.capacity;
		    
		    for (int i = 0; i < vect.size; ++i) {
		        in >> vect.vector[i];
		    }
		    return in;
		}
		
		friend ostream& operator<<(ostream& out, const Vector<T>& vect)
		{
			for (int i = 0; i < vect.size; i++)
			{
				out << vect.vector[i] << endl;
			}
			return out;
	    }
};

template <typename T>
void Vector<T>::copy(const Vector<T>& other)
{
	this->vector= new T[other.capacity];

	for (unsigned int i = 0; i < other.size; i++)
	{
		this->vector[i] = other.vector[i];
	}

	this->capacity = other.capacity;
	this->size = other.size;
}

template <typename T>
void Vector<T>::destroy()
{
	delete[] vector;
}

template <typename T>
void Vector<T>::resize()
{
	this->capacity *= 2;
	T* helper = new T[this->capacity];
	
	for(unsigned int i = 0; i < this->size; ++i)
	{
		helper[i] = this->vector[i];
	}
	
	delete[] vector;
	this->vector = helper;
}

template <typename T>
Vector<T>::Vector() 
{
	this->size = 0;
	this->capacity = 8;
	this->vector = new T[this->capacity];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copy(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if(this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	destroy();
}

template <typename T>
unsigned int Vector<T>::getSize() const
{
	return this->size;
}

template <typename T>
void Vector<T>::push_back(const T& newElement)
{
	if (size >= capacity)
	{
		resize();
	}
	this->vector[size++] = newElement;
}

template <typename T>
void Vector<T>::pop_back()
{
	if (size > 0)
	{
		this->size--;
	}
}

template<typename T>
void Vector<T>::deleteAt(unsigned int index)
{
	if (index >= size)
	{
		cerr << "Index was outside the bounds of the array." << endl;
	}

	for (unsigned int i = index; i < size - 1; i++)
	{
		vector[i] = vector[i + 1];
	}
	this->size--;
}

template<typename T>
void Vector<T>::print() const
{
	for (unsigned int i = 0; i < size; i++) 
	{
        cout << this->vector[i] << " ";
    }
}


template <typename T>
T Vector<T>::operator[](unsigned int index) const
{
	return this->vector[index];
}

template <typename T>
T& Vector<T>::operator[](unsigned int index)
{
	return this->vector[index];
}
