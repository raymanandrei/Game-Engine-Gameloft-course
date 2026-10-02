#pragma once
#include "../Utilities/EngineMath.hpp"
#include "../Utilities/rapidxml/rapidxml.hpp"

void readVector3ColorFromXml(Vector3 &property, rapidxml::xml_node<> *node);

void readVector3XYZFromXml(Vector3 &property, rapidxml::xml_node<> *node);