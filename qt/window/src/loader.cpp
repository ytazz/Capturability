#include "loader.h"
#include <assert.h>
#include <fstream>
#include <iostream>

namespace CA {

Loader::Loader(const std::string &name)
    : name(name), parser(XML_ParserCreate(NULL)), depth(0) {
  if (!parser) {
    std::cout << "Couldn't allocate memory for parser" << std::endl;
    exit(-1);
  }
  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, start, end);
}

Loader::~Loader() {}

void Loader::parse() {
  std::ifstream l_file(name.c_str());
  if (!l_file) {
    std::cout << "ERROR : Could not open file \"" << name << "\"" << std::endl;
    exit(-1);
  }
  const int l_size = 10;
  char l_buf[l_size];
  bool l_end = false;
  while (!(l_end = l_file.eof())) {
    l_file.read(l_buf, l_size);
    if (!XML_Parse(parser, l_buf, l_file.gcount(), l_end)) {
      std::cout << "ERROR : Parse error at line "
                << XML_GetCurrentLineNumber(parser) << " :"
                << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
      exit(-1);
    }
  }
  l_file.close();
  // std::cout << "PARSE SUCCESSFULL" << std::endl;
}

void Loader::start(void *data, const char *el, const char **attr) {
  Loader *l_parser = static_cast<Loader *>(data);
  assert(l_parser);
  l_parser->start_element(el);
  for (int i = 0; attr[i]; i += 2) {
    l_parser->get_attribute(attr[i], attr[i + 1]);
  }
}

void Loader::end(void *data, const char *el) {
  Loader *l_parser = static_cast<Loader *>(data);
  assert(l_parser);
  l_parser->end_element(el);
}

void Loader::start_element(const std::string &name) {
  callbackElement(name, true);
}

void Loader::end_element(const std::string &name) {
  callbackElement(name, false);
}

void Loader::get_attribute(const std::string &name, const std::string &value) {
  callbackAttribute(name, value);
}

bool Loader::equalStr(const char *chr1, const char *chr2) {
  bool is_equal = false;

  if (strcmp(chr1, chr2) == 0)
    is_equal = true;

  return is_equal;
}

bool Loader::equalStr(const std::string &str1, const char *chr2) {
  return equalStr(str1.c_str(), chr2);
}

bool Loader::equalStr(const char *chr1, const std::string &str2) {
  return equalStr(chr1, str2.c_str());
}

bool Loader::equalStr(const std::string &str1, const std::string &str2) {
  return equalStr(str1.c_str(), str2.c_str());
}

Vector2 Loader::convertStrToVec(const std::string &str) {
  int space_position = str.find(" ");

  std::string val1 = "", val2 = "";
  for (int i = 0; i < space_position; i++) {
    val1 += str[i];
  }
  for (uint i = space_position + 1; i < str.length(); i++) {
    val2 += str[i];
  }

  Vector2 vec = {stof(val1), stof(val2)};
  return vec;
}

} // namespace CA