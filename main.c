#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "game.h"

static int showWelcomeMenu(void) {
    char line[64];

    while (1) {
        printf("=== Bienvenue sur 2048 ! ===\n");
        printf("1. Nouvelle partie\n");
        printf("2. Charger une sauvegarde\n");
        printf("3. Quitter\n");
        printf("Choix : ");

        if (!fgets(line, sizeof(line), stdin)) {
            return 3;
        }

        int i = 0;
        while (line[i] != '\0' && isspace((unsigned char)line[i])) {
            i++;
        }

        if (line[i] == '1' && (line[i + 1] == '\0' || line[i + 1] == '\n')) {
            return 1;
        }
        if (line[i] == '2' && (line[i + 1] == '\0' || line[i + 1] == '\n')) {
            return 2;
        }
        if (line[i] == '3' && (line[i + 1] == '\0' || line[i + 1] == '\n')) {
            return 3;
        }

        printf("Choix invalide. Veuillez entrer 1, 2 ou 3.\n\n");
    }
}

int main(void) {
    int gridSize = 0;
    int *board = NULL; // Plateau représenté par un tableau 1D
    int score = 0;
    int input;
    int gameOver = 0;
    char line[64];
    int victoryDisplayed = 0;  // Flag pour tracker si la victoire a été affichée

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  

    initConsole();

    int menuChoice = showWelcomeMenu();
    if (menuChoice == 3) {
        resetConsole();
        return 0;
    }

    if (menuChoice == 2) {
        if (!loadGame(&gridSize, &board, &score)) {
            printf("Impossible de charger la sauvegarde. Nouvelle partie en cours.\n");
            gridSize = 0;
        }
    }

    // Si aucune sauvegarde n'a été chargée, démarrer une nouvelle partie.
    if (board == NULL) {
        printf("Quelle est la taille de la grille ? (ex: 4 pour une grille 4x4) : ");
        if (fgets(line, sizeof(line), stdin)) {
            int value;
            if (sscanf(line, "%d", &value) != 1 || value < 2) {
                printf("Taille invalide ou entrée vide. Utilisation de la taille par défaut (4).\n");
                gridSize = 4;
            } else {
                gridSize = value;
            }
        } else {
            printf("Erreur de lecture. Utilisation de la taille par défaut (4).\n");
            gridSize = 4;
        }

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
        victoryDisplayed = 0;  // Nouvelle partie, réinitialiser le flag
    } else {
        srand((unsigned)time(NULL));
        victoryDisplayed = 0;  // Sauvegarde chargée, réinitialiser le flag
    }

    // Boucle principale : affiche le plateau, gère les entrées et les mouvements.
    while (1) {
        printBoard(gridSize, board, score);
        
        // Vérifier si le joueur a atteint 2048 (victoire)
        int hasWon = 0;
        if (!victoryDisplayed) {
            for (unsigned i = 0; i < gridSize; i++) {
                for (unsigned j = 0; j < gridSize; j++) {
                    if (board[i * gridSize + j] == 2048) {
                        hasWon = 1;
                        break;
                    }
                }
                if (hasWon) break;
            }
        }
        
        if (hasWon) {
            victoryDisplayed = 1;
            printf("Félicitations ! Vous avez atteint 2048 !\n");
            printf("============================\n");
            printf("Appuyez sur ENTRÉE pour continuer à jouer\n");
            printf("Appuyez sur ÉCHAP pour quitter\n");
            printf("Appuyez sur E pour sauvegarder et quitter\n");
            printf("============================\n");
            
            int victoryHandled = 0;
            while (!victoryHandled) {
                input = _getch();
                if (input == 0 || input == 224) {
                    input = _getch();
                }
                
                if (input == 13) { // Entrée
                    victoryHandled = 1;
                    break;
                } else if (input == 27) { // Échap
                    resetConsole();
                    free(board);
                    printf("Merci d'avoir joué !\n");
                    return 0;
                } else if (input == 'e' || input == 'E') {
                    saveGame(gridSize, board, score);
                    resetConsole();
                    free(board);
                    printf("Merci d'avoir joué !\n");
                    return 0;
                }
            }
            // Continue le jeu après la victoire
            continue;
        }
        
        if (!canMove(gridSize, board)) {
            gameOver = 1;
        }

        if (gameOver) {
            printf("GAME OVER! Score final : %d\n", score);
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
                    victoryDisplayed = 0;  // Réinitialiser le flag de victoire
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
                victoryDisplayed = 0;  // Réinitialiser le flag de victoire au chargement
                break;
            default:
                continue;
        }

        if (moved) {
            addRandomTile(gridSize, board);
        }
    }
    
    resetConsole();
    free(board);
    return 0;
}