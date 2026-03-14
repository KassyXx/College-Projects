#include <stdio.h>


//Verificam daca e an bisect sau nu
int anBisect (int an){
    if (an % 4 == 0)
        return 1;  
    return 0;
}

//Punem zilele fiecarei luni
int zileLuna(int luna, int an){
    int zile_pe_luna[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (luna == 2 && anBisect(an))  //Daca e Februarie (luna 2) si e an bisect atunci are 29 de zile
        return 29;

    return zile_pe_luna[luna];
}


int zileDeLaDataPrecizata(int zi, int luna, int an){
    int total = 0;

    //Punem zilele din anii ce au trecut
    for (int i = 1970; i < an; i++){
        if(anBisect(i))
            total += 366;
        else
            total += 365;
    }

    //Punem zilele din lunile anului curent
    for (int i = 1; i < luna; i++){
        total += zileLuna(i, an);
    }

    //Punem zilele din luna curenta
    total += zi - 1;

    return total;
    
}

int numarareWeekenduri(int ziua1, int luna1, int an1, int ziua2, int luna2, int an2){
    int zile1 = zileDeLaDataPrecizata(ziua1, luna1, an1); //Initializam aceste doua variabile pentru a le putea compara
    int zile2 = zileDeLaDataPrecizata(ziua2, luna2, an2);

    //Le comparam, iar in caz ca sunt puse ca Data 1 sa fie sfarsitul intervalului si Data 2 inceputul intervalului le interschimbam
    if (zile1 > zile2){
        int aux = zile1;
        zile1 = zile2;
        zile2 = aux;
    }


    int weekenduri = 0;
    int zi_sapt = (zile1 + 4) % 7; //Am pus +4 deoarece data de 1 Ianuarie 1970 este o zi de joi (adica numarul 4)

    //Cautam prima sambata
    if (zi_sapt != 6){ //Daca ziua saptamanii nu e sambata avansam pana la prima sambata (nu alegem duminica deoarece nu e un weekend complet)
        int zile_sambata = (6 - zi_sapt + 7) % 7;
        zile1 += zile_sambata; //Adaugam cate zile mai trebuie pana la prima sambata
        zi_sapt = 6; //Initializam pe numarul 6 care este corespunzator zilei de sambata
    }

    //Numaram fiecare weekend
    for (int i = zile1; i < zile2; i += 7){ //Mergen din 7 in 7 pentru ca zile1 este deja setat pe sambata si numaram weekendurile
        if (i + 1 <= zile2){ //Verificam daca duminica este in interval pentru a avea un weekend complet
            weekenduri++;
        }
    }

    return weekenduri;
    
}



int main(){
    int zi_1, luna_1, an_1;
    int zi_2, luna_2, an_2;
    int nrDeWeekenduri = 0;
    FILE *fin, *fout;
    fin = fopen("in.txt", "r");
    fout = fopen("out.txt", "w");

    if(fin == NULL || fout == NULL){
        printf("Eroare la deschiderea/crearea fisierului!\n");
        return 1;
    }

    fscanf(fin,"%d %d %d", &zi_1, &luna_1, &an_1);

    fscanf(fin,"%d %d %d", &zi_2, &luna_2, &an_2);

    nrDeWeekenduri = numarareWeekenduri(zi_1, luna_1, an_1, zi_2, luna_2, an_2);

    fprintf(fout,"%d", nrDeWeekenduri);

    fclose(fin);
    fclose(fout);
    
    return 0;
}