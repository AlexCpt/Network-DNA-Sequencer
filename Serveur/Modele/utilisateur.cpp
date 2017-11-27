#include "stdafx.h"
#include "utilisateur.h"

//Méthodes Get
int utilisateur::GetId()
{
	return id;
}

string utilisateur::GetNom()
{
	return nom;
}

string utilisateur::GetPrenom()
{
	return prenom;
}

string utilisateur::GetMail()
{
	return mail;
}


void utilisateur::SetNom(string nouveauNom)
{
	nom = nouveauNom;
}

void utilisateur::SetPrenom(string nouveauPrenom)
{
	prenom = nouveauPrenom;
}

void utilisateur::SetMail(string nouveauMail)
{
	mail = nouveauMail;
}

void utilisateur::SetId(int nouvelId)
{
	id = nouvelId;
}

void utilisateur::SetMdp(string nouveauMdp)
{
	mdp = nouveauMdp;
}

//Constructeurs et destructeur
utilisateur::utilisateur()
{
	id = -1;
}

utilisateur::utilisateur(string prenom_c, string nom_c, string mail_c, string mdp_c)
{
	{
		prenom = prenom_c;
		nom = nom_c;
		mail = mail_c;
		mdp = mdp_c;
		id = -1;
	}
}


utilisateur::~utilisateur()
{

}