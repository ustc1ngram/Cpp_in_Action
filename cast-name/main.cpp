#include <iostream>

int main() {
    /*
     * 常量转换的对象只能是指针或引用，即无法支持基本数据类型的转换
     * 使用const_cast可以返回一个指向非常量的指针（或引用），通过该指针（或引用）可以对其数据成员进行任意改变
     * 只能改变运算对象的底层const（去掉const）
     * 底层const：指针指向的对象是一个常量
     * 顶层const：指针指向本身是个常量
     * 只有const_cast能改变表达式的常量属性
     */
    const char* pc = "const";
    /*
    char* cp = pc; // error
     */
    char* cp = const_cast<char*>(pc);
    std::cout << pc << std::endl;
    std::cout << cp << std::endl;
    return 0;
}
