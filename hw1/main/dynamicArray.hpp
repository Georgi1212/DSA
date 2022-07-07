#pragma once

#include<cassert>
#include <stdexcept>

template<class T>
class DynamicArray {
    private:
        T* m_elements;
        unsigned int m_size;
        unsigned int m_capacity;

        void copy(const DynamicArray& other)
        {
            m_size = other.m_size;
            m_capacity = m_size * 2;

            m_elements = new T[m_capacity];

            for(unsigned int i = 0; i < m_size; ++i)
            {
                m_elements[i] = other.m_elements[i];
            }
        }

        void destroy()
        {
            delete[] m_elements;
        }

        void resize()
        {
            this->m_capacity *= 2;
            T* helper_array = new T[m_capacity];

            for(unsigned int i = 0; i < m_size; ++i)
            {
                helper_array[i] = m_elements[i];
            }
            delete[] m_elements;
            m_elements = helper_array;
        }
        
    public:
        DynamicArray()
        {
            m_size = 0;
            m_capacity = 8;
            m_elements = new T[m_capacity];
        }

        DynamicArray(const DynamicArray& other)
        {
            copy(other);
        }

        DynamicArray& operator=(const DynamicArray& other)
        {
            if(this != &other)
            {
                destroy();
                copy(other);
            }
            return *this;
        }

        ~DynamicArray()
        {
            destroy();
        }

        void push_back(const T& element)
        {
            if(m_size == m_capacity)
            {
                resize();
            }
            m_elements[m_size++] = element;
        }

        void push_front(const T& element)
        {
            if(m_size == m_capacity)
            {
                resize();
            }

            for(unsigned int i = m_size; i > 0; --i)
            {
                m_elements[i] = m_elements[i-1];
            }

            m_elements[0] = element;
            ++m_size;
        }

        void pop_back()
        {
            --m_size;
        }

        void pop_front()
        {
            for(unsigned int i = 1; i <= m_size; ++i)
            {
                m_elements[i-1] = m_elements[i];
            }
            --m_size;
        }

        void deleteAt(int index)
        {
            if (index >= m_size)
            {
                throw std::invalid_argument("Index was outside the bounds of the array.");
            }

            for (unsigned int i = index; i < m_size - 1; i++)
            {
                m_elements[i] = m_elements[i + 1];
            }
            this->m_size--;
        }

        const T& operator[](unsigned int index) const
        {
            if (index < m_size) return m_elements[index];
            throw std::invalid_argument("Invalid index");
        }

        T& operator[](unsigned int index)
        {
            if (index < m_size) return m_elements[index];
            throw std::invalid_argument("Invalid index");
        }

        T& front()
        {
            return m_elements[0];
        }

        const T& front() const
        {
            return m_elements[0];
        }

        T& back()
        {
            assert(m_size != 0);
            return m_elements[m_size - 1];
        }

        const T& back() const
        {
            assert(m_size != 0);
            return m_elements[m_size - 1];
        }

        bool empty() const
        {
            return m_size==0;
        }

        unsigned int size() const
        {
            return m_size;
        }
};