/*
Name: Mitchell Jones & Brandon Stolz        Class: CPS 360
Assignment: 5
Due: Oct 23, 2019
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

int main(char argc, char **argv){

int a,b,c,d;

if (argc != 5) usage(argv[0]);

printrslt("compute1: ", compute1(a, b, c, d));


exit(0);
}

/*Problem: Display the standard error

Solution: Print the standard error using fprintf function, display simply
the correct number of values that this program requires by showing an example 
of input on the command line at run time.*/

void usage(char *progname){

fprintf(stderr, "./%s <arg-a> <arg-b> <arg-c> <arg-d>\n", progname); exit(1);
}

/*Problem: Compute the desired output requested by Program Outline.

Solution: Pass in the values to be computed, and using the order of operations
the arithmatic computations can be done. Simply create a sum variable and return it
once operations have been done.*/

int compute1(int a, int b, int c, int d){

	int sum = 0;
	
	sum = a * b - c / d + b % a + b * c * d;

return sum;
}

/*Problem: Print an int value (the sum of operations) to the screen,
with a label.

Solution: Pass in the label and int to be dispalyed, then using the 
printf funtion.*/


void printrslt(char *label, int result){
	
	printf("%-16s", label);
	printf("%d\n", result);
}
