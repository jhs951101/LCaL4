#include "Karnaugh.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

int convertBinary(int* num, int size){  // 0 또는 1의 형태로 저장된 수식을 minterm으로 변환하는 함수

	int decimal_n = 0;  // decimal_n: minterm으로 변환된 최종 값

	int k = size-1;  // k: 제곱용 보조 변수
	for(int i=0; i<size; i++){
		decimal_n += ( num[i] * pow(2,k) );  // decimal_n에 값을 누적함으로써 minterm을 구할 수 있음
		k--;  // 제곱을 하기 위해 k를 1만큼 감소시킴
	}

	return decimal_n;  // 최종적으로 계산된 minterm을 return함
}

void ZeroAndOne(int* num, int* arr ,int& cnt, int a, int b, int c){  // 0 또는 1의 형태를 여러 가지 케이스로 나누는 함수 (Overloading)

	// (보이지 않는 문자가 3개인 경우)	
	/*  a, b, c: 보이지 않는 문자의 자리 (w:0, x:1, y:2, z:3)  */
	/*  ex) w: x,y,z가 보이지 않으므로 a,b,c의 값은 1,2,3  */

	for(int i=1; i<=2; i++){

		if(i == 1) num[a] = 0;  // 처음에 a자리를 0으로 가정
		else num[a] = 1;  // 다음 a자리를 1로 가정

		for(int j=1; j<=4; j++){

			if(j == 1){  // 첫째, b,c자리를 모두 0으로 가정
				num[b] = 0;
				num[c] = 0;
			}
			else if(j == 2){  // 둘째, b자리는 1, c자리는 0으로 가정
				num[b] = 1;
				num[c] = 0;
			}
			else if(j == 3){  // 셋째, b자리는 0, c자리는 1으로 가정
				num[b] = 0;
				num[c] = 1;
			}
			else{  // 넷째, b,c자리를 모두 1으로 가정
				num[b] = 1;
				num[c] = 1;
			}

			arr[cnt] = convertBinary(num, 4);  // minterm으로 변환된 값을 배열에 넣어줌
			cnt++;  // 원소의 갯수: +1
		}
	}

}

void ZeroAndOne(int* num, int* arr ,int& cnt, int a, int b){  // 0 또는 1의 형태를 여러 가지 케이스로 나누는 함수 (Overloading)

	// (보이지 않는 문자가 2개인 경우)	
	/*  a, b: 보이지 않는 문자의 자리 (w:0, x:1, y:2, z:3)  */
	/*  ex) wz: x,y가 보이지 않으므로 a,b의 값은 1,2  */

	for(int j=1; j<=4; j++){

		if(j == 1){  // 첫째, a,b자리를 모두 0으로 가정
			num[a] = 0;
			num[b] = 0;
		}
		else if(j == 2){  // 둘째, a자리는 1, b자리는 0으로 가정
			num[a] = 1;
			num[b] = 0;
		}
		else if(j == 3){  // 셋째, a자리는 0, b자리는 1로 가정
			num[a] = 0;
			num[b] = 1;
		}
		else{  // 넷째, a,b자리를 모두 1로 가정
			num[a] = 1;
			num[b] = 1;
		}

		arr[cnt] = convertBinary(num, 4);  // minterm으로 변환된 값을 배열에 넣어줌
		cnt++;  // 원소의 갯수: +1
		// 2진수로 변환된 숫자를 배열에 넣음
	}

}

void ZeroAndOne(int* num, int* arr ,int& cnt, int a){  // 0 또는 1의 형태를 여러 가지 케이스로 나누는 함수 (Overloading)

	// (보이지 않는 문자가 1개인 경우)	
	/*  a: 보이지 않는 문자의 자리 (w:0, x:1, y:2, z:3)  */
	/*  ex) wxz: y가 보이지 않으므로 a의 값은 2  */

	for(int j=1; j<=2; j++){

		if(j == 1)
			num[a] = 0;  // 첫째, a자리를 0으로 가정
		else
			num[a] = 1;  // 둘째, a자리를 1로 가정

		arr[cnt] = convertBinary(num, 4);  // minterm으로 변환된 값을 배열에 넣어줌
		cnt++;  // 원소의 갯수: +1
		// 2진수로 변환된 숫자를 배열에 넣음
	}

}


void Karnaugh::insert(string s){

	poly = s;  // 입력받은 식을 저장함
}

