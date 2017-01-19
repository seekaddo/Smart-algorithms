

#include <stdio.h>
#include "hash.h"


/* Zum Test des Programm Habe ich folgen Daten verwendet von CIS
 *
 *  Name        Matrikelnummer
 *
 *  James       160021
 *  Addo		160023
    Focsa		160025
    Fröhlich	160028
    Grottenthaler 160031
    Himmler		160033
    Kebhart		160038
    Khalikov	160041

 * */

int main(int argc, char *argv[]) {
    if(argc >=1  && *(argv[1] +1) == 'd') {
      #define DEBUG 1

    }
    Hash_ll *Hash_table[ST_SIZE];
    init_hash_t(Hash_table);

    Hash_ll student;
    int wahl;

    do {
        printf("Menüs: Wilkommen an der Studenten-Informationen-System\n");
        printf("1. Neue Studenten eintragen\n2. Nach Studenten Suchen."
                       "\n3. Studenten von System Löschen.\n0. Programmende\n");
        printf("Wahl: \n");
        wahl = _scanf_int(1);


        switch (wahl) {
            case 0:
                info("Programm beendet.");
                break;

            case 1:
                info("<=====Neue Studenten Eintragen=====>");
                printf("Bitte fuehlen Sie die Folgen Daten fuer der neuen Student ein.\n");
                printf("Matrikelnummer: \n");

                //scanf("%u", &student.matr_num);
                student.matr_num = _scanf_int(6);
                printf("Nachname: ");
                scanf("%s", student.name);
                insert_r(Hash_table, student);
                printf("\n");
                break;

            case 2:
                _logdd(BLUE,"<=====Nach Studenten Suchen=====>");
                printf("Bitte geben Sie der 6-Stelligen Matrikelnummer des Student ein.\n");
                student.matr_num = _scanf_int(6);
                char *name = r_search(Hash_table, student.matr_num);

                (name) ?printf(" ___________________________________\n"),
                printf("|Student-ID: %u                 |\n",student.matr_num),
                printf("|Name: %s                      |\n", name),
                printf("|___________________________________|\n") :
                error_msg("Sorry the Student cannot be found.");
                break;

            case 3:
                _logdd(MAGNENTAP,"<=====Studenten von System Löschen.=====>");
                printf("Bitte geben Sie der 6-Stelligen Matrikelnummer des Student ein.\n");
                student.matr_num = _scanf_int(6);
                r_delete(Hash_table, student.matr_num);
                break;

            default:
                printf("sorry not a valid option\n");
        }
        printf("\n");
    } while (wahl != 0);

    clean_p(Hash_table,ST_SIZE-1);
    return 0;
}
