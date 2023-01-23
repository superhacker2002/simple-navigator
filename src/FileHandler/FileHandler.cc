#include "FileHandler.h"

s21::FileHandler::FileHandler() {}

s21::FileHandler::~FileHandler() {}

void s21::FileHandler::writeToFile(const std::string& filepath, s21::GraphData& data) {
  std::ofstream file(filepath);
  if (file.is_open()) {
    writeHeader_(file);
    for (int i = 0; i < data.matrix.GetRows(); ++i) {
      for (int j = 0; j < data.matrix.GetCols(); ++j) {
        if (data.matrix.at(i, j) != 0) {
          file << char('A' + (i > 25 ? i % 26 : i)) + std::to_string(i / 26) << \
            " -- " << \
            char('A' + (j > 25 ? j % 26 : j))  + std::to_string(j / 26) << \
             std::string("[ label = \"") + std::to_string(data.matrix.at(i, j)) << \
             "\"];\n";
        }
      }
    }
    writeFooter_(file);
  } else {
    throw std::invalid_argument(std::strerror(errno)\
      + std::string("Write error. Can't open file for writing."));
  }
}

void s21::FileHandler::writeHeader_(std::ofstream& file) {
  file << "graph s21_graph_name {\n";
}

void s21::FileHandler::writeFooter_(std::ofstream& file) {
  file << "}\n";
}

// should be called in a try-catch block
s21::GraphData s21::FileHandler::parseFile(const std::string& filepath) {
  m_file_ = std::ifstream(filepath);
  std::string buffer;
  if (m_file_.is_open()) {
    if (!m_file_.eof()) {
      size_t size = getGraphMatrixSize_();
      m_grph_data_.matrix = Matrix<int>(size, size);
    }
    int i = 0;
    for (; i < m_grph_data_.matrix.GetCols() && !m_file_.eof(); ++i) {
      getline(m_file_, buffer);
      parseLine_(buffer, i);
    }
    if (i != m_grph_data_.matrix.GetCols()) {
      throw std::invalid_argument("Parse error : Incorrect file.");
    }
  } else {
    throw std::invalid_argument(std::strerror(errno)\
      + std::string(". Parse error : Can't open file for reading."));
  }
  return m_grph_data_;
}

void s21::FileHandler::parseLine_(const std::string& line, size_t i) {
  int j = 0;
  for (auto it = line.begin(); j < m_grph_data_.matrix.GetRows(); ++j) {
    try {
      m_grph_data_.matrix(i, j) = std::stoi(it.base());
      moveIter_(it);
    } catch (...) {
      throw std::invalid_argument(std::strerror(errno)\
        + std::string(". Parse error : Can't parse line from file."));
    }
  }
  if (j != m_grph_data_.matrix.GetRows()) {
    throw std::invalid_argument("Parse error : Incorrect file.");
  }
}

size_t s21::FileHandler::getGraphMatrixSize_() {
  std::string buffer;
  getline(m_file_, buffer);
  try {
    return std::stoul(buffer);
  } catch (...) {
    throw std::invalid_argument(std::strerror(errno)\
      + std::string(". Parse error : Can't get graph size from file."));
  }
}

void s21::FileHandler::moveIter_(std::string::const_iterator& it) {
  while (isNumber_(*it)) ++it;
  while (*it == ' ') ++it;
}

bool s21::FileHandler::isNumber_(const char sym) {
  return sym >= '0' && sym <= '9';
}