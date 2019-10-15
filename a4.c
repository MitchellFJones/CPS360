/*
Name: Mitchell Jones & Brandon Stolz        Class: CPS 360
Assignment: 4
Due: Oct 16, 2019                                           
Points: 10

Problem: Using the C Programming Language create a program that will simulate correctly the operations of
a half adder, a full adder, a ripple-carry adder, a look-ahead-carry adder, an even parity-bit generator, an 
odd parity-bit checker, a two by one multiplexer, and a four by one multiplexer. Do this using no arithmetic operators,
no control-flow constructs, and no atoi() functions. The purpose is to correctly use boolean logic circuits
in the realm of the C language. Using if statments (aside from checking the number of arguments being passed in for
standard error purposes) is not allowed, the goal is to use the boolean logic within our circuits to implement the 
desired logic.

Solution: Following the outline of the program, creating funtions within this program is not hard.
Simply convert the boolean logic of a circuit to direct variables in C. Using the bitwise operators of C
(&, |, ̃, ^, >>, <<) we can iterate, combine, negate, add, and even compare through any number given using it's binary.
Every circuit in this program requires different logic, and in turn uses different bitwise operators. Specfic circuits
in this program use each other. The Ripple-Carry Adder for example takes the operation given in the fulladdr function and applies
it four different times, using a different value for the sum each time. That implementation is very similar to that in the real world.
When entering values, the program uses HEX values (making it easier to check whether an operation was run correctly).

Data-Structure Used: No Structs or User-Defined Types were used in this program (since there was no need being
that only boolean logic was being handled). Only low level and simple variables were used.

Errors-Handled: The standard error will read in whether the correct number of inputs has been used.
*/

#include <stdio.h>
#include <stdlib.h>

/*Problem: Display and run funtions based off of digital logic circuits. 

Solution: Creates three variables a, b, and c using the arguments given on the command line.
Create sum, out (result of bit), and outcary (result of bit add operation) as well as their respective pointer values. If
input has values that are below the requirement, display the standard error (usage).
Input variables into various funtions to obtain results, and display them.*/

int main(int argc, char *argv[]){

    void halfaddr(int a, int b, int *sum, int *outcary);
    void fulladdr(int a, int b, int incary, int *sum, int *outcary);
    void rcadd4(int a, int b, int incary, int *sum, int *outcary);
    void lacadd4(int a, int b, int incary, int *sum, int*outcary);
    void evenparity3gen(int a, int *paritybit);
    void oddparity4chk(int a, int *checkbit);
    void mux2by1(int a, int b, int *yout);
    void mux4by1(int a, int b, int *yout);
    void printresult(char *label, int a);
    void usage(char *progname);

    int a = strtol(argv[1], NULL, 16), b = strtol(argv[2], NULL, 16), c = strtol(argv[3], NULL, 16), 
    out, sum, outcary, *o = &out; *s = &sum, *co = &outcary;

    if(argc < 4) usage(argv[0]);
    
    printf("%s\n", "halfadder:");
    halfaddr(a, b, s, co);
    printresult("sum:", sum); printresult("outcary:", outcary); printf("\n");
    
    printf("%s\n", "fulladder:");
    fulladdr(a, b, c, s, co);
    printresult("sum:", sum); printresult("outcary:", outcary); printf("\n");
    
    printf("%s\n", "racadd4 (4-bit-adder):");
    racadd4(a, b, c, s, co);
    printresult("sum:", sum); printresult("outcary:", outcary); printf("\n");
    
    printf("%s\n", "lacadd4: (4-bit-adder):");
    lacadd4(a, b, c, s, co);
    printresult("sum:", sum); printresult("outcary:", outcary); printf("\n");
    
    printf("%s\n", "evenparity3gen:");
    evenparity3gen(a, o);
    printresult("yout:", out); printf("\n");

    printf("%s\n", "oddparity4chk:");
    oddparity4chk(a, o);
    printresult("yout:", out); printf("\n");

    printf("%s\n", "mux2by1:");
    mux2by1(a, b, o);
    printresult("yout:", out); printf("\n");

    printf("%s\n", "mux4by1:");
    mux4by1(a, b, o);
    printresult("yout:", out); printf("\n");

    exit (0);
}

/*Problem: Given bad agruments through command line.

Solution: On call will display the name of program followed by the standard error, this
will display the corrent inputs for this program.*/

void usage(char *progname){
    
    fprintf(stderr, "./%s <arg-a> <arg-b> <arg-c>\n", progname); exit(1);
}

/*Problem: Adds two bits together (without using a carry-in-bit).

Solution: Sum is the exclusive OR of a and b, while outcary is the AND of
a and b, making a half adder.*/

void halfaddr(int a, int b, int *sum, int *outcary){
    
    *sum = (a & 1) ^ (b & 1);
    *outcary = (a & 1) & (b & 1);
}

/*Problem: Adds two bits together (using carry-in-bit).

Soultion: Sum is the exclusive OR of a, b, and incary (from previous operation), while
outcary is the AND of a and b OR the incary of AND a OR b. Creating a full adder.*/

void fulladdr(int a, int b, int incary, int *sum, int *outcary){
    
    *sum = (a & 1) ^ (b & 1) ^ (incary & 1);
    *outcary = (a & b) | (incary & (a | b));
}

/*Problem: Find the sum of the lower order 4 bits of two numbers.

Solution: Create 4 sum values that can store the value of the sum each time a full adder
operation is done. Meaning that the value will be stored in a different spot as iteration beings.
Sum is merely the OR concatenation of all sums together. Using 4 fulladdrs, this will create a
ripple-carry-adder of 4 lower order bits.*/

