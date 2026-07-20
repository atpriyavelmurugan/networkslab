#include <stdio.h>
#include <ctype.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        char s[1005];
        scanf("%s", s);

        int total_sum = 0;
        int i; // Declare the loop variable here for older compilers
        
        for (i = 0; s[i] != '\0'; i++) {
            if (isdigit(s[i])) {
                total_sum += s[i] - '0';
            }
        }

        printf("%d\n", total_sum);
    }

    return 0;
}