void Karnaugh::devide(){

	int len = poly.length()-1;  // len: 입력받은 식 전체의 길이
	int point = 0;  // point: 지점을 저장 (식 전체를 나누는 데에 사용)
	int count = 0;  // count: 갯수를 저장 (식 전체를 나누는 데에 사용)
	int a = 0;  // a: 수식의 갯수

	for(int i=0; i<=len; i++){

		if(i == len){  // 식에서 제일 끝 문자에 도달했을 경우
			terms[a] = poly.substr(point,count+1);  // 구역을 지정해서 배열에 저장함
			a++;  // 수식의 갯수: +1
			term_num = a;  // 수식의 갯수를 class 변수로 넘겨줌
		}

		if(poly.at(i) == '+'){
			terms[a] = poly.substr(point,count);  // 구역을 지정해서 배열에 저장함

			point = i+1;  // 지점을 '+'에서 한 칸 앞쪽으로 지정함
			count = 0;  // 구역을 재지정하기위해 count를 0으로 함
			a++;  // 수식의 갯수: +1
		}
		else{
			count++;  // 구역을 지정하기 위해 count를 +1 해나감
		}
	}

}

void Karnaugh::minterm(){

	for(int i=0; i<4; i++)
		for(int j=0; j<100; j++)
			tempTerm[i][j] = -1;  // 배열 값을 모두 -1로 세팅함

	for(int n=0; n<=term_num-1; n++){

		string str = terms[n];  // str: 수식들이 저장된 배열로부터 값을 받는 변수
		char arr1[8];  // arr[]: 수식을 나누어 저장하는 배열

		for(int j=0; j<8; j++)
			arr1[j] = ' ';  // 배열 값을 모두 ' '으로 세팅함

		for(int j=0; j<=str.length()-1; j++)
			arr1[j] = str.at(j);  // 수식에서 문자 하나하나를 배열에 저장함 ( "w`x`yz" ->  w, `, x, `, y, z )

		if( (arr1[0] >= 119 && arr1[0] <= 122) && arr1[1] == ' ' ){  // 문자가 단 하나만 존재하고 알파벳인 경우
			int pos = arr1[0] - 119;  // 숫자가 들어갈 자리를 지정함
			tempTerm[pos][n] = 1;  // 지정된 자리에 숫자를 넣음
		}
		else{

			for(int j=0; j<=str.length()-2; j++){

				if( (arr1[j] >= 119 && arr1[j] <= 122) && (arr1[j+1] >= 119 && arr1[j+1] <= 122) ){
					// 왼쪽 값과 오른쪽 값 모두 알파벳일 경우, 왼쪽 값은 확실히 1임
					int pos = arr1[j] - 119;  // 숫자가 들어갈 자리를 지정함
					tempTerm[pos][n] = 1;  // 지정된 자리에 숫자를 넣음
				}
				else if( (arr1[j] >= 119 && arr1[j] <= 122) && arr1[j+1] == '`' ){
					// 왼쪽 값이 알파벳이고 오른쪽 값이 '`'이면, 왼쪽 값은 0
					int pos = arr1[j] - 119;  // 숫자가 들어갈 자리를 지정함
					tempTerm[pos][n] = 0;  // 지정된 자리에 숫자를 넣음
				}
			}
			if( arr1[str.length()-1] >= 119 && arr1[str.length()-1] <= 122 ){  // 제일 끝 문자가 알파벳일 경우 1
				int pos = arr1[str.length()-1] - 119;  // 숫자가 들어갈 자리를 지정함
				tempTerm[pos][n] = 1;  // 지정된 자리에 숫자를 넣음
			}
		}
	}

}

