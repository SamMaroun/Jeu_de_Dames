//20-05-2020
//Création:Emile LAVEY

#ifndef _PION_H
#define _PION_H


class Pion
{

private:
    bool m_couleur; //false=Noir, true=Blanc
    bool m_estDame; //false=pion normal, true=dame
    bool m_estMort; //false=vivant, true=mort

public:
    //On initialise tous les pions à blanc, non dame et tous mort
    Pion(bool couleur=true, bool estDame=false, bool estMort=true);

//GETTERS
    bool getCouleur();
	bool getEstDame();
	bool getEstMort();

//SETTERS
    void setCouleur(bool couleur);
	void setEstDame(bool estDame);
	void setEstMort(bool estMort);

};
#endif
