#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
   char str[100];
   char *left, *right;

   printf("Enter a string: ");
   scanf("%s", str);

   left = str;
   right = str + strlen(str) - 1;

   while (left < right) {
       if (*left != *right) {
           printf("Not Palindrome\n");
           return 0;
       }
       left++;
       right--;
   }

   printf("Palindrome\n");
   return 0;
}
