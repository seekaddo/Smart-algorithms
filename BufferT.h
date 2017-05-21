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




#endif //BLUEPRINT_BUFFER_H
