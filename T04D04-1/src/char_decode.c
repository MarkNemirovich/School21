#include <stdio.h>

void encoding();
void decoding();
int decode(char c);

int main(int argc, char **argv) {
    if (argc == 2 && argv[1][0] == '0' && argv[1][1] == '\0')
        encoding();
    else if (argc == 2 && argv[1][0] == '1' && argv[1][1] == '\0')
        decoding();
    else {
        printf("n/a");
    }
    return 0;
}

void encoding() {
    int litera = 1;
    char c, err = 0;
    while (err == 0) {
        c = getchar();
        if (c == '\n') {
            break;
        }
        if (litera == 1) {
            litera = 0;
            if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')) {
                err = 1;
                break;
            } else
                printf("%x", c);
        } else {
            litera = 1;
            if (c != ' ') {
                err = 1;
                break;
            } else
                printf("%c", c);
        }
    }
    if (err == 1) {
        printf("\x1b[2K");
        printf("\rn/a");
    }
}

void decoding() {
    int litera = 0, h, l;
    char c, err = 0;
    while (err == 0) {
        c = getchar();
        if (c == '\n') {
            break;
        }
        if (litera == 0) {
            litera = 1;
            h = decode(c);
            if (h == -1) {
                err = 1;
                break;
            }
        } else if (litera == 1) {
            litera = 2;
            l = decode(c);
            if (l == -1) {
                err = 1;
                break;
            }
            printf("%c", 16 * h + l);
        } else {
            litera = 0;
            if (c != ' ') {
                err = 1;
                break;
            } else
                printf("%c", c);
        }
    }
    if (err == 1) {
        printf("\x1b[2K");
        printf("\rn/a");
    }
}

int decode(char c) {
    int code;
    if (c >= '0' && c <= '9')
        code = (c - '0');
    else if (c >= 'A' && c <= 'F')
        code = (c - 'A' + 10);
    else if (c >= 'a' && c <= 'f')
        code = (c - 'a' + 10);
    else
        code = -1;
    return code;
}