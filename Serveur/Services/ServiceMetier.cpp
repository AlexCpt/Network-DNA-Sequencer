#include "stdafx.h"
#include "ServiceMetier.h"
#include "PatientDAO.h"
#include "MedecinDAO.h"
#include "EntrepriseDAO.h"
#include "DicoDAO.h"
#include "AnalyseDAO.h"
#include <cstring>

//Méthodes permettant la connexion (renvoie l'utilisateur ayant rentré son mail et mdp, null si n'existe pas)
Patient ServiceMetier::ConnecterPatient(string mail, string mdp)
{
	Patient patient;
	PatientDAO pDAO;
	if (pDAO.GetUtilisateurByMail(patient, mail, mdp) != 0)
	{
		return Patient();
	}
	return patient;
}

Client_Medecin ServiceMetier::ConnecterMedecin(string mail, string mdp)
{
	Client_Medecin medecin;
	MedecinDAO mDAO;
	if (mDAO.GetUtilisateurByMail(medecin, mail, mdp) != 0)
	{
		return Client_Medecin();
	}
	return medecin;
}

Entreprise ServiceMetier::ConnecterEntreprise(string mail, string mdp)
{
	Entreprise entreprise;
	EntrepriseDAO eDAO;
	if (eDAO.GetUtilisateurByMail(entreprise, mail, mdp) != 0)
	{
		return Entreprise();
	}
	return entreprise;
}

//A voir si cette méthode est vraiment utile
int ServiceMetier::SeDeconnecter()
{
	cout << "Vous vous êtes déconnecté." << endl;
	return 0;
}

int ServiceMetier::AjouterPatient(Patient patient, string mdp)
{
	//Appel DAO
	PatientDAO pDAO;
	int reussite = pDAO.AddUtilisateur(patient, mdp);
	if (reussite == 0)
	{
		return 0;
	}
	return 1;
}

int ServiceMetier::AjouterClient_Medecin(Client_Medecin medecin, string mdp)
{
	//Appel DAO
	AfxMessageBox(_T("Ca passe la (bd)"));
	MedecinDAO mDAO;
	int reussite = mDAO.AddUtilisateur(medecin, mdp);
	if (reussite == 0)
	{
		AfxMessageBox(_T("success"));
		return 0;
	}
	AfxMessageBox(_T("echec"));
	return 1;
}

int ServiceMetier::AjouterEntreprise(Entreprise entreprise, string mdp)
{
	//Appel DAO
	EntrepriseDAO eDAO;
	int reussite = eDAO.AddUtilisateur(entreprise, mdp);
	if (reussite == 0)
	{
		return 0;
	}
	return 1;
}

int ServiceMetier::SupprimerComptePatient(long idCompte)
{
	//Appel DAO
	PatientDAO pDAO;
	Patient patient;
	int reussite = pDAO.GetUtilisateurById(patient, idCompte);
	if (reussite == 0)
	{
		reussite = pDAO.DeleteUtilisateur(patient);
		if (reussite == 0)
		{
			return 0;
		}
	}
	return 1;
}

int ServiceMetier::SupprimerCompteMedecin(long idCompte)
{
	//Appel DAO
	MedecinDAO mDAO;
	Client_Medecin medecin;
	int reussite = mDAO.GetUtilisateurById(medecin, idCompte);
	if (reussite == 0)
	{
		reussite = mDAO.DeleteUtilisateur(medecin);
		if (reussite == 0)
		{
			return 0;
		}
	}
	return 1;
}

//Permet de récupérer toutes les analyses d'un patient (pour affichage sur IHM)
int ServiceMetier::RecupererListeAnalyses(int id, vector<string> &nom, vector<int> &risque)
{
	AnalyseDAO aDAO;
	int reussi = aDAO.GetAnalyseByIdClient(nom, risque, id);
	if (reussi == 0)
	{
		return 0;
	}
	return 1;
}

//Renvoie le génome du patient pour consultation (affichage sur IHM)
string ServiceMetier::RecupererGenome(Patient patient)
{
	return patient.GetGenome();
}

//Permet de mettre l'analyse tout juste réalisée dans le profil du patient
int ServiceMetier::AjouterAnalyse(Patient patient, vector<string> nom, vector<int> risque)
{
	AnalyseDAO aDAO;
	for(unsigned int i=0; i<nom.size();i++)
	{
		int reussi = aDAO.AddAnalyse(nom[i], risque[i], patient.GetId());
		if (reussi != 0)
		{
			return 1;
		}
	}
	return 0;
}

//Permet de recherher un patient dans la BDD à partir d'un mot clef, à faire avec les classes DAO
vector<Patient> ServiceMetier::RecherchePatient(string nom)
{
	//Appel DAO
	//vector<Patient> patients = PatientDAO.findByName(nom);
	return vector<Patient>();
}

//Renvoie un patient à partir de son id, DAO à faire
Patient ServiceMetier::ConsulterProfilPatient(long id)
{
	//Appel DAO
	PatientDAO pDAO;
	Patient patient;
	int reussite = pDAO.GetUtilisateurById(patient,id);
	if (reussite == 0)
	{
		return patient;
	}
	return Patient();
}

vector<Patient> ServiceMetier::GetAllPatients()
{
	PatientDAO pDAO;
	vector<Patient> patients;
	pDAO.GetAllUtilisateurs(patients);
	return patients;
}

//Renvoie tous les noms de dictionnaire
vector<string> ServiceMetier::AfficherListeDictionnaire()
{
	//Appel DAO
	DicoDAO dDAO;
	vector <string> dico;
	int reussi = dDAO.GetAllDico(dico);
	if(reussi==0)
	{ 
		return dico;
	}
	return vector<string>();
}

int ServiceMetier::AjouterDictionnaire(string nom, string chemin)
{
	DicoDAO dDao;
	int reussi = dDao.AddDico(nom, chemin);
	if (reussi == 0)
	{
		return 0;
	}
	return 1;
}

int ServiceMetier::ModifierDicoNom(string nom, int id)
{
	DicoDAO dDao;
	int reussi = dDao.changeDicoName(id,nom);
	if (reussi == 0)
	{
		return 0;
	}
	return 1;
}

int ServiceMetier::ModifierDicoPath(string path, int id)
{
	DicoDAO dDao;
	int reussi = dDao.changeDicoPath(id, path);
	if (reussi == 0)
	{
		return 0;
	}
	return 1;
}

int ServiceMetier::supprimerDictionnaire(int id_c)
{
	DicoDAO dDao;
	int reussi = dDao.DeleteDico(id_c);
	if (reussi == 0)
	{
		return 0;
	}
	return 1;
}

int ServiceMetier::RealiserAnalyse(int idPatient, int idDico, string nomMaladie)
{
	PatientDAO pDAO;
	Patient patient;
	int reussitePatient = pDAO.GetUtilisateurById(patient, idPatient);
	DicoDAO dDAO;
	string dicoPath;
	string dico;
	int reussiteDico = dDAO.GetDicoById(dico, dicoPath, idDico);
	if (reussitePatient == 0 && reussiteDico == 0)
	{
		string genomePath = patient.GetGenome();
		AnalyseDAO aDAO;
		int resAnalyse = aDAO.faireAnalyse(genomePath, dicoPath, nomMaladie);
		aDAO.AddAnalyse(nomMaladie, resAnalyse, idPatient);
		return resAnalyse;
	}
	return -1;
}

ServiceMetier::ServiceMetier()
{
}


ServiceMetier::~ServiceMetier()
{
}
