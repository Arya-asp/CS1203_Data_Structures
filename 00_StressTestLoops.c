#include <stdio.h>
#include <stdlib.h>

//change the increment and n and see at what point you end up with an extra loop

int main(int argc, char** argv){

    float i;
    float increment = 0.0000000001; //Change around this
    float n = 0.000002; //And this (this is 10 times increment)
    int count = 1;

    for (i=0.0; i<n; i+=increment) {
        printf("Loop Number: %d\n", count);
        count++;
    }

    return 0;
}
//Class code
//Takeaways:
// The value of n is directly proportional to the number of loop and the value of the increment is inversely proportional to the same. 
// The number of loops is the n/incr.
// We can see the number of loops be inconsistent with the value of n and the increment due to the fact that the increment and n are floats and not an int.