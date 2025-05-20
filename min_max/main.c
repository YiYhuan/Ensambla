#include <stdio.h>


int main(void) {
    int value1, value2, value3;
    int min, max;

    extern void min_max(int a, int b, int c, int *min, int *max);

    printf("Ingrese un numero: ");
    scanf("%d", &value1);
    printf("Ingrese otro numero: ");
    scanf("%d", &value2);
    printf("Ingrese otro numero: ");
    scanf("%d", &value3);
    printf("Los numeros son: %d, %d, %d\n", value1, value2, value3);
    
    min_max(value1, value2, value3, &min, &max);

    printf("Minimum: %d\n", min);

    printf("Maximum: %d\n", max);
    return 0;
} 