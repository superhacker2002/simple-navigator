#include "file_handler.h"

s21::FileHandler::FileHandler() {}

s21::FileHandler::~FileHandler() {}

void s21::FileHandler::writeToFile(const std::string &filepath,
                                   s21::GraphData &data) {
  std::ofstream file(endsWith_(filepath, ".dot") ? filepath
                                                 : filepath + ".dot");
  if (file.is_open()) {
    writeHeader_(file);
    for (int i = 0; i < data.matrix->GetRows(); ++i) {
      for (int j = 0; j < data.matrix->GetCols(); ++j) {
        if (data.matrix->at(i, j) != 0) {
          if (i > j || data.matrix->at(i, j) != data.matrix->at(j, i)) {
            file << getVertexName_(i) << " -- " << getVertexName_(j)
                 << getLabel_(data.matrix->at(i, j));
          }
        }
      }
    }
    writeFooter_(file);
  } else {
    throw std::invalid_argument(
        std::strerror(errno) +
        std::string("Writing error : Can't open file for writing."));
  }
}

bool s21::FileHandler::endsWith_(const std::string &str,
                                 const std::string &suffix) {
  if (str.length() < suffix.length()) {
    return false;
  }
  return str.compare(str.length() - suffix.length(), suffix.length(), suffix) ==
         0;
}

const std::string s21::FileHandler::getVertexName_(const int it) {
  return static_cast<char>('A' + (it > 25 ? it % 26 : it)) +
         std::to_string(it / 26);
}

const std::string s21::FileHandler::getLabel_(const int value) {
  return std::string("[ label = \"") + std::to_string(value) +
         std::string("\"];\n");
}

void s21::FileHandler::writeHeader_(std::ofstream &file) {
  file << "graph s21_graph_name {\n";
}

void s21::FileHandler::writeFooter_(std::ofstream &file) { file << "}\n"; }

s21::GraphData s21::FileHandler::parseFile(const std::string &filepath) {
  m_file_ = std::ifstream(filepath);
  std::string buffer;
  if (m_file_.is_open()) {
    createMatrix_();
    int i = 0;
    for (; i < m_grph_data_.matrix->GetCols() && !m_file_.eof(); ++i) {
      getline(m_file_, buffer);
      parseLine_(buffer, i);
    }
    if (i != m_grph_data_.matrix->GetCols()) {
      throw std::invalid_argument(
          "Parsing error : Incorrect adjacency matrix.");
    }
  } else {
    throw std::invalid_argument(std::strerror(errno));
  }
  return m_grph_data_;
}

void s21::FileHandler::createMatrix_() {
  if (!m_file_.eof()) {
    size_t size = getGraphMatrixSize_();
    m_grph_data_.matrix = std::make_unique<s21::GraphData::MatrixType>(size);
  }
}

void s21::FileHandler::parseLine_(const std::string &line, size_t i) {
  int j = 0;
  for (auto it = line.begin(); j < m_grph_data_.matrix->GetRows(); ++j) {
    try {
      (*m_grph_data_.matrix)(i, j) = std::stof(it.base());
      moveIter_(it);
    } catch (...) {
      throw std::invalid_argument(
          std::string("Parsing error : Incorrect file contents."));
    }
  }
  if (j != m_grph_data_.matrix->GetRows()) {
    throw std::invalid_argument("Parsing error : Incorrect adjacency matrix.");
  }
}

size_t s21::FileHandler::getGraphMatrixSize_() {
  std::string buffer;
  getline(m_file_, buffer);
  try {
    return std::stoul(buffer);
  } catch (...) {
    throw std::invalid_argument(
        std::string("Parsing error : Incorrect size of adjacency matrix."));
  }
}

void s21::FileHandler::moveIter_(std::string::const_iterator &it) {
  while (isNumber_(*it)) ++it;
  while (*it == ' ') ++it;
}

bool s21::FileHandler::isNumber_(const char sym) {
  return (sym >= '0' && sym <= '9') || sym == '.';
}