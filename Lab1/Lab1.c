#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int sum(int a, int b) {
   return a + b;
}
int mul(int a, int b) {
   return a * b;
}
int sub(int a, int b) {
   return a - b;
}
int divide(int a, int b) {
   return a / b;
}
void col(int a) {
   while(a != 1){
      printf("%d, ", a);
      if(a % 2 == 0){
         a /= 2;
      }
      else{
         a = 3 * a + 1;
      }
   }
   printf("%d", a);
}

int main() {
   // get name of the current logged-in user
   char * user;
   user = (char *)malloc(10*sizeof(char));
   user = getlogin();
   
   char input[30]; // entire line of input
   char cmd[10]; // command, precedes ints
   int a = 0; // first int input
   int b = 0; // second int input
   
   int count = -1; // count how many ints in total are entered, for error handling
   
   char * check; // primarily used for strtok()
   char err[30]; // saves entire line of input for error printing
   int isChar = 0; // used for error-handling (is an operand a char)
   
   for(;;) {
      // Reset these variables to their default values any time the loop restarts
      count = -1;
      a = 0;
      b = 0;
      isChar = 0;
      
      printf("%s> $ ", user);
      fgets(input, 30, stdin);
      input[strcspn(input, "\n")] = 0; // Prevents newline from being read as part of the input
      strcpy(err, input);
      check = strtok(input, " ");
            
      while(check) {
         if(count == -1){
            strcpy(cmd, check);
         }
         count++;
         
         for(int i = 0; i < strlen(check); i++) {
            if(count == 1) {
               if(isdigit(check[i]) != 0) {
                  a = atoi(check);
               }
               else{
                  isChar = 1;
               }
            }
            else if(count == 2) {
               if(isdigit(check[i]) != 0) {
                  b = atoi(check);
               }
               else {
                  isChar = 1;
               }
            }
         }
          check = strtok(NULL," ");
      }
       // CHECK: Any value following 'cmd' input is expected to be an integer
      if(isChar == 1) {
         printf("Invalid command: '%s'\n", err);
         continue;
      }
         
      // DEBUG                               
         // printf("\t| INT COUNT: %d\n", count);
         // printf("\t| cmd = '%s'\n", cmd);
         // printf("\t| a = %d\n", a);
         // printf("\t| b = %d\n", b);
      // END DEBUG
                  
      // CHECK: 'bye' should not be followed by operands / additional chars.
      if(count != 0) {
         if(strcmp(cmd, "bye") == 0) {
            printf("ERROR: 'bye' shouldn't be followed by operands / additional chars.\n");
            continue;
         }
      }
      if(count == 0) {
         if(strcmp(input, "bye") == 0) { // print 'bye' and exit the program
            printf("bye\n");
            return 0;
         }
         // CHECK: Any command besides 'bye' must include integers.
         else if(strcmp(cmd, "sum") == 0 || strcmp(cmd, "mul") == 0 || strcmp(cmd, "sub") == 0 || strcmp(cmd, "div") == 0 || strcmp(cmd, "col") == 0) {
            printf("ERROR: Command '%s' should be followed by some integer(s).\n", cmd);
         }
         else{
            printf("Invalid command: %s\n", input);
         }
      }
      else if(count == 1) {
         // CHECK: sum, mul, sub, and div requires more than one integer
         if(strcmp(cmd, "sum") == 0 || strcmp(cmd, "mul") == 0 || strcmp(cmd, "sub") == 0 || strcmp(cmd, "div") == 0) {
            printf("ERROR: '%s' requires at least two integers.\n", cmd);
         }
         else if(strcmp(cmd, "col") == 0) { // Collatz Conjecture
            if(a < 1){
               // CHECK: for Collatz Conjecture, input must be > 0
               printf("ERROR: Collatz Conjecture must take a positive integer!\n"); 
            }
            else{
               col(a);
               printf("\n");
            }
         }
         else {
            printf("Invalid command: '%s'\n", err);
         }
      }
      else if(count == 2){
         if(strcmp(cmd, "sum") == 0) { // summation
            printf("%d\n", sum(a, b));
         }
         else if(strcmp(cmd, "mul") == 0) { // multiplication
            printf("%d\n", mul(a, b));
         }
         else if(strcmp(cmd, "sub") == 0) { // subtraction
            printf("%d\n", sub(a, b));
         }
         else if(strcmp(cmd, "div") == 0) { // division
            if(b == 0) {
               // CHECK: Don't divide by zero, silly!
               printf("ERROR: Cannot divide by zero!\n");
            }
            else{
               printf("%d\n", divide(a, b));
            }
         }
         // CHECK: Col should only take in a single integer
         else if(strcmp(cmd, "col") == 0) {
            printf("ERROR: 'col <int>' should not be followed by some additional char(s)/int(s)\n");
         }
         else {
            printf("Invalid command: '%s'\n", err);
         }
      }
      else if(count > 2) { // CHECK: There should never be more than 2 integers or any additional chars after the 2 ints
         printf("ERROR: Input should never include more than three variables (char[], int, int)\n");
      }
      else {
         printf("Invalid command: '%s'\n", err);
      }
   }
}