#pragma once
#include <string>

using namespace std;

class Karnaugh
{
protected:
	string poly;  // poly: �� ��ü�� �����ϴ� ��Ʈ��
	string terms[100];  // terms[]: '+'�� �ν������ν� ����� ����
	int tempTerm[4][100];  // tempTerm[][]: 0 �Ǵ� 1�� ���·� �ٲ� ������ ���� (ex: wx'yz' -> 1010)
	int term_num; // term_num: ������ ������ �����ϴ� ����

public:
	void insert(string s);  // �Է¹��� ���� �����ϴ� �Լ�
	void devide();  // '+'�� �ν������ν� �� ��ü�� ������ �Լ�
	void minterm();  // ������ 0 �Ǵ� 1�� ���·� �ٲٴ� �Լ�
	void kmap();  // ������ minterm�� ����ϰ� minterm�� k-map�� ����ϴ� �Լ�
};