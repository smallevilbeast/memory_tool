#include "MemParser.h"
#include <stdexcept>
#include <iostream>

namespace evlib
{

	MemParser::MemParser(const std::vector<Token>& tokens, const MemParseCallback& callback)
	:tokens(tokens)
	,position(0)  
	, m_callback(callback)
    , m_bIsBaseOffset(true)
	{
		
	}

	uint64_t MemParser::getAddress()
	{
		return parseExpression();
	}

	uint64_t MemParser::parseExpression()
	{
		auto result = parseFactor();
		while (position < tokens.size() && (
			tokens[position].type == TokenType::Plus ||
			tokens[position].type == TokenType::Minus))
		{
			if (tokens[position].type == TokenType::Plus) {
				position++;
				result += parseFactor();
			}
			else if (tokens[position].type == TokenType::Minus) {
				position++;
				result -= parseFactor();
			}
		}
		return result;
	}

	uint64_t MemParser::parseFactor()
	{
		if (tokens[position].type == TokenType::OpenBracket) {
			position++;
			auto result = parseExpression();
			if (tokens[position].type == TokenType::CloseBracket) {
				position++;
				if (m_callback) {
					result = m_callback(result, m_bIsBaseOffset);
					m_bIsBaseOffset = false;
				}
				return result;
			}
			else {
				throw std::runtime_error("Missing closing bracket");
			}
		}
		else if (tokens[position].type == TokenType::Number) {
			auto value = std::stoull(tokens[position].value, nullptr, 16);
			position++;
			return value;
		}
		else {
			throw std::runtime_error("Unexpected token");
		}
	}

}