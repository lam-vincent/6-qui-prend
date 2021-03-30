#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct carte {
    int valeur;
    int tete;
};
typedef struct carte carte;

// Cette structure suivra la dernière carte d'une série, la position de celle-ci, et le total de têtes de boeufs que cette série contient
struct serie {
    carte carte;
    int position;
    int tete;
};
typedef struct serie Serie;

struct joueur {
    char nom[12];
    carte enMain[10];
    int points;
};
typedef struct joueur joueur;

void remplirDeck(carte deck[104]) {
    for (int i = 0; i < 104; i++) {
        // Pour chaque valeur de i, on donne i + 1 à la valeut de la carte et on calcule le nombre de tetes de boeuf ensuite selon les règles
        int valeur = i + 1;
        deck[i].valeur = valeur;
        deck[i].tete = 0;
        if (valeur % 5 == 0 && valeur % 10 != 0) deck[i].tete += 2;
        if (valeur % 10 == 0) deck[i].tete += 3;
        if (valeur % 11 == 0) deck[i].tete += 5;
    }
}

void melangerCartes(carte* deck, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        int X = taille - i; // X compte le nombre de cartes restantes entre la fin du paquet et la position actuelle
        int j = i + X * rand()/RAND_MAX; // j donne la position de la carte avec laquelle on va échanger. On la récupère de manière aléatoire entre 0 et X, puis on ajoute la position actuelle
        carte temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

void trierCartesDebut(carte* enMain) {
    // On utilie un algorithme de tri par sélection pour trier les cartes en main
    for (int i = 0; i < 9; i++) {
		int minIndex = i;
		
		for (int j = i + 1; j < 10; j++) {
			if (enMain[j].valeur < enMain[minIndex].valeur) minIndex = j;
		}
		
		if (i != minIndex) {
			carte temp = enMain[i];
			enMain[i] = enMain[minIndex];
			enMain[minIndex] = temp;
		}
	}
}

void logCartes(carte* deck, int taille) {
    for (int i = 0; i < taille; i++) {
        printf("(%d, %d) ", deck[i].valeur, deck[i].tete);
    }
    printf("\n");
}

// Fonction utilisée à l'initialisation de la parite
void initJoueur(joueur* liste, int taille, carte deck[104]) {
    for (int i = 0; i < taille; i++) {
        printf("Joueur %d, entrez votre nom\n", i + 1);
        scanf("%12s", liste[i].nom);

        for (int j = i * 10; j < (i + 1) * 10; j++) {
            liste[i].enMain[j % 10] = deck[j];
        }
        trierCartesDebut(liste[i].enMain);
        liste[i].points = 0;
    }
}

// Fonction utilisée dans la boucle de jeu
void initJoueur2(joueur* liste, int taille, carte deck[104]) {
    for (int i = 0; i < taille; i++) {
        for (int j = i * 10; j < (i + 1) * 10; j++) {
            liste[i].enMain[j % 10] = deck[j];
        }
        trierCartesDebut(liste[i].enMain);
    }
}

int main() {
    /******************
     * Initialisation *
     ******************/
    srand(time(NULL));
    int nbJoueurs;
    do {
        printf("Combien de joueurs y a-t-il ? (2 a 10)\n");
        scanf("%d", &nbJoueurs);
    } while (nbJoueurs < 2 || nbJoueurs > 10);

    // Initialisation du deck
    carte deck[104];
    remplirDeck(deck);
    melangerCartes(deck, 104);
    
    // Initialisation des joueurs
    joueur* listeJoueurs = malloc(sizeof(joueur) * nbJoueurs);
    initJoueur(listeJoueurs, nbJoueurs, deck);

    // Définition des 4 séries de cartes sur lesquells on va jouer
    Serie serie[4];
    for (int i = 0; i < 4; i++) {
        serie[i].carte = deck[nbJoueurs * 10 + i];
        serie[i].position = 0;
        serie[i].tete = serie[i].carte.tete;
    }

    /**********************
     * Début de la partie *
     **********************/
    int fini = 0;
    while (fini == 0) {
        /**********************
         * Début de la manche *
         **********************/
        for (int compteurTour = 1; compteurTour <= 10; compteurTour++) {

            // On note les cartes jouées de chaque joueur pour déterminer l'ordre de jeu
            int* ordreJoueurs = malloc(sizeof(int) * nbJoueurs);
            for (int i = 0; i < nbJoueurs; i++) {
                ordreJoueurs[i] = i;
            }

            // On demande ces cartes
            carte* cartesJouees = malloc(sizeof(carte) * nbJoueurs);
            int* indexCartesJouees = malloc(sizeof(int) * nbJoueurs); // On aura besoin de leur position ensuite pour les retirer de la main du joueur
            for (int compteurJoueur = 1; compteurJoueur <= nbJoueurs; compteurJoueur++) {
                joueur* j = &listeJoueurs[compteurJoueur - 1]; // On note j le joueur actuel pour éviter de devoir réécrire le nom en entier

                // On informe le joueur de ses cartes et du contenu de chaque série
                printf("%s, vos cartes sont ", j->nom);
                logCartes(j->enMain, 11 - compteurTour);
                printf("Les series disponibles sont\n");
                for (int i = 0; i < 4; i++) {
                    Serie* s = &serie[i]; // Pour éviter de réécrire serie[i] partout
                    printf("Serie %d - %d carte%s- %d tete%sde boeuf - derniere carte (%d, %d)\n", i + 1, s->position + 1, s->position + 1 > 1 ? "s " : " ", s->tete, s->tete > 1 ? "s " : " ", s->carte.valeur, s->carte.tete);
                }

                // On récupère le choix du joueur
                int indexCarte;
                do {
                    printf("Quelle carte voulez-vous poser face cachee ? (Entrez la position de la carte)\n");
                    scanf(" %d", &indexCarte);
                    indexCarte--;
                } while (indexCarte < 0 || indexCarte > (10 - compteurTour));

                cartesJouees[compteurJoueur - 1] = j->enMain[indexCarte];
                indexCartesJouees[compteurJoueur - 1] = indexCarte;
            }

            // On trie les cartes jouées des joueurs et on trie ordreJoueurs en même temps
            for (int i = 0; i < nbJoueurs - 1; i++) {
                int minIndex = i;
                
                for (int j = i + 1; j < nbJoueurs; j++) {
                    if (cartesJouees[j].valeur < cartesJouees[minIndex].valeur) minIndex = j;
                }
                
                if (i != minIndex) {
                    carte tempCarte = cartesJouees[i];
                    cartesJouees[i] = cartesJouees[minIndex];
                    cartesJouees[minIndex] = tempCarte;

                    int temp = ordreJoueurs[i];
                    ordreJoueurs[i] = ordreJoueurs[minIndex];
                    ordreJoueurs[minIndex] = temp;
                }
            }

            for (int compteurJoueur = 1; compteurJoueur <= nbJoueurs; compteurJoueur++) {
                joueur* j = &listeJoueurs[ordreJoueurs[compteurJoueur - 1]];
                carte* c = &cartesJouees[compteurJoueur - 1]; // La carte jouée du joueur j. On utilise le pointeur c pour éviter de devoir tout réécrire à chaque fois

                // On vérifie que la carte choisie peut être jouée dans une série
                int peutJouer = 0;
                for (int i = 0; i < 4; i++) {
                    if (serie[i].carte.valeur < c->valeur) {
                        peutJouer = 1;
                        break;
                    }
                }

                int indexSerie;
                if (peutJouer) {
                    // On cherche la série la plus proche sur laquelle on peut jouer
                    int min = 104;
                    for (int i = 0; i < 4; i++) {
                        Serie* s = &serie[i];
                        if (c->valeur > s->carte.valeur && c->valeur - s->carte.valeur < min) {
                            min = c->valeur - s->carte.valeur;
                            indexSerie = i;
                        }
                    }

                    // On informe le joueur de la série sur laquelle il joue
                    printf("%s, votre carte (%d, %d) va etre jouee sur la serie %d\nAppuyez sur ENTREE pour continuer", j->nom, c->valeur, c->tete, indexSerie + 1);
                    if (compteurJoueur == 1) getchar(); // Le premier getchar() se débarasse du \n restant après un scanf
                    getchar(); // Le deuxième sert à attendre l'entrée utilisateur
                } else {
                    printf("Votre carte (%d, %d) est trop faible pour etre jouee dans une des 4 series.\nVeuillez choisir la serie a recuperer (Entrez le numero de la serie)\n", c->valeur, c->tete);
                    do {
                        scanf("%d", &indexSerie);
                        indexSerie--;
                    } while (indexSerie < 0 || indexSerie > 3);
                }

                Serie* s = &serie[indexSerie];

                // On vérifie que la série est à son maximum (5 cartes) ou que le joueur n'ait pas pu jouer. Si c'est le cas, on compte les têtes et on réinitialise la série
                if (s->position == 4 || !peutJouer) {
                    s->position = -1; // On le met à -1 pour que ça colle avec le ++ en dessous
                    j->points += s->tete;
                    printf("%s, vous recuperez %d point%s! Vous avez maintenant %d points\n", j->nom, s->tete, s->tete > 1 ? "s " : " ", j->points);
                    s->tete = 0;
                }

                // On met à jour la structure série avec la carte jouée
                s->carte = *c;
                s->position++;
                s->tete += c->tete;
                
                // On met la carte jouée à la fin de la liste (pour la masquer) et on glisse les éléments entre indexCarte et la fin de un vers la gauche (pour les garder triés)
                for (int i = indexCartesJouees[compteurJoueur - 1]; i < 10 - compteurTour; i++) {
                    carte carteJouee = j->enMain[i];
                    j->enMain[i] = j->enMain[i + 1];
                    j->enMain[i + 1] = carteJouee;
                }

                printf("\n");
            }

            printf("\n");
        }

        // Vérification qu'aucun joueur n'a dépassé 66 têtes
        for (int i = 0; i < nbJoueurs; i++) {
            if (listeJoueurs[i].points > 66) {
                fini = 1;
                break;
            }
        }

        printf("\nManche terminee ! Les scores sont actuellement :\n");
        for (int i = 0; i < nbJoueurs; i++) {
            printf("%s - %d points\n", listeJoueurs[i].nom, listeJoueurs[i].points);
        }

        if (!fini) {
            // Initialisation du deck
            remplirDeck(deck);
            melangerCartes(deck, 104);
            
            // Initialisation des joueurs
            initJoueur2(listeJoueurs, nbJoueurs, deck);

            // Définition des 4 séries de cartes sur lesquelles on va jouer
            for (int i = 0; i < 4; i++) {
                serie[i].carte = deck[nbJoueurs * 10 + i];
                serie[i].position = 0;
                serie[i].tete = serie[i].carte.tete;
            }
        }
    }

    // On recherche et on annonce le vainqueur
    joueur min = listeJoueurs[0];
    for (int i = 1; i < nbJoueurs; i++) {
        if (listeJoueurs[i].points < min.points) min = listeJoueurs[i];
    }
    printf("%s gagne la partie avec %d points !\n", min.nom, min.points);

    return 0;
}