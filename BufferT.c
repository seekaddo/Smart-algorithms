//
// Created by Addo Dennis on 04/01/2017.
//
#include <stdio.h>
#include "BufferT.h"


int main(int argc, char *argv[]) {

    char bf[20];
    Rbuffer * testBuffer = NULL;
    int menue_eingabe;
    Rbuffer datV;
    buffer_info(testBuffer, "Initialisiert");

    do
    {

        printf("\n=====================================\n");
        printf("Welche Aktion wollen Sie durchfuehren?\n");
        printf("1 ... Messwert hinzufuegen\n");
        printf("2 ... Messwert suchen\n");
        printf("3 ... Messwert Löschen\n");
        printf("0 ... Programmende\n");
        printf("=====================================\n");
        printf("Ihre Wahl? ");
        scanf("%i", &menue_eingabe);
        printf("\n");


        switch (menue_eingabe)
        {
            case 0:
                _logdd(MAGNENTAP,"Das Programm wird beendet ...");
                break;
            case 1:

                printf(" -----------------------------------------\n");
                printf("|       MESSWERT HINFUEGEN                |\n");
                printf(" -----------------------------------------\n");
                info("Geben Sie den Namen des Messgeraetes ein: ");
                scanf("%s",bf);
                datV.name = strcpy(malloc(sizeof(char) * strlen(bf)+ 1),bf);
                info("Geben Sie den Messwert ein: ");
                scanf("%lf",&datV.meswert);
                info("Geben Sie das Datum ein (dd.mm.yyyy): \n");
                scanf("%d.%d.%d",&datV.ddate.day,&datV.ddate.month,&datV.ddate.year);

                if (add(&testBuffer,datV) == 0) {
                    info("Der Eintrag wurde hinzugefuegt");
                }else {
                    warn_msg("!!! Der Eintrag konnte nicht hinzugefuegt werden !!!");
                }

                buffer_info(testBuffer,"Hinzufuegen - Danach");
                free(datV.name), datV.name = NULL;
                //bf[12] = '\0';

                break;
            case 2:
                printf(" -----------------------------------------\n");
                printf("|       MESSWERT SUCHEN                   |\n");
                printf(" -----------------------------------------\n");
                info("Geben Sie das gewuenschte Datum ein (dd.mm.yyyy): ");
                scanf("%d.%d.%d",&datV.ddate.day,&datV.ddate.month,&datV.ddate.year);

                double w = find(&testBuffer, datV.ddate);
                if (w != -1)
                    printf("Ein Eintrag mit dem Wert %.2f wurde gefunden\n",w);
                else
                    warn_msg("!!! Es wurde kein entsprechender Eintrag gefunden !!!");
                break;
            case 3:
                printf(" -----------------------------------------\n");
                printf("|       MESSWERT LÖSCHEN                  |\n");
                printf(" -----------------------------------------\n");

                printf("Geben Sie das gewuenschte Datum ein (dd.mm.yyyy): ");
                scanf("%d.%d.%d",&datV.ddate.day,&datV.ddate.month,&datV.ddate.year);

               // double we = find(&testBuffer, datV.ddate);
                int we = delete(&testBuffer,&testBuffer, datV.ddate);
                if (we == 0)
                    printf("Ein Eintrag  wurde gelöscht\n");
                else
                    printf("!!! Es wurde kein entsprechender Eintrag gelöscht !!!\n");

                buffer_info(testBuffer,"NACH->>Löschenfunktion");

                break;
            default:
                error_msg("Ungueltige Eingabe!");
        }
    } while (menue_eingabe != 0);

    cleanup(&testBuffer);

    return 0;
}
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

