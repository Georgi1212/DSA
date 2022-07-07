#pragma once

#include <iostream>
#include <cassert>
#include <stdexcept>


template<class T>
class stack
{
    private:
        T* m_arr{new T[8]};
        size_t m_size{};
        size_t m_capacity{8};

        void resize()
        {
            m_capacity *= 2;
            T* helper_arr = new T[m_capacity];
            for(size_t i = 0; i < m_size; ++i)
            {
                helper_arr[i] = m_arr[i];
            }

            delete[] m_arr;
            m_arr = helper_arr;
        }
    public:
        stack() = default;
        ~stack()
        {
            delete[] m_arr;
        }

        stack(const stack<T>& other)
        {
            m_arr = new T[other.m_capacity];

            for(size_t i = 0; i < other.m_size; ++i)
            {
                m_arr[i] = other.m_arr[i];
            }
            m_size = other.m_size;
            m_capacity = other.m_capacity;
        }

        stack<T>& operator=(const stack<T>& other)
        {
            stack<T> cpy = other;
            std::swap(m_size, cpy.m_size);
            std::swap(m_capacity, cpy.m_capacity);
            std::swap(m_arr, cpy.m_arr);

            return *this;
        }

        const T& tos() const
        {
            assert(m_size != 0);
            return m_arr[m_size - 1];
        }

        T &tos()
        {
            assert(m_size != 0);
            return m_arr[m_size - 1];
        }

        void push(const T& element)
        {
            if(m_size == m_capacity)
            {
                resize();
            }
            m_arr[m_size++] = element;
        }

        void pop()
        {
            assert(m_size !=0);
            m_size--;
        }

        bool empty() const
        {
            return m_size == 0;
        }

        size_t size() const
        {
            return m_size;
        }

        void print() const
        {
            std::cout<<"Your stack is: ";

            for(size_t i = 0; i < m_size; i++)
            {
                std::cout<<m_arr[i]<< " ";
            }
        }
};
