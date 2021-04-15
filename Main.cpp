#include "DirectoryManagementSystem.h"
#include <iostream>
#include <fstream>
#include "AreaCodesBook.h"
using namespace std;
int main()
{
	ifstream inputFile("input3.txt");
	DirectoryManagementSystem dms;
	dms.IngestData(inputFile);
	dms.ShowAllContacts();
	dms.Query();
}