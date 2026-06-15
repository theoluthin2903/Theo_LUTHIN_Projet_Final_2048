# 🎮 Projet 2048 en C

## 📌 Description

Ce projet est une implémentation du célèbre jeu **2048** en langage C, jouable directement dans le terminal.
Le joueur déplace des tuiles sur une grille afin de les fusionner et atteindre la valeur **2048**.

Le programme gère :

* L’affichage du plateau dans la console
* Les déplacements du joueur
* La fusion des tuiles
* Le score
* La sauvegarde et le chargement d’une partie

---

## ⚙️ Fonctionnalités

* 🎲 Grille personnalisable (ex : 4x4, 5x5, etc.)
* 🎮 Contrôle au clavier
* 💾 Sauvegarde automatique de la partie
* 🔄 Chargement d’une sauvegarde au lancement
* 🧠 Gestion des règles du jeu 2048
* 🖥️ Affichage console amélioré (UTF-8)

---

## 📁 Structure du projet

```
Theo_LUTHIN_Projet_Final_2048/
│── main.c        → Programme principal
│── board.c       → Gestion du plateau de jeu
│── moves.c       → Logique des déplacements
│── display.c     → Affichage du jeu dans la console
│── save.c        → Sauvegarde et chargement
│── game.h        → Déclarations et structures communes
```

---

## ▶️ Compilation

⚠️ Le projet utilise des bibliothèques spécifiques à Windows (`conio.h`, `windows.h`)

Pour compiler avec **GCC (MinGW)** :

```bash
gcc main.c board.c moves.c display.c save.c -o 2048
```

---

## 🚀 Lancement

```bash
./2048
```

---

## 🎮 Comment jouer

1. Au lancement :

   * Choisir de charger une sauvegarde ou non
2. Choisir la taille de la grille
3. Utiliser les touches du clavier pour déplacer les tuiles :

   * ↑ ou Z : déplacement vers le haut
   * ↓ ou S : déplacement vers le bas
   * ← ou Q : déplacement vers la gauche
   * → ou D : déplacement vers la droite
4. Fusionner les tuiles de même valeur pour augmenter le score
5. Atteindre **2048** pour gagner 🎉

---

## 💾 Sauvegarde

* Le jeu propose de charger une sauvegarde au démarrage
* Les données sauvegardées incluent :

  * Taille de la grille
  * Plateau
  * Score

---

## 🛠️ Améliorations possibles

* Ajout d’un mode graphique (SDL)
* Gestion multiplateforme (Linux/Mac)
* Ajout d’un menu interactif
* Meilleure gestion des entrées utilisateur
* Ajout d’un classement des scores

---

## 👨‍💻 Auteur

Projet réalisé par **Théo LUTHIN**

---
