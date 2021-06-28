#include "Karnaugh.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

int convertBinary(int* num, int size){  // 0 �Ǵ� 1�� ���·� ����� ������ minterm���� ��ȯ�ϴ� �Լ�

	int decimal_n = 0;  // decimal_n: minterm���� ��ȯ�� ���� ��

	int k = size-1;  // k: ������ ���� ����
	for(int i=0; i<size; i++){
		decimal_n += ( num[i] * pow(2,k) );  // decimal_n�� ���� ���������ν� minterm�� ���� �� ����
		k--;  // ������ �ϱ� ���� k�� 1��ŭ ���ҽ�Ŵ
	}

	return decimal_n;  // ���������� ���� minterm�� return��
}

void ZeroAndOne(int* num, int* arr ,int& cnt, int a, int b, int c){  // 0 �Ǵ� 1�� ���¸� ���� ���� ���̽��� ������ �Լ� (Overloading)

	// (������ �ʴ� ���ڰ� 3���� ���)	
	/*  a, b, c: ������ �ʴ� ������ �ڸ� (w:0, x:1, y:2, z:3)  */
	/*  ex) w: x,y,z�� ������ �����Ƿ� a,b,c�� ���� 1,2,3  */

	for(int i=1; i<=2; i++){

		if(i == 1) num[a] = 0;  // ó���� a�ڸ��� 0���� ����
		else num[a] = 1;  // ���� a�ڸ��� 1�� ����

		for(int j=1; j<=4; j++){

			if(j == 1){  // ù°, b,c�ڸ��� ��� 0���� ����
				num[b] = 0;
				num[c] = 0;
			}
			else if(j == 2){  // ��°, b�ڸ��� 1, c�ڸ��� 0���� ����
				num[b] = 1;
				num[c] = 0;
			}
			else if(j == 3){  // ��°, b�ڸ��� 0, c�ڸ��� 1���� ����
				num[b] = 0;
				num[c] = 1;
			}
			else{  // ��°, b,c�ڸ��� ��� 1���� ����
				num[b] = 1;
				num[c] = 1;
			}

			arr[cnt] = convertBinary(num, 4);  // minterm���� ��ȯ�� ���� �迭�� �־���
			cnt++;  // ������ ����: +1
		}
	}

}

void ZeroAndOne(int* num, int* arr ,int& cnt, int a, int b){  // 0 �Ǵ� 1�� ���¸� ���� ���� ���̽��� ������ �Լ� (Overloading)

	// (������ �ʴ� ���ڰ� 2���� ���)	
	/*  a, b: ������ �ʴ� ������ �ڸ� (w:0, x:1, y:2, z:3)  */
	/*  ex) wz: x,y�� ������ �����Ƿ� a,b�� ���� 1,2  */

	for(int j=1; j<=4; j++){

		if(j == 1){  // ù°, a,b�ڸ��� ��� 0���� ����
			num[a] = 0;
			num[b] = 0;
		}
		else if(j == 2){  // ��°, a�ڸ��� 1, b�ڸ��� 0���� ����
			num[a] = 1;
			num[b] = 0;
		}
		else if(j == 3){  // ��°, a�ڸ��� 0, b�ڸ��� 1�� ����
			num[a] = 0;
			num[b] = 1;
		}
		else{  // ��°, a,b�ڸ��� ��� 1�� ����
			num[a] = 1;
			num[b] = 1;
		}

		arr[cnt] = convertBinary(num, 4);  // minterm���� ��ȯ�� ���� �迭�� �־���
		cnt++;  // ������ ����: +1
		// 2������ ��ȯ�� ���ڸ� �迭�� ����
	}

}

void ZeroAndOne(int* num, int* arr ,int& cnt, int a){  // 0 �Ǵ� 1�� ���¸� ���� ���� ���̽��� ������ �Լ� (Overloading)

	// (������ �ʴ� ���ڰ� 1���� ���)	
	/*  a: ������ �ʴ� ������ �ڸ� (w:0, x:1, y:2, z:3)  */
	/*  ex) wxz: y�� ������ �����Ƿ� a�� ���� 2  */

	for(int j=1; j<=2; j++){

		if(j == 1)
			num[a] = 0;  // ù°, a�ڸ��� 0���� ����
		else
			num[a] = 1;  // ��°, a�ڸ��� 1�� ����

		arr[cnt] = convertBinary(num, 4);  // minterm���� ��ȯ�� ���� �迭�� �־���
		cnt++;  // ������ ����: +1
		// 2������ ��ȯ�� ���ڸ� �迭�� ����
	}

}


void Karnaugh::insert(string s){

	poly = s;  // �Է¹��� ���� ������
}

