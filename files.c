#include "proj.h"

void read_all(char *file_name, int key)
{
        char temp_first[20];
        char temp_last[20];
        int temp_age;
	char buffer[255];
        FILE *fp;

        if ((fp = fopen(file_name, "r")) == NULL)
        {
                printf("The file could not be opened. \n");
                return;
        }

        while (fgets(buffer, 255, fp))
        {
		char *p = buffer;
		while(*p != '\0')
		{
			*p = *p ^ key;
			p++;
		}
		sscanf(buffer, "%s %s %d", temp_first, temp_last, &temp_age);	
                insert(temp_first, temp_last, temp_age);
        }
        fclose(fp);
}


void save_all(char *file_name, int key)
{
        int i = 0;
	char buffer[255];
        NODE *p;
        FILE *fp;

        if ((fp = fopen(file_name, "w")) == NULL)
        {
                printf("File 1 (text file) could not be opened. \n");
                return;
        }

        for (i = 0; i < 3; i++)
        {
                p = List[i].head;
                while (p != NULL)
                {
			sprintf(buffer, "%s %s %d \n", p -> first_name, p -> last_name, p -> age);

			char *q = buffer;
                	while(*q != '\n')
               		{
                	        *q = *q ^ key;
        	                q++;
	                }

                        fprintf(fp, "%s", buffer);

                        p = p -> next;
                }
        }
        fclose(fp);
}

void *loopThread(void *arg)
{
        int i = 0;
        int counter = 0;
        NODE *p;
        FILE *fp;
        char *file_name = (char *) arg;

        while (counter != -1)
        {
                pthread_mutex_lock(&mutex);
                if ((fp = fopen(file_name, "wb")) == NULL)
                {
                        printf("File 2 (binary file) could not be opened. \n");
                        return;
                }

                for (i = 0; i < 3; i++)
                {
                        p = List[i].head;
                        while (p != NULL)
                        {
                                fwrite(p, sizeof(NODE), 1, fp);
                                p = p -> next;
                        }
                }
                fclose(fp);
                pthread_mutex_unlock(&mutex);
                sleep(15);
        }
}

void readThread(char *file_name)
{
        char *temp_first;
        char *temp_last;
        int temp_age;
        NODE p;
        FILE *fp;

        if ((fp = fopen(file_name, "rb")) == NULL)
        {
                printf("File 2 (binary file) could not be opened. \n");
                return;
        }

        while (fread(&p, sizeof(NODE), 1, fp) == 1)
        {
                printf("%s %s, %d \n", p.first_name, p.last_name, p.age);
        }

        fclose(fp);
}

