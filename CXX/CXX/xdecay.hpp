#pragma once
#include <iostream>
#include <type_traits>
template<typename T,typename X>
struct decay_equal :std::is_same<typename std::decay<T>::type ,X>::type
{

};

void test_decay() {


	std::cout << "int is same: " << decay_equal<int&,int*>::value << std::endl;

	std::cout << "int is same: " << decay_equal<int&&, int*>::value << std::endl;

	std::cout << "int is same: " << decay_equal<int[], int*>::value << std::endl;

	std::cout << "int is same: " << decay_equal<int, int>::value << std::endl;

	std::cout << "int is same: " << decay_equal<int&, int>::value << std::endl;

	std::cout << "int is same: " << decay_equal<int&&, int>::value << std::endl;

	std::cout << "int is same: " << decay_equal<const int, int>::value << std::endl;
}




