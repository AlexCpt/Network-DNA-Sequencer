#include "stdafx.h"
#include "Database.h"

// database implementation inspired by https://dcravey.wordpress.com/2011/03/21/using-sqlite-in-a-visual-c-application/

Database::Database()
{
}

Database::~Database()
{
}

sqlite3 * Database::get_database()
{
	return database;
}

int Database::open_database()
{
	int code;

	code = sqlite3_open(database_name, &database);
	
	if (code != 0)
	{
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(database) << endl;
		AfxMessageBox(_T("Echec"));
		sqlite3_close(database);
	}

	return code;
}

int Database::close_database()
{
	sqlite3_close(database);

	return 0;
}

int Database::create_tables()
{
	int code;
	char *error;

	const char *CTEntreprise = "CREATE TABLE Entreprise (id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING, prenom STRING, mail STRING, mdp STRING);";
	code = sqlite3_exec(database, CTEntreprise, NULL, NULL, &error);
	if (code != 0)
	{
		cerr << "Error creating Table Entreprise: " << sqlite3_errmsg(database) << endl;
		AfxMessageBox(_T("Echec"));
		sqlite3_free(error);
		return 1;
	}

	const char *CTPatient = "CREATE TABLE Patient (id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING, prenom STRING, mail STRING, mdp STRING, dateNaissance STRING, genome STRING);";
	code = sqlite3_exec(database, CTPatient, NULL, NULL, &error);
	if (code != 0)
	{
		cerr << "Error creating Table Patient: " << sqlite3_errmsg(database) << endl;
		AfxMessageBox(_T("Echec"));
		sqlite3_free(error);
		return 1;
	}

	const char *CTMedecin = "CREATE TABLE Medecin (id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING, prenom STRING, mail STRING, mdp STRING);";
	code = sqlite3_exec(database, CTMedecin, NULL, NULL, &error);
	if (code != 0)
	{
		cerr << "Error creating Table Medecin: " << sqlite3_errmsg(database) << endl;
		AfxMessageBox(_T("Echec"));
		sqlite3_free(error);
		return 1;
	}

	const char *CTDictionnaire = "CREATE TABLE Dictionnaire (id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING, chemin STRING);";
	code = sqlite3_exec(database, CTDictionnaire, NULL, NULL, &error);
	if (code != 0)
	{
		cerr << "Error creating Table Dictionnaire: " << sqlite3_errmsg(database) << endl;
		AfxMessageBox(_T("Echec"));
		sqlite3_free(error);
		return 1;
	}

	const char *CTAnalyse = "CREATE TABLE Analyse (id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING, risque INTEGER, idClient INTEGER);";
	code = sqlite3_exec(database, CTAnalyse, NULL, NULL, &error);
	if (code != 0)
	{
		cerr << "Error creating Table Dictionnaire: " << sqlite3_errmsg(database) << endl;
		AfxMessageBox(_T("Echec"));
		sqlite3_free(error);
		return 1;
	}

	return 0;
}