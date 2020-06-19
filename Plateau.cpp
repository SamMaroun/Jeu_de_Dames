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
             std::cout << m_damier[x][y];
         }
     }
}

int Plateau::getDamier(int x,int y) const{
    return m_damier[x][y];
}

//true si le déplacement est possible
bool Plateau::deplacementPion(int x_init, int y_init,int x_dest, int y_dest){ //Retourne 0 si le tour c'est bien passé, 1 sinon

    if(m_damier[x_init][y_init] == m_damier[x_dest][y_dest])
        return false;

    int decalageX = x_init - x_dest;
    int decalageY = y_init - y_dest;

    /*if(m_damier[pos_x][pos_y]==m_damier[pos_x_dest][pos_y_dest]){ //On test si on mange un allié
        std::cout<< "On ne mange pas nos alliés"<< std::endl;
        return false;
    }

    if(m_damier[pos_x][pos_y]!=m_damier[pos_x_dest][pos_y_dest]){ //On veut manger un ennemi

           int decalageX = pos_x - pos_x_dest; //stock la direction de manger
           int decalageY = pos_y- pos_y_dest;


           if(m_damier[pos_x_dest - decalageX][pos_y_dest - decalageY]==0){ //Mange un pion ennemi
                   m_damier[pos_x_dest][pos_y_dest]=0;
                   m_damier[pos_x_dest - decalageX][pos_y_dest - decalageY]=m_damier[pos_x][pos_y];


                   if(m_damier[pos_x][pos_y]==1 && pos_y_dest - decalageY==0){// Création dame après avoir mangé
                       m_damier[pos_x_dest - decalageX][pos_y_dest - decalageY]=2;
                   }
                   if(m_damier[pos_x][pos_y]==-1 && pos_y_dest - decalageY==9){// Création dame après avoir mangé
                       m_damier[pos_x_dest - decalageX][pos_y_dest - decalageY]=-2;
                   }

                   m_damier[pos_x][pos_y]=0;
                   return true;
           }

           if(m_damier[pos_x_dest - decalageX][pos_y_dest - decalageY]!=0){
               std::cout<<"Il n'y a pas de place après le pion que tu veux manger."<<std::endl;
                return false;
           }

    }

    if(m_damier[pos_x_dest][pos_y_dest]==0){ //On se deplace sur un 0
       m_damier[pos_x_dest][pos_y_dest]=m_damier[pos_x][pos_y];

       if(m_damier[pos_x][pos_y]==1 && pos_y_dest==0)// Creation dame apres avoir mange
           m_damier[pos_x_dest][pos_y_dest]=2;


       if(m_damier[pos_x][pos_y]==-1 && pos_y_dest==9)//Creation dame aprs avoir mang
           m_damier[pos_x_dest ][pos_y_dest]=-2;

       m_damier[pos_x][pos_y]=0;

       return true;
    }
    return false;*/
}

/*
bool Plateau::deplacementDame(int pos_x, int pos_y,int pos_x_dest, int pos_y_dest){

}
*/

//WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
int Plateau::victoire(){
    int nbPionsBlanc = 0;
    int nbPionsNoir = 0;

    for(int x = 0; x<10; x++){
        for(int y = 0; y<10; y++){
           if(m_damier[x][y] == 1 || m_damier[x][y] ==2)
               nbPionsBlanc++;

           if(m_damier[x][y] == -1 || m_damier[x][y] == -2)
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
