#include <iostream>
#include <string>
#include <vector>
#include "CSVReader.h"
#include "IntervalOptimizer.h"

using namespace std;

vector<vector<int>> convert_to_intervals(vector<vector<string>> csv);
void remove_header(vector<vector<string>>& csv);
void print_2d_vector(vector<vector<int>> lines);

int main(int argc, char** argv)
{
	if (argc < 2) {
		cerr << "Error: missing csv file name." << endl;
		cout << "Usage: main.exe FILE [-c]" << endl;
		cout << "-c: favor minimizing cost over maximizing number of intervals" << endl;
		return 2;
	}
	vector<vector<string>> csv;
	try {
    	CSVReader csvReader;
    	csv = csvReader.read(argv[1]);
	} catch (const char* message) {
		cerr << message << endl;
		return 1;
	}
	vector<vector<int>> intervals = convert_to_intervals(csv);
	bool favor_cost = argc >= 3 && argv[2] == "-c";
	IntervalOptimizer optimizer;
	vector<vector<int>> optimized_intervals = optimizer.optimize(intervals, favor_cost);
	print_2d_vector(optimized_intervals);
 
	return 0;
}

vector<vector<int>> convert_to_intervals(vector<vector<string>> csv)
{
	remove_header(csv);
	vector<vector<int>> intervals;
	vector<int> interval;
	for (vector<string> row : csv) {
		interval.clear();
		for (string s : row) {
			interval.push_back(stoi(s));
		}
		intervals.push_back(interval);
	}

	return intervals;
}

void remove_header(vector<vector<string>>& csv)
{
	csv.erase(csv.begin());
}

void print_2d_vector(vector<vector<int>> rows)
{
	for (vector<int> row : rows)
	{
		for (int i : row)
		{
			cout << i << " ";
		}
		cout << endl;
	}
}