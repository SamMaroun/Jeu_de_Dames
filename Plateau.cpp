/*	AUTHOR:Sam MAROUN & Emile LAVEY
    DATE: 20/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Plateau
*/

#include "Plateau.h"

Plateau::Plateau(){

    //Création d'un plateau de jeu
    int damier[10][10] =
              { { 0,-1, 0,-1, 0,-1, 0,-1, 0,-1},
                {-1, 0,-1, 0,-1, 0,-1, 0,-1, 0},
                { 0,-1, 0,-1, 0,-1, 0,-1, 0,-1},
                {-1, 0,-1, 0,-1, 0,-1, 0,-1, 0},

                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

                { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} };

     for(int x=0; x<10; x++){
         for(int y=0; y<10; y++){
             m_damier[x][y]= damier[x][y];
         }
     }
}

int Plateau::getDamier(int x,int y) const{
    return m_damier[x][y];
}

//true si le déplacement est bien effectué
bool Plateau::deplacementPion(int x_init, int y_init,
                              int x_dest, int y_dest, int couleur){

    //Si une dame est selectionnée, ce n'est pas un pion
    //donc c'est l'autre méthode qui agira
    if(couleur == 2 || couleur == -2)
        return false;

    //si on clique deux fois sur la même case pas de deplacement
    //ou sur une case invalide
    if(m_damier[x_init][y_init] == m_damier[x_dest][y_dest]
            || !caseValide(x_dest,y_dest))
        return false;

    //couleur opposant
    int couleurOpposant = couleur*(-1);

    //si decalageX positif, deplacement bas vers haut
    int decalageX = x_init - x_dest; //inversement si decalageX negatif

    //si decalage Y positif, deplacement droite vers gauche
    int decalageY = y_init - y_dest; //inversement si decalageY negatif

    //un déplacement de base pion blanc sur une case vide
    if(decalageX == 1 && (decalageY == 1 || decalageY == -1)){

        //On verife que la case destination est vide
        //et que le pion n'est pas noir
        if(m_damier[x_dest][y_dest] == 0 && couleur != -1){
            m_damier[x_dest][y_dest] = couleur;//On place le pion blanc à sa destination
            m_damier[x_init][y_init] = 0;//On le supprime de sa position initiale

            //transformation en dame blanche, si on est à la fin du plateau
            if(x_dest == 0)
                m_damier[x_dest][y_dest] += couleur;

            return true;
        }

        //dans l'autre cas deplacement impossible
        else
            return false;
        }

    //Réalisation d'une prise
    else if(decalageX == 2){

        //test si pion de la prise est noir et que la destination est vide
        //et que la cellule est valide
        //la prise peut s'effectuer
        if((m_damier[x_init-1][y_init-decalageY/2] == couleurOpposant ||
                m_damier[x_init-1][y_init-decalageY/2] == couleurOpposant-1)
                    && m_damier[x_dest][y_dest] == 0){

            m_damier[x_dest][y_dest] = couleur;//destination le pion est blanc
            m_damier[x_init][y_init] = 0;//initial plus de pion
            m_damier[x_init-1][y_init-decalageY/2] = 0; //la prise fonctionne, plus de pion

            //transformation en dame blanche, si on est à la fin du plateau
            if(x_dest == 0)
                m_damier[x_dest][y_dest] += couleur;

            return true;
         }

         else
            return false;
        }

    //deplacement noir de base sur une case vide
    if(decalageX == -1 && (decalageY == 1 || decalageY == -1)){

        //On verifié que la case destination est vide
        if(m_damier[x_dest][y_dest] == 0 && couleur != 1){
            m_damier[x_dest][y_dest] = couleur;//On place le pion noir à sa destination
            m_damier[x_init][y_init] = 0;//On le supprime de sa position initiale

            //transformation en dame noir, si on est à la fin du plateau
            if(x_dest == 9)
                m_damier[x_dest][y_dest] += couleur;

            return true;
         }

         //Si elle n'est pas vide, le déplacement est impossible
         else
            return false;
        }

     else if(decalageX == -2){

        //test si pion de la prise est blanc, que la destination est vide
        //et que la cellule est valide
        //la prise peut s'effectuer

        if((m_damier[x_init+1][y_init-decalageY/2] == couleurOpposant ||
                m_damier[x_init+1][y_init-decalageY/2] == couleurOpposant+1)
                    && m_damier[x_dest][y_dest] == 0){

            m_damier[x_dest][y_dest] = couleur;//destination le pion est blanc
            m_damier[x_init][y_init] = 0;//initial plus de pion
            m_damier[x_init+1][y_init-decalageY/2] = 0; //la prise fonctionne, plus de pion

            //transformation en dame noir, si on est à la fin du plateau
            if(x_dest == 9)
                m_damier[x_dest][y_dest] += couleur;

            return true;
         }

         else
            return false;
        }

    return false;
}

