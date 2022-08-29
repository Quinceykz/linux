

#include "stdio.h"

#ifdef TEST

#else
int main()
{
        FILE *fp = NULL;
        char *buf[3] = {
                "This is first line!\n",
                "Second Line!\n",
                "OK, the last line!\n"
        };
        char tmp_buf[3][64], *p;
        int i;

        fp = fopen("chap7_demo.dat", "rb+");

        if (NULL==fp) {
                printf("error to open file!\n");
                return -1;
        }

        for (i=0;i<3;i++)
                fputs(buf[i], fp);
        fseek(fp, 0, SEEK_SET);

        for (i=0;i<3;i++) {
                p = tmp_buf[i];
                fgets(p, 64, fp);
                printf("%s", p);
        }

        fclose(fp);
        
        return 0;
}

#endif
