#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int equalSufPost(string, int);
int* WordArr(string);
int KMP(string, string);
int* BM_ARR(string);
int BM(string, string);

void main(){
	setlocale(LC_ALL, "rus");
	string str_val, str_sub;
	
	for (;;)
	{
		cin.sync();
		cout << "Введите вашу строку." << endl;
		SetConsoleCP(1251);
		getline(cin, str_val);
		SetConsoleCP(866);
		cin.sync();
		cout << endl;
		cout << "Введите вашу подстроку." << endl;
		SetConsoleCP(1251);
		getline(cin, str_sub);
		SetConsoleCP(866);
		cin.sync();
		cout << endl;
		int change;
		cout << "1 - поиск по методу кнута морисса-пратта\n2 - поиск по методу бойера-мура" << endl;
		cin >> change;
		if (change == 1)
		{
			cout << KMP(str_val, str_sub) << endl;
		}
		else if (change == 2)
		{
			cout << BM(str_val, str_sub) << endl;
		}
		else
		{
			break;
		}
	}	
}

int equalSufPost(string str, int quant){
	for ( int i = quant-1; i >= 0; --i){
		for (int j = 0, z = quant - i; j < i; ++j, ++z)
		{
			if (str[j] == str[z])
			{
				if (j == i-1)
				{
					return i;
				}
				else
				{
					continue;
				}
				
			}
			break;
		}
	}
	return 0;
}

int* WordArr(string str){
	int* ptr_arr = new int[str.length()];
	ptr_arr[0] = 0;
	for (int i = 1; i < str.length(); i++)
	{
		ptr_arr[i] = equalSufPost(str, i+1);
	}
	return ptr_arr;
}

int KMP(string S, string T){
	int index_S = 0, index_T = 0, count = 0;
	int* ptr_arr;
	ptr_arr = WordArr(T);
	while (true)
	{
		if (S[index_S] == T[index_T])
		{
			if (index_T == T.length()-1)
			{
				return index_S - (index_T)+1;
			}
			else
			{
				++index_S;
				++index_T;
			}
		}
		else if (index_T == 0)
		{
			++index_S;
		}
		else
		{
			index_T = ptr_arr[index_T-1];
		}


		if (index_S > S.length())
		{
			return -1;
		}
	}

}

int* BM_ARR(string word){
	int quant= 256;
	int* ptr_Arr = new int[quant];
	for (int i = 0; i < quant; ++i)
	{
		ptr_Arr[i] = 0;
	}
	for (int i = word.length()-2, count = 1; i >= 0; --i, ++count)
	{
		if (ptr_Arr[int((unsigned char)word[i])] == 0)
		{
			ptr_Arr[int((unsigned char)word[i])] = count;
		}
	}
	for (int i = 0; i < quant; ++i)
	{
		if (ptr_Arr[i] == 0)
		{
			ptr_Arr[i] = word.length();
		}
	}
	return ptr_Arr;
}

int BM(string str_val, string sub_str){
	int index_sub_str = sub_str.length()-1;
	int index_str_val = index_sub_str;
	int* arr = BM_ARR(sub_str);
	while ( index_str_val < str_val.length())
	{
		if (str_val[index_str_val] != sub_str[index_sub_str])
		{
			index_str_val += arr[ int( (unsigned char)str_val[index_str_val] ) ];
			index_sub_str = sub_str.length()-1;
		}
		else if (index_sub_str == 0)
		{
			return index_str_val+1;
		}
		else
		{
			--index_str_val;
			--index_sub_str;
		}
	}
	return -1;
}
