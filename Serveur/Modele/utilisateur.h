#pragma once
using namespace std;
#include <string>

class utilisateur
{
private :
	int id;
	string prenom;
	string nom;
	string mail;
	string mdp;

public:
	//Méthodes Get
	int GetId();
	string GetNom();
	string GetPrenom();
	string GetMail();

	void SetNom(string nouveauNom);

	void SetPrenom(string nouveauPrenom);

	void SetMail(string nouveauMail);

	void SetId(int nouvelId);

	void SetMdp(string nouveauMdp);


	//Constructeurs et destructeur
	utilisateur();
	utilisateur(string prenom_c, string nom_c, string mail_c, string mdp_c);

	~utilisateur();
};

