#include "stdafx.h"
#include "PatientDAO.h"

PatientDAO::PatientDAO()
{
}

PatientDAO::~PatientDAO()
{
}

int PatientDAO::AddUtilisateur(Patient User, string mdp)
{
	int code;
	char *error;

	string sqlInsertStr = "INSERT INTO Patient (nom, prenom, mail, mdp, dateNaissance, genome) VALUES('"
		+ User.GetNom() + "', '"
		+ User.GetPrenom() + "', '"
		+ User.GetMail() + "', '"
		+ mdp + "', '"
		+ User.GetdNaissance() + "', '"
		+ User.GetGenome()+"');";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_patient): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int PatientDAO::GetUtilisateurById(Patient &User, int id_in)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Patient WHERE id = '" + to_string(id_in) + "';";

	const char *sqlSelect = sqlSelectStr.c_str();

	char **results = NULL;
	int rows, columns;

	code = sqlite3_get_table(database, sqlSelect, &results, &rows, &columns, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 query (read_patient): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}
	else
	{
		User.SetId(stol(results[0 + columns]));
		User.SetNom(results[1 + columns]);
		User.SetPrenom(results[2 + columns]);
		User.SetMail(results[3 + columns]);
		User.SetMdp(results[4 + columns]);
		User.SetdNaissance(results[5 + columns]);
		User.SetGenome(results[6 + columns]);
	}

	sqlite3_free_table(results);

	return code;
}

int PatientDAO::GetUtilisateurByMail(Patient & User, string mail, string mdp)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Patient WHERE mail = '"+ mail +"' AND mdp ='" +mdp+"';";

	const char *sqlSelect = sqlSelectStr.c_str();

	char **results = NULL;
	int rows, columns;

	code = sqlite3_get_table(database, sqlSelect, &results, &rows, &columns, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 query (read_patient): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}
	else
	{
		User.SetId(stol(results[0 + columns]));
		User.SetNom(results[1 + columns]);
		User.SetPrenom(results[2 + columns]);
		User.SetMail(results[3 + columns]);
		User.SetMdp(results[4 + columns]);
		User.SetdNaissance(results[5 + columns]);
		User.SetGenome(results[6 + columns]);
	}

	sqlite3_free_table(results);

	return code;
}

int PatientDAO::GetAllUtilisateurs(vector<Patient>& patients)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Patient;";

	const char *sqlSelect = sqlSelectStr.c_str();

	char **results = NULL;
	int rows, columns;

	code = sqlite3_get_table(database, sqlSelect, &results, &rows, &columns, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 query (read_dico): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}
	else
	{
		for (int i = 0; i < rows*7; i=i+7)
		{
			Patient patient;
			patient.SetId(stol(results[i + columns]));
			patient.SetNom(results[i+1 + columns]);
			patient.SetPrenom(results[i+2 + columns]);
			patient.SetMail(results[i+3 + columns]);
			patient.SetMdp(results[i+4 + columns]);
			patient.SetdNaissance(results[i+5 + columns]);
			patient.SetGenome(results[i+6 + columns]);
			patients.push_back(patient);
		}
	}

	sqlite3_free_table(results);

	return code;
}

int PatientDAO::DeleteUtilisateur(Patient User)
{
	int code;
	char *error;
	string sqlInsertStr = "DELETE FROM Patient WHERE ID = '" + to_string(User.GetId()) + "';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (delete_patient): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}
