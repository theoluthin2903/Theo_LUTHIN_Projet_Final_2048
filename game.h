#ifndef GAME_H
#define GAME_H

// Console et affichage.
// `initConsole` prépare la console (UTF-8, gestion Ctrl+C, couleurs).
// `resetConsole` restaure l'état original avant la sortie.
void initConsole(void);
void resetConsole(void);

// Gestion du plateau.
// Le plateau est stocké en 1D (size*size).
void initBoard(int size, int *board);
void addRandomTile(int size, int *board);
void printBoard(int size, int *board, int score);
int canMove(int size, int *board);

// Mouvements et score.
// Chaque fonction retourne 1 si le plateau a été modifié (mouvement réel),
// sinon 0. Le score est mis à jour via le pointeur `score`.
int moveLeft(int size, int *board, int *score);
int moveRight(int size, int *board, int *score);
int moveUp(int size, int *board, int *score);
int moveDown(int size, int *board, int *score);

// Sauvegarde / chargement.
// `loadGame` alloue un nouveau plateau et met à jour `*board` et `*size`.
int saveGame(int size, int *board, int score);
int loadGame(int *size, int **board, int *score);

#endif // GAME_H
