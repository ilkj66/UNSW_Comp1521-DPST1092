/*

Run at CSE like this

$ clang invalid3.c -o invalid3
$ ./invalid3
I hate you.
$

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void f(void);

int main(void) {
    f();

    printf("I love you and will never say,\n");
    printf("I hate you.\n");

    return 0;
}

void f(void) {
    uint64_t a[1];
    a[2] += 17;

    // function f has it return address on the stack
    // the call of function f from main should return to
    // the next statement which is:  printf("I love you and will never say,\n");
    //
    // with clang at CSE  f's return address is stored where a[12] would be
    //
    // so changing a[2] changes where the function returns
    //
    // adding 17 to a[12] happens to cause it to return 2 statements later
    // at:  printf("I hate you.\n");
}
