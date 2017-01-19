/*
Finding the cycle-length of of a given range of numbers from i to j inclusive
Given the input 22, the following sequence of numbers will be printed 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1

Sample Input

1 10
100 200
201 210
900 1000'

Sample Output

1 10 20
100 200 125
201 210 89
900 1000 174
*/


#include <stdio.h>


int get_serie(int a);
int main(int argc, char* argv[]){
    int val1,val2 ,max = 1;
    int n1,n2;

    printf("Bitte geben Sie die start and endzahl  ein: ");
    scanf("%d%d",&val1,&val2);
    n1 = val1; n2 = val2;


    for (int i = val1; i <= val2; ++i) {
        int serie = get_serie(i);
        if (serie > max){
            max = serie;
        }
    }

    printf("%d %d %d",n1,n2,max);
    return 0;
}
int get_serie(int v){
    int val = v;
    int index = 0,series_counter = 1;
    do
    {

        if (val % 2== 0){
            val /= 2;
            index++;
            series_counter++;
        } else{
            val = (val * 3) + 1;
            index++;
            series_counter++;
        }

    }while (val != 1);
    return series_counter;
}
