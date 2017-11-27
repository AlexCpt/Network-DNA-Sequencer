#include "stdafx.h"
#include "AnalyseDAO.h"
#include <set>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iostream>
#include <vector>


AnalyseDAO::AnalyseDAO()
{
	Database db;
	db.open_database();
	database = db.get_database();
}


AnalyseDAO::~AnalyseDAO()
{
}

void AnalyseDAO::SetDatabase(sqlite3 * database_in)
{
	database = database_in;
}

int AnalyseDAO::AddAnalyse(string nomMaladie, int risque, int idClient)
{
	int code;
	char *error;

	string sqlInsertStr = "INSERT INTO Analyse (nom, risque, idClient) VALUES('" + nomMaladie + "', '" + to_string(risque) +"', '"+ to_string(idClient) + "');";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (write_analyse): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int AnalyseDAO::GetAnalyseByIdClient(vector<string>& nomMaladie, vector<int>& risque, int idClient)
{
	int code;
	char *error;

	string sqlSelectStr = "SELECT nom, risque FROM Analyse WHERE idClient = '" + to_string(idClient) + "';";

	const char *sqlSelect = sqlSelectStr.c_str();

	char **results = NULL;
	int rows, columns;

	code = sqlite3_get_table(database, sqlSelect, &results, &rows, &columns, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 query (read_analyse): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}
	else
	{
		for (int i = 0; i < rows;i=i+2)
		{
			nomMaladie.push_back(results[i + columns]);
			risque.push_back(stol(results[i+1 + columns]));
		}
	}

	sqlite3_free_table(results);

	return code;
}

int AnalyseDAO::DeleteAnalyse(int id_in)
{
	int code;
	char *error;
	string sqlInsertStr = "DELETE FROM Analyse WHERE ID = '" + to_string(id_in) + "';";

	const char *sqlInsert = sqlInsertStr.c_str();

	code = sqlite3_exec(database, sqlInsert, NULL, NULL, &error);

	if (code != 0)
	{
		cerr << "Error executing SQLite3 statement (delete_analyse): " << sqlite3_errmsg(database) << endl;
		sqlite3_free(error);
	}

	return code;
}

int AnalyseDAO::faireAnalyse(string genomePath, string dicoPath, string nomMaladie)
{
	set<string> set;
	size_t buffer_size = 256;
	char *buffer = new char[buffer_size];

	std::ifstream genome(genomePath);

	while (genome)
	{
		genome.read(buffer, buffer_size);
		set.insert(buffer);
		genome.read(buffer, 1);
	}
	std::ifstream dico(dicoPath);
	string trash;
	while (dico && trash != "<" + nomMaladie + ">")
	{
		getline(dico, trash);
	}
	int i = 1;
	while (dico && i <= 1000)
	{
		dico.read(buffer, buffer_size);
		if (set.find(buffer) == set.end())
		{
			//sain
			return 0;
		}
		dico.read(buffer, 1);
		i++;
	}
	//malade
	return 1;
	delete[] buffer;
}
