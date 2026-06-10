#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "game.h"

int main(void) {
    int gridSize = 0;
    int *board = NULL; // Plateau représenté par un tableau 1D
    int score = 0;
    int input;
    int gameOver = 0;
    int ch;
    char loadChoice = 'n';

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  

    // Active l'encodage UTF-8 pour afficher correctement les accents.
    printf("Charger la dernière sauvegarde ? (O/N) : ");
    if (scanf(" %c", &loadChoice) == 1 && (loadChoice == 'o' || loadChoice == 'O')) {
        if (!loadGame(&gridSize, &board, &score)) {
            printf("Nouvelle partie en cours.\n");
            gridSize = 0;
        }
    }
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    initConsole();

    // Si aucune sauvegarde n'a été chargée, démarrer une nouvelle partie.
    if (board == NULL) {
        printf("Quelle est la taille de la grille ? (ex: 4 pour une grille 4x4) : ");
        if (scanf("%d", &gridSize) == 0 || gridSize < 2) {
            printf("Taille invalide. Utilisation de la taille par défaut (4).\n");
            gridSize = 4;
        }
        while ((ch = getchar()) != '\n' && ch != EOF) {}

        board = malloc(gridSize * gridSize * sizeof(int)); // Allocation dynamique du plateau
        if (!board) {
            fprintf(stderr, "Erreur mémoire.\n");
            resetConsole();
            return 1;
        }

        // Initialise le plateau et place deux tuiles aléatoires de départ.
        srand((unsigned)time(NULL));
        initBoard(gridSize, board);
        addRandomTile(gridSize, board);
        addRandomTile(gridSize, board);
    } else {
        srand((unsigned)time(NULL));
    }

    // Boucle principale : affiche le plateau, gère les entrées et les mouvements.
    while (1) {
        printBoard(gridSize, board, score);
        if (!canMove(gridSize, board)) {
            gameOver = 1;
        }

        if (gameOver) {
            printf("GAME OVER! Final Score: %d\n", score);
            printf("Appuyez sur R pour rejouer ou Échap pour quitter\n");

            while (1) {
                input = _getch();
                if (input == 0 || input == 224) {
                    input = _getch();
                }

                if (input == 'r' || input == 'R') {
                    initBoard(gridSize, board);
                    score = 0;
                    addRandomTile(gridSize, board);
                    addRandomTile(gridSize, board);
                    gameOver = 0;
                    break;
                } else if (input == 27) { // Echap
                    resetConsole();
                    free(board);
                    printf("Merci d'avoir joué !\n");
                    return 0;
                }
            }
            continue;
        }

        // Lecture de la touche sans affichage à l'écran.
        input = _getch();
        if (input == 0 || input == 224) {
            input = _getch();
        }

        int moved = 0;
        switch (input) {
            case 'z':
            case 'Z':
            case 72: // Flèche haut
                moved = moveUp(gridSize, board, &score);
                break;
            case 's':
            case 'S':
            case 80: // Flèche bas
                moved = moveDown(gridSize, board, &score);
                break;
            case 'q':
            case 'Q':
            case 75: // Flèche gauche
                moved = moveLeft(gridSize, board, &score);
                break;
            case 'd':
            case 'D':
            case 77: // Flèche droite
                moved = moveRight(gridSize, board, &score);
                break;
            case 'e':
            case 'E':
                saveGame(gridSize, board, score); // Sauvegarder et quitter
                resetConsole();
                free(board);
                printf("Merci d'avoir joué !\n");
                return 0;
            case 27: // Echap
                resetConsole();
                free(board);
                printf("Merci d'avoir joué !\n");
                return 0;
            case 'l':
            case 'L':
                loadGame(&gridSize, &board, &score); // Charger une sauvegarde
                break;
            default:
                continue;
        }

        if (moved) {
            addRandomTile(gridSize, board);
        }
    }
    resetConsole();
    return 0;
}