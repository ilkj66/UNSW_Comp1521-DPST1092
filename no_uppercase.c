#include <stdio.h>
#include <ctype.h>

int main(void) {
	int c;
	//scanf("%c", &c);
	while ((c = getchar()) != EOF) {
		if (c >= 'A' && c <= 'Z') {
			c = c + ('a' - 'A');
		}
		putchar(c);
	}
    //printf("\n");

	return 0;
}
