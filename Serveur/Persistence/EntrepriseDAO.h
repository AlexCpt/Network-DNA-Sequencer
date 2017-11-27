#pragma once
#include <iostream>
#include <string>
#include "UtilisateurDA.h"
#include "Entreprise.h"
#include "sqlite3.h"

using namespace std;
class EntrepriseDAO : public UtilisateurDA
{
public:
	EntrepriseDAO();
	~EntrepriseDAO();

	int AddUtilisateur(Entreprise company, string mdp);
	int GetUtilisateurById(Entreprise &company, int id_in);
	int GetUtilisateurByMail(Entreprise &User, string mail, string mdp);
	int DeleteUtilisateurById(Entreprise company);
};

