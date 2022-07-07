#pragma once
#include<iostream>
#include<stdexcept>
#include<cassert>

template<class T>
struct Node
    {
        T m_data{};
        Node* m_next{nullptr};

        Node(const T& data, Node<T>* next) 
        {
            m_data = data;
            m_next = next;
        }
    };

template<class T>
class LList{
    private:
        Node<T> *m_first;
        Node<T> *m_last;

        //size_t m_size; - когато ни интересува броя на възлите в списъка

        void copy(const LList& other)
        {
            //m_size = 0;
            m_first = m_last = nullptr;

            Node<T>* current = other.m_first;

            while(current)
            {
                push_back(current->m_data);
                current = current->m_next;
            }
        }
        void destroy()
        {
            while(m_first != nullptr)
            {
                Node<T>* current = m_first;
                m_first = m_first->m_next;
                delete current;
            }
        }

    public:
        LList() : m_first(nullptr), m_last(nullptr) {} //m_size(0)
        LList(const LList& other)
        {
            copy(other);
        }
        LList& operator=(const LList& other)
        {
            if(this != &other)
            {
                destroy();
                copy(other);
            }
            return *this;
        }
        ~LList()
        {
            destroy();
        }

        bool empty() const { return (m_first == nullptr) && (m_last == nullptr); }
        //size_t size() const { return m_size; }

        void push_back(const T& element)
        {
            Node<T>* new_last = new Node<T>();
            new_last->m_data = element;

            if(m_last != nullptr)
            {
                m_last->m_next = new_last;
            }

            if(m_first == nullptr)
            {
                assert(m_last == nullptr);
                m_first = new_last;
            }
            m_last = new_last;
            //++m_size;
        }

        void push_front(const T& element)
        {
            Node<T>* new_first = new Node<T>();
            new_first->m_data = element;
            new_first->m_next = m_first;

            if(m_last == nullptr)
            {
                assert(m_first == nullptr);
                m_last = new_first;
            }
            m_first = new_first;
        }

        //void push_after(Node<T>* ptr, const T& element);

        void pop_front()
        {
            if(m_first == nullptr)
            {
                assert(m_last == nullptr);
                throw std::invalid_argument("Cannot pop empty list");
            }

            Node<T>* first_cpy = m_first;
            m_first = m_first->m_next;
            delete first_cpy;
            if(m_first == nullptr)
            {
                m_last = nullptr;
            }
        }

        //linear complexity
        void pop_back()
        {
            if (m_last == nullptr)
            {
                assert(m_first == nullptr);
                throw std::invalid_argument("Cannot pop empty list");
            }
            if(m_first == m_last)
            {
                delete m_first;
                m_first = nullptr;
                m_last = nullptr;
                return;
            }
            Node<T>* last_cpy = m_last;
            Node<T>* current = m_first;

            while(current->m_next != m_last)
            {
                current = current->m_next;
            }
            current->m_next = nullptr;
            m_last = current;
            delete last_cpy;

        }
        //void pop_nth ...

        //Node* find(const T& ) SH
        //Node* get(size_t index) SH

        void print()
        {
            Node<T>* current = m_first;
            while(current != nullptr)
            {
                std::cout<< current->m_data << " ";
                current = current->m_next;
            }
            std::cout << std::endl;
        }
};

