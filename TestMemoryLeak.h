#pragma once

class Child1;

class Parent1
{
protected:
	shared_ptr<Child1> _child;
	
public:
	Parent1(shared_ptr<Child1> child)
	{
		_child = child;
	}
};

class Child1
{
protected:
	shared_ptr<Parent1> _parent;

public:
	void SetParent(shared_ptr<Parent1> parent)
	{
		_parent = parent;
	}
};

class TestMemoryLeak : Runable
{
protected:


public:
    TestMemoryLeak();
    ~TestMemoryLeak();

public:
    virtual void Run()
    {	   
		shared_ptr<Child1> child = make_shared<Child1>();
		shared_ptr<Parent1> parent = make_shared<Parent1>(child);
		child->SetParent(parent);
    }

};

