#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


void printHeap(std::vector<int>&& vecs) {
	for (auto iter : vecs) {
		std::cout << iter << std::endl;
	}
}


void test_heap() {
	std::vector<int> xu_heap = { 9, 6, 2, 4, 7, 0, 1, 8, 3, 5 };

	//构建一个最小的堆
	std::make_heap(xu_heap.begin(),xu_heap.end(),std::greater<int>());
	printHeap(std::move(xu_heap));
	std::cout << "对顶的元素：" << xu_heap[0] << std::endl;

	std::pop_heap(xu_heap.begin(), xu_heap.end(), std::greater<int>());
	xu_heap.pop_back();
	printHeap(std::move(xu_heap));
	std::cout << "对顶的元素：" << xu_heap[0] << std::endl;

	std::pop_heap(xu_heap.begin(), xu_heap.end(), std::greater<int>());
	xu_heap.pop_back();
	printHeap(std::move(xu_heap));
	std::cout << "对顶的元素：" << xu_heap[0] << std::endl;

	std::cout << "----------------------" << std::endl;
	//构建一个最大堆
	std::make_heap(xu_heap.begin(), xu_heap.end(), std::less<int>());
	printHeap(std::move(xu_heap));


	return;
}