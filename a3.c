/*
Name: Mitchell Jones & Brandon Stolz        Class: CPS 360
Assignment: 3
Due: Oct 4, 2019                                           
Points: 10
*/

#define SIZE 32         /* 32*8 elements in a set */
struct set{
        char data[SIZE];
        int count;      /* count of elements/members */
};
typedef struct set set; /* set type - user defined */


#include <stdlib.h>
#include <stdio.h>
#define SIZE 32

int main(void)
{
    
    void initaset(set *s1);
    int buildaset(set *s1);
    void printaset(char *label, set s1);
    void clearaset(set *s1);
    void dosetops(set seta, set setb);
    
   set seta, setb;
   int i;
   /* prototypes for the functions called by main go here */
   initaset(&seta); initaset(&setb);
 
   for(i = 0; i < 4; i++) {
      if(!buildaset(&seta) || !buildaset(&setb)) {
         fprintf(stderr, "Set build failure. \n");
         clearaset(&seta); clearaset(&setb); continue;
      }
      
      printaset("\nSet A: ", seta); printaset("Set B: ", setb);
      dosetops(seta, setb);
      clearaset(&seta); clearaset(&setb);
   }
   
   exit(0);
}
/*
Problem: Build two sets using struct set, and run set operations.

Solution: Create two sets then intialize them. Using buildaset() values
will be stored in our set using scanf, however if buildaset() returns a zero
then print the standard error for build failure, and clear the sets. On success,
we print out our sets using printaset(), and dosetops() will run union, intersect,
and difference. Clear our sets after dosetops(), and repeat proccess.
*/



void initaset(set *s1){       
    int i;
      s1->count = 0;
      for(i = 0; i < SIZE; i++)
         s1->data[i] = 0;
            
}

/*
Problem: Initialize a set, clearing values of count.

Solution: Pass in the value of a set, makes its count zero. 
Iterate through the set using SIZE, makinng each value zero.
*/

void addtoset(int elm, set *s1) {
    
    int i, j;
    int isinset(int el, set s1);
    if (isinset(elm, *s1)) return;
    i = elm >> 3;
    j = elm & 7;
    s1->data[i] = s1->data[i] | (1<<j);
    s1->count += 1;
}

/*
Problem: Add a value to a set (int elm), if that value is already in the set don't add it again.

Solution: Using isinset, check if elm is already in set, if so return. I is elm right shifted
by 3 (Byte location), j elm & 7 (Bit location). S1's data is equal to the value byte location and
bit location. increase s1's count by one.

*/

int isinset(int elm, set s1){    
    
    int i, j;
    i = elm >> 3;
    j = elm & 7;
    if (s1.data[i] & (1<<j)) return 1;
    return 0;
            
}
/*
Problem: Search if a value (int elm) is in a set, return 1 if found.

Solution: Make i and j your byte and bit location, if there is a value found
at s1's data of i and j, elm is in the set. if not return zero.

*/


void setunion(set s1, set s2, set *s3) {
    void addtoset(int elm, set *s1);
    void printaset(char *label, set s1);
    void clearaset(set *s1);
    
    int i, j;
    
    for (i = 0; i < 32; i++){
        for (j = 0; j < 8; j++) {
                if (s1.data[i] & (1 << j)) addtoset(i << 3 | j, s3);
                
        }
    }
        
    for (i = 0; i < 32; i++){
        for (j = 0; j < 8; j++) {
                if (s2.data[i] & (1 << j)) addtoset(i << 3 | j, s3);
                
        }
    }
    
    printaset("Set Union: ", *s3);
    clearaset(s3);
}
/*
Problem: Find the union of two sets and display them.

Solution: Pass in value of blank third set, iterate through
the byte and bit locations of both sets. If there is a value at some 
location add that value to our new set (s3). After doing for both sets use 
printaset() to display s3, then clear s3 using clearaset().

*/

