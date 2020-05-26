/*	AUTHOR:Sam MAROUN
    DATE: 20/05/2020
    NAME:Plateau.h
    DESCRIPTION:Déclaration de la classe Plateau
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "Pion.h"

class Plateau{
    public:
        //Le constructeur place l'ensemble des pions en début de partie
        Plateau();

        //Déplacement : prend la position du pion
        void deplacementPion(int pos_x, int pos_y);

        //Test la fin de jeu
        //valeur par défaut 0, si personne n'a encore gagné
        //1 si les blancs gagnent, 2 si les noirs gagnent
        int victoire();



    private:
        //Le damier = plateau de pion
        Pion m_damier[10][10];

};

#endif // PLATEAU_H
