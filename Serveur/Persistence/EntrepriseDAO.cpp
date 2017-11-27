#include "stdafx.h"
#include "EntrepriseDAO.h"


EntrepriseDAO::EntrepriseDAO()
{
}


EntrepriseDAO::~EntrepriseDAO()
{
}

int EntrepriseDAO::AddUtilisateur(Entreprise company, string mdp)
{
	int code;
	char *error;

	string sqlInsertStr = "INSERT INTO Entreprise (nom, prenom, mail, mdp) VALUES('"
		+ company.GetNom() + "', '"
		+ company.GetPrenom() + "', '"
		+ company.GetMail() + "', '"
		+ mdp + "');";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_company): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int EntrepriseDAO::GetUtilisateurById(Entreprise & company, int id_in)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Entreprise WHERE id = '" + to_string(id_in) + "';";

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
		company.SetId(stol(results[0 + columns]));
		company.SetNom(results[1 + columns]);
		company.SetPrenom(results[2 + columns]);
		company.SetMail(results[3 + columns]);
		company.SetMdp(results[4 + columns]);
	}

	sqlite3_free_table(results);

	return code;
}

int EntrepriseDAO::GetUtilisateurByMail(Entreprise & User, string mail, string mdp)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Entreprise WHERE mail = '" + mail +"' AND mdp = '"+ mdp + "';";

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

int EntrepriseDAO::DeleteUtilisateurById(Entreprise company)
{
	int code;
	char *error;

	string sqlInsertStr = "DELETE FROM Entreprise WHERE ID = '" + to_string(company.GetId()) + "';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (delete_company): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}
