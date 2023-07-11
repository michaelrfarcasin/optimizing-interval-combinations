#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "CSVReader.h"

using namespace std;

vector<vector<string>> CSVReader::read(string path)
{
    fstream file (path, ios::in);
    if (!file.is_open()) {
        throw "Could not open the file: " + path;
    }

    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    while (getline(file, line))
    {
        row.clear();
        stringstream str(line);
        while (getline(str, word, ','))
        {
            row.push_back(word);
        }
        content.push_back(row);
    }
 
	return content;
}