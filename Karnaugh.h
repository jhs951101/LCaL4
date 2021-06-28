#pragma once
#include <string>

using namespace std;

class Karnaugh
{
protected:
	string poly;  // poly: 식 전체를 저장하는 스트링
	string terms[100];  // terms[]: '+'를 인식함으로써 나누어서 저장
	int tempTerm[4][100];  // tempTerm[][]: 0 또는 1의 형태로 바뀐 수식을 저장 (ex: wx'yz' -> 1010)
	int term_num; // term_num: 수식의 갯수를 저장하는 변수

public:
	void insert(string s);  // 입력받은 식을 저장하는 함수
	void devide();  // '+'를 인식함으로써 식 전체를 나누는 함수
	void minterm();  // 수식을 0 또는 1의 형태로 바꾸는 함수
	void kmap();  // 수식의 minterm을 계산하고 minterm과 k-map을 출력하는 함수
};