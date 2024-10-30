#include <stdio.h>

int main(void) {
	char ch;
	while (scanf("%c", &ch) == 1) {
		if (ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U' && 
		ch != 'a' && ch != 'e' && ch != 'i' && ch != 'o' && ch != 'u') {
			printf("%c", ch);
		}
	}
	return 0;
}
