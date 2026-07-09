#include "stdafx.h"
#include "../Utilities/Math.h"
#include "../Utilities/rapidxml/rapidxml.hpp"
#include <string>

//Reads from xml property with rgb tags
void readVector3ColorFromXml(Vector3& property, rapidxml::xml_node<>* node) {
	property.x = std::stof(node->first_node("r")->value());
	property.y = std::stof(node->first_node("g")->value());
	property.z = std::stof(node->first_node("b")->value());
}

//Reads from xml property with xyz tags
void readVector3XYZFromXml(Vector3& property, rapidxml::xml_node<>* node) {
	property.x = std::stof(node->first_node("x")->value());
	property.y = std::stof(node->first_node("y")->value());
	property.z = std::stof(node->first_node("z")->value());
}