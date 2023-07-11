#pragma once
#include <vector>

class IntervalOptimizer 
{
    public:
        std::vector<std::vector<int>> optimize(
            std::vector<std::vector<int>> intervals,
            bool favor_cost
        );
};