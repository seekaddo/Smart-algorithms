//
// Created by Addo Dennis on 01/12/2016.
//
/******************************************************************************
 *                   Projekt Augabe --BICSS-1                                 *
 *                                                                            *
 *      Author(en):     Dennis Addo                                           *
 *      Datei:          hash.c                                                *
 *      Datum:          01/12/2016                                            *
 *                                                                            *
 ******************************************************************************/

#include "hash.h"
#include <string.h>
#include <stdlib.h>


/*using avi to arrive O(1) in cleaning the hashtable*/
static int avi_student[ST_SIZE] = {[0 ... (ST_SIZE) - 1] = -1};

static int isEmptyHashT;                        // O(1) better than isHashEMpty method below


/*Todo: This methods are only accessible in this file*/
static void insert_helper(Hash_ll **student, Hash_ll Student);

static void r_delete_helper(Hash_ll **student, unsigned int matr_number);

static char *rsearch_helper(Hash_ll *student, int matn);

static void clean_pHel(Hash_ll **node);


/*The hash- function for  the index(schluessel)-key h(k)*/
/*Todo: multiplication hashing with the fastest computation*/
unsigned int hash_funkt(unsigned int matr_number) {
    return (hash(matr_number));
}

/* Initializing the hash-table*/
void init_hash_t(Hash_ll **hash_table) {

    int i = 0;
    for (i = 0; i < ST_SIZE; ++i) {
        hash_table[i] = NULL;
    }
}


/*Todo: Recursive implementation of the insert method*/
void insert_r(Hash_ll **hash_table, Hash_ll student) {
    unsigned int k = hash_funkt(student.matr_num);
    avi_student[k] = k;
    if (hash_table[k] == NULL) {

        if ((hash_table[k] = malloc(sizeof(struct Node)))) {

            hash_table[k]->matr_num = student.matr_num;
            strcpy(hash_table[k]->name, student.name);
            //hash_table[k]->name = strdup(student.name);
            hash_table[k]->next = NULL;
            ++isEmptyHashT;
            printf("%s was successfully added \n", hash_table[k]->name);
        } else{

            printf("sorry not enough memory \n");
        }

    } else if (hash_table[k]->matr_num != student.matr_num) {
        return insert_helper(&hash_table[k], student);
    } else {
        printf("sorry the student with this matri_number:%d"
                       " is already in the system!!\n", student.matr_num);
    }
}

void insert_helper(Hash_ll **node, Hash_ll student) {
    if (*node == NULL) {

        if (((*node) = malloc(sizeof(struct Node)))) {
            (*node)->matr_num = student.matr_num;
            strcpy((*node)->name, student.name);
            (*node)->next = NULL;
            ++isEmptyHashT;
            printf("%s was successfully added collision\n", (*node)->name);
        }

    } else if ((*node)->matr_num != student.matr_num) {

        return insert_helper(&((*node)->next), student);

    } else {
        printf("sorry there is already a student with this matri_number:%d"
                       " in the system!!\n", student.matr_num);
    }

}


/* Todo: Removing student from the hash-table recursively  helper*/
void r_delete(Hash_ll **hash_table, unsigned int matr_number) {
    if (!isEmptyHashT) {
        error_msg("Ooops You are trying to delete from an empty Database!!.");
        return;
    }

    unsigned k = hash_funkt(matr_number);
    if (hash_table[k] != NULL && hash_table[k]->next == NULL &&
        hash_table[k]->matr_num == matr_number) {
        Hash_ll *cur_node = hash_table[k];
        hash_table[k] = hash_table[k]->next;
        printf("Deletingr.....%s\n", cur_node->name);
        free(cur_node);
        --isEmptyHashT;
        cur_node = NULL;
    } else if (hash_table[k] != NULL && hash_table[k]->next != NULL) {
        return r_delete_helper(&hash_table[k], matr_number);
    } else {
        error_msg("There is no student with this ID in Database");
    }

}
//Todo: O(n) bad for large dataset, will reimplement this with static variable.
/*static int isHashEMpty(Hash_ll **pNode) {
    int i = 0;
    while (i < ST_SIZE) {
        if (pNode[i]) return 1;
        i++;
    }
    return 0;
}*/

