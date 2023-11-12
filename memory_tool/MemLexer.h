#pragma once
#include <string>
#include <vector>

namespace evlib {
	enum class TokenType {
		Number,
		Plus,
		Minus,
		OpenBracket,
		CloseBracket,
		End
	};

	struct Token {
		TokenType type;
		std::string value;
	};

	class MemLexer {
	public:
		MemLexer(const std::string& input);
		const std::vector<Token>& getTokens() const;
		void printTokens();

	private:
		void tokenize();
		void tokenizeNumber();


	private:
		std::string input;
		size_t position;
		std::vector<Token> tokens;

	};
}