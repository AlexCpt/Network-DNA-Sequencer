#include "stdafx.h"
#include "DicoDAO.h"


DicoDAO::DicoDAO()
{
	Database db;
	db.open_database();
	database = db.get_database();
}


DicoDAO::~DicoDAO()
{
}


void DicoDAO::SetDatabase(sqlite3 * database_in)
{
	database = database_in;
}

int DicoDAO::AddDico(string nomDico, string chemin)
{
	int code;
	char *error;

	string sqlInsertStr = "INSERT INTO Dictionnaire (nom, chemin) VALUES('"+ nomDico +"', '"+chemin+ "');";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_dico): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int DicoDAO::GetDicoById(string & dico, string & chemin, int id_in)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT * FROM Dictionnaire WHERE id = '" + to_string(id_in) + "';";

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
		dico = results[1 + columns];
		chemin = results[2 + columns];
	}

	sqlite3_free_table(results);

	return code;
}

int DicoDAO::changeDicoName(int id_in, string name)
{
	int code;
	char *error;

	string sqlInsertStr = "UPDATE Dictionnaire SET nom = '"+ name +"' WHERE id = '"+ to_string(id_in) +"';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_dico): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int DicoDAO::changeDicoPath(int id_in, string path)
{
	int code;
	char *error;

	string sqlInsertStr = "UPDATE Dictionnaire SET chemin = '" + path + "' WHERE id = '" + to_string(id_in) + "';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_dico): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int DicoDAO::GetAllDico(vector<string>& dico)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT nom FROM Dictionnaire;";

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
		for (int i = 0; i < rows; i++)
		{
			dico.push_back(results[i + columns]);
		}
	}

	sqlite3_free_table(results);

	return code;
}

int DicoDAO::DeleteDico(int id_in)
{
	int code;
	char *error;
	string sqlInsertStr = "DELETE FROM Dictionnaire WHERE ID = '" + to_string(id_in) + "';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (delete_dico): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}
