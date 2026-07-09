#pragma once
#include "../Utilities/rapidxml/rapidxml.hpp"
#include "../Utilities/Math.h"

void readVector3ColorFromXml(Vector3& property, rapidxml::xml_node<>* node);

void readVector3XYZFromXml(Vector3& property, rapidxml::xml_node<>* node);