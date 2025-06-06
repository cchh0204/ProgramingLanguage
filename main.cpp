#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#define PATH "list.txt"
using namespace std;

class Account {
	string code; // 계좌번호
	string owner; //예금주
	int bal; //잔액
	string password; // 비밀번호
public:
	Account(string code =" ", string owner = " " , int bal = 0, string password = " ");
	string getCode() { return code; };
	string getOwner() { return owner; };
	int getBal() { return bal; };
	string getPassword() { return password; };

	void setOwner(string newowner) { this->owner = newowner; }
	void setBal(int newbal) { this->bal = newbal; }
	void setPassword(string newpassword) { this->password = newpassword; }
	
};

Account::Account(string code, string owner, int bal, string password) {
	this->code = code;
	this->owner = owner;
	this->bal = bal;
	this->password = password;
}




vector<string> split(string str, string delimiter)
{
	vector<string> v;
	int sidx = 0;
	while (true)
	{
		int fidx = str.find(delimiter, sidx);
		if (fidx == -1)
		{
			v.push_back(str.substr(sidx));
			break;
		}
		v.push_back(str.substr(sidx, fidx - sidx));
		sidx = fidx + delimiter.length();
	}
	return v;
}

bool fileread(string path, map<string, Account>& accounts)
{
	ifstream fin(path);
	if (!fin) {
		cout << "파일없음" << endl;
		ofstream fout(path);
		fout.close();
		return 0;
	}

	string buf;
	while (getline(fin, buf))
	{
		vector<string> line = split(buf, " ");
		
		if (line.size() == 4) {
			string code = line[0];
			string owner = line[1];
			int bal = stoi(line[2]); // 문자열 "10000"을 정수 10000으로 변환
			string password = line[3];

			accounts[code] = Account(code, owner, bal, password);
		}
		else {
			cout << "올바르지 않습니다." << endl;
		}
	}
	fin.close();
	return 1;
}

bool filewrite(string path, map<string, Account>& accounts)
{
	ofstream fout(path);
	if (!fout) { // 열기 실패 검사
		cout << "파일열기 실패" << endl;
		return 0;
	}

	for (auto item : accounts)
	{
		Account& acc = item.second;
		fout << acc.getCode() << " "
			<< acc.getOwner() << " "
			<< acc.getBal() << " "
			<< acc.getPassword() << endl;
	}
	fout.close();
	return 1;
}


void showAccounts(map<string, Account>& accounts)
{
	for (auto& pair : accounts)
	{
		Account& acc = pair.second;
		cout << acc.getCode() << " " << acc.getOwner() << endl;
	}
}

int main()
{
	map<string, Account> accounts;
	map<string, Account>::iterator it;
	string code, owner, password;
	int bal;
	int select = 0;

	fileread(PATH, accounts); 


	while (select != 4)
	{
		cout << "1.계좌등록  2.계좌정보수정  3.현황보기  4.종료 : ";
		cin >> select;
		switch (select)
		{
		case 1: {
			cout << "##계좌등록" << endl;
			cout << "계좌번호 : "; cin >> code;
			cout << "예금주 : "; cin >> owner;
			cout << "잔액 : "; cin >> bal;
			cout << "비밀번호 : "; cin >> password;
			Account newAccount(code, owner, bal, password);

			if (accounts.find(code) == accounts.end()) // 계좌번호가 없다면.
			{
				accounts[code] = newAccount;
				
				filewrite(PATH, accounts);

				cout << "등록되었습니다. " << endl;
				cout << endl;
			}
			else
			{
				cout << "이미 등록된 계좌입니다." << endl;
				cout << endl;
			}

			
			break;
		}
		case 2:
			

			cout << "##계좌수정" << endl;
			cout << "계좌번호 : "; cin >> code;

			it = accounts.find(code);

			if (it != accounts.end()) {
				cout << "예금주: "; cin >> owner;
				cout << "잔액: "; cin >> bal;
				cout << "비밀번호: "; cin >> password;
				
				it->second.setOwner(owner);
				it->second.setBal(bal);
				it->second.setPassword(password);

				filewrite(PATH, accounts);

				cout << "변경되었습니다. " << endl;
			}
			else 
				cout << "존재하지 않는 계좌입니다." << endl;
			
			break;

		case 3:
			cout << "##현황보기" << endl;
			showAccounts(accounts);
			cout << endl;
			break;

		case 4:
			cout << "종료합니다" << endl;
			cout << endl;
			break;

		default:;
		}
	}




}
