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
		cout << "파일없음" << endl;
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
	if (!fout) { // 열기 실패 검사
		cout << "파일열기 실패" << endl;
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
	map<string, int>::iterator it; //자료구조 조회를 위한 포인터
	string prod;
	int cnt;
	int select = 0;

	fileread(PATH, s); // s가 map,즉 저장소


	while (select != 4)
	{
		cout << "1.입고  2.출고  3.현황  4.종료 : ";
		cin >> select;
		switch (select)
		{
		case 1:
			//입고리처리부
			cout << "상품명 : "; cin >> prod;
			cout << "수량 : "; cin >> cnt;

			if (s.find(prod) == s.end()) //재고에 제품이 등록되지 않았다면.
			{
				s[prod] = cnt; // prod라는 제품이 cnt개 최초 등록됨
			}
			else
			{
				s[prod] += cnt; // 기존 등록정보가 있으면 cnt만큼 증가
			}
			cout << "입고되었습니다" << endl;

			filewrite(PATH, s);

			break;
		case 2:
			//출고처리부
			cout << "상품명 : "; cin >> prod;
			cout << "수량 : "; cin >> cnt;

			if (s.find(prod) == s.end()) //재고에 제품이 등록되지 않았다면.
			{
				cout << "상품이 재고에 없습니다." << endl;
			}
			else
			{
				if (s[prod] < cnt) {
					cout << "출고량이 재고량 보다 많습니다. 전부 출고합니다." << endl;
					s[prod] = 0;
					s.erase(prod);
					filewrite(PATH, s);
				}
				else {
					s[prod] -= cnt; // 기존 등록정보가 있으면 cnt만큼 감소
					filewrite(PATH, s);
					if (s[prod] == 0) {
						s.erase(prod);
						filewrite(PATH, s);
					}
					cout << "출고되었습니다" << endl;
				}
			}
			
			

			break;
		case 3:
			//현황처리
			for (it = s.begin(); it != s.end(); it++)
			{
				cout << it->first << " : " << it->second << endl;
			}

			break;
		case 4:
			cout << "종료합니다" << endl;
			break;
		default:;
		}
	}




}