bool Plateau::deplacementDame(int x_init, int y_init,
                              int x_dest, int y_dest, int couleur){

    //Si un pion est selectionné, ce n'est pas une dame
    //donc c'est l'autre méthode qui agira
    if(couleur == 1 || couleur == -1)
        return false;

    //si on clique deux fois sur la même case pas de deplacement
    //ou sur une case invalide
    if(m_damier[x_init][y_init] == m_damier[x_dest][y_dest]
            || !caseValide(x_dest,y_dest))
        return false;

    //couleur opposant
    int couleurOpposant = couleur*(-1);

    //compteur pion ennemi
    int compteurEnnemi = 0;

    //si decalageX positif, deplacement bas vers haut
    int decalageX = x_init - x_dest; //inversement si decalageX negatif

    //si decalage Y positif, deplacement gauche vers droite
    int decalageY = y_init - y_dest; //inversement si decalageY negatif

    //Deplacement dame
    //dans le cas d'une diagonale haut gauche
    if(decalageX > 0 && decalageY == decalageX){

        //On réalise un test sur la diagonale
        for(int i=1; i<decalageX; i++){

            //si il y'a un pion de la même couleur que nous
            //le deplacement n'est pas possible
            //on ne peut pas sauter au dessus d'un pion allié
            if(m_damier[x_init-i][y_init-i] == couleur
                    || m_damier[x_init-i][y_init-i] == couleur/2){
                return false;
            }

            //s'il y'a un pion de la couleur adversaire
            //on compte le nombre d'ennemi sur la ligne
            else if(m_damier[x_init-i][y_init-i] == couleurOpposant
                    || m_damier[x_init-i][y_init-i] == couleurOpposant/2){
                compteurEnnemi++;
            }
        }

        //on ne peut pas sauter au dessus de plusieurs ennemi en même temps
        //On vérifie qu'il n'y a pas plus d'un ennemi
        //et que la case destination est vide
        if(compteurEnnemi < 2 && m_damier[x_dest][y_dest] == 0){

            //nous mettons l'ensemble des cases de la case initial
            //jusqu'a la case destination à 0
            for(int i=0; i<decalageX; i++){
                m_damier[x_init-i][y_init-i] = 0;
            }

            m_damier[x_dest][y_dest] = couleur;//on déplace la dame à sa destination

            return true;
        }

        //sinon, le déplacement n'est pas possible
        else
            return false;

    }

    //cas d'une diagonale haut droite
    else if(decalageX > 0 && decalageY == -decalageX){

        //On réalise un test sur la diagonale
        for(int i=1; i<decalageX; i++){

            //si il y'a un pion de la même couleur que nous
            //le deplacement n'est pas possible
            //on ne peut pas sauter au dessus d'un pion allié
            if(m_damier[x_init-i][y_init+i] == couleur
                    || m_damier[x_init-i][y_init+i] == couleur/2){
                return false;
            }

            //s'il y'a un pion de la couleur adversaire
            //on compte le nombre d'ennemi sur la ligne
            else if(m_damier[x_init-i][y_init+i] == couleurOpposant
                    || m_damier[x_init-i][y_init+i] == couleurOpposant/2){
                compteurEnnemi++;
            }
        }

        //on ne peut pas sauter au dessus de plusieurs ennemi en même temps
        //On vérifie qu'il n'y a pas plus d'un ennemi
        //et que la case destination est vide
        if(compteurEnnemi < 2 && m_damier[x_dest][y_dest] == 0){

            //nous mettons l'ensemble des cases de la case initial
            //jusqu'a la case destination à 0
            for(int i=0; i<decalageX; i++){
                m_damier[x_init-i][y_init+i] = 0;
            }

            m_damier[x_dest][y_dest] = couleur;//on déplace la dame à sa destination

            return true;
        }

        //sinon, le déplacement n'est pas possible
        else
            return false;
    }

    //cas diagonale bas droite
    else if(decalageX < 0 && decalageY == decalageX){

        //On réalise un test sur la diagonale
        for(int i=-1; i>decalageX; i--){

            //si il y'a un pion de la même couleur que nous
            //le deplacement n'est pas possible
            //on ne peut pas sauter au dessus d'un pion allié
            if(m_damier[x_init-i][y_init-i] == couleur
                    || m_damier[x_init-i][y_init-i] == couleur/2){
                return false;
            }

            //s'il y'a un pion de la couleur adversaire
            //on compte le nombre d'ennemi sur la ligne
            else if(m_damier[x_init-i][y_init-i] == couleurOpposant
                    || m_damier[x_init-i][y_init-i] == couleurOpposant/2){
                compteurEnnemi++;
            }
        }

        //on ne peut pas sauter au dessus de plusieurs ennemi en même temps
        //On vérifie qu'il n'y a pas plus d'un ennemi
        //et que la case destination est vide
        if(compteurEnnemi < 2 && m_damier[x_dest][y_dest] == 0){

            //nous mettons l'ensemble des cases de la case initial
            //jusqu'a la case destination à 0
            for(int i=0; i>decalageX; i--){
                m_damier[x_init-i][y_init-i] = 0;
            }

            m_damier[x_dest][y_dest] = couleur;//on déplace la dame à sa destination

            return true;
        }

        //sinon, le déplacement n'est pas possible
        else
            return false;
    }

    //cas diagonale bas gauche
    else if(decalageX <0 && decalageY == -decalageX){

        //On réalise un test sur la diagonale
        for(int i=-1; i>decalageX; i--){

            //si il y'a un pion de la même couleur que nous
            //le deplacement n'est pas possible
            //on ne peut pas sauter au dessus d'un pion allié
            if(m_damier[x_init-i][y_init+i] == couleur
                    || m_damier[x_init-i][y_init+i] == couleur/2){
                return false;
            }

            //s'il y'a un pion de la couleur adversaire
            //on compte le nombre d'ennemi sur la ligne
            else if(m_damier[x_init-i][y_init+i] == couleurOpposant
                    || m_damier[x_init-i][y_init+i] == couleurOpposant/2){
                compteurEnnemi++;
            }
        }

        //on ne peut pas sauter au dessus de plusieurs ennemi en même temps
        //On vérifie qu'il n'y a pas plus d'un ennemi
        //et que la case destination est vide
        if(compteurEnnemi < 2 && m_damier[x_dest][y_dest] == 0){

            //nous mettons l'ensemble des cases de la case initial
            //jusqu'a la case destination à 0
            for(int i=0; i>decalageX; i--){
                m_damier[x_init-i][y_init+i] = 0;
            }

            m_damier[x_dest][y_dest] = couleur;//on déplace la dame à sa destination

            return true;
        }

        //sinon, le déplacement n'est pas possible
        else
            return false;
    }

    //si la dame ne se déplace pas sur sa diagonale
    //le déplacement est invalide
    else
        return false;

    return false;
}


