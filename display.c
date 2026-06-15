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
// Retourne un attribut de couleur Windows adapté à la valeur avec fond coloré.
static WORD getTileColor(int value) {
    WORD white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    WORD black = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    WORD cyan = BACKGROUND_GREEN | BACKGROUND_BLUE;
    WORD magenta = BACKGROUND_RED | BACKGROUND_BLUE;
    WORD yellow = BACKGROUND_RED | BACKGROUND_GREEN;
    WORD darkBlue = BACKGROUND_BLUE;
    WORD darkRed = BACKGROUND_RED;
    WORD darkGreen = BACKGROUND_GREEN;
    WORD white_bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    
    switch (value) {
        case 0: return white;  // fond vert foncé, texte blanc clair
        case 2: return darkBlue | white;  // fond bleu foncé, texte blanc clair
        case 4: return darkGreen | white;  // fond vert foncé, texte blanc clair
        case 8: return darkRed | white;  // fond rouge foncé, texte blanc clair
        case 16: return yellow | FOREGROUND_RED;  // fond jaune clair, texte rouge foncé
        case 32: return magenta | white;  // fond magenta foncé, texte blanc clair
        case 64: return cyan | FOREGROUND_BLUE;  // fond cyan clair, texte bleu foncé
        case 128: return magenta | white;  // fond magenta foncé, texte blanc clair
        case 256: return yellow | FOREGROUND_RED;  // fond jaune clair, texte rouge foncé
        case 512: return white_bg | FOREGROUND_BLUE;  // fond blanc clair, texte bleu foncé
        case 1024: return yellow | FOREGROUND_BLUE;  // fond jaune clair, texte bleu foncé
        case 2048: return yellow | FOREGROUND_RED | FOREGROUND_INTENSITY;  // fond jaune clair, texte rouge intense
        default: return white_bg | black;
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
// La grille est dessinée ligne par ligne avec des cellules de largeur fixe avec fonds colorés.
void printBoard(int size, int *board, int score) {
    const int cellWidth = 7;
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
        printf("+%.*s", cellWidth, "-------");
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
            int padding = cellWidth - len;
            if (padding < 0) padding = 0;
            int left = padding / 2;
            int right = padding - left;

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
            printf("+%.*s", cellWidth, "-------");
        }
        printf("+\n");
    }
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, originalAttributes);
    }
}
