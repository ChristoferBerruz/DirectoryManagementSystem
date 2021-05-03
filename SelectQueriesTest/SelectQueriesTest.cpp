#include "CppUnitTest.h"
#include "../SearchPersonByName.h"
#include "../SearchPersonByEmail.h"
#include "../SearchBusinessByPhoneNumber.h"
#include "../SearchBusinessByEmailOrWebsite.h"
#include "../SearchPeopleLivingInCT.h"
#include "../AreaCodesBook.h"
#include "../DirectoryManagementSystem.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SelectQueriesTest
{
	TEST_CLASS(SelectQueriesTest)
	{
	public:
		
		TEST_METHOD(QueryI)
		{
			string name = "W";
			SearchPersonByName query(name);
			DirectoryManagementSystem* dms = DirectoryManagementSystem::GetInstance();

			// We should give FULL path to the text file we are about to open
			ifstream inputFile("C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\person-test.txt");
			if (inputFile.is_open())
			{
				dms->IngestData(inputFile);
			}
			map<string, int> actual = query.Search(dms->GetContacts());
			map<string, int> expected;
			expected["Alaska"] = 1;
			expected["Florida"] = 1;
			expected["Tennessee"] = 1;
			Assert::IsTrue(actual == expected);

			DirectoryManagementSystem::DeleteInstance();
		}

		TEST_METHOD(QueryII)
		{
			string emailDomain = ".org";
			SearchPersonByEmail query(emailDomain);
			DirectoryManagementSystem* dms = DirectoryManagementSystem::GetInstance();

			// We should give FULL path to the text file we are about to open
			ifstream inputFile("C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\person-test.txt");
			if (inputFile.is_open())
			{
				dms->IngestData(inputFile);
			}
			map<string, int> actual = query.Search(dms->GetContacts());
			map<string, int> expected;
			expected["Female"] = 3;
			expected["Male"] = 1;
			Assert::IsTrue(actual == expected);
			DirectoryManagementSystem::DeleteInstance();
		}

		TEST_METHOD(QueryIII)
		{
			string areaCode = "203";
			SearchBusinessByPhoneNumber query(areaCode);
			DirectoryManagementSystem* dms = DirectoryManagementSystem::GetInstance();

			// We should give FULL path to the text file we are about to open
			ifstream inputFile("C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\business-test.txt");
			if (inputFile.is_open())
			{
				dms->IngestData(inputFile);
			}
			map<string, int> actual = query.Search(dms->GetContacts());
			map<string, int> expected;
			expected["Tech"] = 1;
			Assert::IsTrue(expected == actual);
			DirectoryManagementSystem::DeleteInstance();
		}

		TEST_METHOD(QueryIV)
		{
			string email = ".com";
			string website = ".com";
			SearchBusinessByEmailOrWebsite query(email, website);
			DirectoryManagementSystem* dms = DirectoryManagementSystem::GetInstance();
			// We should give FULL path to the text file we are about to open
			ifstream inputFile("C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\business-test.txt");
			if (inputFile.is_open())
			{
				dms->IngestData(inputFile);
			}
			map<string, int> actual = query.Search(dms->GetContacts());
			map<string, int> expected;
			expected["Law"] = 2;
			expected["Tech"] = 2;
			expected["Pharma"] = 1;
			Assert::IsTrue(expected == actual);
			DirectoryManagementSystem::DeleteInstance();
		}

		TEST_METHOD(QueryV)
		{
			// We need the source file
			string areasFile = "C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\areacodes.txt";
			AreaCodesBook book(areasFile);
			string areaCode = "203";
			SearchPeopleLivingInCT query(book, areaCode);
			DirectoryManagementSystem* dms = DirectoryManagementSystem::GetInstance();
			// We should give FULL path to the text file we are about to open
			ifstream inputFile("C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\person-test.txt");
			if (inputFile.is_open())
			{
				dms->IngestData(inputFile);
			}
			map<string, int> actual = query.Search(dms->GetContacts());
			map<string, int> expected;
			expected["TX"] = 1;
			Assert::IsTrue(expected == actual);
			DirectoryManagementSystem::DeleteInstance();
		}


	};
}
