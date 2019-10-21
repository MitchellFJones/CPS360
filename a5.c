#include <stdio.h>
#include <stdlib.h>

int main(char argc, char **argv){

int a,b,c,d;

if (argc != 5) usage(argv[0]);




exit(0);
}

/*
*/

void usage(char *progname){

fprintf(stderr, "./%s <arg-a> <arg-b> <arg-c> <arg-d>\n", progname); exit(1);

}

/*
*/

int compute1(int a, int b, int c, int d){

	int sum = 0;
	
	sum = a * b - c / d + b % a + b * c * d;

return sum;
}

/*
*/

void printrslt(char *label, int result){



}