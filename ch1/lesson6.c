#include <stdio.h>

int main(void) {
    int max_recursive_calls = 100;
    char io_mode = 'w';
    float throttle_speed = 0.2;

    printf("Max recursive calls: %d\n", max_recursive_calls);
    printf("IO mode: %c\n", io_mode);
    printf("Throttle speed: %f\n", throttle_speed);

    return 0;
}
