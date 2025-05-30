#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#define PATH "storage.txt"

using namespace std;
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

bool fileread(string path, map<string, int>& storage)
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
		//cout << buf << endl;
		storage[line[0]] = stoi(line[1]);
	}
	fin.close();
	return 1;
}

bool filewrite(string path, map<string, int> storage)
{
	ofstream fout(path);
	if (!fout) { // ���� ���� �˻�
		cout << "���Ͽ��� ����" << endl;
		return 0;
	}

	for (auto item : storage)
	{
		fout << item.first << " " << item.second << endl;
	}
	fout.close();
}


void showMap(map<string, int>& storage)
{
	for (auto item : storage)
	{
		cout << item.first << ":" << item.second << endl;
	}
}


#include<iostream>
#include<string>
#include<map>
using namespace std;

int main()
{
	map<string, int> s;
	map<string, int>::iterator it; //�ڷᱸ�� ��ȸ�� ���� ������
	string prod;
	int cnt;
	int select = 0;

	fileread(PATH, s); // s�� map,�� �����


	while (select != 4)
	{
		cout << "1.�԰�  2.���  3.��Ȳ  4.���� : ";
		cin >> select;
		switch (select)
		{
		case 1:
			//�԰�ó����
			cout << "��ǰ�� : "; cin >> prod;
			cout << "���� : "; cin >> cnt;

			if (s.find(prod) == s.end()) //��� ��ǰ�� ��ϵ��� �ʾҴٸ�.
			{
				s[prod] = cnt; // prod��� ��ǰ�� cnt�� ���� ��ϵ�
			}
			else
			{
				s[prod] += cnt; // ���� ��������� ������ cnt��ŭ ����
			}
			cout << "�԰�Ǿ����ϴ�" << endl;

			filewrite(PATH, s);

			break;
		case 2:
			//���ó����
			cout << "��ǰ�� : "; cin >> prod;
			cout << "���� : "; cin >> cnt;

			if (s.find(prod) == s.end()) //��� ��ǰ�� ��ϵ��� �ʾҴٸ�.
			{
				cout << "��ǰ�� ��� �����ϴ�." << endl;
			}
			else
			{
				if (s[prod] < cnt) {
					cout << "����� ��� ���� �����ϴ�. ���� ����մϴ�." << endl;
					s[prod] = 0;
					s.erase(prod);
					filewrite(PATH, s);
				}
				else {
					s[prod] -= cnt; // ���� ��������� ������ cnt��ŭ ����
					filewrite(PATH, s);
					if (s[prod] == 0) {
						s.erase(prod);
						filewrite(PATH, s);
					}
					cout << "���Ǿ����ϴ�" << endl;
				}
			}
			
			

			break;
		case 3:
			//��Ȳó��
			for (it = s.begin(); it != s.end(); it++)
			{
				cout << it->first << " : " << it->second << endl;
			}

			break;
		case 4:
			cout << "�����մϴ�" << endl;
			break;
		default:;
		}
	}




}
