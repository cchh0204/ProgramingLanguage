#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#define PATH "list.txt"
using namespace std;

class Account {
	string code; // ���¹�ȣ
	string owner; //������
	int bal; //�ܾ�
	string password; // ��й�ȣ
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
		cout << "���Ͼ���" << endl;
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
			int bal = stoi(line[2]); // ���ڿ� "10000"�� ���� 10000���� ��ȯ
			string password = line[3];

			accounts[code] = Account(code, owner, bal, password);
		}
		else {
			cout << "�ùٸ��� �ʽ��ϴ�." << endl;
		}
	}
	fin.close();
	return 1;
}

bool filewrite(string path, map<string, Account>& accounts)
{
	ofstream fout(path);
	if (!fout) { // ���� ���� �˻�
		cout << "���Ͽ��� ����" << endl;
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
		cout << "1.���µ��  2.������������  3.��Ȳ����  4.���� : ";
		cin >> select;
		switch (select)
		{
		case 1: {
			cout << "##���µ��" << endl;
			cout << "���¹�ȣ : "; cin >> code;
			cout << "������ : "; cin >> owner;
			cout << "�ܾ� : "; cin >> bal;
			cout << "��й�ȣ : "; cin >> password;
			Account newAccount(code, owner, bal, password);

			if (accounts.find(code) == accounts.end()) // ���¹�ȣ�� ���ٸ�.
			{
				accounts[code] = newAccount;
				
				filewrite(PATH, accounts);

				cout << "��ϵǾ����ϴ�. " << endl;
				cout << endl;
			}
			else
			{
				cout << "�̹� ��ϵ� �����Դϴ�." << endl;
				cout << endl;
			}

			
			break;
		}
		case 2:
			

			cout << "##���¼���" << endl;
			cout << "���¹�ȣ : "; cin >> code;

			it = accounts.find(code);

			if (it != accounts.end()) {
				cout << "������: "; cin >> owner;
				cout << "�ܾ�: "; cin >> bal;
				cout << "��й�ȣ: "; cin >> password;
				
				it->second.setOwner(owner);
				it->second.setBal(bal);
				it->second.setPassword(password);

				filewrite(PATH, accounts);

				cout << "����Ǿ����ϴ�. " << endl;
			}
			else 
				cout << "�������� �ʴ� �����Դϴ�." << endl;
			
			break;

		case 3:
			cout << "##��Ȳ����" << endl;
			showAccounts(accounts);
			cout << endl;
			break;

		case 4:
			cout << "�����մϴ�" << endl;
			cout << endl;
			break;

		default:;
		}
	}




}
