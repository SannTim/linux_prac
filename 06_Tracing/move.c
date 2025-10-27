#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define EXIT_ARGC          1
#define EXIT_OPEN_IN       2
#define EXIT_STAT_IN       3
#define EXIT_MMAP          4
#define EXIT_OPEN_OUT      5
#define EXIT_WRITE         6
#define EXIT_CLOSE_OUT     7
#define EXIT_UNLINK_IN     8

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(EXIT_ARGC);
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    int fd_in = open(infile, O_RDONLY);
    if (fd_in == -1) {
        perror("open infile");
        exit(EXIT_OPEN_IN);
    }

    // Получаем размер
    struct stat st;
    if (fstat(fd_in, &st) == -1) {
        perror("fstat infile");
        close(fd_in);
        exit(EXIT_STAT_IN);
    }

    off_t size = st.st_size;
    if (size < 0) {
        fprintf(stderr, "Negative file size? Really?\n");
        close(fd_in);
        exit(EXIT_STAT_IN);
    }

    char *buf = malloc(size);
    if (!buf) {
        perror("malloc");
        close(fd_in);
        exit(EXIT_MMAP);
    }

    ssize_t r = read(fd_in, buf, size);
    if (r != size) {
        perror("read infile");
        free(buf);
        close(fd_in);
        exit(EXIT_MMAP);
    }
    close(fd_in);

    int fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1) {
        perror("open outfile");
        free(buf);
        exit(EXIT_OPEN_OUT);
    }

    ssize_t w = write(fd_out, buf, size);
    if (w != size) {
        perror("write outfile");
        free(buf);
        close(fd_out);
        exit(EXIT_WRITE);
    }

    if (close(fd_out) == -1) {
        perror("close outfile");
        free(buf);
        exit(EXIT_CLOSE_OUT);
    }

    free(buf);

    if (unlink(infile) == -1) {
        perror("unlink infile");
        exit(EXIT_UNLINK_IN);
    }

    return 0;
}
