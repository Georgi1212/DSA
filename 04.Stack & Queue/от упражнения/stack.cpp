//top-връща референция към елемента на върха
//push-добавя елемент на върха
// pop- премахва елемент на върха

//size-броя на елементите на стека
// empty- връща дали е празен стека

// ==, >, <, ... - лексикографска наредба (линейна сложност, защото обхожда всички елем. на стека и ги сравнява)
#include<cassert>
#include<iostream>



template<class T> // ако имаме стек от различни типове -> полиморфизъм! (хетерогенен контейнер (клас))
class stack
{
	public:
		stack() = default; // : elements{new T[2]},...;
		~stack()
		{
			delete[] m_elements;
		}
		
		stack(const stack<T>& other)
		{
			m_elements = new T[other.m_capacity];
			for(size_t i=0; i< other.m_size; ++i)
			{
				m_elements[i] = other.m_elements[i];
			}
			m_size = other.m_size;
			m_capacity = other.m_capacity;
		}
		
		stack<T>& operator=(const stack<T>& other)
		{
			stack<T> cpy = other; // вика copy constructor.
			std::swap(m_elements, cpy.m_elements);
			std::swap(m_size, cpy.m_size);
			std::swap(m_capacity, cpy.m_capacity);
			return *this;
		}
		
		T& top()
		{
			assert(m_size != 0); //ako e 0 da prekusne
			return m_elements[m_size-1];
		}
		
		const T& top() const // не можем да променим елементите. елементите в  private ги възприемаме като константи и затова трябва да върнем константна референция
		{
			assert(m_size != 0);
			return m_elements[m_size-1];
		}
		
		void push(T element)
		{
			if(m_size == m_capacity)
			{
				resize();
			}
			m_elements[m_size++] = element;
		}
		
		void pop()
		{
			assert(m_size != 0);
			m_size--;
		}
		size_t size() const
		{
			return m_size;
		}
		bool empty() const
		{
			return m_size == 0;
		}
		
		
	private:
		T* m_elements{new T[2]}; // инициализаме тези променлии с default-на стойност (може да зануляваме). Върши работата на default-ен constructor
		size_t m_size{};
		size_t m_capacity{2};
		
		void resize()
		{
			T* new_elements = new T[m_capacity*2];
			for(size_t i = 0; i < m_size; ++i)
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
	stack<int> s;
    s.push(1);
    std::cout << s.top() << std::endl;
    s.push(2);
    std::cout << s.top() << std::endl;
    s.push(3);
    std::cout << s.top() << std::endl;
    s.push(4);

    auto s1 = s;
    stack<int> s2;

    std::cout<<s1.top()<<std::endl;
    s1.pop();
    s2 = s1;
    std::cout<<s1.top()<<std::endl;
    std::cout<<s2.top()<<std::endl;
    s2.pop();
    std::cout<<s1.top()<<std::endl;
    std::cout<<s2.top()<<std::endl;


    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << std::boolalpha << s.empty() << std::endl;
    return 0;
}
