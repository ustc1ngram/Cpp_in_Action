#include <iostream>
#include <string>

class Test1
{
public:
    // 如果构造函数只接受一个实参，则它实际上定义了转换为此类类型的隐式转换机制
    // 这种构造函数也称为转换构造函数
    Test1(std::string s)
    {
        std::cout << "发生了隐式转换" << std::endl;
    }
};

class Test2
{
public:
    // 使用explicit关键字加以阻止
    // 只能在类内声明构造函数时使用，在类外定义时不应重复
    explicit Test2(std::string s)
    {
        std::cout << "阻止隐式转换" << std::endl;
    }

};
template<typename T>
void myfunc(T t)
{
}

int main()
{
    std::string s = "hello";

    myfunc<Test1>(s); // 输出：发生了隐式转换，表明确实发生了隐式转换
//    myfunc<Test2>(s); // 编译不通过，表明无法进行隐式转换

    // 尽管编译器不会将explicit构造函数用于隐式转换
    // 但是我们可以使用这样的构造函数显示地强制进行转换
    myfunc<Test2>(static_cast<Test2>(s)); // 输出：阻止隐式转换
    return 0;
}