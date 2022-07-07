#include <cassert>
#include <iostream>

template <typename T>
class double_linked_list
{
public:
    template <typename U>
    struct node
    {
        U value{};
        node *next{};
        node *prev{};
    };

    template  <typename U>
    class iterator
    {
    public:
        iterator(node<U>* ptr) : ptr{ptr} {}
        // ++i
        iterator& operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        // i++
        iterator operator++(int)
        {
            auto cpy = *this;
            ptr = ptr->next;
            return cpy;
        }
        bool operator==(const iterator<U> other)
        {
            return ptr == other.ptr;
        }
        bool operator!=(const iterator<U> other)
        {
            return !(*this == other);
        }
        // *i
        U& operator*()
        {
            return ptr->value;
        }
    private:
        node<U>* ptr;
    };

    double_linked_list() = default;

    ~double_linked_list()
    {
       destroy();
    }

    double_linked_list(const double_linked_list<T> &other)
    {
        copy(other);
    }

    double_linked_list &operator=(const double_linked_list<T> &other)
    {
        if(this != &other)
        {
            destroy();
            copy(other);
        }
        return *this;
    }

    bool is_empty() const
    {
        return size == 0;
    }

    void push_back(const T &value)
    {
        if (is_empty())
        {
            push_empty_list(value);
            return;
        }

        auto new_ptr = new node<T>{};
        new_ptr->value = value;
        new_ptr->prev = last;
        last->next = new_ptr;
        last = new_ptr;
        size++;
    }

    void push_front(const T &value)
    {
        if (is_empty())
        {
            push_empty_list(value);
            return;
        }
        auto new_ptr = new node<T>{};
        new_ptr->value = value;
        new_ptr->next = first;
        first->prev = new_ptr;
        first = new_ptr;
        size++;
    }
    void pop_back()
    {
        if (is_empty())
        {
            throw std::length_error("Pop of empty list");
        }
        if (size == 1)
        {
            pop_list_with_one_element();
            return;
        }

        auto to_remove = last;
        last = last->prev;
        last->next = nullptr;
        delete to_remove;
        size--;
    }
    void pop_front()
    {
        if (is_empty())
        {
            throw std::length_error("Pop of empty list");
        }
        if (size == 1)
        {
            pop_list_with_one_element();
            return;
        }

        auto to_remove = first;
        first = first->next;
        first->prev = nullptr;
        delete to_remove;
        size--;
    }
    friend std::ostream &operator<<(std::ostream &out, const double_linked_list<T> &list)
    {
        auto current = list.first;
        while (current != nullptr)
        {
            out << current->value << " ";
            current = current->next;
        }
        return out;
    }

    iterator<T> begin()
    {
        return iterator<T>(first);
    }

    iterator<T> end()
    {
        return iterator<T>(nullptr);
    }

private:
    void push_empty_list(const T &value)
    {
        auto new_elem = new node<T>();
        new_elem->value = value;
        first = new_elem;
        last = new_elem;
        size++;
    }
    void pop_list_with_one_element()
    {
        assert(first == last);
        assert(size == 1);
        delete first;
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    void copy(const double_linked_list<T>& other)
    {
        if(other.first == nullptr)
        {
            return;
        }

/*this->*/first = new node<T>{other.first->value, nullptr, nullptr};
        node<T>* current = first;
        node<T>* currentOther = other.first->next;

        while(currentOther != nullptr)
        {
            current->next = new node<T>{currentOther->value, nullptr, current};
            current = current->next;
            currentOther = currentOther->next;
        }

        /*this->*/last = current;
        
    }
   void destroy()
   {
       auto current = first;
       while (current != nullptr)
       {
           auto cpy = current;
           current = current->next;
           delete cpy;
       }
   }

    node<T> *first{};
    node<T> *last{};
    size_t size{};
};