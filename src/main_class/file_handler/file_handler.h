#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include "../includes/includes.h"
#include <fstream>
#include <stdexcept>

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
      void parseLine_(const std::string& line, size_t j);
      void moveIter_(std::string::const_iterator& it);
      bool isNumber_(const char sym);
      void writeHeader_(std::ofstream& file);
      void writeFooter_(std::ofstream& file);
      const std::string getVertexName_(const int it);
      const std::string getLabel_(const int value);
  };
  
}

#endif  // SRC_PARSER_PARSER_H_