//true, si la case selectionné est valide
//les pions se trouvant uniquement sur les cases noirs
//et dans le damier
bool Plateau::caseValide (int x, int y){

    //cas des lignes paire
    if(x%2 == 0 && y%2 == 1
            && x>=0 && x<10 && y>=0 && y<10)
        return true;

    //cas des lignes impaires
    else if(x%2 == 1 && y%2 == 0
            && x>=0 && x<10 && y>=0 && y<10)
        return true;

    return false; //renvoie 0 si la case n'est pas valide
}



//victoire si l'opposant n'a plus de pion à jouer
int Plateau::victoire(){
    int nbPionsBlanc = 0;
    int nbPionsNoir = 0;

    for(int x = 0; x<10; x++){
        for(int y = 0; y<10; y++){
           if(m_damier[x][y] == 1 || m_damier[x][y] ==2)
               nbPionsBlanc++;

           if(m_damier[x][y] == -1 || m_damier[x][y] == -2)
               nbPionsNoir++;
        }
    }

    //Les blanc gagnent on renvoie 1
    if(nbPionsNoir == 0 && nbPionsBlanc != 0)
        return 1;

    //Les noir gagnent on renvoie 2
    if(nbPionsBlanc == 0 && nbPionsNoir !=0)
        return 2;

    //Personne n'a encore gagné
    else
        return 0;

}
