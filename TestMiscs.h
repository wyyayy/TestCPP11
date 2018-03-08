#pragma once


class Base
{
public:
    Base() {}
    virtual ~Base() {}

    virtual int func(int i) = 0;
    virtual function<int(int)> GetLambda() = 0;
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

    virtual function<int(int)> GetLambda()
    {
        int base2 = 10;
        auto lambdaAuto = [base2](int i)
        {
            return i*base2;
        };
        return lambdaAuto;
    }

    auto GetLambdaA()
    {
        int base2 = 10;
        auto lambdaAuto = [base2](int i)
        {
            return i*base2;
        };
        return lambdaAuto;
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

int TestLambda()
{
    ///const int num = 10000;
    const long long num = 100000000;
    Base *p = new Derived{ 10 };
    int total = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < num; ++i)
    {
        total += p->func(i);
        //total += (i * base);
    }
    auto end = high_resolution_clock::now();
    std::cout << "result: " << total << "\n Virtual call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

    ///-----------------------------------
    total = 0;
    start = high_resolution_clock::now();
    for (int i = 0; i < num; ++i)
    {
        total += calculate(i);
    }
    end = high_resolution_clock::now();
    std::cout << "result: " << total << "\n Direct function call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

    ///-----------------------------------
    Func functor{ 10 };
    total = 0;
    start = high_resolution_clock::now();
    for (int i = 0; i < num; ++i)
    {
        total += functor(i);
    }
    end = high_resolution_clock::now();
    std::cout << "result: " << total << "\n Functor call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;

    ///-----------------------------------
    int base2 = 10;
    auto lambda = [base2](int i)
    {
        return i*base2;
    };


    function<int(int)> lambdaTest = [base2](int i)
    {
        return i*base2;
    };

    auto lambdaFunc = p->GetLambda();

    lambda(3);

    total = 0;
    start = high_resolution_clock::now();
    for (int i = 0; i < num; ++i)
    {
        //total += lambda(i);
        total += lambdaFunc(i);
    }
    end = high_resolution_clock::now();
    std::cout << "result: " << total << "\n Lambda call elapsed: \t" << duration_cast<nanoseconds>(end - start).count() << " nanoseconds.\n" << std::endl;
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


void fun1(int n)  //初始化构造函数  
{
    cout << "Thread " << n << " executing\n";
    //n += 10;

    while (n > 0)
    {
        cout << "Ticking... " << n << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        n--;
    }
}
void fun2(int & n) //拷贝构造函数  
{
    cout << "Thread " << n << " executing\n";
    n += 10;
    this_thread::sleep_for(chrono::milliseconds(1000));
}


class TestMiscs
{
public:
    TestMiscs();
    ~TestMiscs();

public:
    virtual void Run()
    {
        int n = 18;
        thread t1;               //t1不是一个thread  
        thread t2(fun1, n);  //按照值传递  

        t1 = std::move(t2);
        //t1.join();
        t1.detach();

        cout << "n=" << n << '\n';
        n = 10;
    }
};

