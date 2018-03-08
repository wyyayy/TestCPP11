#pragma once
class Runable
{
public:
    Runable();
    virtual ~Runable();

public:
    virtual void Run() = 0;
    virtual void Join() {};
};

