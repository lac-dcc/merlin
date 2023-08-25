#include <stdio.h>

int my_strlen(char* str) {
  int len = 0;

  while (str[len] != '\0') {
    len++;
  }

  return len;
}

int main() {
  char str[] = "Hello World";
  printf("%s : %d\n", str, my_strlen(str));

  return 0;
}