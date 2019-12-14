#pragma once
#include <iostream>
//！研究参数转发-完美转发
template<typename T>
void printT(T& t) {
	std::cout << "left value" << t <<std::endl;
}

//! 
template<typename T>
void printT(T&& t) {
	std::cout << "right value" << t << std::endl;
}


//!
template<typename T>
void testForward(T&& t) {
	printT(t);
	printT(std::forward<T>(t));
	printT(std::move(t));
	std::cout << "---------------------------" << std::endl;
}