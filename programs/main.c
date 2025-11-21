#include<stdio.h>
#include<math.h>
 
void squarearea(float side);
void circlearea(float rad);

int main(){
    squarearea(5);
    circlerad(6);
}

void squarearea(float side){
    printf("Square Area: %.2f", pow(side, 2));
}

void circlearea(float rad){
    printf("Circle Area: %.2f", pow(rad, 2));
}