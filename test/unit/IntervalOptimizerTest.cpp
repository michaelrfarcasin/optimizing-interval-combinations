#include <vector>
#include <iostream>
#include "IntervalOptimizer.h"

using namespace std;

int assertEqual(string function_name, vector<vector<int>> expected, vector<vector<int>> actual);
void print_2d_vector(vector<vector<int>> lines);

int test_optimize_empty_returnsEmtpy()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {};

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, false);

    // Assert
    return assertEqual(__FUNCTION__, intervals, actual);
}

int test_optimize_oneInterval_returnsInterval()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {1, 2, 1}
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, false);

    // Assert
    return assertEqual(__FUNCTION__, intervals, actual);
}

int test_optimize_twoIntervals_overlap_favorCount_returnsIntervalEndingFirst()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {1, 2, 1},
        {2, 3, 0},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, false);

    // Assert
    vector<vector<int>> expected {
        {1, 2, 1},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int test_optimize_twoIntervals_overlap_favorCost_returnsCheaperInterval()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {1, 2, 1},
        {2, 3, 0},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, true);

    // Assert
    vector<vector<int>> expected {
        {2, 3, 0},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int test_optimize_twoIntervals_differentOverlap_favorCost_returnsCheaperInterval()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {1, 2, 1},
        {0, 3, 0},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, true);

    // Assert
    vector<vector<int>> expected {
        {0, 3, 0},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int test_optimize_twoIntervals_noOverlap_returnsBothIntervals()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {1, 2, 1},
        {3, 4, 0},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, false);

    // Assert
    vector<vector<int>> expected {
        {1, 2, 1},
        {3, 4, 0},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int test_optimize_threeIntervals_overlap_favorCount_returnsMostIntervals()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {0, 5, 1},
        {6, 10, 1},
        {5, 6, 1},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, false);

    // Assert
    vector<vector<int>> expected {
        {0, 5, 1},
        {6, 10, 1},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int test_optimize_threeIntervals_overlap_favorCount_outOfOrder_returnsMostIntervals()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {5, 6, 1},
        {6, 10, 1},
        {0, 5, 1},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, false);

    // Assert
    vector<vector<int>> expected {
        {0, 5, 1},
        {6, 10, 1},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int test_optimize_threeIntervals_overlap_favorCost_returnsLowestCost()
{
    // Arrange
    IntervalOptimizer optimizer;
    vector<vector<int>> intervals {
        {0, 5, 1},
        {6, 10, 1},
        {5, 6, 0},
    };

    // Act
    vector<vector<int>> actual = optimizer.optimize(intervals, true);

    // Assert
    vector<vector<int>> expected {
        {5, 6, 0},
    };
    return assertEqual(__FUNCTION__, expected, actual);
}

int main()
{
    bool allPassed = true;
    allPassed = allPassed && test_optimize_empty_returnsEmtpy() == 0;
    allPassed = allPassed && test_optimize_oneInterval_returnsInterval() == 0;
    allPassed = allPassed && test_optimize_twoIntervals_overlap_favorCount_returnsIntervalEndingFirst() == 0;
    allPassed = allPassed && test_optimize_twoIntervals_overlap_favorCost_returnsCheaperInterval() == 0;
    allPassed = allPassed && test_optimize_twoIntervals_differentOverlap_favorCost_returnsCheaperInterval() == 0;
    allPassed = allPassed && test_optimize_twoIntervals_noOverlap_returnsBothIntervals() == 0;
    allPassed = allPassed && test_optimize_threeIntervals_overlap_favorCount_returnsMostIntervals() == 0;
    allPassed = allPassed && test_optimize_threeIntervals_overlap_favorCount_outOfOrder_returnsMostIntervals() == 0;
    allPassed = allPassed && test_optimize_threeIntervals_overlap_favorCost_returnsLowestCost() == 0;

    if (allPassed) {
        cout << "All tests passed.";
    }
    
    return 0;
}

int assertEqual(string function_name, vector<vector<int>> expected, vector<vector<int>> actual)
{
    if (actual == expected) {
        return 0;
    }

    cerr << function_name << " failed." << endl << "Expected:" << endl;
    print_2d_vector(expected);
    cerr << "does not equal actual:" << endl;
    print_2d_vector(actual);
    cerr << endl;

    return 1;
}

void print_2d_vector(vector<vector<int>> rows)
{
    cerr << "{" << endl;
	for (vector<int> row : rows)
	{
		for (int i : row)
		{
			cerr << i << " ";
		}
		cerr << endl;

	}
    cerr << "}" << endl;
}