#pragma once
#include "../Utilities/EngineMath.hpp"
#include "../Utilities/pugixml-1.16/pugixml.hpp"

void readVector3ColorFromXml(Vector3 &property, pugi::xml_node node);

void readVector3XYZFromXml(Vector3 &property, pugi::xml_node node);