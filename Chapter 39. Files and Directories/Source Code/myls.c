#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>  

void print_stats(char *path) {
    struct stat file_status;
    if (stat(path, &file_status) < 0) {
        fprintf(stderr, "Failed to get stats\n");
        exit(EXIT_FAILURE);
    }
    printf("%5u %5u %6ld %6ld %8ld %6lu %5lu  %s", file_status.st_uid, file_status.st_uid, file_status.st_size, 
    file_status.st_blocks, file_status.st_blksize, file_status.st_ino, file_status.st_nlink, ctime(&file_status.st_mtime));
}


int main(int argc, char **argv) {

    int detail = 0, opt;
    
    while ((opt = getopt(argc, argv, "l")) != -1) {
        if (opt == 'l') { 
            detail = 1; 
        }
    }

    char *dir = optind < argc ? argv[optind] : ".";
    char path[1024];
    struct dirent *pDirent;
    DIR *pDir;
    
    if ((pDir = opendir(dir)) == NULL) {
        fprintf(stderr, "Failed to open directory\n");
        exit(EXIT_FAILURE);
    }
    if (detail) {
        printf("    File  Uid   Gid   Size  Block IO_block  Inode Links           Time\n");
    }
    while ((pDirent = readdir(pDir)) != NULL) {
        if (detail) {
            sprintf(path, "%s%s%s", dir, dir[strlen(dir)-1] == '/' ? "" : "/", pDirent->d_name);
            printf("%8s", pDirent->d_name);
            print_stats(path);
        }
        else {
            printf("%s\n", pDirent->d_name);
        }
    }

    exit(EXIT_SUCCESS);
}