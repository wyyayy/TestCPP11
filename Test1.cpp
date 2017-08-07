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

using namespace std;
using namespace std::chrono;

class Base
{
public:
	Base() {}
	virtual ~Base() {}
	virtual int func(int i) = 0;
};

class Derived : public Base
{
public:
	Derived(int base = 10) : base{ base }
	{

	}
	~Derived() {}

	virtual int func(int i)
	{
		return i*base;
	}
private:
	int base;
};

struct Func
{
	int base;
	int operator()(int i)
	{
		return i*base;
	}
	Func(int base) : base{ base }
	{

	}
};
const int base = 10;
int calculate(int i)
{
	return base*i;
}

int test2()
{
	const int num = 10000;
	Base *p = new Derived{ 10 };
	int total = 0;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < num; ++i)
	{
		total += p->func(i);
	}
	auto end = high_resolution_clock::now();
	std::cout << "result: " << total << "\nvirtual call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

	///-----------------------------------
	total = 0;
	start = high_resolution_clock::now();
	for (int i = 0; i < num; ++i)
	{
		total += calculate(i);
	}
	end = high_resolution_clock::now();
	std::cout << "result: " << total << "\ndirect function call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

	///-----------------------------------
	Func functor{ 10 };
	total = 0;
	start = high_resolution_clock::now();
	for (int i = 0; i < num; ++i)
	{
		total += functor(i);
	}
	end = high_resolution_clock::now();
	std::cout << "result: " << total << "\nfunctor call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

	///-----------------------------------
	int base = 10;
	function<int(int)> lambda = [base](int i)
	{
		return i*base;
	};

	auto lambdaAuto = [base](int i)
	{
		return i*base;
	};

	total = 0;
	start = high_resolution_clock::now();
	for (int i = 0; i < num; ++i)
	{
		total += lambda(i);
		//total += lambdaAuto(i);
	}
	end = high_resolution_clock::now();
	std::cout << "result: " << total << "\nlambda call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;
	return 0;
}


/*
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(_Tx *_Ty)
{
	return x*y;
}
*/

template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)
{
	return x*y;
}

void test()
{
	multiply(3, 4);

	auto lambda = [](auto x, auto y) {return x + y; };

	auto ret = lambda(4, 5);

	std::vector<int> c{ 1,2,3,4,5,6,7 };
	int x = 5;
	c.erase(  std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end()   );

	std::function<int(int)> testFunctor;

	tuple<int, float, bool> tuple1 = make_tuple(22, 1.2f, false);
	int get1 = std::get<0>(tuple1);


	std::cout << "c: ";
	for (auto i : c) {
		std::cout << i << ' ';
	}
	std::cout << '\n';

	// the type of a closure cannot be named, but can be inferred with auto
	auto func1 = [](int i) ->int { return i + 4; };
	std::cout << "func1: " << func1(6) << '\n';

	// like all callable objects, closures can be captured in std::function
	// (this may incur unnecessary overhead)
	std::function<int(int)> func2 = [](int i) { return i + 4; };
	std::cout << "func2: " << func2(6) << '\n';
}


void testVector()
{
	vector<int> datas = { 1, 2, 3 };
	const int num = 10000000;

	auto start = high_resolution_clock::now();

	for (int i = 0; i < num; ++i)
	{
		datas[0] = i;
		datas[1] = i;
		datas[2] = i;
	}
	auto end = high_resolution_clock::now();
	std::cout << "result: " << datas[2] << " Vector[] Elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

	///------------
	start = high_resolution_clock::now();
	int* pData = &datas[0];

	for (int i = 0; i < num; ++i)
	{
		pData[0] = i;
		pData[1] = i;
		pData[2] = i;
	}
	end = high_resolution_clock::now();
	std::cout << "result: " << pData[2] << " Pointer Elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

}

void f(int& n1, int& n2, const int& n3)
{
	std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	++n1; // increments the copy of n1 stored in the function object
	++n2; // increments the main()'s n2
		  // ++n3; // compile error
}

