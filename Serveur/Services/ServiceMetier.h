#pragma once
using namespace std;
#include "utilisateur.h"
#include <iostream>
#include "Patient.h"
#include "Client_Medecin.h"
#include "Entreprise.h"

class ServiceMetier
{
public:
	//Méthode de connexion/déconection (déconexion peut être pas utile)
	Patient ConnecterPatient(string mail, string mdp);
	Client_Medecin ConnecterMedecin(string mail, string mdp);
	Entreprise ConnecterEntreprise(string mail, string mdp);
	int SeDeconnecter();

	//Méthodes d'ajouts/suppressions d'utilisateurs à la BDD
	int AjouterPatient(Patient patient, string mdp);
	int AjouterClient_Medecin(Client_Medecin medecin, string mdp);
	int AjouterEntreprise(Entreprise entreprise, string mdp);
	int SupprimerComptePatient(long idCompte);
	int SupprimerCompteMedecin(long idCompte);

	//Méthodes liées aux patients
	int RecupererListeAnalyses(int id, vector<string> &nom, vector<int> &risque);
	string RecupererGenome(Patient patient);
	int AjouterAnalyse(Patient patient, vector<string> nom, vector<int> risque);
	vector <Patient> RecherchePatient(string motClef);
	Patient ConsulterProfilPatient(long id);
	vector<Patient> GetAllPatients();

	//Méthodes dictionnaires
	vector <string> AfficherListeDictionnaire();
	int AjouterDictionnaire(string nom, string chemin);
	int ModifierDicoNom(string nom, int id);
	int ModifierDicoPath(string path, int id);
	int supprimerDictionnaire(int id_c);

	//Méthodes analyses
	int RealiserAnalyse(int idPatient, int idDico, string nomMaladie);

	//Constructeur et destructeur
	ServiceMetier();
	~ServiceMetier();
};

