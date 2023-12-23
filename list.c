#include "proj.h"

void insert(char first[20], char last[20], int age)
{
	NODE *p;
	p = (NODE *)malloc(sizeof(NODE));

	if (check_duplicate(first, last) == 0)
	{
		return;
	}

	strcpy(p -> first_name, first);
	strcpy(p -> last_name, last);
	p -> age = age;
	p -> next = NULL;	

	if (age <= 18)
	{
		if (List[0].head == NULL)
		{
			pthread_mutex_lock(&mutex);
			List[0].head = List[0].tail = p;
			pthread_mutex_unlock(&mutex);
		}

		else
		{
			pthread_mutex_lock(&mutex);
			List[0].tail -> next = p;
			p -> prev = List[0].tail;
			List[0].tail = List[0].tail -> next;
			pthread_mutex_unlock(&mutex);
		}
	}

	if (age > 18 && age < 65)
	{
		if (List[1].head == NULL)
		{
			pthread_mutex_lock(&mutex);
			List[1].head = List[1].tail = p;
			pthread_mutex_unlock(&mutex);
		}

		else
		{
			pthread_mutex_lock(&mutex);
			List[1].tail -> next = p;
			p -> prev = List[1].tail;
			List[1].tail = List[1].tail -> next;
			pthread_mutex_unlock(&mutex);
		}
	}

	if (age >= 65)
	{
		if (List[2].head == NULL)
		{
			pthread_mutex_lock(&mutex);
			List[2].head = List[2].tail = p;
			pthread_mutex_unlock(&mutex);
		}

		else
		{
			pthread_mutex_lock(&mutex);
			List[2].tail -> next = p;
			p -> prev = List[2].tail;
			List[2].tail = List[2].tail -> next;
			pthread_mutex_unlock(&mutex);
		}
	}
}

void list()
{
	int i;
	NODE *p;

	for (i = 0; i < 3; i++)
        {
                p = List[i].head;
                while (p != NULL)
                {
                        printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                        p = p -> next;
                }
        }
}

void list_ages()
{
	NODE *p;
	int input2;

	printf("What age would you like to search? \n");
	scanf("%d", &input2);

	if (input2 <= 18)
	{
		p = List[0].head;
		while (p != NULL)
        	{
                	if (input2 == p -> age)
                	{
                        	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                	}
                	p = p -> next;
        	}
	}

	if (input2 > 18 && input2 < 65)
	{
		p = List[1].head;
	        while (p != NULL)
        	{
                	if (input2 == p -> age)
                	{
                        	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                	}
                	p = p -> next;
        	}
	}

	if (input2 >= 65)
	{
		p = List[2].head;
	        while (p != NULL)
        	{
	                if (input2 == p -> age)
        	        {
                        	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                	}
                	p = p -> next;
        	}
	}
}

void remove_input(char *first, char *last)
{
	NODE *p;
	NODE *q;
	int i;
	int first_check;
	int last_check;

	for (i = 0; i < 3; i++)
	{
		p = List[i].head;
		q = List[i].head;
		while (p != NULL)
		{
			first_check = strcmp(first, p -> first_name);
			last_check = strcmp(last, p -> last_name);

			if (first_check == 0 && last_check == 0)
			{
				if (List[i].head == List[i].tail)
				{
					pthread_mutex_lock(&mutex);
					List[i].head = List[i].tail = NULL;
					pthread_mutex_unlock(&mutex);
				}

				else if (p == List[i].head)
				{
					pthread_mutex_lock(&mutex);
					List[i].head = p -> next;
					pthread_mutex_unlock(&mutex);
				}

				else if (p == List[i].tail)
				{
					pthread_mutex_lock(&mutex);
					List[i].tail = q;
					pthread_mutex_unlock(&mutex);
				}

				else
				{
					q -> next = p -> next;
				}

				free(p);
				return;
                	}
		q = p;
		p = p -> next;
		}
	}
	printf("There was no person with that name. \n");
}


int check_duplicate(char *first, char *last)
{
	int i;
	NODE *p;

	for (i = 0; i < 3; i++)
	{
		p = List[i].head;

		while (p != NULL)
		{
			int first_check = strcmp(first, p -> first_name);
			int last_check = strcmp(last, p -> last_name);

			if (first_check == 0 && last_check == 0)
			{
				printf("You have already entered that person. \n");
				return 0;
			}
			p = p -> next;
		}
	}
	return 1;
}

void delete_all(NODE *p)
{
	if (p == NULL)
	{
		return;
	}

	delete_all(p -> next);
	free(p);
}


void change_age(char *first, char *last)
{
	int new_age;
	int i;
	NODE *p;

        for (i = 0; i < 3; i++)
        {
                p = List[i].head;

                while (p != NULL)
                {
                        int first_check = strcmp(first, p -> first_name);
                        int last_check = strcmp(last, p -> last_name);

                        if (first_check == 0 && last_check == 0)
                        {
                                printf("What is their new age? \n");
				scanf("%d", &new_age);
				remove_input(first, last);
                                insert(first, last, new_age);
				return;
                        }
                        p = p -> next;
                }
        }
	printf("The person you entered could not be found. \n");
}

void doublyLinked_show()
{
	int i;
	NODE *p;

        for (i = 0; i < 3; i++)
        {
                p = List[i].tail;
                while (p != NULL)
                {
                        printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                        p = p -> prev;
                }
        }
}

void recursion_show(NODE *p)
{
        int i;

	if (p -> next != NULL)
	{
		recursion_show(p -> next);
	}
	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
}
