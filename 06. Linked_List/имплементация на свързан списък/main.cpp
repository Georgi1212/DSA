#include "linked_list.hpp"

int main()
{
    LList<int> list;
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
    //list.pop_front();
    //list.pop_back();
    //list.print();
    std::cout<<list.empty()<<std::endl;

    LList<int> l = list;
    l.print();

    LList<int> l1;
    l1 = l;
    l1.print();

    return 0;
}