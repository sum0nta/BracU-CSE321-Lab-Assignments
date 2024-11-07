#include <stdio.h>
#include <string.h>

int main() {
   char email[100];
   char old_domain[] = "@kaaj.com";
   char new_domain[] = "@sheba.xyz";

   printf("Enter email address: ");
   scanf("%s", email);

   // Check if the email contains the old domain
   if (strstr(email, old_domain) != NULL) {
       printf("Email address is outdated\n");
   } else if (strstr(email, new_domain) != NULL) {
       printf("Email address is okay\n");
   } else {
       printf("Email address is using an unknown domain\n");
   }

   return 0;
}
