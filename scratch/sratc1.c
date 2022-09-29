#include <stdio.h>
#include <math.h>
int main() {
    unsigned int x = 0;
    char *a = (void*) &x;
    a[2] = 'h';
    a[1] = 'e';
    a[0] = 'l';
    x <<= 8;
    for(int i = 0; i < 4; i++) {
        printf("%x\n", x);
        x <<= 6;
    }
}
