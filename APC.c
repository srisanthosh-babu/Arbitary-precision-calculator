#include "APC.h"
Status validArg(char*arg){
	
	if(arg == NULL){
		return FAILURE;
	}
	while(*arg){
		if(!isdigit(*arg)){
			return FAILURE;
		}
	arg++;
	}
	return SUCCESS;
}

Status validOperation (char*operator){
	if(*operator == '+' || *operator =='-' || *operator =='*' || *operator == '/'){
		return SUCCESS;
	}
	return FAILURE;
}

Status createList(Dlist**head,Dlist**tail,char*data){
	while(*data){
		if(insertLast(head,tail, (*data)- '0')== SUCCESS){
		data++;
		}
		else{
			return FAILURE;
		}
	}
	return SUCCESS;
}	

Status insertLast(Dlist**head,Dlist**tail,int data){
	Dlist*node=(Dlist*)malloc(sizeof(Dlist));
	if(node==NULL){
		return FAILURE;
	}
	node->data=data;
	node->next=NULL;
	node->prev=*tail;
	if(*tail==NULL){
		*head=node;
		*tail=node;
		return SUCCESS;
	}
	(*tail)->next=node;
	*tail=node;
	return SUCCESS;
}

Status add(Dlist*t1, Dlist*t2, Slist**head) {
    int carry = 0;
    while (t1 || t2 || carry) {
        int d1 = (t1 ? t1->data : 0);
        int d2 = (t2 ? t2->data : 0);
        int sum = d1 + d2 + carry;
        carry = sum / 10;
        insertRes(head, sum % 10);
        if (t1){
		t1 = t1->prev;
	}
        if (t2){
		t2 = t2->prev;
	}
    }
    return SUCCESS;
}

Status sub(Dlist*t1,Dlist*t2, Slist**resHead) {
    int borrow = 0;

    while (t1 || t2) {
        int d1 = (t1 ? t1->data : 0) - borrow;
        int d2 = (t2 ? t2->data : 0);

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insertRes(resHead, d1 - d2);

        if (t1){
		 t1 = t1->prev;
        }
	if (t2){
		 t2 = t2->prev;
	}    
}
    while (*resHead && (*resHead)->data == 0 && (*resHead)->link) {
        Slist*tmp = *resHead;
        *resHead = (*resHead)->link;
        free(tmp);
    }

    return SUCCESS;
}


Status insertRes(Slist**head,int data){
    Slist*node=(Slist*)malloc(sizeof(Slist));
    if(node==NULL){
        return FAILURE;
    }
    node->data=data;
    node->link=*head;
    *head=node;
    return SUCCESS;
}

Status insertResLast(Slist**head,int data)
{
    Slist*node=(Slist*)malloc(sizeof(Slist));
    if(node==NULL){
        return FAILURE;
    }
    node->data=data;
    node->link=NULL;
    if(*head==NULL){
        *head=node;
        return SUCCESS;
    }else{
        Slist*temp=*head;
        while(temp->link!=NULL){
            temp=temp->link;
        }
        temp->link=node;
    }
    return SUCCESS;
}

Slist*reverse_slist(Slist*head) {
    Slist*prev = NULL, *curr = head, *next = NULL;

    while (curr) {
        next = curr->link;   
        curr->link = prev;   
        prev = curr;         
        curr = next;         
    }

    return prev; 
}

Slist*multiply_with_digit(Dlist*tail1, int digit, int shift) {
    int carry = 0;
    Slist*res = NULL;

    for (Dlist*t1 = tail1; t1; t1 = t1->prev) {
        int prod = (t1->data * digit) + carry;
        insertRes(&res, prod % 10);
        carry = prod / 10;
    }
    if (carry)
        insertRes(&res, carry);
    for (int i = 0; i < shift; i++)
        insertResLast(&res, 0);

    return res;
}

Status add_slist(Slist*n1, Slist*n2, Slist**resHead) {
    int carry = 0;
    Slist*res = NULL;
    n1 = reverse_slist(n1);
    n2 = reverse_slist(n2);
    while (n1 || n2 || carry) {
        int sum = carry;
        if (n1) { sum += n1->data; n1 = n1->link; }
        if (n2) { sum += n2->data; n2 = n2->link; }

        insertRes(&res, sum % 10);
        carry = sum / 10;
    }

    *resHead = res;
    return SUCCESS;
}

void freeList(Slist*head) {
    Slist*temp;
    while (head) {
        temp = head;
        head = head->link;
        free(temp);
    }
}

Status mul(Dlist*tail1, Dlist*tail2, Slist**resHead) {
    if (!tail1 || !tail2){
		 return FAILURE;
	}
    Slist*result = NULL;
    int shift = 0;

    for (Dlist*t2 = tail2; t2; t2 = t2->prev, shift++) {
        Slist*temp = multiply_with_digit(tail1, t2->data, shift);
        if (!result) {
            result = temp;
        } else {
            Slist*newRes = NULL;
            add_slist(result, temp, &newRes);
            freeList(result);
            freeList(temp);
            result = newRes;
        }
    }

    *resHead = result;
    return SUCCESS;
}

