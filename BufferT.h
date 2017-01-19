//
// Created by Addo Dennis on 04/01/2017.
//

#ifndef BLUEPRINT_BUFFER_H
#define BLUEPRINT_BUFFER_H

#include <stdlib.h>
#include <string.h>
#include "logging.h"

enum {OK,ERROR,FOUND,NFOUND}b_status;
typedef struct DATUM {
    int day;
    int month;
    int year;
} Datum;

typedef struct _Buffer {
    char *name;
    double meswert;
    Datum ddate;
    struct _Buffer *next;
} Rbuffer;

extern Rbuffer rbuffer;

void init(Rbuffer **ring);

int add(Rbuffer **buffer, Rbuffer bff);

int add_helper(Rbuffer **buffer, Rbuffer **head, Rbuffer d);

double find(Rbuffer **buffer, Datum date);

int delete(Rbuffer **buffer, Rbuffer **head, Datum date);
void buffer_info(Rbuffer *buffer, char *desc);
void cleanup(Rbuffer **r);


void init(Rbuffer **ring) {
    Rbuffer *pnode = malloc(sizeof(struct _Buffer));
    if(!pnode) return;

    pnode->meswert = 0;
    pnode->name = NULL;
    pnode->ddate.day = pnode->ddate.month = pnode->ddate.year = 0;
    pnode->name = NULL;
    *ring = pnode;
}


int add(Rbuffer **buffer, Rbuffer data) {

    if (*buffer == NULL) {
        *buffer = NULL;
        init(&(*buffer));
        (*buffer)->meswert = data.meswert;
        (*buffer)->ddate = data.ddate;
        (*buffer)->name = strcpy(malloc(sizeof(strlen(data.name) + 1)), data.name);
        (*buffer)->next = *buffer;
    } else if ((*buffer)->next == (*buffer)) {
        Datum bd = (*buffer)->ddate;
        if ((bd.year <= data.ddate.year) && (bd.month <= data.ddate.month)) {
            Rbuffer *new = NULL; init(&new);
            new->meswert = data.meswert;
            new->ddate = data.ddate;
            new->name = strcpy(malloc(sizeof(strlen(data.name) + 1)), data.name);
            (*buffer)->next = new;
            new->next = *buffer;
        } else{
            return 1;
        }

    } else {
        return add_helper(&(*buffer), &(*buffer), data);
    }
    return 0;
}

int add_helper(Rbuffer **buffer, Rbuffer **head, Rbuffer d) {
    if ((*buffer)->next == (*head)) {
        Datum bd = (*buffer)->ddate;
        if ((bd.year <= d.ddate.year) && (bd.month <= d.ddate.month)) {
            Rbuffer *new = NULL; init(&new);
            new->meswert = d.meswert;
            new->ddate = d.ddate;
            new->name = strcpy(malloc(sizeof(strlen(d.name) + 1)), d.name);
            (*buffer)->next = new;
            new->next = *head;
        } else{
            return 1;
        }

    } else {
        return add_helper(&(*buffer)->next, &(*head), d);
    }
    return 0;
}


double find(Rbuffer **buffer, Datum date) {
    if ((*buffer)->ddate.day == date.day &&
        (*buffer)->ddate.month == date.month
        && (*buffer)->ddate.year == date.year) {
        return (*buffer)->meswert;
    } else {
        if ((*buffer) == NULL)  return -1;
        else return find(&(*buffer)->next, date);
    }
}


int delete(Rbuffer **buffer, Rbuffer **head, Datum date) {
    if ((*buffer)->ddate.year == date.year &&
        (*buffer)->ddate.month == date.month
        && (*buffer)->ddate.day == date.day) {
        if ((*buffer)->next == *head) {
            Rbuffer *cr_node = (*buffer)->next;
            //*buffer = *head;
            free(*buffer);
            *buffer = cr_node ;
        } else if ((*buffer)->next != *head) {
            Rbuffer *cr_node = (*buffer)->next;
            free(*buffer);
            *buffer = cr_node;
        }
        return 0;
    } if((*buffer)->next == *head){
        return 1;
    }
    else {
        return delete(&(*buffer)->next, &(*head), date);
    }
}

void buffer_info(Rbuffer *buffer, char *desc) {
    int i = 0;
    Rbuffer *tmp = buffer;

    info("=== RINGBUFFER ===");
    info("=== %s\n", desc);
    print("=== Head @ ");
    char next[20];
    sprintf(next,"%p",buffer);
    _logdd(CYAN,next);
    //printf("=== Head @ %p ===\n", buffer);

    if (buffer == NULL) {
        return;
    }

    do {
        printf("Element %d\n", i++);
        printf("  Name: %s\n", tmp->name);
        printf("  Wert: %.2f\n", tmp->meswert);
        printf("  Datum: %02d.%02d.%04d\n", tmp->ddate.day, tmp->ddate.month, tmp->ddate.year);
        printf("  Adresse: %p\n", tmp);
        printf("  Next: ");
        sprintf(next,"%p",tmp->next);
        _logdd(MAGNENTAP,next);
        //printf("  Next: %p\n", tmp->next);
        tmp = tmp->next;
    } while (tmp != buffer);

    printf("\n");

    return;
}

void cleanup(Rbuffer **r) {
    if(*r == NULL) return;

    Rbuffer *p = (*r), *tem;
    while(p->next != *r){
        tem = p;
        p = p->next;
        free(tem); tem = NULL;
    }
}

#endif //BLUEPRINT_BUFFER_H
