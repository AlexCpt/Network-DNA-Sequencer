#include "stdafx.h"
#include "MedecinDAO.h"

MedecinDAO::MedecinDAO()
{
}

MedecinDAO::~MedecinDAO()
{
}

int MedecinDAO::AddUtilisateur(Client_Medecin User, string mdp)
{
	int code;
	char *error;
	AfxMessageBox(_T("AddUtilisateur"));

	string sqlInsertStr = "INSERT INTO Medecin (nom, prenom, mail, mdp) VALUES('"
		+ User.GetNom() + "', '"
		+ User.GetPrenom() + "', '"
		+ User.GetMail() + "', '"
		+ mdp + "');";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_medecin): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int MedecinDAO::GetUtilisateurById(Client_Medecin & User, int id_in)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Medecin WHERE id = '" + to_string(id_in) + "';";

	const char *sqlSelect = sqlSelectStr.c_str();

	char **results = NULL;
	int rows, columns;

	code = sqlite3_get_table(database, sqlSelect, &results, &rows, &columns, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 query (read_medecin): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}
	else
	{
		User.SetId(stol(results[0 + columns]));
		User.SetNom(results[1 + columns]);
		User.SetPrenom(results[2 + columns]);
		User.SetMail(results[3 + columns]);
		User.SetMdp(results[4 + columns]);
	}

	sqlite3_free_table(results);

	return code;
}

int MedecinDAO::GetUtilisateurByMail(Client_Medecin & User, string mail, string mdp)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Medecin WHERE mail = '" + mail + "' AND mdp = '" + mdp + "';";

	const char *sqlSelect = sqlSelectStr.c_str();

	char **results = NULL;
	int rows, columns;

	code = sqlite3_get_table(database, sqlSelect, &results, &rows, &columns, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 query (read_medecin): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}
	else
	{
		User.SetId(stol(results[0 + columns]));
		User.SetNom(results[1 + columns]);
		User.SetPrenom(results[2 + columns]);
		User.SetMail(results[3 + columns]);
		User.SetMdp(results[4 + columns]);
	}

	sqlite3_free_table(results);

	return code;
}

int MedecinDAO::DeleteUtilisateur(Client_Medecin User)
{
	int code;
	char *error;
	string sqlInsertStr = "DELETE FROM Medecin WHERE ID = '" + to_string(User.GetId()) + "';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (delete_patient): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}
