#include "stdafx.h"
#include "Patient.h"

//Méthode Get sur le génome
string Patient::GetGenome()
{
	return genome;
}


//Méthode Get sur la liste des analyses du patient
string Patient::GetdNaissance()
{
	return dNaissance;
}

void Patient::SetdNaissance(string dNaissance_c)
{
	dNaissance= dNaissance_c;
}

void Patient::SetGenome(string genome_c)
{
	genome = genome_c;
}

Patient::Patient()
{
}

Patient::Patient(string prenom_c, string nom_c, string mail_c, string mdp_c, string dNaissance_c, string genome_c):utilisateur(prenom_c,nom_c,mail_c, mdp_c)
{
	dNaissance = dNaissance_c;
	genome = genome_c;
}

Patient::~Patient()
{
}


