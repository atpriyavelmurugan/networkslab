#include <stdio.h>

void calculate_the_maximum(int n, int k) {
    int max_and = 0;
    int max_or = 0;
    int max_xor = 0;
    int target = k - 1; 
    if (k > 1) {
       
        if ((target | (target + 1)) <= n) {
            max_and = target;
        } else {
            max_and = target - 1;
        }

        
        if ((target | (target - 1)) <= n) {
            max_or = target;
        } else {
            max_or = target - 1;
        }

       
        int p = 1;
        while ((p << 1) <= target) {
            p <<= 1;
        }
        if ((target | (p - 1)) <= n) {
            max_xor = target;
        } else {
            max_xor = target - 1;
        }
    }

    printf("%d\n%d\n%d\n", max_and, max_or, max_xor);
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) == 2) {
        calculate_the_maximum(n, k);
    }
    return 0;
}