void Karnaugh::devide(){

	int len = poly.length()-1;  // len: �Է¹��� �� ��ü�� ����
	int point = 0;  // point: ������ ���� (�� ��ü�� ������ ���� ���)
	int count = 0;  // count: ������ ���� (�� ��ü�� ������ ���� ���)
	int a = 0;  // a: ������ ����

	for(int i=0; i<=len; i++){

		if(i == len){  // �Ŀ��� ���� �� ���ڿ� �������� ���
			terms[a] = poly.substr(point,count+1);  // ������ �����ؼ� �迭�� ������
			a++;  // ������ ����: +1
			term_num = a;  // ������ ������ class ������ �Ѱ���
		}

		if(poly.at(i) == '+'){
			terms[a] = poly.substr(point,count);  // ������ �����ؼ� �迭�� ������

			point = i+1;  // ������ '+'���� �� ĭ �������� ������
			count = 0;  // ������ �������ϱ����� count�� 0���� ��
			a++;  // ������ ����: +1
		}
		else{
			count++;  // ������ �����ϱ� ���� count�� +1 �س���
		}
	}

}

void Karnaugh::minterm(){

	for(int i=0; i<4; i++)
		for(int j=0; j<100; j++)
			tempTerm[i][j] = -1;  // �迭 ���� ��� -1�� ������

	for(int n=0; n<=term_num-1; n++){

		string str = terms[n];  // str: ���ĵ��� ����� �迭�κ��� ���� �޴� ����
		char arr1[8];  // arr[]: ������ ������ �����ϴ� �迭

		for(int j=0; j<8; j++)
			arr1[j] = ' ';  // �迭 ���� ��� ' '���� ������

		for(int j=0; j<=str.length()-1; j++)
			arr1[j] = str.at(j);  // ���Ŀ��� ���� �ϳ��ϳ��� �迭�� ������ ( "w`x`yz" ->  w, `, x, `, y, z )

		if( (arr1[0] >= 119 && arr1[0] <= 122) && arr1[1] == ' ' ){  // ���ڰ� �� �ϳ��� �����ϰ� ���ĺ��� ���
			int pos = arr1[0] - 119;  // ���ڰ� �� �ڸ��� ������
			tempTerm[pos][n] = 1;  // ������ �ڸ��� ���ڸ� ����
		}
		else{

			for(int j=0; j<=str.length()-2; j++){

				if( (arr1[j] >= 119 && arr1[j] <= 122) && (arr1[j+1] >= 119 && arr1[j+1] <= 122) ){
					// ���� ���� ������ �� ��� ���ĺ��� ���, ���� ���� Ȯ���� 1��
					int pos = arr1[j] - 119;  // ���ڰ� �� �ڸ��� ������
					tempTerm[pos][n] = 1;  // ������ �ڸ��� ���ڸ� ����
				}
				else if( (arr1[j] >= 119 && arr1[j] <= 122) && arr1[j+1] == '`' ){
					// ���� ���� ���ĺ��̰� ������ ���� '`'�̸�, ���� ���� 0
					int pos = arr1[j] - 119;  // ���ڰ� �� �ڸ��� ������
					tempTerm[pos][n] = 0;  // ������ �ڸ��� ���ڸ� ����
				}
			}
			if( arr1[str.length()-1] >= 119 && arr1[str.length()-1] <= 122 ){  // ���� �� ���ڰ� ���ĺ��� ��� 1
				int pos = arr1[str.length()-1] - 119;  // ���ڰ� �� �ڸ��� ������
				tempTerm[pos][n] = 1;  // ������ �ڸ��� ���ڸ� ����
			}
		}
	}

}

