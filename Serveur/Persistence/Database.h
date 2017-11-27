#pragma once

#include <string>
#include <iostream>
#include "sqlite3.h"
#include "Patient.h"

using namespace std;

class Database
{
private:
	const char *database_name = "Maladif.db";
	sqlite3 *database;

public:
	Database();
	~Database();

	sqlite3 * get_database();

	int open_database();
	int close_database();
	int create_tables();
};
