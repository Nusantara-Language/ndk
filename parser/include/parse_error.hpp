// Header guard
#ifndef PARSE_ERROR_HPP
#define PARSE_ERROR_HPP

// Include STD C++
#include <compare>
#include <cstddef>
#include <set>
#include <string>
#include <utility>

// Include project file
#include <lexer.hpp>

// Namespace
namespace Parser {

  // Struct
  struct ParseErrorLocationColumn {
    size_t startColumn;
    size_t endColumn;
  };

  // Class
  class ParseErrorLocation {
    public:
      // Constructor
      ParseErrorLocation(
        std::string filename, 
        const size_t& row,
        const ParseErrorLocationColumn& column
      ): 
      filename(std::move(filename)), 
      row(row), 
      column(column) 
      {}

      // Getter
      [[nodiscard]] auto getFileName() const -> const std::string&;
      [[nodiscard]] auto getRow() const -> const size_t&;
      [[nodiscard]] auto getStartColumn() const -> const size_t&;
      [[nodiscard]] auto getEndColumn() const -> const size_t&;

      // Operator function
      auto operator+(const ParseErrorLocation& other) const -> ParseErrorLocation;
      auto operator+=(const ParseErrorLocation& other) -> ParseErrorLocation&;
      auto operator<=>(const ParseErrorLocation& other) const -> std::strong_ordering;

    private:
      std::string filename;
      size_t row;
      ParseErrorLocationColumn column;
  };

  class ParseError {
    public:
      // Constructor
      ParseError(
        const std::set<ParseErrorLocation>& locations, 
        std::string message
      ): 
      locations(locations), 
      message(std::move(message))
      {}

    private:
      std::set<ParseErrorLocation> locations;
      std::string message;
  };

  class ParseErrorManager {
    public:
      // Constructor
      ParseErrorManager();

      // Function
      void addError(const lexer::Token& token, const std::string& message);

    private:
      std::set<ParseError> errors;
  };

  auto toParseErrorLocation(const lexer::Token& token) -> ParseErrorLocation;

} // namespace Parser

#endif
