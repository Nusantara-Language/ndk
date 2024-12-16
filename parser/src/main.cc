#include "parser.h"
#include <iostream>
#include <lexer.h>
#include <memory>

int main(int argc, char* argv[])
{
	std::cout << "Nusantara Language Parser" << "\n\n";
    
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

	Parser::ParseNode parser(tokens);

	auto parseNodes = parser.parse();

	std::cout << "Hasil parse:" << "\n";
	if(parseNodes != nullptr) {
		Parser::coutNode(*parseNodes, 0);
	}

	return 0;
}