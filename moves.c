#include <string.h>
#include "game.h"

// Déplace et fusionne toutes les tuiles vers la gauche.
// Méthode:
// - Pour chaque ligne, on parcourt les tuiles non nulles et on utilise
//   une variable "pending" pour retenir une tuile en attente de fusion.
// - Si la tuile suivante est identique à "pending", on fusionne et
//   on écrit le résultat dans "temp"; sinon on pousse "pending" dans
//   "temp" et on continue.
// - Enfin, on recopie "temp" dans la ligne et on détecte si au moins
//   une case a changé (moved).
int moveLeft(int size, int *board, int *score) {
    int moved = 0;
    for (int i = 0; i < size; i++) {
        int temp[size];
        memset(temp, 0, sizeof(temp));
        int index = 0;
        int pending = 0;

        // Parcourt la ligne et fusionne les tuiles identiques consécutives.
        for (int j = 0; j < size; j++) {
            int current = board[i * size + j];
            if (current == 0) continue;
            if (pending == 0) {
                pending = current;
            } else if (pending == current) {
                temp[index++] = pending * 2;
                *score += pending * 2; // Mise à jour du score lors de la fusion
                pending = 0;
            } else {
                temp[index++] = pending;
                pending = current;
            }
        }
        if (pending != 0) {
            temp[index++] = pending;
        }

        // Écrit la nouvelle ligne compressée et compare pour savoir si un mouvement a eu lieu.
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] != temp[j]) {
                moved = 1;
            }
            board[i * size + j] = temp[j];
        }
    }
    return moved;
}

// Déplace et fusionne toutes les tuiles vers la droite.
// Logique similaire à moveLeft mais en parcourant la ligne de droite à gauche
// et en remplissant "temp" depuis la droite (index initial = size-1).
int moveRight(int size, int *board, int *score) {
    int moved = 0;
    for (int i = 0; i < size; i++) {
        int temp[size];
        memset(temp, 0, sizeof(temp));
        int index = size - 1;
        int pending = 0;

        for (int j = size - 1; j >= 0; j--) {
            int current = board[i * size + j];
            if (current == 0) continue;
            if (pending == 0) {
                pending = current;
            } else if (pending == current) {
                temp[index--] = pending * 2;
                *score += pending * 2;
                pending = 0;
            } else {
                temp[index--] = pending;
                pending = current;
            }
        }
        if (pending != 0) {
            temp[index--] = pending;
        }

        for (int j = 0; j < size; j++) {
            if (board[i * size + j] != temp[j]) {
                moved = 1;
            }
            board[i * size + j] = temp[j];
        }
    }
    return moved;
}

// Déplace et fusionne toutes les tuiles vers le haut.
// Même approche que pour les lignes, mais on parcourt par colonne.
int moveUp(int size, int *board, int *score) {
    int moved = 0;
    for (int j = 0; j < size; j++) {
        int temp[size];
        memset(temp, 0, sizeof(temp));
        int index = 0;
        int pending = 0;

        for (int i = 0; i < size; i++) {
            int current = board[i * size + j];
            if (current == 0) continue;
            if (pending == 0) {
                pending = current;
            } else if (pending == current) {
                temp[index++] = pending * 2;
                *score += pending * 2;
                pending = 0;
            } else {
                temp[index++] = pending;
                pending = current;
            }
        }
        if (pending != 0) {
            temp[index++] = pending;
        }

        for (int i = 0; i < size; i++) {
            if (board[i * size + j] != temp[i]) {
                moved = 1;
            }
            board[i * size + j] = temp[i];
        }
    }
    return moved;
}

// Déplace et fusionne toutes les tuiles vers le bas.
// Parcours de la colonne du bas vers le haut, remplissage de "temp" depuis
// la fin (index=size-1).
int moveDown(int size, int *board, int *score) {
    int moved = 0;
    for (int j = 0; j < size; j++) {
        int temp[size];
        memset(temp, 0, sizeof(temp));
        int index = size - 1;
        int pending = 0;

        for (int i = size - 1; i >= 0; i--) {
            int current = board[i * size + j];
            if (current == 0) continue;
            if (pending == 0) {
                pending = current;
            } else if (pending == current) {
                temp[index--] = pending * 2;
                *score += pending * 2;
                pending = 0;
            } else {
                temp[index--] = pending;
                pending = current;
            }
        }
        if (pending != 0) {
            temp[index--] = pending;
        }

        for (int i = 0; i < size; i++) {
            if (board[i * size + j] != temp[i]) {
                moved = 1;
            }
            board[i * size + j] = temp[i];
        }
    }
    return moved;
}
