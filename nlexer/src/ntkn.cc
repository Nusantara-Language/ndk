/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "program/program.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

class NTkn
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
        if (inputFile.substr(inputFile.find_last_of('.') + 1) != "ntkn")
        {
            throw std::runtime_error("File input harus berekstensi .ntkn");
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

        int index = 0;
        for (const auto& token : tokenTypes)
        {
            result += "  " + token.type + " = " + std::to_string(index++) + ",\n";
        }

        result += "};\n";
        return result;
    }

    std::string generateCoutSupportSection() const
    {
        std::string result = "friend std::ostream& operator<<(std::ostream& os, const NToken& token)\n" "{\n" "os << token.location << \" [\";\n" "switch (token.type)\n" "{\n";

        for (const auto& token : tokenTypes)
        {
            result += "case NToken::" + token.type + ":\n" "os << \"" + token.type + "\";\n" "break;\n";
        }

        result += "default:\n" "os << token.type;\n" "break;\n" "}" "os << \"] \" << token.content;" "return os;\n" "}\n";

        return result;
    }

    std::string generateTokenData() const
    {
        std::string result = "static const std::array<NToken::Data, " + std::to_string(tokenTypes.size()) + "> tokenData = {\n";

        for (const auto& token : tokenTypes)
        {
            result += "  NToken::Data{NToken::" + token.type + ", std::regex(R\"(^" + token.pattern + ")\"), " + (token.skip ? "true" : "false") + "},\n";
        }

        result += "};\n";

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
        std::string coutSupportSection = generateCoutSupportSection();
        std::string tokenData = generateTokenData();

        // Replace bagian enum Type
        size_t typeStart = content.find("// NTKN_TYPE_TARGET");
        size_t typeEnd = content.find("// END_NTKN_TYPE_TARGET");
        if (typeStart == std::string::npos || typeEnd == std::string::npos)
        {
            throw std::runtime_error("Marker NTKN_TYPE_TARGET tidak ditemukan");
        }
        content.replace(typeStart + 20, typeEnd - typeStart - 20, "\n" + enumSection);

        // Replace bagian token cout support
        size_t coutSupportStart = content.find("// NTKN_COUT_SUPPORT_TARGET");
        size_t coutSupportEnd = content.find("// END_NTKN_COUT_SUPPORT_TARGET");
        if (coutSupportStart == std::string::npos || coutSupportEnd == std::string::npos)
        {
            throw std::runtime_error("Marker NTKN_COUT_SUPPORT_TARGET tidak ditemukan");
        }
        content.replace(coutSupportStart + 27, coutSupportEnd - coutSupportStart - 27, "\n" + coutSupportSection);

        // Replace bagian token data
        size_t dataStart = content.find("// NTKN_DATA_TARGET");
        size_t dataEnd = content.find("// END_NTKN_DATA_TARGET");
        if (dataStart == std::string::npos || dataEnd == std::string::npos)
        {
            throw std::runtime_error("Marker NTKN_DATA_TARGET tidak ditemukan");
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

int main()
{
    try
    {
        std::string programFolderPath = ncpp::getProgramPath().parent_path().string();
        std::string basePath = std::format("{}/../../nlexer", programFolderPath);

        std::string inputFile = std::filesystem::canonical(basePath + "/ntkn/nusantara.ntkn").string();
        std::string outputFile = std::filesystem::canonical(basePath + "/include/ntoken.h").string();

        NTkn ntkn;
        ntkn.parseTokenFile(inputFile);
        ntkn.updateHeaderFile(outputFile);

        std::cout << "NToken berhasil di buat!" << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Kesalahan: " << e.what() << std::endl;
        return 1;
    }
}