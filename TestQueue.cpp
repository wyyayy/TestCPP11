#include "stdafx.h"
#include "TestQueue.h"


TestQueue::TestQueue()
{
}

TestQueue::~TestQueue()
{

}

void TestQueue::Run()
{    
    assert(!_receiveThread.joinable());
    assert(!_postThread.joinable());

    _receiveThread = std::thread(&TestQueue::_receiveThreadFunc, this);
    _postThread = std::thread(&TestQueue::_postThreadFunc, this);

}

void TestQueue::_postThreadFunc()
{
    int i = 0;
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        _queue.push(make_shared<Task>(i++));
    }
}

void TestQueue::_receiveThreadFunc()
{
    while (true)
    {
        auto task = _queue.pop();
        task->Run();
    }
}

void TestQueue::Join()
{
    _receiveThread.join();
    _postThread.join();
}