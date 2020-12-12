#include "thread_pool.h"

void thread_pool::create_threads(int size)
{    
    stop = false;
    
    for(int i = 0; i < size; i++)
    {
        work_threads.emplace_back(std::thread(&thread_pool::infinite_loop_function, this));
    }
}

void thread_pool::infinite_loop_function()
{
    std::function<void()> task;
    while(true)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this](){return stop || (!tasks_queue.empty());});
            if (stop && tasks_queue.empty()){
                return;
            }
            task = std::move(tasks_queue.front());
            tasks_queue.pop();
        }
        task();
    }   
}

void thread_pool::enqueue_task(std::function<void()> &task)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop){
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks_queue.emplace(task);
    }
    condition.notify_one();
}

thread_pool::~thread_pool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: work_threads)
    {
        worker.join();
    }
}