#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <fstream>
#include <stdexcept>

#include "../../helpers/includes.h"

// note : не забыть обработать чистку
// приватных полей между использованием

namespace s21 {
class FileHandler {
 public:
  FileHandler();
  ~FileHandler();

  GraphData parseFile(const std::string& filepath);
  void writeToFile(const std::string& filepath, s21::GraphData& data);

 private:
  GraphData m_grph_data_;
  std::ifstream m_file_;

  size_t getGraphMatrixSize_();
  void createMatrix_();
  void parseLine_(const std::string& line, size_t j);
  void moveIter_(std::string::const_iterator& it);
  bool isNumber_(const char sym);
  void writeHeader_(std::ofstream& file);
  void writeFooter_(std::ofstream& file);
  const std::string getVertexName_(const int it);
  const std::string getLabel_(const int value);
};

}  // namespace s21

#endif  // FILE_HANDLER_H_