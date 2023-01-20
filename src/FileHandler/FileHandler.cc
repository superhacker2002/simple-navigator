#include "FileHandler.h"

// should be called in a try-catch block
s21::GraphData s21::FileHandler::ParseFile(const std::string& filepath) {
  m_file_ = std::ifstream(filepath);
  std::string buffer;
  if (m_file_.is_open()) {
    if (!m_file_.eof()) {
      // this func call may throw an exception!!!!
      size_t size = GetGraphMatrixSize_();
      m_grph_data_.matrix = Matrix<int>(size, size);
    }
    size_t i = 0;
    for (; i < m_grph_data_.matrix.GetCols() && !m_file_.eof(); ++i) {
      getline(m_file_, buffer);
      ParseLine_(buffer, i);
    }
    if (i != m_grph_data_.matrix.GetCols() - 1) {
      throw std::invalid_argument("Parse error : Incorrect file.");
    }
  } else {
    throw std::invalid_argument(std::strerror(errno)\
      + std::string(". Parse error : Can't open file for reading."));
  }
  return m_grph_data_;
}

void s21::FileHandler::ParseLine_(const std::string& line, size_t i) {
  size_t j = 0;
  for (auto it = line.begin(); j < m_grph_data_.matrix.GetRows(); ++j) {
    try {
      m_grph_data_.matrix(i, j) = std::stoi(it.base());
      MoveIter_(it);
    } catch (...) {
      throw std::invalid_argument(std::strerror(errno)\
        + std::string(". Parse error : Can't parse line from file."));
    }
  }
  if (j != m_grph_data_.matrix.GetRows() - 1) {
    throw std::invalid_argument("Parse error : Incorrect file.");
  }
}

size_t s21::FileHandler::GetGraphMatrixSize_() {
  std::string buffer;
  getline(m_file_, buffer);
  try {
    return std::stoul(buffer);
  } catch (...) {
    throw std::invalid_argument(std::strerror(errno)\
      + std::string(". Parse error : Can't get graph size from file."));
  }
}

void s21::FileHandler::MoveIter_(std::string::const_iterator& it) {
  while (isnumber(*it)) { ++it; }
}