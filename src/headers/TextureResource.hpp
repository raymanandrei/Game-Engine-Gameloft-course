#include <string>

#ifndef TEXTURE_RESOURCE_HPP
#define TEXTURE_RESOURCE_HPP

struct TextureResource {

  GLuint id;
  std::string file;
  GLenum type;
  GLint min_filter;
  GLint mag_filter;
  GLint wrap_s;
  GLint wrap_t;
};

#endif
