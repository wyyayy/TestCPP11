#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>

/// The pop method will block current thread until queue not empty. 
template <typename T>
class BlockingQueue
{
    typedef std::unique_lock<std::mutex> UniqueLock;

public:
    T pop()
    {
        UniqueLock lock(_mutex);

        if (_queue.empty())
        {
            _conditionVariable.wait(lock);
        }

        if (_queue.empty())
        {
            return nullptr;
        }
        else
        {
            auto item = _queue.front();
            _queue.pop();
            return item;
        }
    }

    void pop(T& item)
    {
        UniqueLock lock(_mutex);

        if (_queue.empty())
        {
            _conditionVariable.wait(lock);
        }

        if (_queue.empty())
        {
            return nullptr;
        }
        else
        {
            item = _queue.front();
            _queue.pop();
        }
    }

    void push(const T& item)
    {
        UniqueLock lock(_mutex);
        _queue.push(item);
        lock.unlock();
        _conditionVariable.notify_one();
    }

    void push(T&& item)
    {
        UniqueLock mlock(_mutex);
        _queue.push(std::move(item));
        mlock.unlock();
        _conditionVariable.notify_one();
    }

    /// Cancel pop method's waiting.
    void cancelWaiting()
    {
        _conditionVariable.notify_one();
    }

    bool empty()
    {
        UniqueLock lock(_mutex);
        return 0 == _queue.size();
    }

protected:
    std::queue<T> _queue;

    std::mutex _mutex;
    std::condition_variable _conditionVariable;
};


