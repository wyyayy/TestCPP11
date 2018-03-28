#pragma once

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

///----------------
class Texture;

template<class ResType>
class ObjectRef
{
protected:
    weak_ptr<ResType> _weakPtr;

public:
    ObjectRef(weak_ptr<ResType> texture)
    {
        _weakPtr = texture;
    }

public:
    shared_ptr<ResType> operator->() const
    {
        auto ptr = _weakPtr.lock();

        if (ptr)
        {
            return ptr;
        }
        else
        {
            throw exception("Null referenced object!");
        }
    }

};


class TextureManager
{

public:
    static TextureManager& Get() { return _Instance; }

protected:
    static TextureManager _Instance;

protected:
    map<string, shared_ptr<Texture>> _textureMap;

public:
    TextureManager()
    {
    }

public:
    ObjectRef<Texture> GetTexture(const string& name)
    {
        auto iter = _textureMap.find(name);
        if (iter == _textureMap.end())
        {
            /// Try load specfied texture;
            auto texture = make_shared<Texture>(name);
            _textureMap[name] = texture;
            return ObjectRef<Texture>(texture);
        }
        else
        {
            return ObjectRef<Texture>(_textureMap[name]);
        }
    }

    void DestroyAll()
    {
        for (auto& keyValue : _textureMap) 
        {
            assert(1 == keyValue.second.use_count());
        }
        _textureMap.clear();
    }
};


class Texture
{
protected:
    string _name;

public:
    Texture() {};

    Texture(string name)
    {
        _name = name;
    }

public:
    string GetName() const
    {
        return _name;
    }

    void Destroy()
    {
        delete this;
    }
};

///---
class Parent
{
protected:
    std::function<void()> _lambda;

public:
    void Setup(std::function<void()> lambda)
    {
        _lambda = lambda;
    }

    void ClearRefs()
    {
        _lambda = nullptr;
    }
};

class TestSmartPtr : Runable
{
protected:


public:
    TestSmartPtr();
    ~TestSmartPtr();

public:
    virtual void Run()
    {
        //_CrtSetBreakAlloc(169);

        try
        {
            ObjectRef<Texture> textureRef = TextureManager::Get().GetTexture("myTexture");

            TextureManager::Get().DestroyAll();

            cout << textureRef->GetName() << endl;
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }

        /// Test Lambda recursive referencing
        shared_ptr<Parent> parentPtr = make_shared<Parent>();

        parentPtr->Setup([parentPtr]()
        {
            int a = 0;
            a++;
        });

        parentPtr->ClearRefs();

        //////////////////////////////////////////////////////////////////////////
        shared_ptr<Parent> parentPtr2 = make_shared<Parent>();
        weak_ptr<Parent> weakPtr = parentPtr2;

        shared_ptr<Parent> parentPtr3 = weakPtr.lock();
    }

};

