#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class thread_pool
{
public:
    void create_threads(int size);
    void infinite_loop_function();
    void enqueue_task(std::function<void()> &task);
    ~thread_pool();

private:
    std::vector<std::thread> work_threads;
    std::queue<std::function<void()>> tasks_queue;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

