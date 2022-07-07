#include<cassert>
#include<iostream>

template<typename T>
class queue
{
	public:
		queue() = default;
		~queue()
	    {
	        delete[] m_elements;
	    }
		queue(const queue<T>& other)
		{
			m_elements = new T[other.m_capacity];
	        for (size_t i = 0; i < other.m_last; i++)
	        {
	            m_elements[i] = other.m_elements[i];
	        }
	        m_first = other.m_first;
	        m_last = other.m_last;
	        m_capacity = other.m_capacity;
		}
		queue<T> &operator=(const queue<T> &other)
	    {
	        queue<T> cpy = other;
	        std::swap(m_elements, cpy.m_elements);
	        std::swap(m_first, cpy.m_first);
	        std::swap(m_last, cpy.m_last);
	        std::swap(m_capacity, cpy.m_capacity);
	        return *this;
	    }
		
		T& front()
		{
			assert(m_size != 0);
			return m_elements[m_first];
		}
		const T& front() const
		{
			assert(m_size != 0);
			return m_elements[m_first];
		}
		
		T& back()
		{
			assert(m_size != 0);
			return m_elements[m_last-1];
		}
		
		const T &back() const
	    {
	        assert(m_last != 0);
	        return m_elements[m_last - 1];
	    }
		
		void push(const T& element)
		{
			if(m_size == m_capacity)
			{
				resize();
			}
			m_size++;
			m_elements[m_last++] = element;
		}
		
		void pop()
		{
			m_first++;
		}
		
		size_t size() const
		{
			return m_last - m_first;
		}
		
		bool empty() const
		{
			return size() == 0;
		}
		
	private:
		T* m_elements{new T[2]}; // инициализаме тези променлии с default-на стойност (може да зануляваме). Върши работата на default-ен constructor
		size_t m_size{};
		size_t m_first{};
		size_t m_last{};
		size_t m_capacity{2};
		
		void resize()
		{
			T* new_elements = new T[m_capacity*2];
			for(size_t i = m_first; i < m_last; ++i)
			{
				new_elements[i] = m_elements[i];
			}
			std::swap(new_elements, m_elements);
			m_capacity*=2;
			delete[] new_elements;
		}
};


int main()
{
    queue<int> q;
    q.push(1);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.push(2);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.push(3);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.push(4);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;

    queue<int> q1 = q;
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;
    q1.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;

    queue<int> q2;
    q2 = q1;
    q2.pop();
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;
    std::cout << q.size() << " " << q2.front() << " " << q2.back() << std::endl;

    q.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << std::boolalpha << q.empty() << std::endl;
    return 0;
}
