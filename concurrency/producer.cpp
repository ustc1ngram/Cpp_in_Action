//
// Created by 蔡宏阳 on 2022/12/4.
//
/*
 * 生产者、消费者模型
 * 一组消费者线程和生产者线程共享一个初始为空，大小为n的缓冲队列
 * 缓冲区没满时，生产者才能把消息放入缓冲区，否则必须等待
 * 只有缓冲区不为空时，消费者才能从中取出消息，否则必须等待
 */
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;

class Queue
{
public:
    Queue(int size) : _size(size) {}
    void produce(int val)
    {
        std::unique_lock<std::mutex> lck(mtx);
//        std::lock_guard<std::mutex> guard(mtx);
        while (que.size() == _size)
        {
            /*
             * 缓冲队列已满，通知消费者消费
             * 进入等待状态，并且释放mtx互斥锁
             */
            // wait函数两个参数的用法见concurrency.cpp文件
            cv.wait(lck);
        }
        que.push(val);
        /*
         * 通知其它所有线程
         * 其它线程得到该通知，就会从等待状态变成阻塞状态，获取互斥锁才能继续执行
         */
        cv.notify_all();
//        cv.notify_one();
        std::cout << "生产者生产" << val << "号物品" << std::endl;
    }
    int consume()
    {
        std::unique_lock<std::mutex> lck(mtx);
        while (que.empty())
        {
            // 缓冲队列为空，通知生产者生产
            cv.wait(lck);
        }
        int val = que.front();
        que.pop();
        cv.notify_all();
//        cv.notify_one();
        std::cout << "消费者消费" << val << "号物品" << std::endl;
        return val;
    }
private:
    int _size;
    std::queue<int> que;
};

void producer(Queue *que)
{
    for (int i = 0; i < 10; i++)
    {
        que->produce(i);
    }
}

void consumer(Queue *que)
{
    for (int i = 0; i < 10; i++)
    {
        que->consume();
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    // 两个线程共享的队列
    Queue que(3);
    std::thread t1(producer, &que);
    std::thread t2(consumer, &que);
    t1.join();
    t2.join();
}
