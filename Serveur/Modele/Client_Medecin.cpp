#include "stdafx.h"
#include "Client_Medecin.h"
#include <iostream>

using namespace std;

Client_Medecin::Client_Medecin()
{
}

Client_Medecin::Client_Medecin(string prenom_c, string nom_c, string mail_c, string mdp_c): utilisateur(prenom_c, nom_c,mail_c,mdp_c)
{
}


Client_Medecin::~Client_Medecin()
{
}
