#pragma once

#include <iostream>
#include <string>
#include "utilisateurDA.h"
#include "Client_Medecin.h"
#include "sqlite3.h"

using namespace std;

class MedecinDAO : public UtilisateurDA
{

public:
	MedecinDAO();
	~MedecinDAO();

	int AddUtilisateur(Client_Medecin User, string mdp);
	int GetUtilisateurById(Client_Medecin &User, int id_in);
	int GetUtilisateurByMail(Client_Medecin &User, string mail, string mdp);
	int DeleteUtilisateur(Client_Medecin User);
};
