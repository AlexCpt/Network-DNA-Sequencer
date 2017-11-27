
// AlexMaladif.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CAlexMaladifApp :
// Consultez AlexMaladif.cpp pour l'implémentation de cette classe
//

class CAlexMaladifApp : public CWinApp
{
public:
	CAlexMaladifApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CAlexMaladifApp theApp;