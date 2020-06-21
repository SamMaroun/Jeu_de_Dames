/*	AUTHOR:Sam MAROUN
    DATE: 20/05/2020
    NAME:Plateau.h
    DESCRIPTION:Déclaration de la classe Plateau
*/

#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>


class Plateau{
    public:

        //Le constructeur place l'ensemble des pions en début de partie
        Plateau();

        //getter
        int getDamier(int, int) const;

        //Déplacement : prend la position du pion
        bool deplacementPion(int, int, int, int, int);

        //Déplacement d'une Dame
        bool deplacementDame(int, int, int, int, int);

        //verifie si la case est valide
        bool caseValide (int, int);

        //Test la fin de jeu
        //valeur par défaut 0, si personne n'a encore gagné
        //1 si les blancs gagnent, 2 si les noirs gagnent
        int victoire();



    private:
        int m_damier[10][10]; //Le damier = plateau de pion

};

#endif // PLATEAU_H
