## 1、新建线程
```C++
void do_some_work(int para)
{
    // 获取当前线程的id
    std::this_thread::get_id();
    // 线程睡眠2s
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Hello, mythread_" << para << std::endl;
}

int main()
{
    int para = 01;
    std::thread my_thread(do_some_work, para);
    // 主线程等待子线程结束再继续往下运行
    my_thread.join();
    // 将子线程设置为分离线程，主线程结束，子线程自动结束（类似于守护线程）
    my_thread.detach();
    return 0;
}

```
## 2、线程间互斥
```c++
std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;
 
void save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";
 
    // 是个类模板，在头文件<mutex>里声明
    // 在构造时给互斥加锁，析构时解锁，可以保证互斥总被正确的解锁
    // g_pages_mutex.lock();
    // g_pages_mutex.unlock();
    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}
 
int main() 
{
    std::thread t1(save_page, "http://foo");
    std::thread t2(save_page, "http://bar");
    t1.join();
    t2.join();
 
    // safe to access g_pages without lock now, as the threads are joined
    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}
```
## 3、线程间的同步通信
```c++

```