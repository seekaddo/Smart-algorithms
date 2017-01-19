//
// Created by Addo Dennis on 01/12/2016.
//
/******************************************************************************
 *                   Projekt Augabe --BICSS-1                                 *
 *                                                                            *
 *      Author(en):     Dennis Addo                                           *
 *      Datei:          hash.h                                                *
 *      Datum:          01/12/2016                                            *
 *                                                                            *
 ******************************************************************************/


#ifndef PROJEKTABGABEBICSS_HASH_H
#define PROJEKTABGABEBICSS_HASH_H

#include "../BluePrint/logging.h"

typedef enum {YES,NO} status;
#define hash(i) (i*2654435761) % (ST_SIZE)         //Knuth's multiplicative method
#define ST_SIZE 5             // should always be prime, not even


typedef struct Node {
    unsigned int matr_num;
    char name[14];
    struct Node *next;
} Hash_ll;
extern Hash_ll student;



void init_hash_t(Hash_ll **hash_table);

extern unsigned int hash_funkt(unsigned int matr_number);


void insert_r(Hash_ll **hash_table, Hash_ll student);


void r_delete(Hash_ll **hash_table, unsigned int matr_number);


char *r_search(Hash_ll **hash_table, unsigned int matr_number);


void clean_p(Hash_ll **hashtable, int k);

int _scanf_int(int);


#endif //PROJEKTABGABEBICSS_HASH_H
