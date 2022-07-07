#include "stack.hpp"

int main()
{
    stack<int> s;
    s.push(1);
    std::cout<<s.tos()<<std::endl;
    s.push(2);
    std::cout<<s.tos()<<std::endl;
    s.push(3);
    std::cout<<s.tos()<<std::endl;
    s.push(4);
    std::cout<<s.tos()<<std::endl;

    stack<int> s1 = s;
    s1.print();

    std::cout<<std::endl;

    std::cout<<s1.tos()<<std::endl;
    
    s1.pop();

    stack<int> s2;
    s2 = s1;
    s2.print();

    std::cout<<std::endl;

    std::cout<<s2.tos()<<std::endl;

    std::cout<<std::endl;
    
    std::cout << s.tos() << std::endl;
    s.pop();
    std::cout << s.tos() << std::endl;
    s.pop();
    std::cout << s.tos() << std::endl;
    s.pop();
    std::cout << s.tos() << std::endl;
    s.pop();
    std::cout << std::boolalpha << s.empty() << std::endl;

    return 0;
}