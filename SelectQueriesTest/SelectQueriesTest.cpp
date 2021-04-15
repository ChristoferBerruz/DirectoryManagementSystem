#include "pch.h"
#include "CppUnitTest.h"
#include "../DirectoryManagementSystem.h"
#include "../QueryCoreEngine.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SelectQueriesTest
{
	TEST_CLASS(SelectQueriesTest)
	{
	public:
		
		TEST_METHOD(QueryOne)
		{
			DirectoryManagementSystem dms;
			string res = dms.TestABC();
			//ifstream testFile("person-test.txt");
			//dms.IngestData(testFile);
			//CoreQueryEngine engine;
			//map<string, int> actual = engine.SearchPersonByNameOrderByState(dms.GetContacts(), "W");
			//map<string, int> expected;
			Assert::IsTrue("abc" == res);
		}
	};
}