void printList(Dlist*head){
	if(head==NULL){
		printf("\nList is empty\n");
	}
	else{
		printf("Head-> ");
		while(head){
			printf("%d <-",head->data);
			head=head->next;
			if(head){
				printf(">");
			}
		}
		printf(" Tail\n");
	}
}

void printRes(Slist*head){
	if(head==NULL){
		printf("\nList is empty\n");
	}
	else{
		while(head){
			printf("%d",head->data);
			head=head->link;
		}
		printf("\n");
	}
}

Dlist* get_head_from_tail(Dlist *tail) {
    if (!tail) return NULL;
    Dlist *h = tail;
    while (h->prev) h = h->prev;
    return h;
}

int is_zero_dll(Dlist *head) {
    if (!head) return 1;
    while (head) {
        if (head->data != 0) return 0;
        head = head->next;
    }
    return 1;
}

void free_dlist(Dlist *head) {
    Dlist *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int compare_dll(Dlist *h1, Dlist *h2) {
    if (!h1 && !h2) return 0;
    if (!h1) return -1;
    if (!h2) return 1;

    
    while (h1 && h1->data == 0 && h1->next) h1 = h1->next;
    while (h2 && h2->data == 0 && h2->next) h2 = h2->next;

    int len1 = 0, len2 = 0;
    Dlist *t1 = h1, *t2 = h2;
    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }

    if (len1 < len2) return -1;
    if (len1 > len2) return 1;

    while (h1 && h2) {
        if (h1->data < h2->data) return -1;
        if (h1->data > h2->data) return 1;
        h1 = h1->next;
        h2 = h2->next;
    }
    return 0;
}


Status increment_slist(Slist **q) {
    if (!q) return FAILURE;
    if (*q == NULL) {
        if (insertRes(q, 1) == FAILURE) return FAILURE;
        return SUCCESS;
    }

    Slist *rev = reverse_slist(*q);
    Slist *p = rev;
    int carry = 1;
    Slist *prev = NULL;

    while (p && carry) {
        int sum = p->data + carry;
        p->data = sum % 10;
        carry = sum / 10;
        prev = p;
        p = p->link;
    }

    if (carry) {
        Slist *node = (Slist*)malloc(sizeof(Slist));
        if (!node) return FAILURE;
        node->data = carry;
        node->link = NULL;
       
        if (prev) prev->link = node;
        else rev = node; 
    }

    *q = reverse_slist(rev);
    return SUCCESS;
}

Status divide(Dlist *tail1, Dlist *tail2, Slist **qHead, Dlist **remHead) {
    if (!tail1 || !tail2 || !qHead || !remHead) return FAILURE;

    Dlist *head1 = get_head_from_tail(tail1);
    Dlist *head2 = get_head_from_tail(tail2);

    if (!head1 || !head2) return FAILURE;

    if (is_zero_dll(head2)) {
        printf("Error: Division by zero!\n");
        return FAILURE;
    }

    
    Dlist *divH = NULL, *divT = NULL;
    for (Dlist *p = head1; p; p = p->next) {
        if (insertLast(&divH, &divT, p->data) == FAILURE) {
            free_dlist(divH);
            return FAILURE;
        }
    }

    *qHead = NULL;

   
    while (compare_dll(divH, head2) >= 0) {
        
        Slist *subRes = NULL;
        if (sub(divT, tail2, &subRes) == FAILURE) {
            free_dlist(divH);
            freeList(subRes);
            return FAILURE;
        }

       
        free_dlist(divH);
        divH = NULL;
        divT = NULL;

        for (Slist *s = subRes; s; s = s->link) {
            if (insertLast(&divH, &divT, s->data) == FAILURE) {
                freeList(subRes);
                free_dlist(divH);
                return FAILURE;
            }
        }
        freeList(subRes);

        
        if (increment_slist(qHead) == FAILURE) {
            free_dlist(divH);
            return FAILURE;
        }

        
        if (!divH) break;
    }

    
    if (*qHead == NULL) {
        if (insertRes(qHead, 0) == FAILURE) {
            free_dlist(divH);
            return FAILURE;
        }
    }

    
    *remHead = divH;
    return SUCCESS;
}

Status parse_and_create_list(char *arg, Dlist **head, Dlist **tail, int *sign) {
    if (!arg || !head || !tail || !sign) return FAILURE;
    char *p = arg;
    int s = 1;
    if (*p == '+' || *p == '-') {
        s = (*p == '-') ? -1 : 1;
        p++;
        if (*p == '\0') return FAILURE; 
    }
    
    for (char *q = p; *q; ++q) {
        if (!isdigit((unsigned char)*q)) return FAILURE;
    }
    *head = *tail = NULL;
    while (*p) {
        if (insertLast(head, tail, *p - '0') == FAILURE) {
            
            Dlist *t = *head, *tmp;
            while (t) { tmp = t; t = t->next; free(tmp); }
            *head = *tail = NULL;
            return FAILURE;
        }
        p++;
    }
    *sign = s;
    return SUCCESS;
}

int is_zero_slist(Slist *s) {
    if (!s) return 1;
    while (s) {
        if (s->data != 0) return 0;
        s = s->link;
    }
    return 1;
}

