// MiniStringImpl.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MyString.h"

int main()
{
    myString s = "Hello World!\n";
    std::cout << s.data;
}
