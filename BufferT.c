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


