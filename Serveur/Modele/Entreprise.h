#pragma once
#include <string.h>
#include "utilisateur.h"


class Entreprise : public utilisateur
{
public:

	//Constructeurs et destructeur
	Entreprise();
	Entreprise(string prenom_c, string nom_c, string mail_c, string mdp_c);
	~Entreprise();
};

