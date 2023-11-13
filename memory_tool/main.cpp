#include <iostream>
#include <string>
#include <Windows.h>

#include "MemParser.h"

using namespace evlib;


HANDLE hHandle = NULL;


// 需要根据64/32位 进程和编译器的不同而修改， 测试读取的是32位进程，编译器为32位
uint64_t ReadMem(uint64_t addr, bool isFirst) {
	uint32_t newAddr = (uint32_t)addr;
	uint32_t result = 0;
	if (isFirst) {
		// 加上模块基址
		newAddr += 0x787E0000;
	}
	ReadProcessMemory(hHandle, (LPCVOID)newAddr, &result, sizeof(result), NULL);
	uint64_t finalAddr = result;
	return finalAddr;
}

int main() {

	// 进程id
	DWORD pid = 0x9354;
	hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	// 表达式支持 +/- 数字支持 0x开头的16进制数
	std::string expression = "[[[3057D28]+8]+0x4-2+2]+0x38";
	MemLexer lexer(expression);
	lexer.printTokens();
	MemParser parser(lexer.getTokens(), ReadMem);

	// 最后拿到地址, 根据需要改成读取 1， 2， 4， 8 或 任意长度的数据
	auto virtualAddress = parser.getAddress();
	std::cout << "Result: " << std::hex << ReadMem(virtualAddress, false) << std::endl;

	return 0;
}
