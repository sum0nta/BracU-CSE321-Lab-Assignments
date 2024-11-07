#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
   char password[100];
   int has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;

   printf("Enter password: ");
   scanf("%s", password);

   for (int i = 0; i < strlen(password); i++) {
       if (islower(password[i])) has_lower = 1;
       else if (isupper(password[i])) has_upper = 1;
       else if (isdigit(password[i])) has_digit = 1;
       else if (password[i] == '_' || password[i] == '$' || password[i] == '#' || password[i] == '@') has_special = 1;
   }

   if (has_lower && has_upper && has_digit && has_special) {
       printf("OK\n");
   } else {
       if (!has_lower) printf("Lowercase character missing\n");
       if (!has_upper) printf("Uppercase character missing\n");
       if (!has_digit) printf("Digit missing\n");
       if (!has_special) printf("Special character missing\n");
   }

   return 0;
}
