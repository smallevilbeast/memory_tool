#include "MemLexer.h"
#include <stdexcept>
#include <iostream>

namespace evlib {
	MemLexer::MemLexer(const std::string& input) 
	: input(input)
	, position(0) 
	{
		tokenize();
	}

	const std::vector<Token>& MemLexer::getTokens() const
	{
		return tokens;
	}

	void MemLexer::tokenize()
	{
		while (position < input.size()) {
			char current = input[position];

			if (std::isdigit(current)
				|| current == 'x'
				|| current == 'X'
				|| (current >= 'a' && current <= 'f')
				|| (current >= 'A' && current <= 'F')) {
				tokenizeNumber();
			}
			else if (current == '+') {
				tokens.push_back({ TokenType::Plus, "+" });
				position++;
			}
			else if (current == '-') {
				tokens.push_back({ TokenType::Minus, "-" });
				position++;
			}
			else if (current == '[') {
				tokens.push_back({ TokenType::OpenBracket, "[" });
				position++;
			}
			else if (current == ']') {
				tokens.push_back({ TokenType::CloseBracket, "]" });
				position++;
			}
			else {
				position++;
			}
		}
		tokens.push_back({ TokenType::End, "" });
	}

	void MemLexer::tokenizeNumber()
	{
		size_t start = position;
		while (position < input.length() && (
			std::isdigit(input[position])
			|| input[position] == 'x'
			|| input[position] == 'X'
			|| (input[position] >= 'a' && input[position] <= 'f')
			|| (input[position] >= 'A' && input[position] <= 'F'))) {
			position++;
		}
		tokens.push_back({ TokenType::Number, input.substr(start, position - start) });
	}

	std::string tokenTypeToString(TokenType type) {
		switch (type) {
		case TokenType::Number: return "Number";
		case TokenType::Plus: return "Plus";
		case TokenType::Minus: return "Minus";
		case TokenType::OpenBracket: return "OpenBracket";
		case TokenType::CloseBracket: return "CloseBracket";
		case TokenType::End: return "End";
		default: return "Unknown";
		}
	}


	void MemLexer::printTokens()
	{
		for (auto& token : tokens) {
			std::cout << "Type: " << (int)token.type << " , Value: " << token.value << std::endl;
		};
	}

}