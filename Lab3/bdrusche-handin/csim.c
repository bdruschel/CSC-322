/* Name: Brandon Druschel
 * Student ID: 804085455
 * Login ID: bdrusche
 */
#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct {
   int valid;
   int tag;
   int LRU;
} line ;

//creates a new Cache (2D array of lines) and dynamically allocates
line** newCache(int S, int E){
   //cache* c[S][E];
   line **cache = (line **)malloc(S * sizeof(line *));
   for (int i = 0; i < S; ++i)
       cache[i] = (line *)malloc(E * sizeof(line));
    
   return cache;
}

//print usage info and stop program
void getInfo(){
   printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n"
      "Options:\n"
      "  -h         Print this help message.\n"
      "  -v         Optional verbose flag.\n"
      "  -s <num>   Number of set index bits.\n"
      "  -E <num>   Number of lines per set.\n"
      "  -b <num>   Number of block offset bits.\n"
      "  -t <file>  Trace file.\n\n"
      "Examples:\n"
      "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
      "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
   exit(2);
}

int checkIn(int i){
   if(i < 4)
      return 0;
   return 1;
}

void printError(){
   printf("./csim: Missing required command line argument\n");
   getInfo();
}

int main(int argc, char **argv) {
   int hit;
   int miss;
   int evic;
   
   hit = 0;
   miss = 0;
   evic = 0;
   
   FILE * t; //trace file to be read
   (void)t;
   t = NULL;
   
   int S; //sets
   int E; //lines
   int B; //block size
   (void)B;
   
   int checker; //should count up to 4 parameter inputs (s, e, b, t)
   checker = 0;
   
   int display; //0 = don't display, 1 = do display
   display = 0;
   
   // If no commands are entered ('./csim' counts as one argc), print Error
   if(argc < 2){
      printError();
   }
   
   // Commands are read here
   int option;
   while((option = getopt(argc, argv, "hvs:E:b:t:")) != -1){
      switch(option) {
         case 'h':
            getInfo();
            break;
         
         case 'v':
            //printf("[[Optional verbose flag that displays trace info]]\n");
            display = 1;
            break;
            
         case 's':
            //printf("[[Number of set index bits (S = 2^s is the number of sets)]]\n");
            checker++;
            S = (int) pow(2.0,(double)atof(optarg));
            //printf("|| DEBUG: Sets = %d\n", S);
            break;
            
         case 'E':
            //printf("[[Associativity (number of lines per set)]]\n");
            checker++;
            E = atof(optarg);
            //printf("|| DEBUG: Lines per set = %d\n", E);
            break;
            
         case 'b':
            //printf("[[Number of block bits (B = 2^b is the block size)]]\n");
            checker++;
            B = (int) pow(2.0, (double)atof(optarg));
            //printf("|| DEBUG: Block size = %d\n", B);
            break;
            
         case 't':
            //printf("[[Name of the valgrind trace to display]]\n");
            checker++;
            //printf("|| DEBUG: File = %s\n", optarg);
            t = fopen(optarg, "r");
            break;
            
         default:
            getInfo();
            break;
      }
   }
   
   // if '-v' entered, print contents of file input
   if(display == 1){
      if(t == NULL) {
         //printf("|| DEBUG: ERROR - FILE IS NULL");
         printError();
      }
      char c;
      c = fgetc(t);
      while (c != EOF) {
         printf ("%c", c);
         c = fgetc(t);
      }
   }
   
   // check in case there's a missing argument among s, E, b, t
   if(checkIn(checker) == 0){
      printError();
   }
   
   // create a Cache (2D line Array) w/ # sets and # lines inputted
   line** cache;
   cache = newCache(S, E);
   
   char op;
   unsigned addr;
   int size;
   
   // read through trace file
   while(fscanf(t, " %c %x,%d", &op, &addr, &size) > 0) {
      
   }
   fclose(t);
   free(cache);
   
   // cachlab.h | display final hit and miss statistics 
   printSummary(hit, miss, evic);
   
   return 0;
}
