
// In English
// Finding the smallest number that is divisible by the numbers from 1 to 5
// Finding the smallest number that is divisible by the numbers from 1 to 10
// Finding the smallest number that is divisible by the numbers from 1 to 20



/* Die aufgabe beschreibung hier hinfuegen
*
Was ist die kleinste Zahl die durch jede der Zahlen von 1 bis 20 teilbar ist?

Beispiel: 60 ist die kleinste Zahl die durch alle Zahlen von 1 bis 5 ohne Rest teilbar ist. 2520 ist die

kleinste Zahl die durch alle Zahlen von 1 bis 10 ohne Rest teilbar ist.

Finde die kleinste positive Zahl die durch alle Zahlen von 1 bis 20 ohne Rest teilbar ist.

*
*/

/* unsafe warning wird ausgeblendet */
#define _CRT_SECURE_NO_WARNINGS 


/* Programmcode hier einfügen */
#include <stdio.h>




/*Konstante hier definieren*/


/*Erklaerung*/
/*Teilbar keit fuer 1 bis 5 mit teilbarkeit und division regel
die zahlen 1 2 3 4 5
1 ist durch jede teilbar
2 teil 4 so 2,4 gemeinsam eigenschaft aber 4 ist grosser so essential
3 keine
4 schon erledig
5 keine aber ist die letze zahl die muss durch die kleinste zahl durch teiling so wichtig mit vielfaches von 5
	5 teil sich oder vielfaches von 5 d.h 5,10,15,20.....
	so das ergebnis wenn muss durch 5 teilbar ist auch ein vielfaches von 5 und beendet mit 0,
	so bleiben 3,4,5 als essential eigenschaft
	aber es gibt keine zahl von 1 bis 5 die wird durch 3,4 teilbar und auch 5
	wenn die zahlen kann durch die vielfaches von 5 teilbar dann haben 3,4,5 etwas gemeinsam
	so jetzt bilden wir nur vielfaches von 5. und ueberpruefung nur ob es ist von 3,4 teilbar, nicht 5 war es ist eindeutig

*/

/*Teilbar keit fuer 1 bis 10 mit teilbarkeit und division regel ***die erklaerung geht analog von oben****
die zahlen 1 2 3 4 5 6 7 8 9 10
1 ist durch jede teilbar
2 teil 4 so 2,4 gemeinsam eigenschaft aber 4 ist grosser so essential
3 keine
4 schon erledig und mit 8
5 teil 10
10 teil jede zahl die mit 0 beendet, analog von oben wissen wir das ergebnis muss mit 0 beenden

bleiben uns die essential zu ueberpruefung 6 7 8 9


*/

/*Teilbar keit fuer 1 bis 20 mit teilbarkeit und division regel ***die erklaerung geht analog von oben****
die zahlen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 ist durch jede teilbar
2 teil 4 so 2,4 gemeinsam eigenschaft aber 4 ist grosser so essential
3 keine
4 schon erledig und mit 8
5 teil 10
10 teil jede zahl die mit 0 beendet auch 20, analog von oben wissen wir das ergebnis muss mit 0 beenden

bleiben uns die essential zu ueberpruefung 11 12 13 14 16 17 18 19
 hier koennen noch gemeinsam eigenschaften finden aber es hilft nicht mehr


Ist eine Optimiert loesung. mit der lauftzeit gleich als 20ms

*/





int main(int argc, char* argv[])

{
	/*Teilbar keit fuer 1 bis 5*/
	int i = 5;							

	while (i % 3 || i % 4)
	{
		i += 5;
	}
	printf("Die kleinste zahl die von 1 bis 5 teilbar ist: %d\n", i);


	/*Teilbar keit fuer 1 bis 10*/
	int a = 10;

	while (a % 6 || a % 7 | a % 8 || a % 9 )
	{
		a += 10;
	}
	printf("Die kleinste zahl die von 1 bis 10 teilbar ist: %d\n", a);



	/*Teilbar keit fuer 1 bis 20, hier ist die aufgaben die zwei abbildung von oben ist nur als hilfe zur erklaerung und weiter bilden*/
	int start = 20;

	while (start % 11 || start % 12 | start % 13 || start % 14 || 
			start % 15 || start % 16 || start % 17 || start % 18 || start % 19 )
	{
		start += 20;
	}
	printf("Die kleinste zahl die von 1 bis 20 teilbar ist: %d\n", start);
	
	 
	return 0;
}
