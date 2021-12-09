#include <stdio.h>

int main(void){
    char inname[20];
    int inage;
    printf("Name >> ");
    scanf("%s", inname);
    printf("Age >> "); 
    scanf("%d", &inage);
    printf("Hello %s (%d)\n", inname, inage);
    return 0;
}