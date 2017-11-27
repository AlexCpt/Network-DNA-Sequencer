#pragma once
#include "sqlite3.h"
#include <string>
#include "Database.h"

using namespace std;

class UtilisateurDA
{
protected:
	sqlite3 *database;

public:
	UtilisateurDA();
	~UtilisateurDA();

	void SetDatabase(sqlite3 *database_in);

	template<class T>
	int AddUtilisateur(T User, string mdp);
	template<class T>
	int GetUtilisateurById(T &User, int id_in);
	template<class T>
    int GetUtilisateurByMail(T &User, string mail, string mdp);
	template<class T>
	int DeleteUtilisateur(T User);
};
