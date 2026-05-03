#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

int main() {
    register int reg_var = 10;
    volatile int vol_var = 20;

    int val = setjmp(env);

    if (val != 0) {
        // After longjmp
        printf("After longjmp:\n");
        printf("register variable = %d\n", reg_var);
        printf("volatile variable = %d\n", vol_var);
        return 0;
    }

    // Modify variables
    reg_var = 100;
    vol_var = 200;

    printf("Before longjmp:\n");
    printf("register variable = %d\n", reg_var);
    printf("volatile variable = %d\n", vol_var);

    // Jump back
    longjmp(env, 1);

    return 0;
}