#pragma once

#include "Runable.h"
#include "BlockingQueue.h"

class Task
{
public:
    Task(int number)
    {
        _number = number;
    }

public:
    virtual void Run() 
    {
        cout << "Ticking...." << _number << endl;
    }

protected:
    int _number;
};

class TestQueue : Runable
{
public:
    TestQueue();
    virtual ~TestQueue();

public:
    virtual void Run();
    virtual void Join();


protected:
    void _receiveThreadFunc();
    void _postThreadFunc();

protected:
    thread _postThread;
    thread _receiveThread;

    BlockingQueue<shared_ptr<Task>> _queue;
};