void Karnaugh::kmap(){

	int arrDecimal[100];  // arrDecimal[]: 수식들의 minterm을 저장
	int sup = 0;  // sup: 'arrDecimal[]'의 원소의 갯수

	int temArr[4]; // temArr[]: 'tempTerm[k][n]' 2차원 배열에서 한 행씩 저장
	for(int i=0; i<=3; i++)
		temArr[i] = 0;  // 배열을 모두 0으로 세팅함

	for(int n=0; n<=term_num-1; n++){

		if(tempTerm[0][n] == -1)  // 'w'의 값이 없다면
		{
			if(tempTerm[1][n] == -1)  // 'x'의 값이 없다면
			{
				if(tempTerm[2][n] == -1)  // 'y'의 값이 없다면
				{
					// z (-1, -1, -1, 1)
					for(int k=0; k<=3; k++)
						temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

					ZeroAndOne(temArr, arrDecimal, sup, 0, 1, 2);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
				}
				else
				{
					if(tempTerm[3][n] == -1)  // 'z'의 값이 없다면
					{
						// y (-1, -1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 0, 1, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// yz (-1, -1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 0, 1);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
				}
			}
			else  // 'x'의 값이 있으면
			{
				if(tempTerm[2][n] == -1)  // 'y'의 값이 없다면
				{
					if(tempTerm[3][n] == -1)  // 'z'의 값이 없다면
					{
						// x (-1, 1, -1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 0, 2, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// xz (-1, 1, -1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 0, 2);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
				}
				else
				{
					if(tempTerm[3][n] == -1)  // 'y'의 값이 없다면
					{
						// xy (-1, 1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 0, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// xyz (-1, 1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 0);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
				}
			}
		}
		else  // 'w'의 값이 있으면
		{
			if(tempTerm[1][n] == -1)  // 'x'의 값이 없다면
			{
				if(tempTerm[2][n] == -1)  // 'y'의 값이 없다면
				{
					if(tempTerm[3][n] == -1)  // 'z'의 값이 없다면
					{
						// w (1, -1, -1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 1, 2, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// wz (1, -1, -1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 1, 2);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
				}
				else  // 'y'의 값이 있으면
				{
					if(tempTerm[3][n] == -1)  // 'z'의 값이 없다면
					{
						// wy (1, -1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 1, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// wyz (1, -1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 1);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
				}
			}
			else  // 'x'의 값이 있으면
			{
				if(tempTerm[2][n] == -1)  // 'y'의 값이 없다면
				{
					if(tempTerm[3][n] == -1)  // 'z'의 값이 없다면
					{
						// wx(1, 1, -1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 2, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// wxz (1, 1, -1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 2);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
				}
				else  // 'y'의 값이 있으면
				{
					if(tempTerm[3][n] == -1)  // 'z'의 값이 없다면
					{
						// wxy (1, 1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						ZeroAndOne(temArr, arrDecimal, sup, 3);  // 0 또는 1의 형태로 변환하고 minterm을 계산함
					}
					else  // 'z'의 값이 있으면
					{
						// wxyz (1, 1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2차원 배열에서 해당 행을 저장

						arrDecimal[sup] = convertBinary(temArr, 4);  // 2진수로 변환된 숫자를 배열에 넣음
						sup++; // 원소의 갯수: +1
						
					}
				}
			}
		}

	}

	for(int i=sup-1; i>=1; i--)  // 원소들을 오름차순으로 정렬하는 부분
		for(int j=0; j<i; j++){
			if(arrDecimal[j] > arrDecimal[j+1]){  // 왼쪽 값이 오른쪽 값보다 클 경우 서로 맞바꿈
				int swap = arrDecimal[j+1];  // 맞바꾸기 Step1
				arrDecimal[j+1] = arrDecimal[j];  // 맞바꾸기 Step2
				arrDecimal[j] = swap;  // 맞바꾸기 Step3
			}
		}

	int kmap[4][4] = { 0, 1, 3, 2, 4, 5, 7, 6, 12, 13, 15, 14, 8, 9, 11, 10 };
	  // kmap[][]: Karnaugh Map
	int showing[4][4];  // showing[][]: 입력받은 식에 따른 카르노 맵

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			showing[i][j] = 0;  // 배열 값을 모두 0으로 세팅함

	// 중복값 제거
	int arrDecimal_cleaned[100];  // arrDecimal_cleaned[]: 수식들의 minterm을 저장하는 배열 (중복 값 제거)
	int sup2 = 0;  // sup2: 'arrDecimal_cleaned[]'의 원소의 갯수

	for(int i=0; i<sup; i++){

		bool isDuplicate = false;  // isDuplicate: 중복된 값일 경우 true, 아니면 false
		int num = arrDecimal[i];  // num: minterm이 저장된 배열로부터 숫자를 받음

		for(int j=0; j<sup2; j++){
			if(num == arrDecimal_cleaned[j])  // 중복된 값을 발견했을 경우 true로 변경
				isDuplicate  = true;  // bool 변수를 true로 변경
		}

		if(isDuplicate == false){  // 해당 값이 중복된 값이 아닐 경우
			arrDecimal_cleaned[sup2] = num;  // minterm을 배열에 저장함
			sup2++;  // 원소의 갯수: +1
		}
	}

	int k = sup2-1;  // k: 'arrDecimal_cleaned[]'의 보조 변수
	while(k >= 0){

		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				if(kmap[i][j] == arrDecimal_cleaned[k]){  // minterm이 들어갈 k-map의 위치를 찾았을 경우
					showing[i][j] = 1;  // 해당 위치를 1로 지정함
					break;  // 끝내고 다음 minterm이 들어갈 위치를 찾음
				}

		k--;  // 배열에서 값을 계속 빼내기 위해 1만큼 감소시킴
	}

	cout << "Minterm : ";  // 선 출력문
	for(int i=0; i<sup2; i++)
		cout << arrDecimal_cleaned[i] << " ";  // minterm 값을 출력함

	cout << endl;

	cout << "K-map : " << endl;  // 선 출력문
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++)
			cout << showing[i][j];  // k-map을 출력함

		cout << endl;
	}

}