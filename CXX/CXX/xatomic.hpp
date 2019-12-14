#pragma once
#include <atomic>
#include <mutex>
//! 原子版本的计数器
struct Counter {

	//! 原子
	std::atomic<int> value = 0;

	//! increment value
	void increment() {
		value++;
	}

	//! decrement value
	void decrement() {
		value--;
	}

	//！get the value
	int get() {
		return value.load();
	}

};

struct MCounter {
	std::mutex _mutex;
	int value = 0;
	//
	void increment() {
		std::unique_lock<std::mutex> lock(_mutex);
		value++;
	}
	//
	void decrement() {
		std::unique_lock<std::mutex> lock(_mutex);
		value--;
	}
	//
	int get() {
		return value;
	}
};


















