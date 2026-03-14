#include <stdio.h>
#include <stdlib.h>

int main(){   
    int triunghi[100][100], ok = 1;

    FILE *f;
    f = fopen("trg.in", "r");

    FILE *g;
    g = fopen("trg.out", "w");

    if(f == NULL || g == NULL){
        printf("Eroare la deschiderea/crearea fisierului!\n");
        exit(0);
    }

    //Citirea triunghiului
    int n = 0;
    while (ok != 0){
        for (int j = 0; j <= n; j++){   //Citirea se face foarte simplu, deoarece j<=n => ca pe fiecare linie avem n+1 numere ceea ce il face sa arate ca un triunghi.
            //Acest if ne ajuta sa vedem atunci cand nu mai citeste nimic din fisier si se intrerupe programul 
            if (fscanf(f, "%d", &triunghi[n][j]) != 1){ // n - linie, j - coloana
                ok = 0;
                break;
            }
        }
        //Daca s-a citit cu succes de pe linia curenta inaintam citirea
        if (ok != 0){
            n++;
        }
    }

    for (int i = n - 2; i >= 0; i--){ // incepem de la penultima linie, si urcam in sus pe triunghi
        for (int j = 0; j <= i; j++){ // parcurgerea tuturor elementelor de pe linia i 

            int stanga = triunghi[i+1][j]; //element stanga
            int dreapta = triunghi[i+1][j+1]; //element dreapta
            int maxim;
            
            if (stanga > dreapta)
                maxim = stanga;
            else 
                maxim = dreapta;
            
            triunghi[i][j] = triunghi[i][j] + maxim;
            
        }
    }   

    //adaugam in g rezultatul final
    fprintf(g, "%d", triunghi[0][0]);

    fclose(f);
    fclose(g);
        
    return 0;
}