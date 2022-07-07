#include "dynamicArray.hpp"

int main()
{
    std::cout << "Testing default constructor and print() --------------------------\n\n";
    DynamicArray<int> d1;

	d1.print();

	std::cout << "Testing copy constructor ------------------------------\n\n";

	DynamicArray<double> d2;
	d2.push_back(1.5);

	std::cout << "Next must be: ";
	d2.print();

	DynamicArray<double> d3 = d2;

	d3.print();

	std::cout << "Testing operator = -----------------------------------\n\n";

	DynamicArray<double> d4;
	d4 = d3;
	d4.print();

	std::cout << "Testing resize() and push_back() -------------------------\n\n";

	d4.push_back(1);
	d4.push_back(2);
	d4.push_back(3);
	d4.push_back(4);
	d4.push_back(5);
	d4.push_back(6);
	d4.push_back(7);
	d4.push_back(8);
	d4.push_back(9);
	d4.print();

	std::cout << "Testing push_front() and getSize() -----------------------\n\n";

	d4.push_front(100);
	d4.print();
	std::cout << ": Size is " << d4.size() << std::endl << std::endl;

	std::cout << "Testing pop_front() and pop_back() -----------------------\n\n";
	
	d4.pop_front();
	d4.pop_back();
	d4.print();

    return 0;
}

