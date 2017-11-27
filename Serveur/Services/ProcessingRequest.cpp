#include "stdafx.h"
#include "ProcessingRequest.h"
#include <string>
#include "ServiceMetier.h"
#include "Patient.h"
#include <vector>
#include <numeric>
#include <iostream>
#include <iterator>
#include <sstream>
#include <conio.h>
using namespace std;

ProcessingRequest::ProcessingRequest()
{
}

ProcessingRequest::~ProcessingRequest()
{
}

string ProcessingRequest::getManager(string request)
{
	_cprintf("yo\n");
	istringstream iss(request);
	vector<string> tokens{ istream_iterator<string>{iss},
		istream_iterator<string>{} };
	string requestType = tokens[0];
	string reponse = "";
	ServiceMetier * service = new ServiceMetier();
	static utilisateur user;

	if (requestType == "lancerAnalyse")
	{
		if (user.GetId() == -1)
		{
			reponse = "Requete non autorisée.";
		}
		else
		{
			Patient patient = service->ConsulterProfilPatient(stol(tokens[1]));
			int resultatAnalyse = service->RealiserAnalyse(stol(tokens[1]), stol(tokens[2]), tokens[3]);
			if (resultatAnalyse == 1)
			{
				reponse = "Patient malade !";
			}
			else if (resultatAnalyse == 0)
			{
				reponse = "Patient sain.";
			}
			else
			{
				reponse = "Echec de l'analyse.";
			}
		}
	}
	else if (requestType == "connexionClient")
	{
		if (user.GetId() == -1)
		{
			string mail = tokens[1];
			string mdp = tokens[2];
			Patient patient = service->ConnecterPatient(mail, mdp);
			if (patient.GetId() == -1)
			{
				reponse = "Echec de la connexion, vérifiez votre mail / mot de passe";
			}
			else
			{
				reponse = "Bienvenue " + patient.GetPrenom();
				// Ajouter client à la session
				user = patient;
			}
		}
		else
		{
			reponse = "Un utilisateur est déjà connecté.";
		}

	}

	else if (requestType == "connexionMedecin")
	{
		if (user.GetId() == -1)
		{
			string mail = request.substr(request.find(" ") + 1, request.find_last_of(" ") - (request.find(" ") + 1));
			string mdp = request.substr(request.find_last_of(" ") + 1);
			Client_Medecin medecin = service->ConnecterMedecin(mail, mdp);
			if (medecin.GetId() == -1)
			{
				reponse = "Echec de la connexion, vérifiez votre mail / mot de passe";
			}
			else
			{
				reponse = "Bienvenue " + medecin.GetPrenom();
				// Ajouter medecin à la session
				user = medecin;
			}
		}
		else
		{
			reponse = "Un utilisateur est déjà connecté.";
		}
	}
	else if (requestType == "connexionEntreprise")
	{
		if (user.GetId() == -1)
		{
			string mail = request.substr(request.find(" ") + 1, request.find_last_of(" ") - (request.find(" ") + 1));
			string mdp = request.substr(request.find_last_of(" ") + 1);
			Entreprise entreprise = service->ConnecterEntreprise(mail, mdp);
			if (entreprise.GetId() == -1)
			{
				reponse = "Echec de la connexion, vérifiez votre mail / mot de passe";
			}
			else
			{
				reponse = "Bienvenue " + entreprise.GetPrenom();
				// Ajouter entreprise à la session
				user = entreprise;
			}
		}
		else
		{
			reponse = "Un utilisateur est déjà connecté.";
		}
	}

	else if (requestType == "deconnexion")
	{
		if (user.GetId() == -1)
		{
			reponse = "Vous n'êtes pas connecté.";
		}
		else
		{
			utilisateur disconnected;
			user = disconnected;
			reponse = "Déconnexion ...";
		}

	}

	else if (requestType == "afficherAllDico")
	{
		if (user.GetId() == -1)
		{
			reponse = "requete non authorisée.";
		}
		else
		{
			vector<string> listeDicos = service->AfficherListeDictionnaire();
			for (int i = 0; i < listeDicos.size(); i++)
			{
				reponse += "id : "+to_string(i+1)+"   Nom: " +listeDicos[i] +"\r\n";
			}
		}
	}

	else if (requestType == "modDico")
	{
		if (user.GetId() == -1)
		{
			reponse = "requete non authorisée.";
		}
		else
		{
			int reussi = 0;
			if (tokens[2] == "nom")
			{
				reussi = service->ModifierDicoNom(tokens[3], stoi(tokens[1]));
			}
			else if (tokens[2] == "path")
			{
				reussi = service->ModifierDicoPath(tokens[3], stoi(tokens[1]));
			}
			if (reussi == 0)
			{
				reponse = "Reussite de la modification";
			}
			else
			{
				reponse = "Echec de la modification";
			}
		}
	}

	else if (requestType == "ajoutDico")
	{
		if (user.GetId() == -1)
		{
			reponse = "requete non authorisée.";
		}
		else
		{
			int reussite = service->AjouterDictionnaire(tokens[1], tokens[2]);
			if (reussite == 0)
			{
				reponse = "Reussite de l'ajout du dictionnaire";
			}
			else
			{
				reponse = "Echec de l'ajout du dictionnaire";
			}
		}
	}

	else if (requestType == "supprimerDico")
	{
		if (user.GetId() == -1)
		{
			reponse = "requete non authorisée.";
		}
		else
		{
			int reussite = service->supprimerDictionnaire(stol(tokens[1]));
			if (reussite == 0)
			{
				reponse = "Reussite de la suppression du dico";
			}
			else
			{
				reponse = "Echec de la suppression du dico";
			}
		}
	}

	//Manque le service métier
	else if (requestType == "afficherDico")
	{

	}

	else if (requestType == "nouveauEntreprise")
	{
		Entreprise newEntreprise = Entreprise(tokens[2], tokens[1], tokens[3], tokens[4]);
		int reussi = service->AjouterEntreprise(newEntreprise, tokens[4]);

		if (reussi == 0)
		{
			reponse = "Reussite de la création de l'entreprise";
		}
		else
		{
			reponse = "Echec de la création de l'entreprise";
		}
	}

	else if (requestType == "nouveauMedecin")
	{
		Client_Medecin newMedecin = Client_Medecin(tokens[2], tokens[1], tokens[3], tokens[4]);
		int reussi = service->AjouterClient_Medecin(newMedecin, tokens[4]);

		if (reussi == 0)
		{
			reponse = "Reussite de la création du médecin";
		}
		else
		{
			reponse = "Echec de la création du médecin";
		}
	}

	else if (requestType == "supprimerMedecin")
	{
		int reussite = service->SupprimerCompteMedecin(stol(tokens[1]));
		if (reussite == 0)
		{
			reponse = "Reussite de la suppression du médecin";
		}
		else
		{
			reponse = "Echec de la suppression du médecin";
		}
	}

	else if (requestType == "afficherAllPatient")
	{
		if (user.GetId() == -1)
		{
			reponse = "Requete non autorisée.";
		}
		else
		{
			vector<Patient> listePatients = service->GetAllPatients();
			for (int i = 0; i < listePatients.size(); i++)
			{
				reponse += "id : " + to_string(listePatients[i].GetId()) + " -  Nom : " + listePatients[i].GetNom() + "  -  Prenom : " + listePatients[i].GetPrenom() + "\r\n";
			}
		}
	}

	else if (requestType == "nouveauPatient")
	{
		if (user.GetId() == -1)
		{
			reponse = "Requete non autorisée.";
		}
		else
		{
			Patient newPatient = Patient(tokens[2], tokens[1], tokens[3], tokens[4], tokens[5], tokens[6]);
			int reussi = service->AjouterPatient(newPatient, tokens[4]);

			if (reussi == 0)
			{
				reponse = "Reussite de la création du patient";
			}
			else
			{
				reponse = "Echec de la création du patient";
			}
		}
	}

	else if (requestType == "supprimerPatient")
	{
		if (user.GetId() == -1)
		{
			reponse = "Requete non autorisée.";
		}
		else
		{
			int reussite = service->SupprimerComptePatient(stol(tokens[1]));
			if (reussite == 0)
			{
				reponse = "Reussite de la suppression du patient.";
			}
			else
			{
				reponse = "Echec de la suppression du patient.";
			}
		}
	}

	else if (requestType == "afficherPatient")
	{
		if (user.GetId() == -1)
		{
			reponse = "Requete non autorisée.";
		}
		else
		{
			Patient patient = service->ConsulterProfilPatient(stol(tokens[1]));
			if (patient.GetId() != -1)
			{
				reponse = "Prénom : " + patient.GetPrenom() + "\r\n"
					+ "Nom : " + patient.GetNom() + "\r\n"
					+ "Mail : " + patient.GetMail() + "\r\n"
					+ "Date de naissance : " + patient.GetdNaissance() + "\r\n";
			}
			else
			{
				reponse = "Aucun patient ne correspond à ces informations.";
			}
		}
	}

	else if (requestType == "afficherAllAnalyse")
	{

		vector <string> maladies;
		vector <int> risques;
		service->RecupererListeAnalyses(stoi(tokens[1]), maladies, risques);

		for (int i = 0; i < maladies.size(); i++)
		{
			reponse += " Maladie : " + maladies[i] + "  -  Positif : " + to_string(risques[i]) + "\n";
		}

	}

	else if (requestType == "afficherGenome")
	{
		Patient patient = service->ConsulterProfilPatient(stoi(tokens[1]));
		reponse = patient.GetGenome();
	}
	//A FINIR
	else if (requestType == "afficherProfil")
	{
		if (user.GetId() == -1)
		{
			reponse = "Vous n'êtes pas connecté.";
		}
		else
		{
			reponse = "Prénom : " + user.GetPrenom() + "\n"
				+ "Nom : " + user.GetNom() + "\n"
				+ "Mail : " + user.GetMail() + "\n";
		}

	}
	else
	{
		reponse = "Votre requête n'a pas été reconnue \r\n";
	}
	return reponse;
}