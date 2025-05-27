#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);
    if (x == 5) {
        printf("%d\n", x);
    } else {
        if (x == 2) {
            printf("%d\n", 0);
        }
    }
    return 0;
}
