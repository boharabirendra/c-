#include <iostream>

int main()
{
    unsigned char buf[sizeof(int) * 2];

    int *p = new (buf) int(10);

    int *q = new int(100);
}