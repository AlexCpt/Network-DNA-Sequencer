#pragma once
#include "utilisateur.h"
#include "Patient.h"
#include <string>
#include <vector>

class Client_Medecin : public utilisateur
{
public:

	//Constructeurs et destructeurs
	Client_Medecin();
	Client_Medecin(string prenom_c, string nom_c, string mail_c, string mdp_c);
	~Client_Medecin();
};

