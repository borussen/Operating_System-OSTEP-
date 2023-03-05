#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>   
#include <fcntl.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char **argv) {

    if (argc != 3 || strlen(argv[1]) <= 1 || argv[1][0] != '-') {
        fprintf(stderr, "Usage: %s -<offset> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int lines = atoi(argv[1]);
    lines *= -1;
    lines++;

    char *filename = argv[2];
    struct stat file_status;
    int fd;

    if (stat(filename, &file_status) == -1) { handle_error("stat"); }
    
    if ((fd = open(filename, O_RDONLY)) == -1) { handle_error("open"); }

    if (lseek(fd, -1, SEEK_END) == -1) { handle_error("lseek"); }

    char buf[file_status.st_size];
    int offset;

    while (lines > 0) {
        if (read(fd, buf, 1) == -1) { handle_error("read"); }

        if (buf[0] == '\n') { lines--; }

        offset = lseek(fd, -2, SEEK_CUR);
        if (offset == -1) { break; }
    }

    if (offset > 0 || lines == 0) {
        if (lseek(fd, 2, SEEK_CUR) == -1) { handle_error("lseek"); }
    } 
    else {
        if (lseek(fd, 0, SEEK_SET) == -1) { handle_error("lseek"); }
    }

    memset(buf, 0, file_status.st_size);
    if (read(fd, buf, file_status.st_size) == -1) { handle_error("read"); }

    printf("%s", buf);
    close(fd);

    exit(EXIT_SUCCESS);
}