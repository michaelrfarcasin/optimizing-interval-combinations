#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "CSVReader.h"

using namespace std;

int test_read();

int main()
{
	return test_read();
}

int test_read()
{
	vector<vector<string>> content;
	try {
    	CSVReader csvReader;
    	content = csvReader.read(".\\intervals.csv");
	} catch (const char* message) {
		cerr << message << endl;
		return 1;
	}

	for(vector<string> line : content)
	{
		for(string word : line)
		{
			cout<< word << " ";
		}
		cout << endl;
	}

	return 0;
}