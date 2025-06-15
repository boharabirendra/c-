#include <iostream>

class A
{
public:
    A(int _a)
    {
        a = _a;
    }

private:
    int a;
};

int main()
{
    A __a(10);
}