#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#include <ctype.h>
#include <locale.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <signal.h>
#include <assert.h>

//typedef struct dirent;

#include <sys/types.h>

#include <dirent.h>
//#include <bits/dirent.h>


//struct dirent {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported
//                                   by all file system types */
//    char           d_name[256]; /* filename */
//};
//extern struct dirent;




//typedef struct __direntDJA {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported
//                                   by all file system types */
//    char           d_name[256]; /* filename */
//} dirent;
//


int readsome(DIR    *dirstruct) {

    struct dirent *p_direntry;
    int finished = 0;
    int count = 0;

    while (finished == 0 && count < 40) {
        p_direntry = readdir(dirstruct);

        if (p_direntry == NULL) {
            finished = 1;
        }
        else {
            printf("Found file %s \n", p_direntry->d_name);
        }
        count++;
    }
    
    printf("************\n");
    
    return finished;
}


int main(int argc,char **argv) {
    
    
    DIR *dirstruct;
    DIR *dirstruct2;

    int result;

    dirstruct = opendir("./ImageMagick-6.9.0-0/coders");
    
    if (dirstruct == NULL) {
        printf("Failed to open dir \n");
        return (-1);
    }
    
    readsome(dirstruct);
    
    dirstruct2 = opendir("./ImageMagick-6.9.0-0/coders");
    
    if (dirstruct2 == NULL) {
        printf("Failed to open dir 2 \n");
        return (-1);
    }
    
    readsome(dirstruct2);
    readsome(dirstruct);
    readsome(dirstruct2);
    readsome(dirstruct2);
    readsome(dirstruct);
    

    
    
    result = closedir(dirstruct);
    result = closedir(dirstruct2);
    
    printf("close result is: %d \n", result);
    
    return(0);
}

