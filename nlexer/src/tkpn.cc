/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

class TokenProcessor
{
  private:
  struct TokenInfo
  {
    std::string type;
    std::string pattern;
    bool skip;
  };

  std::vector<TokenInfo> tokenTypes;

  static bool validateTokenFormat(const std::string& line)
  {
    if (line.empty() || line[0] == '#')
    {
      return true;
    }

    std::regex pattern("^[A-Z_]+\\s*:\\s*.+$");
    return std::regex_match(line, pattern);
  }

  static std::string trim(const std::string& str)
  {
    size_t first = str.find_first_not_of(" \t\n\r\f");
    if (first == std::string::npos)
      return "";
    size_t last = str.find_last_not_of(" \t\n\r\f");
    return str.substr(first, (last - first + 1));
  }

  public:
  void parseTokenFile(const std::string& inputFile)
  {
    if (inputFile.substr(inputFile.find_last_of('.') + 1) != "tkn")
    {
      throw std::runtime_error("File input harus berekstensi .tkn");
    }

    std::ifstream file(inputFile);
    if (!file.is_open())
    {
      throw std::runtime_error("Tidak dapat membuka file: " + inputFile);
    }

    std::string line;
    while (std::getline(file, line))
    {
      line = trim(line);
      if (line.empty() || line[0] == '#')
      {
        continue;
      }

      if (!validateTokenFormat(line))
      {
        throw std::runtime_error("Format token tidak valid: " + line);
      }

      size_t colonPos = line.find(':');
      std::string tokenType = trim(line.substr(0, colonPos));
      std::string pattern = trim(line.substr(colonPos + 1));

      if (!std::all_of(tokenType.begin(), tokenType.end(),
              [](char c)
              {
                return (std::isupper(c) != 0) || c == '_';
              }))
      {
        throw std::runtime_error("Tipe token harus huruf kapital: " + tokenType);
      }

      bool skip = false;
      if (pattern.length() > 5 && pattern.substr(pattern.length() - 5) == " skip")
      {
        pattern = trim(pattern.substr(0, pattern.length() - 5));
        skip = true;
      }

      // Tambahkan ke vector untuk mempertahankan urutan
      tokenTypes.push_back({tokenType, pattern, skip});
    }
  }

  std::string generateEnumSection() const
  {
    std::string result = "enum Type {\n";
    // "  NEOF = EOF,\n"
    // "  UNKNOWN = 0,\n"
    // "  NEWLINE = 1,\n";

    int index = 0;
    for (const auto& token : tokenTypes)
    {
      result += "  " + token.type + " = " + std::to_string(index++) + ",\n";
    }

    result += "};\n";
    return result;
  }

  std::string generateTokenData() const
  {
    std::string result = "inline static const std::array<NToken::Data, " + std::to_string(tokenTypes.size()) + "> tokenData = {\n";

    // result += "  NToken::Data{NToken::NEWLINE, R\"(^[\\n])\", false},\n";

    for (const auto& token : tokenTypes)
    {
      result += "  NToken::Data{NToken::" + token.type + ", std::regex(R\"(^" + token.pattern + ")\"), " + (token.skip ? "true" : "false") + "},\n";
    }

    result += "};\n";

    // "  NToken::Data{NToken::UNKNOWN, R\"(^.)\", false},\n"
    //           "  NToken::Data{NToken::NEOF, \"\", false},\n"

    return result;
  }

  void updateHeaderFile(const std::string& headerFile) const
  {
    if (headerFile.substr(headerFile.find_last_of('.') + 1) != "h")
    {
      throw std::runtime_error("File output harus berekstensi .h");
    }

    // Baca file header
    std::ifstream inFile(headerFile);
    if (!inFile.is_open())
    {
      throw std::runtime_error("Tidak dapat membuka file header: " + headerFile);
    }

    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // Generate konten baru
    std::string enumSection = generateEnumSection();
    std::string tokenData = generateTokenData();

    // Replace bagian enum Type
    size_t typeStart = content.find("// TOKEN_TYPE_TARGET");
    size_t typeEnd = content.find("// END_TOKEN_TYPE_TARGET");
    if (typeStart == std::string::npos || typeEnd == std::string::npos)
    {
      throw std::runtime_error("Marker TOKEN_TYPE_TARGET tidak ditemukan");
    }
    content.replace(typeStart + 20, typeEnd - typeStart - 20, "\n" + enumSection);

    // Replace bagian token data
    size_t dataStart = content.find("// TOKEN_DATA_TARGET");
    size_t dataEnd = content.find("// END_TOKEN_DATA_TARGET");
    if (dataStart == std::string::npos || dataEnd == std::string::npos)
    {
      throw std::runtime_error("Marker TOKEN_DATA_TARGET tidak ditemukan");
    }
    content.replace(dataStart + 20, dataEnd - dataStart - 20, "\n" + tokenData);

    // Tulis kembali ke file
    std::ofstream outFile(headerFile);
    if (!outFile.is_open())
    {
      throw std::runtime_error("Tidak dapat menulis ke file header: " + headerFile);
    }
    outFile << content;
  }
};

void printUsage()
{
  std::cout << "Penggunaan: tknp -i <input.tkn> -o <output.h>" << std::endl;
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 5)
    {
      throw std::runtime_error("Jumlah argumen tidak sesuai");
    }

    std::string inputFile;
    std::string outputFile;

    for (int i = 1; i < argc; i += 2)
    {
      std::string arg = argv[i];
      if (arg == "-i")
      {
        inputFile = argv[i + 1];
      }
      else if (arg == "-o")
      {
        outputFile = argv[i + 1];
      }
      else
      {
        throw std::runtime_error("Argumen tidak valid: " + arg);
      }
    }

    if (inputFile.empty() || outputFile.empty())
    {
      throw std::runtime_error("File input dan output harus ditentukan");
    }

    TokenProcessor processor;
    processor.parseTokenFile(inputFile);
    processor.updateHeaderFile(outputFile);

    std::cout << "Pemrosesan file berhasil!" << std::endl;
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    printUsage();
    return 1;
  }
}