#include "stdafx.h"
#define  _CRT_SECURE_NO_WARNINGS
//! cxx
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <typeindex>
#include <typeinfo>
#include <ctime>


//! boost
#include "boost/shared_array.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/make_shared.hpp"
#include "boost/make_default.hpp"
#include "boost/make_unique.hpp"
//! 内存泄漏的诊断(包括定位具体的行)
#include <crtdbg.h>
//#ifdef _DEBUG
//#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif



/*
 * 研究深拷贝和浅拷贝--------------------------------------- ok
 * 研究make_shared<>  share_ptr<> ---------------------------ok
 * 研究unique_ptr<> -----------------------------------------ok
 * 研究unique_lock<std::mutex>------------------------------ ok
 * 研究atomic--原子操作
 * 研究forward<>  -------------------------------------------OK
 * 研究boost的基本使用--boots::shared_ptr<> -----------------ok
 * 研究base::bind -->绑定函数 占位符 --> --------------------OK
 * 研究std::conditional --条件类型 --------------------------ok
 * 研究std::condition_variable --条件变量------------------- ok
 * 研究可变参数
 * 研究chrono------------------------------------------------ok
 * 研究declType
*/

using namespace std;
using namespace std::chrono;
using namespace std::placeholders;
//! 获取类自身的指针--智能指针--同样可以考虑使用boost::shared_ptr<>
class Self :public std::enable_shared_from_this<Self>{
public:
	Self():m_data(888) {

	}
	~Self() {

	}
	std::shared_ptr<Self> getSelf() {
		//return std::make_shared<Self>(this);----》错误的写法
		return shared_from_this();
	}
public:
	int m_data;
};

//！验证深拷贝和浅拷贝
class CopyData
{
public:
	CopyData() {
		m_ptr = new char[10];
	}
	~CopyData() {
		
		if (m_ptr){
			delete m_ptr;
		}
	}

	CopyData(const CopyData& cp) {
		m_x = cp.m_x;
		m_s = cp.m_s;
		m_ptr = new char[10];
		memcpy(m_ptr,cp.m_ptr,sizeof(cp.m_ptr));
	}

	int m_x;
	char m_s;
	char* m_ptr;
};


//！智能指针的删除器
auto deletor = [](void* p) {
	delete p;

};


//! 线程的开启方式，通过类成员函数
class ThreadClass {
public:
	ThreadClass() {

	}
	~ThreadClass() {

	}
	void run() {
		std::cout << "Here is running... ... ..." << std::endl;
	}
};


//! 线程A 输出A,线程B输出B,那么怎么让这2个线程交替输出ABABABABABAB...
class TypeAB {
public:
	TypeAB() {

	}
	~TypeAB() {
		_thread_a.join();
		_thread_b.join();
	}

	//！ 打印字符的顺序ABABABAB... ...
	void PrintAB() {
		//类的成员函数作为线程函数
		_thread_a = std::thread(&TypeAB::printA,this);
		_thread_b = std::thread(&TypeAB::printB,this);
	}


private:
	std::mutex   _mutex;
	std::thread  _thread_a;
	std::thread  _thread_b;
	std::condition_variable _cv;


private:

		void printA() {
			for (auto m = 0; m < 30; m++) {
				
				std::unique_lock<std::mutex> xu_lock(_mutex);
				_cv.wait_for(xu_lock, std::chrono::duration<float>(3));
				std::cout << std::this_thread::get_id() << "--A--" << std::endl;
				_cv.notify_one();
			}
		}


		void printB() {
			for (auto m = 0; m < 30; m++) {
				std::unique_lock<std::mutex> xu_lock(_mutex);
				_cv.wait_for(xu_lock, std::chrono::duration<float>(3));
				std::cout << std::this_thread::get_id() << "--B--" << std::endl;
				_cv.notify_one();
			}
		}
};



//! 函数绑定调用--std::bind()
int plusNumber(int x,int y,int z) {
	int sum = x + y + z;
	return sum;
}


//! 可变参数模板类
template<class T,class ...Args>
class CVariable {
public:
	CVariable() {

	}
	~CVariable() {

	}
	T getSum() {
		return 0;
	}

};


//! 可变参数函数
int getVarSum(int x,...) {



	return 0;
}



