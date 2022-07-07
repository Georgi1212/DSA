#include <cassert>
#include <stdexcept>
#include <iostream>

template <class T>
struct node
{
    T value{};
    node* next_element{nullptr};
};

template<class T>
class linked_list
{
    public:
        linked_list()=default;
        ~linked_list()
        {
            auto current = first;
            while(current != nullptr)
            {
                auto current_cpy = current;
                delete current;
                current = current_cpy->next_element;
            }
        }
        //Ro3

        void push_back(const T& value)
        {
            if(last == nullptr)
            {
                assert(first == nullptr);
                first = new node<T>();
                first->value = value;
                last = first;
            }
            else
            {
                last->next_element = new node<T>();
                last->next_element->value = value;
                last = last->next_element;
            }
        }

        void push_front(const T& value)
        {
            auto new_element = new node<T>();
            new_element->value = value;
            new_element->next_element = first;

            if(first == nullptr)
            {
                assert(last == nullptr);
                last = new_element;
            }
            first = new_element;
        }

        void pop_front()
        {
            if(first != nullptr)
            {
                auto first_cpy = first;
                first = first->next_element;
                delete first_cpy;
                if(first == nullptr)
                {
                    last = nullptr;
                }
            }
            else
            {
                throw std::invalid_argument("Cannot pop empty list");
            }
        }

        void pop_back()
        {
            if(last == nullptr){
                throw std::invalid_argument("Cannot pop empty list");
            }

            if(last == first)
            {
                delete first;
                first=nullptr;
                last=nullptr;
                return;
            }
            auto current = first;
            while(current->next_element != last) //current->next_element->next_element != nullptr
            {
                current = current->next_element;
            }
            delete last;
            last = current;
            last->next_element = nullptr;
        } 

        void print()
        {
            auto current = first;
            while(current != nullptr)
            {
                std::cout<<current->value;
                current = current->next_element;
            }
            std::cout<<std::endl;
        }
    private:
        node<T>* first{nullptr};
        node<T>* last{nullptr};

};

int main()
{
    linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.print();
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.print();
    list.pop_front();
    list.pop_back();
    list.print();
    list.pop_front();
    list.pop_back();
    list.print();
    list.pop_front();
    list.pop_back();
    list.print();
    return 0;
}