class Test
{
public:
	int m1;

public:
	Test()
	{
		m1 = 1;
	}

	~Test()
	{
		m1 = 0;
	}
};

class A
{
public:
	int i_ = 0; // C++11允许非静态（non-static）数据成员在其声明处（在其所属类内部）进行初始化

	void output(int x, int y)
	{
		std::cout << x << "" << y << std::endl;
	}

};

int add1(int i, int j, int k)
{
	return i + j + k;
}

void TestLambda()
{
	int a = 0;

	auto loop = std::make_shared<std::function<void()>>();
	long count = loop.use_count();

	*loop = [&loop, &a]()
	{
		a++;
		if (a < 3)
		{
			(*loop)();
		}
		else
		{
			int a = 0;
		}
	};

	count = loop.use_count();
	(*loop)();

	count = loop.use_count();
}

int main()
{
	std::function<void()> test = [&]()
	{
		int a = 0;
		a++;
	};


	ifstream file("spm.spm", ios::in | ios::binary | ios::ate);

	const unsigned int length = 1024 * 100;
	char buffer[length];
	//file.rdbuf()->pubsetbuf(buffer, length);

	auto buf = file.rdbuf();

	streampos size = file.tellg();
	char* memblock;
	steady_clock::time_point lastTime;
	steady_clock::time_point tempTime;

	lastTime = high_resolution_clock::now();

	for (int i = 0; i < 10000; ++i)
	{
		tempTime = high_resolution_clock::now();
	}

	auto deltaTime1 = duration<double>(high_resolution_clock::now() - lastTime);
	cout << "Read whole file time: " << deltaTime1.count() << endl;

	auto test1 = duration<double>(tempTime - high_resolution_clock::now()).count();
	cout << test1;

/*
	memblock = new char[size];
	file.seekg(0, ios::beg);

	lastTime = high_resolution_clock::now();
	file.read(memblock, size);
	auto deltaTime1 = duration<double>(high_resolution_clock::now() - lastTime);
	cout << "Read whole file time: " << deltaTime1.count() << endl;

	delete[] memblock;*/

	///---------------

	int readTimes = 968;

	int sliceSize = size / readTimes;
	memblock = new char[sliceSize];
	file.seekg(0, ios::beg);

	lastTime = high_resolution_clock::now();

	for (int i = 0; i < readTimes; ++i)
	{
		file.read(memblock, sliceSize);
	}

	auto deltaTime2 = duration<double>(high_resolution_clock::now() - lastTime);

	cout << "Read file in slices time: " << deltaTime2.count() << endl;

	delete[] memblock;
	file.close();

	system("pause");

    return 0;
}


//TestLambda();

///system("pause");

///-----------------

/*
auto loop1 = std::function<void()>();
a = 0;

loop1 = [&loop1, &a]()
{
a++;
if (a < 3)
{
loop1();
}
else
{
int a = 0;
}
};

loop1();
*/

/*
// 绑定全局函数
auto add2 = std::bind(add1, std::placeholders::_1, std::placeholders::_2, 10);
// 函数add2 = 绑定add1函数，参数1不变，参数2不变，参数3固定为10.
std::cout << typeid(add2).name() << std::endl;

add2(1, 2);

A a;
// 绑定成员函数，保存为仿函数
auto fr = std::bind(&A::output, &a, std::placeholders::_1, 5);

// 调用成员函数
fr(1);

// 绑定成员变量
std::function<int&(void)> fr2 = std::bind(&A::i_, &a);
fr2() = 100;// 对成员变量进行赋值
std::cout << a.i_ << std::endl;
*/

/*
int n1 = 1, n2 = 2, n3 = 3;
std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
n1 = 10;
n2 = 11;
n3 = 12;
std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
bound_f();
std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';

testVector();

//test();
//test2();

system("pause");
*/
