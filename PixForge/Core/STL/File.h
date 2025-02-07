#pragma once
#include "Vector.h"
#include <string>
#include <fstream>
#include <filesystem>

namespace PF{
class File{
private:
  Vector<std::string> data;
  std::string path;
  std::fstream file;
public:
  File(const std::string path) : path(path){ file.open(path, std::ios::in | std::ios::out); };
  ~File() { file.close(); };
  bool notExist() { return file.good(); };
  void createFile() { file.open(path, std::ios::out); };
  void push(const std::string line) { data.push(line); };
  void clear() { while(data.size() > 0) data.pop(); };
  size_t size() { return data.size(); };
  const std::string getPath() { return path; };
  std::string& operator[](const size_t index) { return data[index]; };
  void remove() { std::filesystem::remove(path); };
public:
  void read();
  void save();
};
}; // namespace PF