void Karnaugh::kmap(){

	int arrDecimal[100];  // arrDecimal[]: ���ĵ��� minterm�� ����
	int sup = 0;  // sup: 'arrDecimal[]'�� ������ ����

	int temArr[4]; // temArr[]: 'tempTerm[k][n]' 2���� �迭���� �� �྿ ����
	for(int i=0; i<=3; i++)
		temArr[i] = 0;  // �迭�� ��� 0���� ������

	for(int n=0; n<=term_num-1; n++){

		if(tempTerm[0][n] == -1)  // 'w'�� ���� ���ٸ�
		{
			if(tempTerm[1][n] == -1)  // 'x'�� ���� ���ٸ�
			{
				if(tempTerm[2][n] == -1)  // 'y'�� ���� ���ٸ�
				{
					// z (-1, -1, -1, 1)
					for(int k=0; k<=3; k++)
						temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

					ZeroAndOne(temArr, arrDecimal, sup, 0, 1, 2);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
				}
				else
				{
					if(tempTerm[3][n] == -1)  // 'z'�� ���� ���ٸ�
					{
						// y (-1, -1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 0, 1, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// yz (-1, -1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 0, 1);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
				}
			}
			else  // 'x'�� ���� ������
			{
				if(tempTerm[2][n] == -1)  // 'y'�� ���� ���ٸ�
				{
					if(tempTerm[3][n] == -1)  // 'z'�� ���� ���ٸ�
					{
						// x (-1, 1, -1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 0, 2, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// xz (-1, 1, -1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 0, 2);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
				}
				else
				{
					if(tempTerm[3][n] == -1)  // 'y'�� ���� ���ٸ�
					{
						// xy (-1, 1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 0, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// xyz (-1, 1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 0);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
				}
			}
		}
		else  // 'w'�� ���� ������
		{
			if(tempTerm[1][n] == -1)  // 'x'�� ���� ���ٸ�
			{
				if(tempTerm[2][n] == -1)  // 'y'�� ���� ���ٸ�
				{
					if(tempTerm[3][n] == -1)  // 'z'�� ���� ���ٸ�
					{
						// w (1, -1, -1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 1, 2, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// wz (1, -1, -1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 1, 2);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
				}
				else  // 'y'�� ���� ������
				{
					if(tempTerm[3][n] == -1)  // 'z'�� ���� ���ٸ�
					{
						// wy (1, -1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 1, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// wyz (1, -1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 1);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
				}
			}
			else  // 'x'�� ���� ������
			{
				if(tempTerm[2][n] == -1)  // 'y'�� ���� ���ٸ�
				{
					if(tempTerm[3][n] == -1)  // 'z'�� ���� ���ٸ�
					{
						// wx(1, 1, -1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 2, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// wxz (1, 1, -1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 2);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
				}
				else  // 'y'�� ���� ������
				{
					if(tempTerm[3][n] == -1)  // 'z'�� ���� ���ٸ�
					{
						// wxy (1, 1, 1, -1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						ZeroAndOne(temArr, arrDecimal, sup, 3);  // 0 �Ǵ� 1�� ���·� ��ȯ�ϰ� minterm�� �����
					}
					else  // 'z'�� ���� ������
					{
						// wxyz (1, 1, 1, 1)
						for(int k=0; k<=3; k++)
							temArr[k] = tempTerm[k][n];  // 2���� �迭���� �ش� ���� ����

						arrDecimal[sup] = convertBinary(temArr, 4);  // 2������ ��ȯ�� ���ڸ� �迭�� ����
						sup++; // ������ ����: +1
						
					}
				}
			}
		}

	}

	for(int i=sup-1; i>=1; i--)  // ���ҵ��� ������������ �����ϴ� �κ�
		for(int j=0; j<i; j++){
			if(arrDecimal[j] > arrDecimal[j+1]){  // ���� ���� ������ ������ Ŭ ��� ���� �¹ٲ�
				int swap = arrDecimal[j+1];  // �¹ٲٱ� Step1
				arrDecimal[j+1] = arrDecimal[j];  // �¹ٲٱ� Step2
				arrDecimal[j] = swap;  // �¹ٲٱ� Step3
			}
		}

	int kmap[4][4] = { 0, 1, 3, 2, 4, 5, 7, 6, 12, 13, 15, 14, 8, 9, 11, 10 };
	  // kmap[][]: Karnaugh Map
	int showing[4][4];  // showing[][]: �Է¹��� �Ŀ� ���� ī���� ��

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			showing[i][j] = 0;  // �迭 ���� ��� 0���� ������

	// �ߺ��� ����
	int arrDecimal_cleaned[100];  // arrDecimal_cleaned[]: ���ĵ��� minterm�� �����ϴ� �迭 (�ߺ� �� ����)
	int sup2 = 0;  // sup2: 'arrDecimal_cleaned[]'�� ������ ����

	for(int i=0; i<sup; i++){

		bool isDuplicate = false;  // isDuplicate: �ߺ��� ���� ��� true, �ƴϸ� false
		int num = arrDecimal[i];  // num: minterm�� ����� �迭�κ��� ���ڸ� ����

		for(int j=0; j<sup2; j++){
			if(num == arrDecimal_cleaned[j])  // �ߺ��� ���� �߰����� ��� true�� ����
				isDuplicate  = true;  // bool ������ true�� ����
		}

		if(isDuplicate == false){  // �ش� ���� �ߺ��� ���� �ƴ� ���
			arrDecimal_cleaned[sup2] = num;  // minterm�� �迭�� ������
			sup2++;  // ������ ����: +1
		}
	}

	int k = sup2-1;  // k: 'arrDecimal_cleaned[]'�� ���� ����
	while(k >= 0){

		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				if(kmap[i][j] == arrDecimal_cleaned[k]){  // minterm�� �� k-map�� ��ġ�� ã���� ���
					showing[i][j] = 1;  // �ش� ��ġ�� 1�� ������
					break;  // ������ ���� minterm�� �� ��ġ�� ã��
				}

		k--;  // �迭���� ���� ��� ������ ���� 1��ŭ ���ҽ�Ŵ
	}

	cout << "Minterm : ";  // �� ��¹�
	for(int i=0; i<sup2; i++)
		cout << arrDecimal_cleaned[i] << " ";  // minterm ���� �����

	cout << endl;

	cout << "K-map : " << endl;  // �� ��¹�
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++)
			cout << showing[i][j];  // k-map�� �����

		cout << endl;
	}

}