void setintersect(set s1, set s2, set *s3){
    void addtoset(int elm, set *s1);
    void printaset(char *label, set s1);
    void clearaset(set *s1);
    int isinset(int elm, set s1);
    
    
    int i, j;
    
    for (i = 0; i < 32; i++){
        for (j = 0; j < 8; j++) {
                if (s1.data[i] & (1 << j)){
                    if (isinset(i << 3 | j, s2))
                        addtoset(i << 3 | j, s3);
                }  
        }
    }
    
    printaset("Set Intersect: ", *s3);
    clearaset(s3);
    
    
}

/*
Problem: Find the intersect of two sets and display them.

Solution: Pass in value of blank third set. Iterate through the byte and bit locations of s1. 
At each location use isinset(), checking if that value is in s2.
If it is, add it to our blank set s3. Display s3 using printaset(),
clear s3 using clearaset().

*/


void setdiff(set s1, set s2, set *s3){
    void addtoset(int elm, set *s1);
    void printaset(char *label, set s1);
    void clearaset(set *s1);
    int isinset(int elm, set s1);
    
    
    int i, j;
    
    for (i = 0; i < 32; i++){
        for (j = 0; j < 8; j++) {
                if (s1.data[i] & (1 << j)){
                    if (!isinset(i << 3 | j, s2))
                        addtoset(i << 3 | j, s3);
                }  
        }
    }
    
    printaset("A Difference B: ", *s3);
    clearaset(s3);
    
    for (i = 0; i < 32; i++){
        for (j = 0; j < 8; j++) {
                if (s2.data[i] & (1 << j)){
                    if (!isinset(i << 3 | j, s1))
                        addtoset(i << 3 | j, s3);
                }  
        }
    }
    
    printaset("B Difference A: ", *s3);
    clearaset(s3);
}
/*
Problem: Find the difference set of s1 on s2, and s2 on s1.

Solution: Pass in value of blank third set. Iterate through byte and
bit locations of s1, using isinset() to check if that value is in s2.
If it is not, add that value to s3. Print s3 using printaset(), clear s3
using clearaset(). Repeat process by iterating through s2 on s1.

*/

void dosetops(set seta, set setb){
    void setunion(set s1, set s2, set *s3);
    void setintersect(set s1, set s2, set *s3);
    void initaset(set *s1);
    void setdiff(set s1, set s2, set *s3);
    
    set s3;
    initaset(&s3);
    setunion(seta, setb, &s3);
    setintersect(seta, setb, &s3);
    setdiff(seta, setb, &s3);
}
/*
Problem: Run operations that find union, intersect, and differnce of two sets.

Solution: Create a new set called s3 and initialize it. Pass the address of s3 into
setunion(), setintersect(), and setdiff() along with the two sets being compared.
*/

void printaset(char *label, set s1){
    int count;
    count = s1.count;
    int i;
    int j;
    
    printf("%s", label);
    
    if(count == 0) printf("Empty Set");
    
        for (i = 0; i < 32; i++){
            for (j = 0; j < 8; j++) {
                if (s1.data[i] & (1 << j)) printf("%d ", i << 3 | j);
                
            }
        }
        printf("\n");
    
    
}
/*
Problem: Print the values of a set.

Solution: Check if the set to print is empty, if it is display Empty Set.
Iterate through the byte and bit locations of our set, checking if a value exists.
If one does exist print off its location.

*/

int buildaset(set *s1){
    
    void addtoset(int elm, set *s1);
    int countelm = 0;
    int counter = 0;
    int temp;
    
    scanf("%d", &countelm);
    
    if (countelm > -1) {
        while (counter < countelm){
            scanf("%d", &temp);
            addtoset(temp, s1);
            counter++;
        }
        return 1;
    }
    
    return 0;
}

/*
Problem: Build at set by adding in values using scanf, return one on success.

Solution: Scan the number of values being entered in a set (count), if count is
a negative number return zero. While the number of bits in the set is less than 
the number we want to add scan the value of the number we are adding. Use addtoset(),
and increase the counter (number of bits in set) by one.

*/
void clearaset(set *s1) {  
    initaset(s1);
}
/*
Problem: Clear all the data from a set.

Solution: Use function as wrapper, pass in value of a set and 
use initaset() to intitalize the values back to zero.
*/
