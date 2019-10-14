/*
Name: Mitchell Jones & Brandon Stolz        Class: CPS 360
Assignment: 4
Due: Oct 16, 2019                                           
Points: 10

Problem:

Solution:

Data-Structure Used:

Errors-Handled:
*/

#include <stdio.h>
#include <stdlib.h>
/*Problem:

Solution:*/

int main(int argc, char *argv[]){
    
    void usage(char *progname);
    
    exit (0);
}

/*Problem:

Solution:*/

void usage(char *progname){
    
    fprintf(stderr, "./%s <arg-a> <arg-b> <arg-c>\n", progname); exit(1);
}

/*Problem:

Solution:*/

void halfaddr(int a, int b, int *sum, int *outcary){
    
    *sum = (a & 1) ^ (b & 1);
    *outcary = (a & 1) & (b & 1);
}

/*Problem: 

Soultion:*/

void fulladdr(int a, int b, int incary, int *sum, int *outcary){
    
    *sum = (a & 1) ^ (b & 1) ^ (incary & 1);
    *outcary = (a & b) | (incary & (a | b));
}

/*Problem:

Solution:*/

void rcadd4(int a, int b, int incary, int *sum, int *outcary){
    
    int s3, s2, s1, s0;
    
    int *s3p = &s3, *s2p = &s2, *s1p = &s1, *s0p = &s0;
    
    fulladdr(a & 1, b & 1, incary, s0, outcary);
    fulladdr((a >> 1) & 1, (b >> 1) & 1, *outcary, s1, outcary);
    fulladdr((a >> 2) & 1, (b >> 2) & 1, *outcary, s2, outcary);
    fulladdr((a >> 3) & 1, (b >> 3) & 1, *outcary, s3, outcary);
    
    *sum = (s3 << 3) | (s2 << 2) | (s1 << 1) | s0;
}

/*Problem:

Solution:*/

void lacadd4(int a, int b, int incary, int *sum, int *outcary){
    
}

/*Problem:

Solution:*/

void evenparity3gen(int a, int *paritybit){
    
    int b2, b1, b0;
    
    b2 = (a >> 2) & 1;
    b1 = (a >> 1) & 1;
    b0 = (a & 1);
    
    *checkbit = (b2 ^ b1) | b0;
}

/*Problem:

Solution:*/

void oddparity4chk(int a, int *checkbit){
    
    int b3, b2, b1, b0;
    
    b3 = (a >> 3) & 1;
    b2 = (a >> 2) & 1;
    b1 = (a >> 1) & 1;
    b0 = (a & 1);
    
    *checkbit = ((b3 ^ b2) ^ (b1 ^ b0)) ^ 1;
}

/*Problem:

Solution:*/

void mux2by1(int a, int b, int *yout){
    
   int i1, i0, s;
    
   i0 = a & 1;
   i1 = (a >> 1) & 1;
   s = b & 1;

   *yout = (i0 & (s ^ 1)) | (i1 & s);
}

/*Problem:

Solution:*/

void mux4by1(int a, int b, int *yout){
    
}

/*Problem:

Solution:*/

void printresults(char *label, int a){
    
    printf("%-16s", label);
    
    int i, j;
    for(i = 31, j = 0; i >= 0; i--, j++) {
        if ((j & 0x7)  == 0) putchar(' ');
        (a & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}
