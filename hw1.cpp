#include "Karnaugh.h"
#include <iostream>
#include <string>

using namespace std;

int main(){

	Karnaugh K;  // K: 카느로 맵 클래스
	string str;  // str: 식을 입력받기 위한 변수
	bool correct;  // correct: 입력받은 값이 올바른 값이면 true, 아니면 false

	while(true){

		cin >> str;  // 식을 입력받음

		correct = true;  // 초기에는 변수 값을 true로 함

		for(int i=0; i<str.length(); i++)
			if( str.at(i) != 'w' && str.at(i) != 'x' && str.at(i) != 'y' && str.at(i) != 'z' && str.at(i) != '`' && str.at(i) != '+'){
				// w, x, y, z, `, + 이외의 값이 있으면 Error임
				cout << "Error: incorrect value." << endl << endl;  // 에러 메시지 출력
				correct = false;  // 에러이므로 값을 false로 변경
			}

		if(correct == true) break;  // 올바른 값이어야 계산을 진행함

	}

	K.insert(str);  // 식을 카르노 클래스로 보냄
	K.devide();  // 전체 식을 '+'에 따라 나눔
	K.minterm();  // 나누어진 수식을 0 또는 1의 형태로 바꿈
	K.kmap();  // 수식의 minterm을 계산하고 minterm과 k-map을 출력함

	return 0;
}