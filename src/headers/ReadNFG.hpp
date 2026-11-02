#include "Vertex.hpp"
#include <string>
#include <vector>

#ifndef READ_NFG_HPP
#define READ_NFG_HPP

void readNfgLine(std::string str, std::string field, std::vector<float> &numbers);

void readNfg(std::string filename, std::vector<Vertex> &vertices, std::vector<unsigned short> &indices);

#endif
