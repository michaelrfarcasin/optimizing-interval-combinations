#pragma once
#include <string>
#include <vector>

class CSVReader 
{
    public:
        std::vector<std::vector<std::string>> read(std::string path);
};