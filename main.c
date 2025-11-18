#include "APC.h"

int main(int argc,char*argv[]){
    if(argc < 4){
        printf("\nEnter valid number of arguments\n");
        return 0;
    }

    char op = argv[2][0];
    if (op == 'x') op = '*';

    if (! (op=='+' || op=='-' || op=='*' || op=='/' ) ) {
        printf("\nERROR: Invalid operator\n");
        return 0;
    }

    int sign1 = 1, sign2 = 1;
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Slist *Rhead = NULL;   
    Slist *Qhead = NULL;  
    Dlist *rem = NULL;   
    int resSign = 1, qSign = 1, remSign = 1;

    
    if (parse_and_create_list(argv[1], &head1, &tail1, &sign1) == FAILURE ||
        parse_and_create_list(argv[3], &head2, &tail2, &sign2) == FAILURE) {
        printf("\nERROR: Invalid operand(s)\n");
        
        free_dlist(head1);
        free_dlist(head2);
        return 0;
    }

    printf("\nOperands created:\nOperand 1:\n"); printList(head1);
    printf("Operand 2:\n"); printList(head2);

   
    Dlist *h1 = head1;
    Dlist *h2 = head2;

    
    if (op == '+') {
        if (sign1 == sign2) {
            if (add(tail1, tail2, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
            resSign = sign1;
        } else {
            int cmp = compare_dll(h1, h2);
            if (cmp == 0) {
                insertRes(&Rhead, 0); resSign = 1;
            } else if (cmp > 0) {
                if (sub(tail1, tail2, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
                resSign = sign1;
            } else {
                if (sub(tail2, tail1, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
                resSign = sign2;
            }
        }

        
        if (resSign == -1 && !is_zero_slist(Rhead)) printf("-");
        printRes(Rhead);
    }
    else if (op == '-') {
        
        int effective_sign2 = -sign2;
        if (sign1 == effective_sign2) {
            if (add(tail1, tail2, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
            resSign = sign1;
        } else {
            int cmp = compare_dll(h1, h2);
            if (cmp == 0) {
                insertRes(&Rhead, 0); resSign = 1;
            } else if (cmp > 0) {
                if (sub(tail1, tail2, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
                resSign = sign1;
            } else {
                if (sub(tail2, tail1, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
                resSign = -sign1;
            }
        }

        if (resSign == -1 && !is_zero_slist(Rhead)) printf("-");
        printRes(Rhead);
    }
    else if (op == '*') {
        if (mul(tail1, tail2, &Rhead) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
        resSign = (sign1 * sign2 == -1) ? -1 : 1;
        if (resSign == -1 && !is_zero_slist(Rhead)) printf("-");
        printRes(Rhead);
    }
    else if (op == '/') {
        
        if (divide(tail1, tail2, &Qhead, &rem) == FAILURE) { printf("\nERROR : Operation Failed\n"); goto cleanup; }
        qSign = (sign1 * sign2 == -1) ? -1 : 1;
        remSign = is_zero_dll(rem) ? 1 : sign1;
        if (qSign == -1 && !is_zero_slist(Qhead)) printf("-");
        printf("Quotient : "); printRes(Qhead);
        if (rem && remSign == -1 && !is_zero_dll(rem)) printf("-");
        printf("\nRemainder: "); if (rem) printList(rem); else printf("0\n");
    } else {
        printf("\nInvalid Operation\n");
    }

cleanup:
    
    free_dlist(head1);
    free_dlist(head2);
    freeList(Rhead);
    freeList(Qhead);
    free_dlist(rem);

    return 0;
}
