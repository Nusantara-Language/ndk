// Include STD C++
#include <compare>
#include <cstddef>
#include <stdexcept>
#include <string>

// Include project file
#include "lexer.hpp"
#include "parse_error.hpp"

// Class ParseErrorLocation Getter
auto Parser::ParseErrorLocation::getFileName() const -> const std::string & {
  return this->filename;
}

auto Parser::ParseErrorLocation::getRow() const -> const size_t& {
  return this->row;
}

auto Parser::ParseErrorLocation::getStartColumn() const -> const size_t& {
  return this->column.startColumn;
}

auto Parser::ParseErrorLocation::getEndColumn() const -> const size_t& {
  return this->column.endColumn;
}


// Class ParseErrorLocation Operator
auto Parser::ParseErrorLocation::operator+(const ParseErrorLocation &other) const -> Parser::ParseErrorLocation
{
  if(this->filename != other.filename) {
    throw std::runtime_error("filename is not the same.");
  }

  if(this->row != other.row) {
    throw std::runtime_error("row is not the same.");
  }

  return {
    this->filename,
    this->row,
    {
      this->getStartColumn(), 
      other.getEndColumn()
    }
  };
}

auto Parser::ParseErrorLocation::operator+=(const ParseErrorLocation &other) -> Parser::ParseErrorLocation & {
  if (this->filename != other.filename) {
    throw std::runtime_error("filename is not the same.");
  }

  if (this->row != other.row) {
    throw std::runtime_error("row is not the same.");
  }

  this->column.endColumn = other.column.endColumn;

  return *this;
}

auto Parser::ParseErrorLocation::operator<=>(const ParseErrorLocation& other) const -> std::strong_ordering
{
  if(auto res = this->getFileName() <=> other.getFileName(); res != 0) { return res; }
  return this->getRow() <=> other.getRow();
}

void Parser::ParseErrorManager::addError(
  const lexer::Token &token,
  const std::string &message
) {}

auto Parser::toParseErrorLocation(
  const lexer::Token &token
) -> Parser::ParseErrorLocation {
  return {
    token.fileName,
    token.location.row,
    {
      token.location.column,
      token.location.column + static_cast<int>(token.content.size() - 1)
    }
  };
}