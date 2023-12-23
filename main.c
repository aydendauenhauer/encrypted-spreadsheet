	#include "proj.h"

int main(int argc, char *argv[])
{
        char first[20];
        char last[20];
        int age;
        int input = 0;
        int i;
	int key;
	key = atoi(argv[3]);
        NODE *p;
        pthread_t thr;
        pthread_mutex_init(&mutex, NULL);


        if (argc < 4)
        {
                printf("Please enter 2 file names and an encryption key (a number between 0 and 255) when running the code. \n");
                input = -1;
        }

	if (key < 128 || key > 255)
	{
		printf("Please make the encryption key one byte (between 128 and 255). \n");
		input = -1;
	}

        read_all(argv[1], key);

        pthread_create(&thr, NULL, loopThread, (void *) argv[2]);

        while (input != -1)
        {
                printf("Enter '1' to add to the spreadsheet. \n");
                printf("Enter '2' to show the list alphabetically by last name. \n");
                printf("Enter '3' to show the list of people at a given age. \n");
                printf("Enter '4' to remove someone from the spreadsheet. \n");
                printf("Enter '5' to change the age of someone. \n");
                printf("Enter '6' to show the list from the auto-saved (binary) file. \n");
                printf("Enter '7' to show the list using a doubly linked list. \n");
                printf("Enter '8' to show the list using a doubly linked list recursively. \n");
                printf("Enter '0' to save all information to a text file and quit. \n");
                scanf("%d", &input);

                if (input == 1)
                {
                        printf("Enter a first name. \n");
                        scanf("%s", first);
                        printf("Enter a last name. \n");
                        scanf("%s", last);         
                        printf("Enter an age. \n");
                        scanf("%d", &age);
                        printf("%s %s %d \n", first, last, age);
			insert(first, last, age);
                }

                if (input == 2)
                {
                        list();
                }

                if (input == 3)
                {
                        list_ages();
                }

                if (input == 4)
                {
                        printf("Enter the first name of the person you'd like to remove. \n");
                        scanf("%s", first);
                        printf("Enter the last name of the person you'd like to remove. \n");
                        scanf("%s", last);
                        remove_input(first, last);
                }

                if (input == 5)
                {
                        printf("Enter the first name of the person whose age you wish to change. \n");
                        scanf("%s", first);
                        printf("Enter the last name of the person whose age you wish to change. \n");
                        scanf("%s", last);
                        change_age(first, last);
                }

                if (input == 6)
                {
                        readThread(argv[2]);
                }

                if (input == 7)
                {
                        doublyLinked_show();
                }

                if (input == 8)
                {
                        for (i = 0; i < 3; i++)
                        {
                                p = List[i].head;
                                recursion_show(p);
                        }
                }

                if (input == 0)
                {
                        save_all(argv[1], key);
                        for (i = 0; i < 3; i++)
                        {
                                p = List[i].head;
                                delete_all(p);
                        }
                        return;
                }
        }
}

    
