#include "stdafx.h"
#include "CppUnitTest.h"
#include "ProcessingRequest.h"
#include <string.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(TestProcessingRequest)
	{
	public:
		ProcessingRequest traitement;

		TEST_METHOD(TU1)
		{
			string result = traitement.getManager("connexionClient utilisateur@noninscrit motdepasse");
			string expected = "Echec de la connexion, vérifiez votre mail / mot de passe";
			Assert::AreEqual(result, expected);
		}

		//Ajouter informations d'un bonhomme qui existe
		TEST_METHOD(TU2)
		{
			string result = traitement.getManager("connexionClient ");
				//Assert::AreEqual()
		}

		
		TEST_METHOD(TU9)
		{
			string result = traitement.getManager("ajoutDico dicoTest test/test/test");
			string expected = "Reussite de l'ajout du dictionnaire";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(TU10)
		{
			string result = traitement.getManager("modDico 1484546 path new/path");
			string expected = "Echec de la modification";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(TU11)
		{
			string result = traitement.getManager("modDico 1 nom nouveauNom");
			string expected = "Reussite de la modification";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(TU12)
		{
			string result = traitement.getManager("afficherDico 189489454");
			string expected = "Echec de l'affichage";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(TU13)
		{
			string result = traitement.getManager("afficherDico 1");
			string expected = "Reussite de l'affichage";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(TU14)
		{
			string result = traitement.getManager("supprimerDico 4489451");
			string expected = "Echec de la suppression du dico";
			Assert::AreEqual(result, expected);
		}

	
	};
}