#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
char s[15];
typedef struct line {
    struct line * prior;
    int data;
    struct line * next;
}line;

line* initLine(FILE *fp);

void display(line * head);
void Rdisplay(line * head);
void LSort(line *head1);
void connect(line *head1,line *head2);

typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} Hash;

Hash *hl = NULL;

int Compare(Hash *a, Hash *b)
{
    /*Hash *aa = (Hash*)a;
    Hash *bb = (Hash*)b;*/
    return a->key-b->key;
}

line *sortList(line* head){
    if (head == NULL) {
        return NULL;
    }
    hl = NULL;
    line *cur = head;
    Hash *temp = NULL;
     do{
        temp = (Hash*)calloc(1, sizeof(Hash));
        temp->key = cur->data;
        temp->value = 1;
        HASH_ADD_INT(hl, key, temp);
        cur = cur->next;
        //printf("IN");
    }while (cur != head);
    HASH_SORT(hl, Compare);
    cur = head;
    Hash *current = NULL;
    Hash *next = NULL;
    HASH_ITER(hh, hl, current, next) {
        if ((current != NULL) && (cur != NULL)) {
            cur->data = current->key;
            cur = cur->next;
        }
    }
    return head;
}

int main() {
    FILE *fp;
    
    printf("Input file name:");
    scanf("%s",s);
    fp=fopen(s,"r");
    line * head1=NULL;
    head1 = initLine(fp);
    display(head1);
    Rdisplay(head1);
    printf("\nAfter sort:\n");
    LSort(head1);
    printf("\n");
    line * head2=NULL;
    head2 = initLine(fp);
    display(head2);
    Rdisplay(head2);
    printf("\nAfter sort:\n");
    LSort(head2);
    printf("\n");
    fclose(fp);
    connect(head1,head2);
    return 0;
}

line* initLine(FILE *fp) {
    int i;
    if(fp){
        //printf("OPEN\n");
    }else{
        printf("NO");
        }
    line * list = NULL;
    line *head = (line*)malloc(sizeof(line));
    /*本次題目head為一指標，故不建立node
    head->prior = NULL;
    head->next = NULL;
    head->data = 1;*/
    list = head;
    int len;
    
    fscanf(fp,"%d",&len);
    printf("List in %d (before sort):\n",len);
    int k;
    for (i = 1; i <= len; i++) {
		
        fscanf(fp,"%d",&k);
        
        line * body = (line*)malloc(sizeof(line));
        body->prior = NULL;
        body->next = NULL;
        body->data = k;
        list->next = body;
        body->prior = list;
        list = list->next;
    }
    //以上已建立double-link-list，以下進行首尾相接形成環
    list->next = head->next;
    head->next->prior = list;
    return head;
}

void display(line * head) {
    line * temp = head->next;
    //由於是環狀，所以當指標temp指向的下一個node是head->next時，此時已至環狀的最後一個node
    while (temp->next != head->next) {
        if (temp->next == NULL) {
            //printf("%d\n", temp->data);
            break;
        }
        else {
            printf("%d<->", temp->data);
        }
        temp = temp->next;
    }
    //輸出最後一node的值
    printf("%d\n", temp->data);
}

void Rdisplay(line * head) {
    line * temp = head->next->prior;
    //由於是環狀，所以當指標temp指向的上一個node是head->next->prior時，此時已至環狀的最後一個node
    while (temp->prior != head->next->prior) {
        if (temp->prior == NULL) {
            //printf("%d\n", temp->data);
            break;
        }
        else {
            printf("%d<->", temp->data);
        }
        temp = temp->prior;
    }
    //輸出最後一node的值
    printf("%d\n", temp->data);
}

void LSort(line *head){

	head->next=sortList(head->next);

    display(head);
	
}


void connect(line *head1,line *head2){
	line * temp1 = head1->next;
	line * temp1_fixed = head1->next;
	line * temp2 = head2->next;
	line * temp2_fixed = head2->next;
    while (temp1->next != head1->next) {
        temp1 = temp1->next;
    }
    temp1->next=temp2_fixed;
    temp2_fixed->prior=temp1;
    while (temp2->next != head2->next) {
        temp2 = temp2->next;
    }
    temp2->next=temp1_fixed;
    temp1_fixed->prior=temp2;
	printf("\nThe connect list(before sore):\n");
    display(head1);
    free(head2);
    printf("\nThe connect list(after sore):\n");
    LSort(head1);
    printf("\nThe backward connect list(after sore):\n");
    Rdisplay(head1);
   	
}