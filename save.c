#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// Sauvegarde la taille, le score et l'état du plateau dans un fichier texte.
// Format simple : première ligne "size score", puis size lignes contenant
// les valeurs des cases séparées par des espaces.
int saveGame(int size, int *board, int score) {
    FILE *file = fopen("sauvegarde_2048.txt", "w");
    if (!file) {
        printf("Erreur lors de la sauvegarde du jeu.\n");
        return 0;
    }

    fprintf(file, "%d %d\n", size, score);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", board[i * size + j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Jeu sauvegardé dans 'sauvegarde_2048.txt'.\n");
    return 1;
}

// Charge une partie depuis le fichier de sauvegarde et remplace le plateau actuel.
// La fonction alloue un nouveau plateau, lit les valeurs et remplace le
// pointeur fourni. En cas d'erreur elle libère la mémoire allouée.
int loadGame(int *size, int **board, int *score) {
    FILE *file = fopen("sauvegarde_2048.txt", "r");
    if (!file) {
        printf("Aucune sauvegarde trouvée.\n");
        return 0;
    }

    int savedSize;
    if (fscanf(file, "%d %d", &savedSize, score) != 2 || savedSize < 2) {
        printf("Fichier de sauvegarde invalide.\n");
        fclose(file);
        return 0;
    }

    int *newBoard = malloc(savedSize * savedSize * sizeof(int));
    if (!newBoard) {
        printf("Mémoire insuffisante pour charger la sauvegarde.\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < savedSize; i++) {
        for (int j = 0; j < savedSize; j++) {
            if (fscanf(file, "%d", &newBoard[i * savedSize + j]) != 1) {
                printf("Erreur de lecture du fichier de sauvegarde.\n");
                free(newBoard);
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    free(*board); // Remplace l'ancien plateau par le nouveau
    *board = newBoard;
    *size = savedSize;
    printf("Sauvegarde chargée avec succès.\n");
    return 1;
}