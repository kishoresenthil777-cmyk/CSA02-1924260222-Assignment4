
#include <stdio.h>

int next_external_token(void);

int next_token(void) {
    static int token = 1000;
    return ++token;
}

int auto_token(void) {
    int token = 1000;
    return ++token;
}

int main(void) {
    int s1 = next_token();
    int s2 = next_token();
    int s3 = next_token();

    int a1 = auto_token();
    int a2 = auto_token();
    int a3 = auto_token();

    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto : %d %d %d\n", a1, a2, a3);

    printf("extern: %d %d %d\n",
        next_external_token(),
        next_external_token(),
        next_external_token());

    for (register int i = 1; i <= 3; i++) {
        printf("register: %d\n", i);
    }

    return 0;
}
