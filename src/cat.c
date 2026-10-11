#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE 4096

int main(int argc, char *argv[]) {
    char buffer[BUFF_SIZE];
    int n_read;
    if (argc == 1) {
        while ((n_read = read(STDIN_FILENO, buffer, BUFF_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, n_read);
        }
        return 0;
    }
    if (argc > 2) {
        fprintf(stderr, "Multi-file processing is not supported in this version\n");
        return 1;
    }
    const int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "cat: %s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    while ((n_read = read(fd, buffer, BUFF_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, n_read);
    }
    if (isatty(STDOUT_FILENO)) {
        write(STDOUT_FILENO, "\n", 1);
    }
    return 0;
}