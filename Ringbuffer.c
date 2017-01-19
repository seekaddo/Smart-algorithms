//
// Created by Addo Dennis on 27/12/2016.
//Todo: a simple integer prototype for a bigger struct elements.
/* Creating a ringbuffer that is a circular linkedlist iteration and recursive
 * when the ring is full, the tail should point to the head. we adding until
 * is full and then we point the tail to the head */

#include <stdio.h>
#include <stdlib.h>

typedef struct _Buffer{
    int data;
    struct _Buffer *next;
}RBuffer;

void add(RBuffer **ring, int n);
void Recursive_add(RBuffer **ring, int n);
void help(RBuffer **pr,RBuffer **ring,int n);
void buffer_info(RBuffer *ring);
void freeall(RBuffer **r);



//Todo: Main starts here
int main(int argc, char *argv[]) {
    RBuffer *proot = NULL;
    Recursive_add(&proot, 45);
        //buffer_info(proot);printf("\n");
    Recursive_add(&proot, 75);
        //buffer_info(proot);printf("\n");
    Recursive_add(&proot, 23);
        //buffer_info(proot);printf("\n");
    Recursive_add(&proot, 89);
    Recursive_add(&proot, 90);
        buffer_info(proot);printf("\n");



    freeall(&proot);
    return 0;
}

/*Adding at the button and close the Ringbuffer*/
void add(RBuffer **ring, int n){

    if(*ring == NULL){
        *ring =(RBuffer *)malloc(sizeof(struct _Buffer));
        (*ring)->data = n;
        (*ring)->next = *(ring);
    } else if((*ring)->next == *(ring)){                            // when we have only one element in the ring
        RBuffer *new = (RBuffer *)malloc(sizeof(struct _Buffer));
        new->data = n;
        (*ring)->next = new;
        new->next = (*ring);

    } else{
        RBuffer *new =(RBuffer *) malloc(sizeof(struct _Buffer));
        new->data = n;
        RBuffer *rp = (*ring);
        while(rp->next != (*ring)) rp = rp->next;

        rp->next = new;
        new->next = (*ring);
    }

}
void Recursive_add(RBuffer **ring, int n){
    if(*ring == NULL){
        *ring =(RBuffer *)malloc(sizeof(struct _Buffer));
        (*ring)->data = n;
        (*ring)->next = *(ring);
    } else if((*ring)->next == *(ring)){
        RBuffer *new = (RBuffer *)malloc(sizeof(struct _Buffer));
        new->data = n;
        (*ring)->next = new;
        new->next = (*ring);

    } else{
        //RBuffer *rp = (*ring);                //pass in the whole ring not ring.next
        help(&(*ring),&(*ring),n);
    }
}
void help(RBuffer **pr,RBuffer **ring,int n){       // not need making const ring
    // if next of passed elements is the same als ring.
    if((*pr)->next == *(ring)){
        RBuffer *new = (RBuffer *)malloc(sizeof(struct _Buffer));
        new->data = n;
        (*pr)->next = new;
        new->next = (*ring);

    } else{
        help(&((*pr)->next),&(*ring),n);        // if not then go to the next element( pass it address)
    }
}

//Todo: just for debugging
void buffer_info(RBuffer *buffer){
    RBuffer *tmp = buffer;
    int i=0;

    printf("\n=== RINGBUFFER ===\n");
    printf("=== Head @ %p\n",buffer);

    /* when the list is empty */
    if(tmp == NULL)
    {
        return;
    }
    do
    {
        printf("Element %d\n",i++);
        printf("  Number: %i\n",tmp->data);
        printf("  Adresse: %p\n",tmp);
        printf("  Next: %p\n",tmp->next);
        tmp=tmp->next;
    } while(tmp != buffer);

    printf("\n");
}

void freeall(RBuffer **r){
    RBuffer *p = (*r), *tem;
    while(p->next != *r){
        tem = p;
        p = p->next;
        free(tem); tem = NULL;
    }
}
