#include "syscall.h"

int main() {
    int id;

    id = Open("hello.txt", 1);
    Remove("hello.txt");
    Close(id);

    Remove("abc.txt");
    Remove("123.txt");

    Halt();
    return 0;
}