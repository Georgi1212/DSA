#include "queue.hpp"

int main()
{
    queue<int> q;
    q.enqueue(1);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.enqueue(2);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.enqueue(3);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.enqueue(4);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;

    int one = q.front();

    queue<int> q1 = q;
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;
    q1.dequeue();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;

    queue<int> q2;
    q2 = q1;
    q2.dequeue();
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;
    std::cout << q.size() << " " << q2.front() << " " << q2.back() << std::endl;

    q.dequeue();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.dequeue();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.dequeue();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.dequeue();
    std::cout << std::boolalpha << q.empty() << std::endl;

    std::cout << one << std::endl;
    return 0;
}