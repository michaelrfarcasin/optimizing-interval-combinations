#include <vector>
#include <algorithm>
#include "IntervalOptimizer.h"

using namespace std;

bool compare_start_value(vector<int> a, vector<int> b);
bool overlap(vector<int> a, vector<int> b);
bool is_first_interval_better(vector<int> a, vector<int> b, bool favor_cost);

vector<vector<int>> IntervalOptimizer::optimize(
    vector<vector<int>> intervals,
    bool favor_cost
) {
    if (intervals.empty()) {
        return intervals;
    }
    sort(intervals.begin(), intervals.end(), compare_start_value);
    vector<int> last_added = intervals.front();
    vector<vector<int>> optimized_intervals = { last_added };
    for (vector<int> interval : intervals) {
        if (overlap(last_added, interval) && is_first_interval_better(last_added, interval, favor_cost)) {
            continue;
        }
        if (overlap(last_added, interval)) {
            optimized_intervals.erase(optimized_intervals.end() - 1);
        }
        last_added = interval;
        optimized_intervals.push_back(interval);
    }

	return optimized_intervals;
}

bool compare_start_value(vector<int> a, vector<int> b)
{
    if (a[0] == b[0] && a[1] == b[1]) {
        return a[2] < b[2];
    }
    if (a[0] == b[0]) {
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

bool overlap(vector<int> a, vector<int> b)
{
    bool first_overlaps_second = b[0] <= a[1] && a[1] <= b[1];
    bool second_overlaps_first = a[0] <= b[1] && b[1] <= a[1];

    return first_overlaps_second || second_overlaps_first;
}

bool is_first_interval_better(vector<int> a, vector<int> b, bool favor_cost)
{
    if (favor_cost) {
        return a[2] <= b[2];
    }

    return a[1] <= b[1];
}