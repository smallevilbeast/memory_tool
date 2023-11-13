#pragma once
#include <string>
#include "MemLexer.h"
#include <stdint.h>
#include <functional>

namespace evlib {

	using MemParseCallback = std::function<uint64_t(uint64_t addr, bool isFirst)>;
	class MemParser {
	public:
		MemParser(const std::vector<Token>& tokens, const MemParseCallback& callback);
		uint64_t getAddress();

	private:
		uint64_t parseExpression();
		uint64_t parseFactor();

	private:
		const std::vector<Token>& tokens;
		size_t position;
		MemParseCallback m_callback;

		bool m_bIsFirst;
	};
}
