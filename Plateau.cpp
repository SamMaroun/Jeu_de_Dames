/*	AUTHOR:Sam MAROUN
    DATE: 20/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Plateau
*/

#include "Plateau.h"

Plateau::Plateau(){

    //Placement des noirs impaire
    //Tous les pions sont mort par défaut, on les passe à vivant
    //Et on met la couleur noir
    for(int i_y=0; i_y<4; i_y+=2){
        for(int i_x=1; i_x<10; i_x+=2){
            m_damier[i_x][i_y].setEstMort(false);
            m_damier[i_x][i_y].setCouleur("Noir");

        }
    }

    //Placement des noirs paire
    for(int i_y=1; i_y<4; i_y+=2){
        for(int i_x=0; i_x<10; i_x+=2){
            m_damier[i_x][i_y].setEstMort(false);
            m_damier[i_x][i_y].setCouleur("Noir");
        }
    }

    //Placement des blancs impaire
    //Tous les pions sont blanc par défaut
    //Inutile de set la couleur ici
    for(int i_y=8; i_y<5; i_y-=2){
        for(int i_x=1; i_x<10; i_x-=2){
            m_damier[i_x][i_y].setEstMort(false);
        }
    }

    //Placement des blancs paire
    for(int i_y=9; i_y<5; i_y-=2){
        for(int i_x=0; i_x<10; i_x-=2){
             m_damier[i_x][i_y].setEstMort(false);
        }
    }

    //Placement des cases vides (Pion mort)
       for(int i_y=4; i_y<6; i_y++){
           for(int i_x=0; i_x<10; i_x++){
               m_damier[i_x][i_y].setEstMort(true);
           }
       }

}

void Plateau::deplacementPion(int pos_x, int pos_y){
    //Dans le cas des noirs, on se déplace vers le base
    //if(m_damier[pos_x][pos_y].getCouleur() == false){
        //if(m_damier[pos_x][pos_y].getEstDame() == false){

        //}
    //}
}

int Plateau::victoire(){
    int nbPionsBlanc = 0;
    int nbPionsNoir = 0;

    for(int i_y = 0; i_y<10; i_y++){
        for(int i_x = 0; i_x<10; i_x++){
           if(m_damier[i_x][i_y].getCouleur() == true)
               nbPionsBlanc++;

           else
               nbPionsNoir++;
        }
    }

    //Les blanc gagnent on renvoie 1
    if(nbPionsNoir == 0 && nbPionsBlanc != 0)
        return 1;

    //Les noir gagnent on renvoie 2
    if(nbPionsBlanc == 0 && nbPionsBlanc !=0)
        return 2;

    //Personne n'a encore gagné
    else
        return 0;

}

