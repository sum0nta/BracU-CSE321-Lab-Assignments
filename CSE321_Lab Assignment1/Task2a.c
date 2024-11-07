#include <stdio.h>

int main() {
   int num1;
   printf("Type a number: \n");
   scanf("%d", &num1);
   int num2;
   printf("Type a number: \n");
   scanf("%d", &num2);
   if(num1 > num2){
       int result = num1 - num2;
       printf("Result: %d", result);
   }
   else if(num1 < num2){
       int result = num1 + num2;
       printf("Result: %d", result);
   }
   else{
       int result = num1 * num2;
       printf("Result: %d", result);
   }
  
   return 0;
}
