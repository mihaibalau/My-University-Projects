#include <stdio.h>

char string[100];
int numbers[12];

void convert_string(char string[100], int numbers[12]);

int main(){

    printf("Enter the string containing n binary representations on 8 bits: \n");
    scanf("%s", string);

    convert_string(&string[100], &numbers[12]);

    for(int i=0; i<12; i++)
        if(numbers[i] != 0)
            printf("%d, ", numbers[i]);
        else
            return 0;
    return 0;
}