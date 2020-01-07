#pragma once
#include <iostream>
#include <future>
#include <utility>
#include <thread>

//! thread function
int thread_function(int x) {
	return x + 2;
}









void test_future() {
	//！获取异步线程的值(detach-->得到一个异步的线程)
	//! 通过线程本身的方法无法获取线程函数的返回值,传统的方法都是通过参数来返回
	std::thread t1(thread_function,3);
	t1.detach();

	std::cout << "type of function: " << typeid(decltype(thread_function)).name() << std::endl;
	std::packaged_task<decltype(thread_function)> task(thread_function);

	std::future<int> fut = task.get_future();

	int value = fut.get();

	std::cout << "" << value << std::endl;


	return;
}


struct STU_INFO
{
	std::string _name;
	std::string _subject;
	float       _result;
};

std::mutex _mutex;

//get operation
void get_val(std::promise<STU_INFO>& prom ) {
	std::this_thread::sleep_for(std::chrono::microseconds(1));


	try
	{
		std::lock_guard<std::mutex> xu_lock(_mutex);
		std::cout << "now thread id is : " << std::this_thread::get_id() << std::endl;
		//
		std::future<STU_INFO> stu_fut = prom.get_future();
		auto val = stu_fut.get();
		std::cout << val._name << std::endl;
		std::cout << val._subject << std::endl;
		std::cout << val._result << std::endl;
	}
	catch (...)
	{
		std::cout << "" << std::endl;
	}

}

//set value
void set_val(std::promise<STU_INFO>& prom) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	STU_INFO xu;
	xu._name = "xu.hsu";
	xu._subject = "语文";
	xu._result = 99;

	std::lock_guard<std::mutex> xu_lock(_mutex);
	std::cout << "now thread id is : " << std::this_thread::get_id() << std::endl;

	//set value
	prom.set_value(xu);

}

void test_promise() {

	std::promise<STU_INFO> promise;
	std::thread t1(set_val, std::ref(promise));
	std::thread t2(get_val, std::ref(promise));
	t1.join();
	t2.join();


	return;

}