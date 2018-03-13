#include "stdafx.h"
#include "TestMiscs.h"


TestMiscs::TestMiscs()
{
}


TestMiscs::~TestMiscs()
{
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
