//20-05-2020
//Création:Emile LAVEY

#include "Pion.h"

//CONSTRUCTEUR-----------------------------------------------------
Pion::Pion(bool couleur, bool estDame, bool estMort){
        m_couleur=couleur;
		m_estDame=estDame;
		m_estMort=estMort;
}


//GETTERS---------------------------------------------------------
bool Pion::getCouleur(){
    return m_couleur;
}

bool Pion::getEstDame(){
	return m_estDame;
}

bool Pion::getEstMort(){
	return m_estMort;
}



//SETTERS----------------------------------------------------------
void Pion::setCouleur(bool couleur){
        m_couleur=couleur;
}


void Pion::setEstDame(bool estDame){
	m_estDame=estDame;
}

void Pion::setEstMort(bool estMort){
    m_estMort=estMort;
}
