// ⚡ CheckZ @ CheckZ Labs | Crafted 2025
#include <stdio.h>
#include <stdlib.h>

//Student marks analyzer (avg, highest, lowest).  
//→ File reading, arrays, statistical functions.

int main() {
    FILE *file;
    int marks[100];
    int count = 0;
    float sum = 0.0;
    float avg;
    int highest;
    int lowest;
    file = fopen("marks.txt", "r");
    if(file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    while(fscanf(file, "%d", &marks[count]) != EOF && count < 100) {
        sum += marks[count];
        count++;
    }
    fclose(file);
    if(count == 0) {
        printf("No marks found.\n");
        return 1;
    }
    highest = marks[0];
    lowest = marks[0];
    for(int i = 1; i < count; i++) {
        if(marks[i] > highest) highest = marks[i];
        if(marks[i] < lowest) lowest = marks[i];
    }
    avg = sum / count;
    printf("Average: %.2f\n", avg);
    printf("Highest: %d\n", highest);
    printf("Lowest: %d\n", lowest);
    return 0;
}