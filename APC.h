#ifndef APC_H
#define APC_H
#include "types.h"
typedef struct node{
	int data;
	struct node*prev;
	struct node*next;
}Dlist;

typedef struct result{
	int data;
	struct result*link; 
}Slist;

Status createList(Dlist**,Dlist**,char*);
Status insertLast(Dlist**,Dlist**,int);
Status insertFirst(Dlist**,Dlist**, int);
Status insertRes(Slist**,int);
Status insertResLast(Slist**,int);
Status validArg(char*);
Status validOperation(char*);
Status add(Dlist*,Dlist*,Slist**);
Status sub(Dlist*,Dlist*,Slist**);
Slist*multiply_with_digit(Dlist*,int,int);
Status add_slist(Slist*,Slist*, Slist**); 
Slist*reverse_slist(Slist*); 
void freeList(Slist*);
Status mul(Dlist*,Dlist*, Slist**);
Dlist*get_head_from_tail(Dlist*);
int is_zero_dll(Dlist*);
int is_zero_slist(Slist*);
void free_dlist(Dlist*);
int compare_dll(Dlist*, Dlist*);
Status increment_slist(Slist**);
Status divide(Dlist*, Dlist*, Slist**, Dlist**);
Status parse_and_create_list(char*, Dlist**, Dlist**, int*);
void printList(Dlist*);
void printRes(Slist*);


#endif
