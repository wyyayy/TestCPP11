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

using namespace std;
using namespace std::chrono;

int main()
{
    TestQueue testQueue;
    testQueue.Run();

    testQueue.Join();

    return 0;
}
