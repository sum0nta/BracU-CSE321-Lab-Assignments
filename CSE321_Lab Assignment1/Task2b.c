#include <stdio.h>
#include <stdlib.h>

int main() {
   FILE *input_file = fopen("input.txt", "r");
   FILE *output_file = fopen("output.txt", "w");

   char c;
   int is_space = 0;

   while ((c = fgetc(input_file)) != EOF) {
       if (c == ' ') {
           if (!is_space) {
               fputc(c, output_file);
               is_space = 1;
           }
       } else {
           fputc(c, output_file);
           is_space = 0;
       }
   }

   fclose(input_file);
   fclose(output_file);


   return 0;
}
