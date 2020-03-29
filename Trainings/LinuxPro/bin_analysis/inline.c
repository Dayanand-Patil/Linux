
#include <stdio.h> 
  
// Inline function in C 
inline int foo() 
{ 
    return 2; 
} 

int hello()
{
	printf("hellow\n");
 } 
// Driver code 
int main() 
{ 
  
    int ret; 
  
    // inline function call 
    ret = foo(); 
  
    printf("Output is: %d\n", ret); 
    getchar();
    return 0; 
} 

