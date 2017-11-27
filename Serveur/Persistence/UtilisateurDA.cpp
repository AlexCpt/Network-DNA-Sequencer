#include "stdafx.h"
#include "UtilisateurDA.h"

UtilisateurDA::UtilisateurDA()
{
	Database db;
	db.open_database();
	database = db.get_database();
}

UtilisateurDA::~UtilisateurDA()
{
}

void UtilisateurDA::SetDatabase(sqlite3 *database_in)
{
	database = database_in;
}

template<class T>
inline int UtilisateurDA::AddUtilisateur(T User, string mdp)
{
}

template<class T>
inline int UtilisateurDA::GetUtilisateurById(T &User, int id_in)
{
}

template<class T>
inline int UtilisateurDA::GetUtilisateurByMail(T &User, string mail, string mdp)
{
}

template<class T>
inline int UtilisateurDA::DeleteUtilisateur(T User)
{
}