static void r_delete_helper(Hash_ll **student, unsigned int matr_number) {
    if ((*student) != NULL && (*student)->matr_num == matr_number) {

            Hash_ll *cur_node = *student;
            *student = (*student)->next;
            printf("Deleting-collision.....%s\n", cur_node->name);
            free(cur_node);
            --isEmptyHashT;
            cur_node = NULL;


    } else {

        if((*student)->next == NULL)
            error_msg("There is no student with this ID in Database");
        else
            return r_delete_helper(&(*student)->next, matr_number);
    }
}


//Todo: to search for a specific Student in CIS recursively
char *r_search(Hash_ll **hash_table, unsigned int matr_number) {

    if (!isEmptyHashT) {     //O(1)
        error_msg("Ooops You are trying to query an empty Database!!.");
        return NULL;
    }

    size_t k = hash_funkt(matr_number);
    Hash_ll *nsh = hash_table[k];
    if (!nsh) return NULL;

    if (nsh->matr_num == matr_number) {
        return hash_table[k]->name;
    } else {
        return rsearch_helper(hash_table[k]->next, matr_number);
    }

}

static char *rsearch_helper(Hash_ll *student, int matn) {
    if (!student) return NULL;

    if (student->matr_num == matn)
        return student->name;

    return rsearch_helper(student->next, matn);
}


//todo: cleaning up the Hashtable
/*void clean_up(Hash_ll **hashtable) {
    int i = 0;
    while (avi_student[i] != -1) {

        if (hashtable[avi_student[i]] != NULL) {
            Hash_ll *ns = hashtable[avi_student[i]]->next;
            while (ns != NULL) {
                Hash_ll *temp = ns;
                ns = ns->next;
                free(temp);
                temp = NULL;
                printf("Cleaning up Hashtableinn.....\n");
            }
        }

        free(hashtable[avi_student[i]]);
        hashtable[avi_student[i]] = NULL;
        i++;
    }
    printf("Cleaning up Hashtable......\n");
    free(*hashtable);
    *hashtable = NULL;
    printf("Done.");
}*/
//Todo: cleaning up with recursion
void clean_p(Hash_ll **hashtable, int key) {
    if (key < 0 || !isEmptyHashT) return;           // empty hashtable

    if (key >= 0 && (avi_student[key] != -1)
        && hashtable[avi_student[key]]) {

        if (hashtable[avi_student[key]]->next == NULL) { //eine kollision
            free(hashtable[avi_student[key]]);
            hashtable[avi_student[key]] = NULL;
            printf("Cleaning up Hash-node.....\n");
            clean_p(hashtable, (key -= 1));

        } else {
            clean_pHel(&(hashtable[avi_student[key]]));

        }
    }


    if (key >= 0) {
        clean_p(hashtable, (key -= 1));
    }

}
/*Todo: cleaning up helper for the linked-list at index */
static void clean_pHel(Hash_ll **node) {
    if (*node == NULL) {
        return;
    } else {
        Hash_ll *p = *node;
        *node = (*node)->next;
        free(p);
        printf("Cleaning up Hashtableinn.....\n");
        clean_pHel(&(*node));
    }
}

//todo: scanf wrapper
int _scanf_int(int n) {
    int value;
    int nbyte = 0;
    switch (n){
        case 1:
            printf("=> ");
            while (scanf("%d", &value) != n) {

                int chr;
                warn_msg("  Input entered is not an integer...");
                do {
                    chr = getchar();
                } while ((chr != EOF) && (chr != '\n'));
                printf("=> ");
            }
            break;
        case 6:
            printf("=> ");
            do{
                scanf(" "),scanf("%d%n", &value,&nbyte);
                if (n != nbyte) {
                    int chr;
                    warn_msg("  Input entered is not a 6-digit number...");
                    do {
                        chr = getchar();
                    } while ((chr != EOF) && (chr != '\n'));
                    printf("=> ");
                }
            }while(n != nbyte);
            break;
        default:
            printf("=> ");
            scanf("%d", &value);
    }

    return value;
}