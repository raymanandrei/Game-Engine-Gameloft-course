#pragma once

#include <vector>

void readNfgLine(std::string str, std::string field, std::vector<float>& numbers);

void readNfg(std::string filename, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices);