#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "Vertex.h"

void readNfgLine(std::string str, std::string field, std::vector<float>& numbers) {

	int posIndex = str.find(field);

	if (posIndex != -1) {

		std::string numbersStr = str.substr(posIndex + field.length() + 1, str.find(';') - posIndex - field.length() - 1);
		std::stringstream ss(numbersStr);
		std::string token;

		while (std::getline(ss, token, ','))
			numbers.push_back(std::stod(token));
	}
}

void readNfg(std::string filename, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices) {
	std::ifstream file(filename);
	std::string str;
	while (std::getline(file, str))
	{
		std::vector<float> numbers;
		Vertex v;
		readNfgLine(str, "pos:", numbers);

		if (numbers.size() == 3) {

			v.pos.x = numbers[0];
			v.pos.y = numbers[1];
			v.pos.z = numbers[2];
		}

		str = str.substr(str.find(";") + 1, str.length() - str.find(";") - 1);
		numbers.clear();
		readNfgLine(str, "norm:", numbers);

		if (numbers.size() == 3) {
			v.norm.x = numbers[0];
			v.norm.y = numbers[1];
			v.norm.z = numbers[2];
		}

		str = str.substr(str.find(";") + 1, str.length() - str.find(";") - 1);
		numbers.clear();
		readNfgLine(str, "binorm:", numbers);

		if (numbers.size() == 3) {
			v.binorm.x = numbers[0];
			v.binorm.y = numbers[1];
			v.binorm.z = numbers[2];
		}

		str = str.substr(str.find(";") + 1, str.length() - str.find(";") - 1);

		numbers.clear();
		readNfgLine(str, "tgt:", numbers);

		if (numbers.size() == 3) {
			v.tgt.x = numbers[0];
			v.tgt.y = numbers[1];
			v.tgt.z = numbers[2];
		}

		str = str.substr(str.find(";") + 1, str.length() - str.find(";") - 1);

		numbers.clear();
		readNfgLine(str, "uv:", numbers);

		if (numbers.size() == 2) {
			v.uv.x = numbers[0];
			v.uv.y = numbers[1];
			vertices.push_back(v);
		}

		int posIndex = str.find("NrIndices:");
		if (posIndex != std::string::npos) {
			std::string numberStr = str.substr(posIndex + 10);
			int nrIndices = std::stoi(numberStr);
			while (std::getline(file, str)) {

				int posIndex = str.find(".");

				std::string numbersStr = str.substr(posIndex + 1, str.find('.', posIndex + 1) - posIndex - 1);
				std::stringstream ss(numbersStr);
				std::string token;

				while (std::getline(ss, token, ',')) {
					indices.push_back(std::stoi(token));
				}

			}
		}

	}
}
