#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include "../Includes/Includes.h"
#include <fstream>
#include <stdexcept>

// note : не забыть обработать чистку
// приватных полей между использованием

namespace s21 {
  class FileHandler {
    public:
      FileHandler() {}
      ~FileHandler() {}

      GraphData ParseFile(const std::string& filepath);
      
    private:
      GraphData m_grph_data_;
      std::ifstream m_file_;

      size_t GetGraphMatrixSize_();
      void ParseLine_(const std::string& line, size_t j);
      void MoveIter_(std::string::const_iterator& it);
  };
  
}

#endif  // SRC_PARSER_PARSER_H_