//! 左值 右值  完美转发
int leftValue(int&& x,int&& y) {

	int num = x + y;

	return num;
}



template<class T>
class Forward {
public:
	Forward(T&& x, T&& y):_x(std::forward<T>(x)),_y(std::forward<T>(y)) {

	}
	
	T _x, _y;
};















int main()
{
	//! 关于reset()
	//! 智能指针用完不自己reset()的话 还是有内存泄漏
	//std::shared_ptr<int> ip = std::make_shared<int>(666);
	//std::shared_ptr<int> ippp(new int(888),std::default_delete<int>());
	//std::shared_ptr<int> inppp(new int(777), [](int* p) {delete p; });
	//std::shared_ptr<int> ippppp(new int(555),deletor);
	//std::shared_ptr<int> ipp(ip);
	//std::cout << "ip的实际引用计数: " << ip.use_count() << std::endl;
	//ip.reset();
	//std::cout << "ip的实际引用计数: " << ip.use_count() << std::endl;
	//std::cout << "ipp的实际引用计数: " << ipp.use_count() << std::endl;
	//ipp.reset();
	//std::cout << "ipp的实际引用计数: " << ipp.use_count() << std::endl;
#if 1
	//! 创建指向自身的shared_ptr
	//Self myself;
	//Self *pself = new Self();
	//std::shared_ptr<Self> ss1(pself);
	//delete pself;
	//pself = nullptr;
	//std::cout << "ss1的引用计数是：" << ss1.use_count() << std::endl;

	//std::shared_ptr<Self> ss2 = make_shared<Self>(Self());
	//std::cout << "ss2的引用计数是：" << ss2.use_count() << std::endl;
	//std::cout << "ss2的成员变量是：" << ss2->m_data << std::endl;

	//std::shared_ptr<Self> ss2 = ss1->getSelf();
	//std::shared_ptr<Self> ss3 = myself.getSelf();
	//std::cout << "ss2的引用计数是：" << ss2.use_count() << std::endl;
	//std::cout << "ss3的引用计数是：" << ss3.use_count() << std::endl;
#endif


#if 0
	//! 研究shared_ptr<>的使用,特别是初始化一个常量字符串
	std::shared_ptr<char*> c2 = std::make_shared<char*>(const_cast<char*>("xuxu is stupid..."));
	std::shared_ptr<char*> c3 = c2;
	std::shared_ptr<char*> c4 = std::move(c3);
	std::shared_ptr<char*> c5 = c4;
	std::cout << "c2的内容: " << *c2 << std::endl;
	std::cout << "c2的地址: " << c2 << std::endl;

	std::cout << "c2的引用计数: " << c2.use_count() << std::endl;
	std::cout << "c3的引用计数: " << c3.use_count() << std::endl;
	std::cout << "c4的引用计数: " << c4.use_count() << std::endl;
	std::cout << "c5的引用计数: " << c5.use_count() << std::endl;

	char* ps = "xi is stupid...\0";
	std::cout << "ps: " << ps << std::endl;


	//! weak_ptr<>
	std::weak_ptr<char*> wc1(c5);
	std::cout << "wc1 引用计数: " << wc1.use_count() << std::endl;
	//! 为了解决shared_ptr<>循环引用造成的内存泄露，使用weak_ptr<>作为辅助来监督shared_ptr<>的执行
	//! 判断weak_ptr<>所持有的shared_ptr<>对象是否过期，如果没有的话，通过Lock()方法返回一个有效的shared_ptr<>指针
	if (!wc1.expired()) {
		std::shared_ptr<char*> useful_ptr = wc1.lock();
		std::cout << "weak1: " << *useful_ptr << std::endl;
	}

#endif



#if 0
	//! unique_ptr<>
	std::unique_ptr<char> uc1 = make_unique<char>('v');
	char* c1 = uc1.get();
	std::cout << "uc1: " << uc1.get() << std::endl;
	std::cout << "c1: " << *c1 << std::endl;
	delete c1;

#endif


# if 0 //浅拷贝-深拷贝
	CopyData data1, data2;
	data1.m_x = 1;
	data1.m_s = 's';
	data1.m_ptr = "this is a inner string";

	data2 = data1;
	std::cout << "data2: " << data2.m_x << std::endl;
	std::cout << "data2: " << data2.m_s << std::endl;
	std::cout << "data2: " << data2.m_ptr << std::endl;

	{
		//！如果是浅拷贝，两个对象指向同一个内存，造成double free,破坏了堆的结构，程序崩溃
		//! 如果添加拷贝构造函数，即是实现深拷贝，那么对象中的m_ptr指向不同的堆内存，程序不会崩溃
		CopyData data3;
		CopyData data4(data3);
	}
#endif 

#if 0 //通过代码输出不同类型的变量所属的内存区域
	int param1 = 10;
	int *param2 = NULL;
	int *param3 = new int();
	static int param4 = 8;
	static int param5;
	const int param6 = 9;
	delete param3;
#endif


#if 1 //std::conditional<true,double,double>

#endif



#if 0 //boost::shared_ptr<>
	//boost::shared_ptr<int> bp = boost::make_shared<int>(111);
	boost::shared_ptr<int> bp2(new int(999999));

	std::cout << "boost--shared_ptr<>: " << *bp2 << std::endl;
	std::cout << "boost--shared_ptr<> 引用次数: " << bp2.use_count() << std::endl;
	bp2.reset();


	boost::shared_ptr<float> fp(new float(1.00));
	std::cout << "fp: " << fp.use_count() << std::endl;
#endif



#if 0 //条件类型，根据前置条件判断模板类型的实际类型
	typedef std::conditional<true, int, double>::type Type1;
	typedef std::conditional<false, int, double>::type  Type2;

	std::cout << typeid(Type1).name() << std::endl;
	std::cout << typeid(Type2).name() << std::endl;

	Type1 a = 2.6;
	Type2 b = 2.1;

	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
#endif


#if 0  //条件变量-锁-线程-生产者--消费者
	TypeAB ab;
	ab.PrintAB();

#endif



#if 0 //chrono--时间及日期的使用
	system_clock::time_point tp_start = system_clock::now();
	for (auto m = 0;m < 1000;m++)
	{
		std::cout << "***" << std::endl;
	}
	system_clock::time_point tp_end = system_clock::now();
	std::chrono::duration<double> time_span = duration_cast<std::chrono::duration<double>>(tp_end - tp_start);
	std::cout << "经过了：" << time_span.count() << "秒" << std::endl;

	//! 输出昨天 今天和明天
	//! 思路是获取现在的时刻-now(),然后加上一天持续的时间，或减去一天持续的时间

	std::chrono::duration<int, std::ratio<60 * 60 * 24>> one_day(1);
	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;
	system_clock::time_point yesterday = today - one_day;

	std::time_t tomorrow_time, yesterday_time;
	tomorrow_time = system_clock::to_time_t(tomorrow);
	//yesterday_time = system_clock::to_time_t(yesterday);
	char buff[128], buff2[128];
	ctime_s(buff, sizeof(buff), &tomorrow_time);
	ctime_s(buff2, sizeof(buff2), &yesterday_time);
	std::cout << "明天是: " << buff << std::endl;
	std::cout << "昨天是: " << buff2 << std::endl;
	
#endif


#if 0
	auto bf1 = std::bind(plusNumber,1,2,3);
	std::cout << "bind1 result: "  <<  bf1() << std::endl;
	auto bf2 = std::bind(plusNumber,_1,_2,_3);
	std::cout << "bind2 result: " << bf2(6,6,6) << std::endl;
#endif




#if 1 //可变参数模板类的使用方法

	//CVariable<double,double,int> cvv;
	//std::cout << "res: " <<  cvv.getSum(1.2) << std::endl;

#endif



#if 1 //完美转发
	int res = leftValue(2, 3);
	std::cout << "res: " << res << std::endl;

	//给定2个左值,那么函数参数中的右值引用怎么绑定到左值上
	int x_ = 10, y_ = 20;
	int res2 = leftValue(static_cast<int&&>(x_), static_cast<int&&>(y_));
	int res3 = leftValue(std::move(x_), std::move(y_));
	std::cout << "res2: " << res2 << std::endl;
	std::cout << "res3: " << res3 << std::endl;


	Forward<float> fff(8,9);
	std::cout << "---" << fff._x << "---" << fff._y << std::endl;
#endif











	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

