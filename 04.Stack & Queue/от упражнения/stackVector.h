#include<iostream>
#include<vector>
#include<cassert>

template<class T, class Container = std::vector<T> > //по-добре вместо std::vector да се използва Vector.hpp (моята имплементация на вектор, защото 
class stackVector									//има функциите resize, конструкторите и деструкторите
{
	private:
		Container m_data;
		
		/*void resize()
		{
			T* new_elements = new T[m_capacity*2];
			for(size_t i = 0; i < m_size; ++i)
			{
				new_elements[i] = m_elements[i];
			}
			std::swap(new_elements, m_elements);
			m_capacity*=2;
			delete[] new_elements;
		}*/
				
	public:
		size_t size() const
		{
			return this->m_data.size();
		}	
		/*stackVector()
		{
			this->m_data = new T[this->m_capacity];
			this->m_size = 0;
			this->m_capacity = 8;
		}
		
		~stackVector()
		{
			delete[] m_data;
		}*/                                       // ------> защото тези фuнкционалности ги има в std::vector
		
		/*stackVector(const stackVector<T, Container>& other)
		{
			m_data = new T[other.m_capacity]; //m_data = new T[other.getCapacity()];  ??
			for(size_t i=0; i< other.m_size; ++i)  // for(size_t i=0; i < other.getSize(); ++i)
			{
				m_data[i] = other.m_data[i];
			}
			
			m_size = other.m_size;
			m_capacity = other.m_capacity;
		}
		
		stackVector<T,Container>& operator=(const stackVector<T, Container>& other)
		{
			stackVector<T, Container> cpy = other;
			std::swap(m_data, cpy.m_data);
			std::swap(m_size, cpy.m_size);
			std::swap(m_capacity, cpy.m_capacity);
			
			return *this;
		}*/
		
		T& top()
		{
			//assert(m_size != 0); //ako e 0 da prekusne
			//return m_data[m_size - 1];
			return m_data.back();
		}
		
		const T& top() const // не можем да променим елементите. елементите в  private ги възприемаме като константи и затова трябва да върнем константна референция
		{
			//assert(m_size != 0);
			//return m_data[m_size - 1];
			return m_data.back();
		}
		
		void push(const T& element)
		{
		/*	if(m_size == m_capacity)
			{
				resize();
			}
			m_elements[m_size++] = element;*/
			
			this->m_data.push_back(element);
		}
		
		void pop()
		{
			//assert(m_size != 0);
			//m_size--;
			this->m_data.pop_back();
		}
		
		bool empty() const
		{
			//return m_size == 0;
			return m_data.empty();
		}
};
