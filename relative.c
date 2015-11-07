

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc,char **argv) {
	MagickWand *magick_wand;
	MagickBooleanType status;



	MagickWandGenesis();
	magick_wand = NewMagickWand();

    chdir("/home/github/imagemagicktest/output");

	status = MagickReadImage(magick_wand, "../subdir/61806Convert_red.png");

	if (status == MagickFalse) {
        printf("Failed to MagickReadImage");
        return -1;
    }


    MagickSetImageFormat(magick_wand, "png");

	status = MagickWriteImages(magick_wand, "./output.png", MagickTrue);
	if (status == MagickFalse) {
        printf("Failed to MagickWriteImages");
        return -1;
    }

	MagickWandTerminus();
 
    return(0);
}


/*
int mainasdsd(int argc,char **argv) {

    char * filename = "/home/github/imagick-demos/imagick-demos/imagick/../imagick/images/Biter_500.jpg";
    struct stat sb;
    int result;
    

    result = stat(filename, &sb);
    
    if (result != 0) {
        printf("Call failed\n");
        return -1;
    }
    
    
    
    printf("File type:                ");

   switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
            (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
            (long) sb.st_blksize);
    printf("File size:                %lld bytes\n",
            (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) sb.st_blocks);

    printf("Last status change:       %d\n", ctime(&sb.st_ctime));
    printf("Last file access:         %d\n", ctime(&sb.st_atime));
    printf("Last file modification:   %d\n", ctime(&sb.st_mtime));
    

    return 0;
}

*/