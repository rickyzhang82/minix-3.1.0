/* Implements sethostname() by writing to /etc/hostname.file. */
/* Minix lacks this function. */

#include <config.h>

#ifdef _MINIX

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "linebuffer.h"
#define HOSTNAME_FILE "/etc/hostname.file"
#define HOSTNAME_TEMP "/etc/hostnameXXXXXX" /* must end in "XXXXXX" */

int sethostname(char *hostname, size_t len) {
    /* The hostname is on the first line of HOSTNAME_FILE; then a '\n'.
     * Keep the rest of the file intact.
     */
    char hostname_temp[] = HOSTNAME_TEMP;
    FILE *fp;
    struct linebuffer lb;
    int newfd, ok;

    fp = fopen(HOSTNAME_FILE, "r+");
    if (fp == NULL) return -1;
    initbuffer(&lb);

    /* Create a new file with an unpredictable filename. 
     * Write the new hostname to the first line and copy the rest 
     * of the old file. Then rename old to new. 
     * This is much easier to do than to modify the first line and we 
     * never end up with a rotten hostname file (atomic rename), however, 
     * another process that had the hostname file open, may find it gone.
     */
    newfd = mkstemp(hostname_temp);
    if (newfd < 0 || 
        write(newfd, hostname, len) < len || write(newfd, "\n", 1) < 1) {
            ok = -1; /* Writing first line of temp file failed. */
    } else { /* copy lines */
        readlinebuffer(&lb, fp); /* Skip first line (old hostname). */

        /* Copy the rest of the old file to the new file. */
        while (readlinebuffer(&lb, fp) != NULL) {
            if (write(newfd, lb.buffer, lb.length) < lb.length) {
                ok = -1;
                break;
            }
        }
        if (ferror(fp)) ok = -1;
        else ok = 0;
    }

    close(newfd);
    freebuffer(&lb);
    fclose(fp);
    if (ok == 0) {
        /* mkstemp creates with 600; hostname file should be 644. */
        chmod(hostname_temp, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        ok = rename(hostname_temp, HOSTNAME_FILE);
    }
    else unlink(hostname_temp); /* Remove the temp file */
    return ok;
}

#endif /* _MINIX */
