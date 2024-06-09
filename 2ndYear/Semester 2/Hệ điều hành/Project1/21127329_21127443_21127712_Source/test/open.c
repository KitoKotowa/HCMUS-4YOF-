#include "syscall.h"

int main() {
    int id = Open("hello.txt", 0);
    Close(id);
    Halt();
    return 0;
}