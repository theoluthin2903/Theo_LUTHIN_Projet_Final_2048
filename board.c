#include <stdlib.h>
#include "game.h"

// Initialise toutes les cases du plateau à zéro.
// Le plateau est un tableau 1D, indexé par i*size + j.
void initBoard(int size, int *board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i * size + j] = 0;
        }
    }
}

// Ajoute une nouvelle tuile aléatoire (2 ou 4) sur une case vide.
// Le tableau temporaire "emptyTiles" collecte les coordonnées (i,j)
// des cases vides pour choisir ensuite une position au hasard.
void addRandomTile(int size, int *board) {
    int emptyTiles[size * size][2];
    int count = 0;

    // Recense les positions vides de la grille.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] == 0) {
                emptyTiles[count][0] = i;
                emptyTiles[count][1] = j;
                count++;
            }
        }
    }

    // Si au moins une case est vide, place une tuile 2 ou 4.
    if (count > 0) {
        int randomIndex = rand() % count;
        int value = (rand() % 10 == 0) ? 4 : 2; // 10% de chance d'obtenir un 4
        board[emptyTiles[randomIndex][0] * size + emptyTiles[randomIndex][1]] = value;
    }
}

// Vérifie si le joueur peut encore effectuer un mouvement.
// On considère qu'un mouvement est possible s'il existe une case vide
// ou deux cases adjacentes de même valeur (pouvant fusionner).
int canMove(int size, int *board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int current = board[i * size + j];
            if (current == 0) return 1; // Il existe une case vide.
            if (j < size - 1 && current == board[i * size + j + 1]) return 1; // Peut fusionner horizontalement.
            if (i < size - 1 && current == board[(i + 1) * size + j]) return 1; // Peut fusionner verticalement.
        }
    }
    return 0; // Aucune action possible.
}
