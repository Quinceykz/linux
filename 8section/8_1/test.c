
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#ifdef TEST

#else

extern int errno;

int main()
{
        int fd,file_mode;
        char buf[64] = "this is a posix file!(line1)\n";
        off_t curr_pos;

        fd = open("./posix.data", O_CREAT|O_RDWR|O_EXCL, S_IRWXU);  //return a key of dir(fd)  object:creat a .data 

        printf("%d\n", fd);
        if (-1==fd)     {
                switch (errno)  {
                        case EEXIST:
                        printf("File exist!\n");
                        break;
                
                default:
                        printf("open file fail!\n");
                        break;
                }
                return 0;
        }

        write(fd, buf, strlen(buf)); // write message from buf to fd document.
// the function of lseek just like the pointer of mouse.
        curr_pos = lseek(fd, 0, SEEK_CUR);      // set address offset of document    set from now
        printf("File Point at: %d\n", (int)curr_pos);

        lseek(fd, 0, SEEK_SET);                 //set from the start of document.

        strcpy(buf, "File Pointer Moved!\n");   //write new information to buf
        write(fd, buf, strlen(buf));

        file_mode = fcntl(fd, F_GETFL);
        if (-1!=file_mode) {
                switch (file_mode&O_ACCMODE) {
                        case O_RDONLY:
                                printf("file mode is READ ONLY\n");
                                break;
                        case O_WRONLY:
                                printf("file mode is WRITE ONLY\n");
                                break;
                        case O_RDWR:
                                printf("file mode is READ & WRITE\n");
                                break;
                }
        }

        close(fd);

        return 0;

}

#endif
