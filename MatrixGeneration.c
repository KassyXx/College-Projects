#include <stdio.h>
#include <math.h>

int main(){   
    FILE *f, *g;
    f = fopen("in.txt", "r");
    g = fopen("out.txt", "w");

    if(f == NULL || g == NULL){
        printf("Eroare la deschiderea/crearea fisierului!\n");
        return 1;
    }
    
    int m[8][8];
    int N, Q;

    fscanf(f,"%d %d", &N, &Q);  //citim prima linie unde N - numarul pentru matrice, Q - numarul de coordonate

    int k = (int)pow(2,N); //2^N
    int n = k * k;  // marimea tabelului (4*4 = 16)

    for (int i = 0; i < k; i++){
        if (i % 2 == 0){    //daca linia este para
            for (int j = k - 1; j >= 0; j--) //completam de la dreapta - stanga 
                m[i][j] = n--;
        } else{
            for (int j = 0; j < k; j++) //completam de la stanga - dreapta
                m[i][j] = n--;
        }
    }
    //Citim Q perechi de coordonate de pe linie
    for (int coord = 0; coord < Q; coord++) {
        int x, y;
        fscanf(f, "%d %d", &x, &y);  // citim coordonaele din fisier
        fprintf(g, "%d\n", m[x-1][y-1]); // facem indexare de la 0 ca sa corespunda si cu coordonatele din fisier
    }

    fclose(f);
    fclose(g);
        
    return 0;
}
