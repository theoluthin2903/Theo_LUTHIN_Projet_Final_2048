#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "game.h"

static HANDLE hConsole = INVALID_HANDLE_VALUE;
static WORD originalAttributes = 0;

// Gestionnaire pour restaurer le style de la console avant de quitter.
// Permet de restaurer les attributs (couleurs) si l'utilisateur
// interrompt le programme (Ctrl+C, fermeture de la fenêtre, ...).
static BOOL WINAPI CtrlHandler(DWORD ctrlType) {
    if (ctrlType == CTRL_C_EVENT || ctrlType == CTRL_BREAK_EVENT || ctrlType == CTRL_CLOSE_EVENT) {
        if (hConsole != INVALID_HANDLE_VALUE) {
            SetConsoleTextAttribute(hConsole, originalAttributes);
        }
        printf("\nJeu arrêté. À bientôt !\n");
        ExitProcess(0);
        return TRUE;
    }
    return FALSE;
}

// Choisit une couleur pour chaque valeur de tuile.
// Retourne un attribut de couleur Windows adapté à la valeur.
static WORD getTileColor(int value) {
    switch (value) {
        case 2: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 4: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case 8: return FOREGROUND_RED | FOREGROUND_INTENSITY;
        case 16: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case 32: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 64: return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 128: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 256: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case 512: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 1024: return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 2048: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        default: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

// Configure la console pour UTF-8 et sauvegarde les attributs actuels.
// Cela permet d'utiliser des couleurs puis de les restaurer proprement.
void initConsole(void) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            originalAttributes = csbi.wAttributes;
        }
        SetConsoleCtrlHandler(CtrlHandler, TRUE);
    }
}

// Restaure l'apparence de la console avant de quitter le programme.
// À appeler avant de terminer pour ne pas laisser la console dans un état modifié.
void resetConsole(void) {
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, originalAttributes);
    }
}

// Affiche le plateau et le score avec une bordure et des couleurs.
// La grille est dessinée ligne par ligne avec des cellules de largeur fixe.
void printBoard(int size, int *board, int score) {
    system("cls"); // Efface l'écran de la console.
    WORD borderColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    printf("Score: %d   (Flèches ou Z/Q/S/D = jouer, E = sauvegarder et quitter, L = charger, R = rejouer, Échap = quitter)\n\n", score);

    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, borderColor);
    }
    for (int j = 0; j < size; j++) {
        printf("+-----");
    }
    printf("+\n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value = board[i * size + j];
            char text[16];
            if (value == 0) {
                strcpy(text, "."); // Case vide.
            } else {
                sprintf(text, "%d", value); // Affiche la valeur de la tuile.
            }
            int len = (int)strlen(text);
            int left = (5 - len) / 2;
            int right = 5 - len - left;

            if (hConsole != INVALID_HANDLE_VALUE) {
                SetConsoleTextAttribute(hConsole, borderColor);
            }
            printf("|");
            // Choix de la couleur en fonction de la valeur de la tuile.
            WORD color = getTileColor(value);
            if (hConsole != INVALID_HANDLE_VALUE) {
                SetConsoleTextAttribute(hConsole, color);
            }
            for (int k = 0; k < left; k++) printf(" ");
            printf("%s", text);
            for (int k = 0; k < right; k++) printf(" ");
        }
        if (hConsole != INVALID_HANDLE_VALUE) {
            SetConsoleTextAttribute(hConsole, borderColor);
        }
        printf("|\n");
        for (int j = 0; j < size; j++) {
            printf("+-----");
        }
        printf("+\n");
    }
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, originalAttributes);
    }
}
