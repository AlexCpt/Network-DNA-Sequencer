#pragma once

#include <iostream>
#include <string>
#include "UtilisateurDA.h"
#include "Patient.h"

using namespace std;

class PatientDAO : public UtilisateurDA
{

public:
	PatientDAO();
	~PatientDAO();

	int AddUtilisateur(Patient User, string mdp);
	int GetUtilisateurById(Patient &User, int id_in);
	int GetUtilisateurByMail(Patient &User, string mail, string mdp);
	int GetAllUtilisateurs(vector<Patient>& patients);
	int DeleteUtilisateur(Patient User);
};
