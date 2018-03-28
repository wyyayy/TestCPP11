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

using namespace std;
using namespace std::chrono;

template<typename T> T getDefaultValue(T& t1) 
{
    return {};
}

int main()
{
    bool a = 0;
    bool ret = getDefaultValue(a);

    TestSmartPtr testSmartPtr;
    testSmartPtr.Run();

    //TestQueue testQueue;
    //testQueue.Run();

    //testQueue.Join();

    return 0;
}
