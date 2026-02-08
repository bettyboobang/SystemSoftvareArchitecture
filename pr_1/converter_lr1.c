#include <stdio.h>
#include <ctype.h>
#include <math.h>

int  digit_value(char c) {//function for digit value for symbol
 if(c >= '0' && c <= '9') {
   return c - '0';
 }
 if(c >= 'A' && c <= 'Z') {
   return c - 'A' + 10;
 }
 if(c >= 'a' && c <= 'z') {
   return c - 'a' + 10;
 }
 return -1;//no digit
}

int main(void) {
 int base;
 char c;
 double result = 0.0;
 double fraction_factor = 1.0;
 int is_fraction = 0;
 int digit;
 printf("Enter a digit:");
 if(scanf("%d", &base) != 1) {//read base of the digit system
   printf("Error: can not read system base.\n");
    return 1;
 }
 if(base < 2 || base > 36) {
    printf("Error: base must be from 2 to 36.\n");
    return 1;
 }
 while ((c = getchar()) != EOF && isspace(c));//skip space symbols
 if(c == EOF) return 0;
 do{//loop for pocessing digits
   if(c == '.' || c == ','){//check for fraction
      if(is_fraction == 0) {
         is_fraction = 1;
       }
       continue;//to the next symbol
    }
   digit = digit_value(c);
   if (digit != -1 && digit < base) {
       if(is_fraction) {
          fraction_factor /= (double)base;
          result += digit * fraction_factor;
       } else {
           result = result * base + digit;
        }
   }
  } while ((c = getchar()) != EOF && !isspace(c));
 printf("The result is: %g\n", result);//%g cleans excess zeros
 return 0;
}
