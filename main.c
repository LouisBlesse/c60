#include <stdio.h>

#define MAX 160


int lecture_fichier_ppm(int* pnl, int* pnc, int r[MAX][MAX], int g[MAX][MAX], int b[MAX][MAX])
{
    int nc = 1;
    int nl = 1;

    //ouvre le fichier
    FILE *pf;
    pf = fopen ("c60.ppm", "r+");
    int *lines = NULL;

    //test si le fichier Ã  bien Ã©tÃ© trouvÃ© et renvoie -999 sinon
    if (pf == NULL)
    {
        return -999;
    }

    //lis toutes les lignes du fichier une par une
    int *nbr = NULL ;
    char ligne;
    char ligne_Tot;
    //ligne 1
    fgets(&ligne, 50, pf) ;
    sscanf(&ligne,"%d", nbr);

    //ligne 2
    fgets(&ligne, 50, pf) ;
    //sscanf(&ligne,"%d %d", pnl, pnc);

    //ligne 3
    fgets(&ligne, 50, pf) ;

    //ligne Toutes les autres lignes
    printf("RED Fun\n");
    for(int i=0 ; i<MAX ; i++)
    {
        nc = 1;
        nl++;
        for(int j=0 ; j<MAX ; j++)
        {
            nc++;
            fgets(&ligne, 50, pf);
            sscanf(&ligne,"%d %d %d", &r[i][j], &g[i][j], &b[i][j]);
            printf("%d i = %d, j = %d\n", r[i][j],i,j);
        }
        nc --;
    }
    nl --;
    fclose(pf);
    //nc et nl contiennent le nombres de colonnes et de lignes
    pnc = (int *) nc;
    pnl = (int *) nl;
    printf("\n\n\nnc = %d\nnl = %d\n", nc, nl);
    printf("\n\n\npnc = %d\npnl = %d\n", pnc, pnl);
    return 0;
};

int mediane (int tab[], int n){
    int temp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(tab[i] > tab[j]) {
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
    int med = tab[n/2];
    return med;
}

void filtre_median (int nl, int nc, int d[MAX][MAX]){
    //Copie du tableau
    int tmp[MAX][MAX];
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            tmp[i][j] = d[i][j];
        }
    }

    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            if (j==0){
                if (i==0){
                    //coin en haut à gauche
                    int arr[] = {d[0][0], d[1][0], d[0][1]};
                    int n = 3;
                    tmp[i][j] = mediane(arr, n);
                }
                else if (i==nc-1){
                    //coin en bas à gauche
                    int arr[] = {d[nc-1][0], d[nc-2][0], d[nc-1][1]};
                    int n = 3;
                    tmp[i][j] = mediane(arr, n);
                }
                else {
                    //côté gauche
                    int arr[] = {d[i][j], d[i-1][j], d[i+1][j], d[i][j+1]};
                    int n = 4;
                    tmp[i][j] = mediane(arr, n);
                }
            }
            else if (j == nc-1){
                if (i==0){
                    //coin en haut à droite
                    int arr[] = {d[0][nl-1], d[1][nl-1], d[0][nl-2]};
                    int n = 3;
                    tmp[i][j] = mediane(arr, n);
                }
                else if (i==nc-1){
                    //coin en bas à droite
                    int arr[] = {d[nl-1][nc-1], d[nc-1][nl-2], d[nc-2][nl-1]};
                    int n = 3;
                    tmp[i][j] = mediane(arr, n);
                }
                else {
                    //côté droit
                    int arr[] = {d[i][j], d[i-1][j], d[i+1][j], d[i][j-1]};
                    int n = 4;
                    tmp[i][j] = mediane(arr, n);
                }
            }
            else if(i==0 && j!=0 && j!=nc-1){
                //en haut
                int arr[] = {d[i][j], d[i+1][j], d[i][j-1], d[i][j+1]};
                int n = 4;
                tmp[i][j] = mediane(arr, n);
            }
            else if(i==nc-1 && j!=0 && j!=nc-1){
                //en haut
                int arr[] = {d[i][j], d[i-1][j], d[i][j-1], d[i][j+1]};
                int n = 4;
                tmp[i][j] = mediane(arr, n);
            }
            else{
                //tout le reste
                int arr[] = {d[i][j], d[i-1][j],d[i+1][j], d[i][j-1], d[i][j+1]};
                int n = 5;
                tmp[i][j] = mediane(arr, n);
            }

        }
    }
    printf("RED mod :\n");

    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            d[i][j] = tmp[i][j];
            printf("%d\n", d[i][j]);
        }
    }
}

int main()
{
    int* pnl = 0;
    int* pnc = 0;
    int nc = 160;
    int nl = 160;
    int r[MAX][MAX];
    int g[MAX][MAX];
    int b[MAX][MAX];

    /////Question 2 :
    int result = lecture_fichier_ppm(pnl, pnc, r, g, b);
    if (result == -999){
        printf("Fichié non trouvé");
    }

    printf("RED main:\n");
    for(int i=0 ; i<MAX ; i++) {
        for(int j=0 ; j<MAX ; j++) {
            printf("%d i = %d, j = %d\n", r[i][j],i,j);
        }
    }

    filtre_median (nl, nc, r);
    return 0;
}
