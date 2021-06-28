#include "Karnaugh.h"
#include <iostream>
#include <string>

using namespace std;

int main(){

	Karnaugh K;  // K: ī���� �� Ŭ����
	string str;  // str: ���� �Է¹ޱ� ���� ����
	bool correct;  // correct: �Է¹��� ���� �ùٸ� ���̸� true, �ƴϸ� false

	while(true){

		cin >> str;  // ���� �Է¹���

		correct = true;  // �ʱ⿡�� ���� ���� true�� ��

		for(int i=0; i<str.length(); i++)
			if( str.at(i) != 'w' && str.at(i) != 'x' && str.at(i) != 'y' && str.at(i) != 'z' && str.at(i) != '`' && str.at(i) != '+'){
				// w, x, y, z, `, + �̿��� ���� ������ Error��
				cout << "Error: incorrect value." << endl << endl;  // ���� �޽��� ���
				correct = false;  // �����̹Ƿ� ���� false�� ����
			}

		if(correct == true) break;  // �ùٸ� ���̾�� ����� ������

	}

	K.insert(str);  // ���� ī���� Ŭ������ ����
	K.devide();  // ��ü ���� '+'�� ���� ����
	K.minterm();  // �������� ������ 0 �Ǵ� 1�� ���·� �ٲ�
	K.kmap();  // ������ minterm�� ����ϰ� minterm�� k-map�� �����

	return 0;
}