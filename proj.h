#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node
#define LIST struct list

struct list
{
        NODE *head;
        NODE *tail;
};

struct node
{
        char first_name[20];
        char last_name[20];
        int age;
        NODE *next;
        NODE *prev;
};

LIST List[3];

pthread_mutex_t mutex;


void insert(char first[20], char last[20], int age);

void list();

void list_ages();

void remove_input(char *first, char *last);

int check_duplicate(char *first, char *last);

void read_all(char *file_name, int key);

void save_all(char *file_name, int key);

void delete_all(NODE *p);

void change_age(char *first, char *last);

void *loopThread(void *arg);

void readThread(char *file_name);

void doublyLinked_show();

void recursion_show(NODE *p);

int main(int argc, char *argv[]);
