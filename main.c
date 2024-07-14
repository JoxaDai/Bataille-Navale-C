#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_GRILLE 5
#define BATEAU 1
#define TIR_REUSSI 2
#define TIR_ECHOUE 3
#define EAU 0
#define MINE 4
#define NOMBRE_MINES 3

void initialiserGrille(int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
void afficherGrille(int grille[TAILLE_GRILLE][TAILLE_GRILLE], int reveal);
void placerBateau(int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
void placerMines(int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
int tirer(int grille[TAILLE_GRILLE][TAILLE_GRILLE], int x, int y);

int main() {
    int grille[TAILLE_GRILLE][TAILLE_GRILLE];
    int x, y;
    time_t start_time, end_time;
    double time_spent;

    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    initialiserGrille(grille);
    placerBateau(grille);
    placerMines(grille);

    printf("Bienvenue à la bataille navale !\n");
    afficherGrille(grille, 0);

    time(&start_time);

    while (1) {
        printf("Entrez les coordonnées de tir (x y) : ");
        scanf("%d %d", &x, &y);

        if (tirer(grille, x, y)) {
            printf("Bravo ! Vous avez coulé le bateau !\n");
            break;
        } else {
            printf("Tir raté ! Essayez encore.\n");
        }
        afficherGrille(grille, 0);
    }

    time(&end_time);
    time_spent = difftime(end_time, start_time);
    afficherGrille(grille, 1); // Afficher la grille complète à la fin
    printf("Vous avez gagné en %.2f secondes.\n", time_spent);

    return 0;
}

void initialiserGrille(int grille[TAILLE_GRILLE][TAILLE_GRILLE]) {
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            grille[i][j] = EAU;
        }
    }
}

void afficherGrille(int grille[TAILLE_GRILLE][TAILLE_GRILLE], int reveal) {
    printf("  ");
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (grille[i][j] == EAU) {
                printf("~ ");
            } else if (grille[i][j] == BATEAU) {
                printf(reveal ? "B " : "~ ");
            } else if (grille[i][j] == TIR_REUSSI) {
                printf("X ");
            } else if (grille[i][j] == TIR_ECHOUE) {
                printf("O ");
            } else if (grille[i][j] == MINE) {
                printf(reveal ? "M " : "~ ");
            }
        }
        printf("\n");
    }
}

void placerBateau(int grille[TAILLE_GRILLE][TAILLE_GRILLE]) {
    int x = rand() % TAILLE_GRILLE;
    int y = rand() % TAILLE_GRILLE;
    grille[x][y] = BATEAU;
}

void placerMines(int grille[TAILLE_GRILLE][TAILLE_GRILLE]) {
    for (int i = 0; i < NOMBRE_MINES; i++) {
        int x, y;
        do {
            x = rand() % TAILLE_GRILLE;
            y = rand() % TAILLE_GRILLE;
        } while (grille[x][y] != EAU);
        grille[x][y] = MINE;
    }
}

int tirer(int grille[TAILLE_GRILLE][TAILLE_GRILLE], int x, int y) {
    if (grille[x][y] == BATEAU) {
        grille[x][y] = TIR_REUSSI;
        return 1;
    } else if (grille[x][y] == MINE) {
        printf("Oh non ! Vous avez touché une mine !\n");
        grille[x][y] = TIR_ECHOUE;
    } else if (grille[x][y] == EAU) {
        grille[x][y] = TIR_ECHOUE;
    }
    return 0;
}

