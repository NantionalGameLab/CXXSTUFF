#pragma once
#include <iostream>
int ctrl = 0;

void test_do() {
	do
	{
		ctrl++;
		std::cout << ctrl << std::endl;
	} while (ctrl < 100);
}