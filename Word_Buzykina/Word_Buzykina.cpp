#include <iostream>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <windows.h>
#include <TCHAR.H>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iterator>
typedef std::string TString;
using namespace std;
class Slovo {
	int type, rid, chislo, osoba, vidminok;
};
void SetConsole(const wchar_t* pszTitle = NULL, BOOL bFullScreen = FALSE)
{
	CONSOLE_FONT_INFOEX font;
	HANDLE hStdOut = NULL;

	// ������� ��������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// �����
	font.cbSize = sizeof font;
	font.nFont = 1;
	font.dwFontSize = { 9, 18 };
	font.FontFamily = 0 | FF_DONTCARE & ~TMPF_FIXED_PITCH;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, LF_FACESIZE, L"Lucida Console");

	// ��������� ������
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetCurrentConsoleFontEx(hStdOut, FALSE, &font))
		cout << "No";

	// ��������� � ������ �����...
	if (pszTitle)
		SetConsoleTitleW(pszTitle);
	if (bFullScreen)
		//      SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
//------------------------------------------------------------------
//�������, ������� ���������, ����������� �� ����� ���������
//������� ����
bool IsVowel(char letter) {
	char l = tolower(letter);
	TString a = "����峿��";
	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == l) return true;
	return false;
}
//------------------------------------------------------------------
//�������, ������� ���������, ����������� �� ����� ���������
//��������� ����
bool IsConsonant(char letter) {
	char l = tolower(letter);
	TString a = "���������������������";
	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == l) return true;
	return false;
}
//------------------------------------------------------------------
//�������, ������� ���������, ����������� �� ����� ���������
bool IsLetter(char letter) {
	char l = tolower(letter);
	TString a = "��������賿��������������������";
	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == l) return true;
	return false;
}
//------------------------------------------------------------------
//�������, ������� ��������� ������� ������� ����� � ������
bool ContainVowel(TString str) {
	for (size_t k = 0; k < str.length(); k++)
		if (IsVowel(str[k])) return true;
	return false;
}
//------------------------------------------------------------------
//�������, ������� �������� �� ������ �����
TString GetWord(TString str) {
	TString word;
	size_t i = 0, n = str.length();

	while (!IsLetter(str[i]) && i < n)
		i++;

	while (IsLetter(str[i]) && i < n) {
		word += str[i];
		i++;
	}

	return word;
}
//------------------------------------------------------------------
//�������, ������� ��������� ����� �� �����
TString SplitWord(TString str) {
	TString split, syll;
	size_t len = str.length(), i = 0;
	//���� ����� �����
	while (i < len) {
		//�������� 1-�� ��������
		if (IsConsonant(str[i]) && IsVowel(str[i + 1]) && IsVowel(str[i + 2])) {
			if (i + 3 < len) {
				syll = str.substr(i, 2);
				split.append(syll);
				split += '-';
				i += 2;
			}
		}
		else
			//�������� 1-�� �������� �� ������, ��������� 2-��
			if (IsVowel(str[i]) && IsConsonant(str[i + 1]) && IsConsonant(str[i + 2])) {
				if (i + 3 < len)
					if (ContainVowel(str.substr(i + 3))) {
						syll = str.substr(i, 2);
						split.append(syll);
						split += '-';
						i += 2;
					}
			}
			else
				//�������� 2-�� �������� �� ������, ��������� 3-�
			{
				size_t m = i;

				while (!IsVowel(str[m]) && m < len) m++;
				m++;
				syll = str.substr(i, m - i);
				if (m < len)
					if (ContainVowel(str.substr(m))) {
						split.append(syll);
						split += '-';
						i = m;
					}
			}
		split += str[i];
		i++;
		//�������������� ������� ��� ��������� �������
		if (IsVowel(str[i - 1]) && i < len)
			if (ContainVowel(str.substr(i)))
				split += '-';
	}
	return split;
}
//------------------------------------------------------------------
TString Processing(TString str) {
	size_t start, end = str.length();
	TString text, word;
	//�-��-���
	for (size_t i = 0; i < end; i++) {
		start = i;
		//��������� ���������� �����
		word = GetWord(str.substr(start, end));
		i += word.length();
		//�������� �� �����
		text.append(SplitWord(word));
		//����� �������� �� �����
		//������� ������ ����������
		while (!IsLetter(str[i]) && i < end) {
			text += str[i];
			i++;
		}
		i--;
	}
	return text;
}
TString BackProcess(TString str1) {
	size_t end = str1.length();
	string nullmas = "";
	for (const auto c : str1) {
		if (!ispunct(c)) {

			nullmas.push_back(c);
		}
	}
	str1 = nullmas;
	return str1;
}
int check(TString checking) {
	TString ent = checking;
	TString get;
	for (size_t i = 0; i < ent.length(); i++) {
		if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') {
			cout << "�������: ���" << endl;
			if (ent.length() > 5) {
				if (ent[i + 3] == '�' && ent[i + 4] == '�' && ent[i + 5] == '�') cout << "������� (2): ���" << endl;
				if (ent[i + 3] == '�' && ent[i + 4] == '�' && ent[i + 5] == '�') cout << "������� (2): ��" << endl;
				if (ent[i + 3] == '�' && ent[i + 4] == '�' && ent[i + 5] == '�') cout << "������� (2): ��" << endl;
				if (ent[i + 3] == '�' && ent[i + 4] == '�' && ent[i + 5] == '�') cout << "������� (2): ���" << endl;
				if (ent[i + 3] == '�' && ent[i + 4] == '�' && ent[i + 5] == '�') cout << "������� (2): ���" << endl;
			}
			return false;
		}
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�' && ent[i + 3] == '�' && ent[i + 4] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�' && ent[i + 3] == '�' && ent[i + 4] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�' && ent[i + 3] == '�' && ent[i + 4] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�' && ent[i + 3] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�' && ent[i + 3] == '�' && ent[i + 4] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�' && ent[i + 2] == '�' && ent[i + 3] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�') return true;
		else if (ent[i] == '�' && ent[i + 1] == '�') return true;
		else if (ent[i] == '�') return true;
		else if (ent[i] == '�') return true;
		else cout << "�������� ����" << endl;
	}
	return true;
}
void other_check(TString geti) {
	TString get = geti;
	if (get == "���" || get == "���" || get == "�����" || get == "��" || get == "��" || get == "��" || get == "���" || get == "��"
		|| get == "�����" || get == "��" || get == "�����" || get == "����" || get == "�����"
		|| get == "���" || get == "���" || get == "��" || get == "����" || get == "�" || get == "��" || get == "��"
		|| get == "�" || get == "�") {
	}
	else {
		cout << "������ �������� �� ����";
		exit(0);
	}
}
void EnterChar() {
	TString pref = "p", corin = "c", suf = "s", ending = "e";
	int number_pref;
	cout << "������ ��������? (0-3): ";
	cin >> number_pref;
	if (number_pref == 1) {
		cout << "�������: ";
		cin >> pref;
		other_check(pref);
	}
	else if (number_pref == 2) {
		TString pref1;
		cout << "������� (1): ";
		cin >> pref;
		other_check(pref);
		cout << "������� (2): ";
		cin >> pref1;
		other_check(pref1);
		pref += pref1;
	}
	else if (number_pref == 3) {
		TString pref1, pref2;
		cout << "������� (1): ";
		cin >> pref;
		other_check(pref);
		cout << "������� (2): ";
		cin >> pref1;
		other_check(pref1);
		cout << "������� (3): ";
		cin >> pref2;
		other_check(pref2);
		pref += pref1 + pref2;
	}
	cout << "�����: ";
	cin >> corin;
	if (corin == "p") {
		cout << "� ����� �� ���� ���� � ���� �����";
		return EnterChar();
	}
	cout << "������: ";
	cin >> suf;
	cout << "���������: ";
	cin >> ending;
	if (number_pref == 0) cout << "�����: " << corin << suf << ending << endl;
	else cout << "�����: " << pref << corin << suf << ending << endl;
}
void ReloadSlovo(TString slovo) {
	TString word = slovo;
	check(word);
}
//------------------------------------------------------------------
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	SetConsole();
	TString text, text1, t1, slovo;
	cout << "�����: ";
	getline(cin, text);
	cout << "��������: " << Processing(text) << endl;
	cout << "-----------------------------------------" << endl;
	cout << "�����: ";
	getline(cin, text1);
	remove_copy(text1.begin(), text1.end(), back_inserter(t1), '-');
	cout << "������: " << t1 << endl;
	cout << "-----------------------------------------" << endl;
	EnterChar();
	cout << "����� ��� ��������� �� ��������: ";
	cin >> slovo;
	ReloadSlovo(slovo);
	system("pause");
	return 0;
}
