#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <time.h>  

int main(int argc, char **argv) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: ./stat <filename>\n");
        exit(EXIT_FAILURE);
    }

    struct stat file_status;
    char *filename = argv[1];

    if (stat(filename, &file_status) != 0) {
        fprintf(stderr, "Failed to access file status\n");
        exit(EXIT_FAILURE);
    }

    printf("File: %s\n", argv[1]);
    printf("Size: %ld     Blocks: %ld       IO block: %ld\n", (long)file_status.st_size, (long)file_status.st_blocks, (long) file_status.st_blksize);
    printf("Mode: %lo    Inode: %lu    Links: %ld\n", (unsigned long) file_status.st_mode, file_status.st_ino, file_status.st_nlink);
    printf("Uid: %ld      Gid: %ld\n", (long) file_status.st_uid, (long) file_status.st_gid);
    printf("Access: %s", ctime(&file_status.st_atime));
    printf("Modify: %s", ctime(&file_status.st_mtime));
    printf("Change: %s", ctime(&file_status.st_ctime));
    
    exit(EXIT_SUCCESS);
}