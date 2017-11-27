#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "Database.h"

using namespace std;

class AnalyseDAO
{
private:
	sqlite3 *database;

public:
	AnalyseDAO();
	~AnalyseDAO();

	void SetDatabase(sqlite3 *database_in);
	int AddAnalyse(string nomMaladie, int risque, int idClient);
	int GetAnalyseByIdClient(vector <string> &nomMaladie, vector<int> &risque, int idClient);
	int DeleteAnalyse(int id_in);

	int faireAnalyse(string genomePath, string dicoPath, string nomMaladie);
};

