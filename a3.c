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


int isinset(int elm, set s1){    
    
    int i, j;
    i = elm >> 3;
    j = elm & 7;
    if (s1.data[i] & (1<<j)) return 1;
    return 0;
            
}


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


int buildaset(set *s1){
    
    void addtoset(int elm, set *s1);
    int count = 0;
    int counter = 0;
    int temp;
    
    scanf("%d", &count);
    
    if (count > -1) {
        while (counter < count){
            scanf("%d", &temp);
            addtoset(temp, s1);
            counter++;
        }
        return 1;
    }
    
    return 0;
}

void clearaset(set *s1) {  
    initaset(s1);
}
