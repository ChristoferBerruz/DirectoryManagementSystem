#include "CppUnitTest.h"
#include "../SearchPersonByName.h"
#include "../DirectoryManagementSystem.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SelectQueriesTest
{
	TEST_CLASS(SelectQueriesTest)
	{
	public:
		
		TEST_METHOD(TestSearchPersonByName)
		{
			string name = "W";
			SearchPersonByName query(name);
			DirectoryManagementSystem dms;

			// We should give FULL path to the text file we are about to open
			ifstream inputFile("C:\\Users\\cberr\\OneDrive\\Documents\\University of Bridgeport\\2021SP Semester\\C++\\DirectoryManagementSystem\\input2.txt");
			if (inputFile.is_open())
			{
				dms.IngestData(inputFile);
			}
			map<string, int> actual = query.Search(dms.GetContacts());
			map<string, int> expected;
			expected["Alaska"] = 1;
			expected["Florida"] = 1;
			expected["Tennessee"] = 1;
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestSearchPersonByEmail)
		{

		}
	};
}
