#include <gnu/libc-version.h>
#include <stdio.h>

int main() {
    char *version = gnu_get_libc_version();
    printf(version);
}