// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <memory>
#include <fstream>
#include <filesystem>
#include<thread>  

#include "TestQueue.h"
#include "TestSmartPtr.h"
#include "TestMemoryLeak.h"
#include "TestColor.h"

#include <iostream>
#include <type_traits>

using namespace std;
using namespace std::chrono;

class AutoMemoryLeakDetect
{
public:
	AutoMemoryLeakDetect()
	{
#ifdef _MSC_VER
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	}

	static AutoMemoryLeakDetect smInstance;
};

AutoMemoryLeakDetect AutoMemoryLeakDetect::smInstance;


template<typename T> T getDefaultValue(T& t1) 
{
    return {};
}

template<typename T>
struct TestTemplate
{
public:
	T _a;

	TestTemplate(std::initializer_list<T> t)
	{
		_a = *(t.begin());
	}

	TestTemplate()
	{
	}

	TestTemplate(T val)
	{
		_a = val;
	}
};

long multiply(int i, int j) { return i * j; }

template <class T>
typename T::multiplication_result multiply(T t1, T t2)
{
	return t1 * t2;
}

template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd(T i) { return bool(i % 2); }

template <class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even(T i) { return !bool(i % 2); }

class TestPtr
{
public:
    int a;
};

shared_ptr<TestPtr> GetPtr(bool value)
{
    if(value) return nullptr;
    else return shared_ptr<TestPtr>();
}

int main()
{	
    void* ret1 = (void*)&GetPtr(true);
    void* ret2 = (void*)&GetPtr(false);

	auto ret = is_odd(false);
	ret = is_even(3);

	string hello = "hello";
	string world = "world";

	std::function<void(string)> func = [ helloWorld = hello + " " + world](string head)
	{
		cout << head <<  helloWorld;
	};

	func("INFO: ");

	multiply(4.0f, 5.0f);

	//TestTemplate<int> test(123);

	//std::hash<std::thread::id>{}(std::this_thread::get_id())
	//struct TestTemplate<int>{}(123);

    //bool a = 0;
    //bool ret = getDefaultValue(a);

    //TestSmartPtr testSmartPtr;
    //testSmartPtr.Run();

	TestMemoryLeak testMemoryLeak;
	testMemoryLeak.Run();

	//TestColor testColor;
	//testColor.Run();

    //TestQueue testQueue;
    //testQueue.Run();

    //testQueue.Join();

    return 0;
}
