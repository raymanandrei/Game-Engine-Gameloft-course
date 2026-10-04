#include "../Utilities/EngineMath.hpp"
#include "../Utilities/pugixml-1.16/pugixml.hpp"
#include "stdafx.hpp"
#include <string>

// Reads from xml property with rgb tags
void readVector3ColorFromXml(Vector3 &property, pugi::xml_node node) {
  property.x = std::stof(node.child_value("r"));
  property.y = std::stof(node.child_value("g"));
  property.z = std::stof(node.child_value("b"));
}

// Reads from xml property with xyz tags
void readVector3XYZFromXml(Vector3 &property, pugi::xml_node node) {
  property.x = std::stof(node.child_value("x"));
  property.y = std::stof(node.child_value("y"));
  property.z = std::stof(node.child_value("z"));
}