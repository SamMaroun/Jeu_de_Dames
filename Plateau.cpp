/*	AUTHOR:Sam MAROUN & Emile LAVEY
    DATE: 20/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Plateau
*/

#include "Plateau.h"

Plateau::Plateau(){
    //Création d'un plateau

     m_damier=[[ 0,-1, 0,-1, 0,-1, 0,-1, 0,-1],
                [-1, 0,-1, 0,-1, 0,-1, 0,-1, 0],
                [ 0,-1, 0,-1, 0,-1, 0,-1, 0,-1],
                [-1, 0,-1, 0,-1, 0,-1, 0,-1, 0],

                [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],

                [ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
                [ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0],
                [ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
                [ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
                ];
}






int Plateau::deplacementPion(int pos_x, int pos_y,int pos_xvoulue, int pos_yvoulue){ //Retourne 0 si le tour c'est bien passé, 1 sinon

    if(m_damier[pos_x][pos_y]==m_damier[pos_xvoulue][pos_yvoulue]){ //On test si on mange un allié
        std::cout<< "On ne mange pas nos alliés"<< std::endl;
        return 1;
    }

    if(m_damier[pos_x][pos_y]!=m_damier[pos_xvoulue][pos_yvoulue]){ //On veut manger un ennemi

           int decalageX = pos_x - pos_xvoulue; //stock la direction de manger
           int decalageY = pos_y- pos_yvoulue;

           if(m_damier[pos_xvoulue - decalageX][pos_yvoulue - decalageY]==0){ //Mange un pion ennemi
                   m_damier[pos_xvoulue][pos_yvoulue]=0;
                   m_damier[pos_xvoulue - decalageX][pos_yvoulue - decalageY]=m_damier[pos_x][pos_y];


                   if(m_damier[pos_x][pos_y]==1 && pos_yvoulue - decalageY==0){// Création dame après avoir mangé
                       m_damier[pos_xvoulue - decalageX][pos_yvoulue - decalageY]=2;
                   }
                   if(m_damier[pos_x][pos_y]==-1 && pos_yvoulue - decalageY==9){// Création dame après avoir mangé
                       m_damier[pos_xvoulue - decalageX][pos_yvoulue - decalageY]=-2;
                   }

                   m_damier[pos_x][pos_y]=0;
                   return 0;
           }

           if(m_damier[pos_xvoulue - decalageX][pos_yvoulue - decalageY]!=0){
               std::cout<<"Il n'y a pas de place après le pion que tu veux manger."<<std::endl;
                return 1;
           }

    }

    if(m_damier[pos_xvoulue][pos_yvoulue]==0){ //On se déplace sur un 0
       m_damier[pos_xvoulue][pos_yvoulue]=m_damier[pos_x][pos_y];

       if(m_damier[pos_x][pos_y]==1 && pos_yvoulue==0){// Création dame après avoir mangé
           m_damier[pos_xvoulue][pos_yvoulue]=2;}

       if(m_damier[pos_x][pos_y]==-1 && pos_yvoulue==9){// Création dame après avoir mangé
           m_damier[pos_xvoulue ][pos_yvoulue]=-2;}

           m_damier[pos_x][pos_y]=0;


       return 0;
    }
}











//int Plateau::deplacementDame(int pos_x, int pos_y,int pos_xvoulue, int pos_yvoulue){

//}



int Plateau::victoire(){
    int nbPionsBlanc = 0;
    int nbPionsNoir = 0;

    for(int i_y = 0; i_y<10; i_y++){
        for(int i_x = 0; i_x<10; i_x++){
           if(m_damier[i_x][i_y] == 1 || m_damier[i_x][i_y] ==2)
               nbPionsBlanc++;

           if(m_damier[i_x][i_y] == -1 || m_damier[i_x][i_y] == -2)
               nbPionsBlanc++;
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




















/*    //Placement des noirs impaire
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

} */
