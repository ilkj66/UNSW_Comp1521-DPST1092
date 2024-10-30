#include <stdio.h>
#include <string.h>
#define MAX 1024
int main(void) {
    char c[MAX];
    while(fgets(c, MAX, stdin) != NULL) {
        int i = 0;
        while (c[i] != '\0') {
            i++;
        }
        if (i % 2 == 0) {
            fputs(c, stdout);
            //fputs("\n", stdout);
        }
    }
    
	return 0;
}
