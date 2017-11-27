#pragma once
#include "utilisateur.h"
#include <string>
#include <vector>
#include <iostream>

class Patient: public utilisateur
{
private:
	string genome;
	string dNaissance;

public:
	//Méthodes Get/Set
	string GetGenome();
	string GetdNaissance();
	void SetdNaissance(string dNaissance_c);
	void SetGenome(string genome_c);

	//Constructeurs et destructeurs
	Patient();
	Patient(string prenom_c, string nom_c, string mail_c, string mdp_c, string dNaissance_c, string genome_c);
	~Patient();
};

