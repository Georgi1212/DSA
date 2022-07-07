#pragma once

template<class T>
class queue{
    private:
        T* m_arr{new T[8]};
        size_t m_first{};
        size_t m_last{};
        size_t m_capacity{8};

        void resize()
        {
            m_capacity *= 2;
            T* new_arr = new T[m_capacity];

            for(size_t i = m_first; i < m_last; i++)
            {
                new_arr[i] = m_arr[i];
            }
            std::swap(new_arr, m_arr);
            delete[] new_arr;
            

        }

        size_t next(size_t index) const
        {
            return (index + 1)% m_capacity;
        }

    public:
        queue() = default;
        ~queue()
        {
            delete[] m_arr;
        }

        queue(const queue<T>& other)
        {
            m_first = other.m_first;
            m_last = other.m_last;
            m_capacity = other.m_capacity;

            m_arr = new T[other.m_capacity];

            for(size_t i = 0; i < other.m_last; ++i)
            {
                m_arr[i] = other.m_arr[i];
            }
        }

        queue<T>& operator=(const queue<T>& other)
        {
            queue<T> cpy = other;
            std::swap(m_first, cpy.m_first);
            std::swap(m_last,cpy.m_last);
            std::swap(m_capacity, cpy.m_capacity);
            std::swap(m_arr, cpy.m_arr);

            return *this;
        }

        T& front()
        {
            return m_arr[m_first];
        }

        const T& front() const
        {
            return m_arr[m_first];
        }

        T& back()
        {
            assert(m_last != 0);
            return m_arr[m_last - 1];
        }

        const T& back() const
        {
            assert(m_last != 0);
            return m_arr[m_last - 1];
        }

        void enqueue(const T& element)
        {
            if(m_last == m_capacity)
            {
                resize();
            }

            //m[m_last++] = element;
            m_arr[m_last] = element;
            m_last = next(m_last);
        }

        void dequeue()
        {
            // m_first++;
            m_first = next(m_first);
        }

        size_t size() const
        {
            return (m_last + m_capacity - m_first) % m_capacity;
        }

        bool empty() const
        {
            return size() == 0;
        }
};