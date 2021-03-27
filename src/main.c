#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct carte {
    int valeur;
    int tete;
};
typedef struct carte carte;

struct joueur {
    char nom[12];
    carte* enMain;
    int points;
};
typedef struct joueur joueur;

void remplirDeck(carte deck[104]) {
    for (int i = 0; i < 104; i++) {
        int valeur = i + 1;
        deck[i].valeur = valeur;
        deck[i].tete = 0;
        if (valeur % 5 == 0 && valeur % 10 != 0) deck[i].tete += 2;
        if (valeur % 10 == 0) deck[i].tete += 3;
        if (valeur % 11 == 0) deck[i].tete += 5;
    }
}

void shuffle(carte* deck, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        int j = i + rand() / (RAND_MAX / (taille - i) + 1);
        carte temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

void logCartes(carte* deck, int taille) {
    for (int i = 0; i < taille; i++) {
        printf("(%d, %d) ", deck[i].valeur, deck[i].tete);
    }
    printf("\n");
}

void initJoueur(joueur* liste, int taille, carte deck[104]) {
    for (int i = 0; i < taille; i++) {
        printf("Joueur %d, entrez votre nom\n", i + 1);
        scanf("%12s", liste[i].nom);
        
        carte deckJoueur[10];

        for (int j = i * 10; j < (i + 1) * 10; j++) {
            deckJoueur[j % 10] =  deck[j];
        }
        liste[i].enMain = deckJoueur;
        free(deckJoueur);

        logCartes(liste[0].enMain, 10);

        liste[i].points = 0;
    }
}

int main() {
    srand(time(NULL));
    int nbJoueurs;
    printf("Combien de joueurs y a-t-il ?\n");
    scanf("%d", &nbJoueurs);

    if (nbJoueurs < 2 || nbJoueurs > 10) {
        printf("Ce nombre est invalide !");
        return 1;
    }

    // Initialisation du deck
    carte deck[104];
    remplirDeck(deck);
    shuffle(deck, 104);
    
    // Initialisation des joueurs
    joueur* listeJoueurs = malloc(sizeof(joueur) * nbJoueurs);
    initJoueur(listeJoueurs, nbJoueurs, deck);

    // Définition de la série de cartes sur laquelle on va jouer
    carte serie[4][5];
    for (int i = 0; i < 4; i++) {
        serie[i][0] = deck[nbJoueurs * 10 + i];
    }
    free(deck); // Les cartes des joueurs et la série étant définis, on a plus besoin du reste du paquet

    return 0;
}