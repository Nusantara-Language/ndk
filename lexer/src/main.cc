#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

int main(int argc, char* argv[])
{
	std::cout << "Nusantara Language Lexer" << "\n\n";

	if(argc < 2)
	{
		std::cerr << "Penggunaan " << argv[0] << " <nama_file>" << "\n";
		return 1;
	}

	std::string content;
	int row = 1;
	int column = 1;
	Lexer::muatFile(argv[1], content);

	std::vector<Lexer::Token> tokens;

	Lexer::generateTokens(argv[1], row, column, content, tokens);

	// Menentukan lebar untuk kolom
    const int filenameWidth = 12;
    const int lineWidth = 1;
    const int indexWidth = 5;
    const int typeWidth = 23;
    const int contentWidth = 10;

	for (int i = 0; i < tokens.size(); ++i) {
        std::cout << std::setw(filenameWidth) << std::left << tokens[i].fileName
                  << ":" 
                  << std::setw(lineWidth) << std::left << tokens[i].row
                  << ":" 
                  << std::setw(indexWidth) << std::left << tokens[i].column
                  << " "
                  << std::setw(typeWidth) << std::left << Lexer::tokenTypeToString(tokens[i].type)
                  << " => "
                  << std::setw(contentWidth) << std::left << tokens[i].content
                  << "\n";
    }

	return 0;
}