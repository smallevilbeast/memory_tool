#include <iostream>
#include <string>
#include <Windows.h>

#include "MemParser.h"

using namespace evlib;


HANDLE hHandle = NULL;


// ��Ҫ����64/32λ ���̺ͱ������Ĳ�ͬ���޸ģ� ���Զ�ȡ����32λ���̣�������Ϊ32λ
uint64_t ReadMem(uint64_t addr, bool isFirst) {
	uint32_t newAddr = (uint32_t)addr;
	uint32_t result = 0;
	if (isFirst) {
		// ����ģ���ַ
		newAddr += 0x787E0000;
	}
	ReadProcessMemory(hHandle, (LPCVOID)newAddr, &result, sizeof(result), NULL);
	uint64_t finalAddr = result;
	return finalAddr;
}

int main() {

	// ����id
	DWORD pid = 0x9354;
	hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	// ���ʽ֧�� +/- ����֧�� 0x��ͷ��16������
	std::string expression = "[[[3057D28]+8]+0x4-2+2]+0x38";
	MemLexer lexer(expression);
	lexer.printTokens();
	MemParser parser(lexer.getTokens(), ReadMem);

	// ����õ���ַ, ������Ҫ�ĳɶ�ȡ 1�� 2�� 4�� 8 �� ���ⳤ�ȵ�����
	auto virtualAddress = parser.getAddress();
	std::cout << "Result: " << std::hex << ReadMem(virtualAddress, false) << std::endl;

	return 0;
}