void rcadd4(int a, int b, int incary, int *sum, int *outcary){
    
    int s3, s2, s1, s0;
    
    int *s3p = &s3, *s2p = &s2, *s1p = &s1, *s0p = &s0;
    
    fulladdr(a & 1, b & 1, incary, s0, outcary);
    fulladdr((a >> 1) & 1, (b >> 1) & 1, *outcary, s1, outcary);
    fulladdr((a >> 2) & 1, (b >> 2) & 1, *outcary, s2, outcary);
    fulladdr((a >> 3) & 1, (b >> 3) & 1, *outcary, s3, outcary);
    
    *sum = (s3 << 3) | (s2 << 2) | (s1 << 1) | s0;
}

/*Problem: Find the sume of the lower order 4 bits of two numbers using the logic
of a look ahead.

Solution: Create the values of the bits for both numbers, the sums, and for the look
ahead store the values for the carry out/carry in (the c variables). After assigning 
the bit values to their variables place the values inside the fulladdr function. The only
difference is the fact that this function stores the value of the carry out.*/

void lacadd4(int a, int b, int incary, int *sum, int *outcary){
    
    int s3, s2, s1, s0;
    
    int *s3p = &s3, *s2p = &s2, *s1p = &s1, *s0p = &s0;

    int a0 = (a & 1), a1 = ((a >> 1) & 1), a2 = ((a >> 2) & 1), a3 = ((a >> 3) & 1),
    b0 = (b & 1), b1 = ((b >> 1) & 1), b2 = ((b >> 1) & 1), b3 = ((b >> 3) & 1);

    int c0 = (a0 & b0) | ((a0 ^ b0) & incary);
    int c1 = (a1 & b1) | ((a1 ^ b1) & c0);
    int c2 = (a2 & b2) | ((a1 ^ b2) & c1);

    *outcary = (a3 & b3) | ((a3 ^ b3) & c2);

    fulladdr(a0, b0, incary, s0, outcary);
    fulladdr(a1, b1, c0, s1, outcary);
    fulladdr(a2, b2, c1, s2, outcary);
    fulladdr(a0, b0, c2, s3, outcary);

    *sum = (s3 << 3) | (s2 << 2) | (s1 << 1) | s0;
}

/*Problem: Generate even parity bit for lower order 3 bits of a value.

Solution: Create 3 variables that represent the first 3 bits of the value.
The even partiy bit will simply be the exclusive OR of bit-2 and bit-1, OR if bit-0
is present. Creating an even parity bit generator.*/

void evenparity3gen(int a, int *paritybit){
    
    int b2, b1, b0;
    
    b2 = (a >> 2) & 1;
    b1 = (a >> 1) & 1;
    b0 = (a & 1);
    
    *paritybit = (b2 ^ b1) | b0;
}

/*Problem: Checks odd parity of lower order 4 bits of a value.

Solution: Create 4 variables to represent the bits of our value. Using the exclusive OR 
of bit-3 and bit-2 along with bit-1 and bit-0, then the exclusive OR of that with 1 will 
determine whether the value is odd or even.*/

void oddparity4chk(int a, int *checkbit){
    
    int b3, b2, b1, b0;
    
    b3 = (a >> 3) & 1;
    b2 = (a >> 2) & 1;
    b1 = (a >> 1) & 1;
    b0 = (a & 1);
    
    *checkbit = ((b3 ^ b2) ^ (b1 ^ b0)) ^ 1;
}

/*Problem: Connects one of the 2 inputs (the lower order 2-bits of a) to out
based on the selection input (lowest order bit of b).

Solution: Create variables to represent the bits in the operation.
The boolean logic states the out is the selection input exclusive OR with 1, AND bit-0 OR
the AND of bit-1 and bit-2 (aka the selction input).*/

void mux2by1(int a, int b, int *yout){
    
   int i2, i1, i0;
    
   i0 = a & 1;
   i1 = (a >> 1) & 1;
   i2 = b & 1;

   *yout = (i0 & (i2 ^ 1)) | (i1 & i2);
}

/*Problem: Connects one of the 4 inputs (the lower order 4-bits of a) to out 
based on the the selection input (low order bits of b).

Solution: Create variables to represent the bits in the operation. The 
boolean logic of the multiplexer creates will correctly give us the desired output based off of
the selection input (aka the lower order bits of b).*/

void mux4by1(int a, int b, int *yout){
  
  int i5, i4, i3, i2, i1, i0;

  i0 = a & 1;
  i1 = (a >> 1) & 1;
  i2 = (a >> 2) & 1;
  i3 = (a >> 3) & 1;
  i4 = b & 1;
  i5 = (b >> 1) & 1;

  *yout = ((i4 & (~1)) & i0 & (i5 & (~1))) | (i4 & i1  & (i5 & (~1))) | ((i4 & (~1)) & i2 & i5) | (i4 & i3 & i5);
    
}

/*Problem: Print the results of bits depending upon the value being passed in.

Solution: Print the label of the line, then using the logic given in printbits,
iterating through each bit slot accounting for the base (in this case being 32), every 8 bits
the funtion will print a blank space for ease of reading. On every slot compare the value of a to the slot
of our iteration, if something is there print a 1, if not print a 0.*/

void printresult(char *label, int a){
    
    printf("%-16s", label);
    
    int i, j;
    for(i = 31, j = 0; i >= 0; i--, j++) {
        if ((j & 0x7)  == 0) putchar(' ');
        (a & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}

