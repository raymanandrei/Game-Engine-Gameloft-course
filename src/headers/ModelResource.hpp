#include <string>

#ifndef MODEL_RESOURCE_HPP
#define MODEL_RESOURCE_HPP

struct ModelResource {
  std::string id;
  std::string file;
  bool wire = false;
};

#endif
