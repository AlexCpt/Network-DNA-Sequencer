#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "Database.h"

using namespace std;

class DicoDAO
{
private:
	sqlite3 *database;

public:
	DicoDAO();
	~DicoDAO();

	void SetDatabase(sqlite3 *database_in);
	int AddDico(string nomDico,string chemin);
	int GetDicoById(string &dico,string &chemin,int id_in);
	int changeDicoName(int id_in, string name);
	int changeDicoPath(int id_in, string path);
	int GetAllDico(vector<string> &dico);
	int DeleteDico(int id_in);
};

