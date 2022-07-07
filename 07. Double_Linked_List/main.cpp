#include "dllist.hpp"


int main()
{
    double_linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    std::cout << list << std::endl;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    std::cout << list << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        (*it) += 5;
    }
    std::cout << list << std::endl;


    double_linked_list<int> list1 = list;
    std::cout << list << std::endl;

    double_linked_list<int> list2;
    list2 = list;
    std::cout << list2 << std::endl;


    // list.insert_at(4, 2);
    // std::cout << list << std::endl;
    // list.insert_at(5, 0);
    // std::cout << list << std::endl;
    // list.insert_at(6, 7);
    // std::cout << list << std::endl;
    list.pop_back();
    std::cout << list << std::endl;
    list.pop_front();
    std::cout << list << std::endl;
    list.pop_back();
    std::cout << list << std::endl;
    list.pop_front();
    std::cout << list << std::endl;
    list.pop_back();
    std::cout << list << std::endl;
    list.pop_front();
    std::cout << list << std::endl;
    // list.pop_front();
    // std::cout << list << std::endl;
    // list.pop_front();
    // std::cout << list << std::endl;
    // list.pop_front();
    // std::cout << list << std::endl;

    return 0;
}