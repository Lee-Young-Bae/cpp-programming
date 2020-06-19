#include <iostream>
#include <fstream> // 파일 입출력을 위한 헤더파일
#include <iomanip> // 조작자를 사용하기 위한 헤더파일
#include <cstdlib> // 난수 생성을 구현하기 위한 헤더파일
#include <ctime> // 난수 생성을 구현하기 위한 헤더파일
#include <windows.h> // Sleep()를 구현하기 위한 헤더파일
using namespace std;

#include "Header.h"
#include "Func.h"

void MyTeamInfo(User* a)
{
	int d;
	do
	{
	    cout << "나의 팀 정보\n";
		cout << "=============================================================\n";
		cout << setw(8) << "번호";
		cout << setw(8) << "이름";
		cout << setw(8) << "등급";
		cout << setw(10) << "공격력";
		cout << setw(8) << "체력";
		cout << setw(8) << "가격";
		cout << setw(8) << "중복\n";
		cout << "-------------------------------------------------------------\n";

		for (int i = 0; i < 6; i++)
		{
			cout << setw(8) << i+1;
			if (a->unit[i].name != "")
			{
				cout << setw(8) << a->unit[i].name;
				cout << setw(8) << a->unit[i].grade;
				cout << setw(10) << a->unit[i].power;
				cout << setw(8) << a->unit[i].life;
				cout << setw(8) << a->unit[i].price;
				cout << setw(8) << a->unit[i].dupli;
			}
			cout << "\n";
		}

		cout << "남은 생명 포인트 : " << a->printlife() << "\n";
		cout << "남은 돈 : "  << a->printmoney() << "전" << "\n";

		
			cout << "\n1. 순서 바꾸기  2. 판매  3. 생명<->돈 교환  4. 나가기\n";
			cout << "선택 : ";
			cin >> d;

			switch (d)
			{
			case 1:
			{
				cout << "\n바꿀 두 유닛의 순서를 입력해 주세요 : ";
				int q, w;
				cin >> q >> w;
				if (a->unit[q - 1].name == "" || a->unit[w - 1].name == "")
				{
					cout << "바꿀 수 없습니다.\n";
				}
				else a->swap(q, w);
			}break;
			case 2:
			{
				cout << "\n판매할 유닛의 번호를 입력해 주세요 : ";
				int e;
				cin >> e;
				a->sell(e);
			}break;
			case 3:
			{
				cout << "\n1전 = 1생명 의 가치를 가집니다.\n";
				cout << "원하는 서비스를 골라주세요.\n";
				cout << "1. 돈->생명포인트   2. 생명포인트->돈\n";
				cout << "선택 : ";
				int r;
				cin >> r;
				if (r == 1)
				{
					cout << "얼마의 돈을 생명 포인트로 바꾸시겠습니까?\n";
					int t;
					cin >> t;
					if (t > a->printmoney())
					{
						cout << "가지고 있는 돈만큼만 바꿀 수 있습니다.\n";
						cout << "=============================================================\n";
					}
					else
					{
						a->setmoney(2, t);
						a->setlife(1, t);
					}
				}
				else if (r == 2)
				{
					cout << "얼마의 생명 포인트를 돈으로 바꾸시겠습니까? : ";
					int t;
					cin >> t;
					if (t >= a->printlife())
					{
						cout << "현재 생명 포인트 - 1 까지의 값만 가능합니다.\n";
						cout << "=============================================================\n";
					}
					else
					{
						a->setmoney(1, t);
						a->setlife(2, t);
					}
				}
			}break;
			default:
				break;
			}
		} while (d != 4);
	cout << "=============================================================\n";
}

int storerand[5]; // 전역 공간에 난수를 저장하는 정수 배열 선언

UnitData UnitShop(User a)
{
	int e;

	UnitData shop[5];

	if (shopbalance <= Player::turn) // 턴이 바뀐 경우 (처음 방문하면 임의의 유닛 제공)
	{
		if (Player::turn <= 50) // 20턴 이상 넘어가면 3등급의 유닛도 상점에서 제공
		{
			if (Player::turn <= 20) // 10턴 이상 넘어가면 2등급의 유닛도 상점에서 제공
			{
				if (Player::turn <= 10) // 10턴 이하이면 1등급의 유닛만 상점에서 제공
				{
					for (int i = 0; i < 5; i++)
						storerand[i] = rand() % 14;
				}
				else for (int i = 0; i < 5; i++)
					storerand[i] = rand() % 28;
			}
			else for (int i = 0; i < 5; i++)
				storerand[i] = rand() % 42;
		}
		for (int f = 0; f < 5; f++)
			shop[f] = un[storerand[f]]; // 생성된 난수에 해당하는 유닛을 데이터베이스에서 찾아 상점에 가져옴
	}
	else
	{
		for (int t = 0; t < 5; t++)
			shop[t] = un[storerand[t]];
	}

	cout << "=============================================================\n";
	cout << "유닛 상점\n";
	cout << "(상점 유닛은 매 턴마다 무작위로 제공됩니다.)\n";
	cout << "현재 가진 돈 : " << a.printmoney() << "전";
	cout << "\n-------------------------------------------------------------\n";
	cout << setw(8) << "번호";
	cout << setw(8) << "이름";
	cout << setw(8) << "등급";
	cout << setw(10) << "공격력";
	cout << setw(8) << "체력";
	cout << setw(8) << "가격";
	cout << "\n-------------------------------------------------------------\n";

	for (int i = 0; i < 5; i++)
	{
		cout << setw(8) << i + 1;
		cout << setw(8) << shop[i].name;
		cout << setw(8) << shop[i].grade;
		cout << setw(10) << shop[i].power;
		cout << setw(8) << shop[i].life;
		cout << setw(8) << shop[i].price;
		cout << "\n";
	}

	do
	{
		cout << "구매를 원하는 유닛의 번호를 입력해 주세요 : ";
		cin >> e;
	} while (e < 1 || e>5);
	cout << shop[e - 1].name << "(을)를 구매합니다.\n";
	cout << "=============================================================\n";

	shopbalance = Player::turn + 1; // 구매가 끝나면 shopbalance 변수를 턴 수보다 1 늘려 다음 번 상점 방문 시 난수 생성 조건에 맞지 않게 함
	return shop[e - 1];
}

void Matchnum(int *p,int i)
{
	int temp;

	for (int m = 0; m < i; m++) // 배열의 각 멤버를 정수 순서대로 쭉 나열함
	{
		p[m] = m+1;
	}
	for (int s = 0; s < 20; s++) // 순서를 20번 섞음
	{
		int x = rand()% i;
		int y = rand()% i;

		if (x != y)
		{
			temp = p[x]; // 생성된 난수 x,y를 이용해 배열의 순서를 섞음
			p[x] = p[y];
			p[y] = temp;
		}
	}

}

void matchingresult(User a, Com* com, int num)
{
	if (Player::plnum % 2 == 0) // 플레이어 수가 짝수인 경우
	{
		cout << a.printname() << " VS "  << com[find(com)].printname() << "\n"; // 사용자 플레이어와 상대 플레이어는 미리 정해짐
		for (int i = 2; i <= Player::plnum; i++) // 나머지 컴퓨터 플레이어는 규칙에 따라 정렬
		{
			for (int j = 0; j < num; j++)
			{
				if (i == com[j].printmatchnum()) // matchnum 순서에 따라 출력
				{
					if (i % 2 == 0) // 짝수이면 VS 표시를 넣음
						cout << com[j].printname() << " VS ";
					else cout << com[j].printname() << "\n"; // 홀수이면 한줄 띄우기
					break;
				}
			}
		}
		
	}
	else // 플레이어 수가 홀수인 경우
	{
		cout << a.printname() << " VS " << com[find(com)].printname() << "\n"; // 사용자 플레이어와 상대 플레이어는 미리 정해짐
		for (int i = 2; i < Player::plnum; i++) // 나머지 컴퓨터 플레이어는 규칙에 따라 정렬하여 출력
		{
			for (int j = 0; j < num; j++)
			{
				if (i == com[j].printmatchnum()) // matchnum 순서에 따라 출력
				{
					if (i % 2 == 0) // 짝수이면 VS 표시를 넣음
					{
						cout << com[j].printname() << " VS ";
						if (i == Player::plnum - 1) // 마지막에 혼자 남은 인덱스인 경우
						{
							for (int i = 0; i < num; i++) // matchnum이 하나 적은 플레이어와 매칭
							{
								if (com[j].printmatchnum() - com[i].printmatchnum() == 1)
									cout << com[i].printname() << "\n";
							}
							//cout << com[j-1].printname() << "\n";
						}
					}
					else cout << com[j].printname() << "\n"; // 홀수이면 한줄 띄우기
					break;
				}
			}
		}
	}
}

int find(Com *com)
{
	for (int q = 0; q < Player::plnum - 1; q++)
	{
		if (com[q].printmatchnum() == 1)
			return q;
	}
}


int battle(User a, Com b)
{
	int aunit, bunit;
	int z = 0, x = 0;

	aunit = a.printunit();
	bunit = b.printunit();

	cout << "2초 후에 경기가 시작됩니다.\n";
	//Sleep(2000);
	cout << a.printname() << "(가진 유닛 : " << aunit << ")"  "   VS   " << b.printname() << "(가진 유닛 : " << bunit << ")" << "의 경기를 시작합니다.\n";
	cout << "=============================================================\n";
	cout << "\n";
	cout << setw(20)<< left << a.printname();
	cout << setw(10) << "  VS  ";
	cout << setw(20) << right << b.printname();
	cout << "\n";
	
	int life1 = a.unit[z].life, life2 = b.unit[x].life, damage; // 각 유닛의 체력과 임의로 결정되는 데미지값을 변수로 선언

	do
	{
		
	    cout << "-------------------------------------------------------------\n";

		cout << setw(20) << left << z; // 유닛 번호(순서) 출력
		cout << setw(10) << " *** ";
		cout << setw(20) << right << x;
		cout << "\n";
		cout << setw(20) << left << a.unit[z].name; // 유닛 이름 출력
		cout << setw(10) << " *** ";
		cout << setw(20) << right << b.unit[x].name;
		cout << "\n";
		if (a.unit[z].grade == 1) // 사용자 유닛 등급 출력
			cout <<setw(20) <<left << "★";
		if (a.unit[z].grade == 2)
			cout << setw(20) << left << "★★";
		if (a.unit[z].grade == 3)
			cout << setw(20) << left << "★★★";
		cout << setw(10) << " *** ";
		if (b.unit[x].grade == 1) // 컴퓨터 유닛 등급 출력
			cout << setw(20) << right << "★";
		if (b.unit[x].grade == 2)
			cout << setw(20) << right << "★★";
		if (b.unit[x].grade == 3)
			cout << setw(20) << right << "★★★";

		cout << "\n";
		cout << "\n";
		cout << setw(20) << left << "남은 체력";
		cout << setw(10) << "방향(데미지)";
		cout << setw(20) << right << "남은 체력";
		cout << "\n";
		cout << "\n";

		int n = 0;
		do
		{
			if (n % 2 == 0) // 번갈아가며 공격을 수행
			{
				damage = attack(a.unit[z].power);
				life2 -= damage;
				cout << setw(20) << left << life1;
				cout << setw(8) << left << " >>> ";
				cout << setw(2) << left << damage;
				cout << setw(20) << right << life2;
				n++;
				cout << "\n";
			}
			else
			{
				damage = attack(b.unit[x].power);
				life1 -= damage;
				cout << setw(20) << left << life1;
				cout << setw(2) << right << damage;
				cout << setw(8) << left << " <<< ";
				cout << setw(20) << right << life2;
				n++;
				cout << "\n";
			}
			//Sleep(800);
		} while (life1 > 0 && life2 > 0);

		if (life1 <= 0) // 사용자의 유닛이 아웃된 경우
		{
			cout << a.printname() << "의 " << a.unit[z].name << " 아웃!\n";
			aunit -= 1;
			z++;
			life1 = a.unit[z].life;
		}
		else if (life2 <= 0) // 컴퓨터 플레이어의 유닛이 아웃된 경우
		{
			cout << b.printname() << "의 " << b.unit[x].name << " 아웃!\n";
			bunit -= 1;
			x++;
			life2 = b.unit[x].life;
		}

		
		cout << "\n";
	} while (aunit != 0 && bunit != 0);
	
	// 경기 종료 후 승자 및 패자 처리
	if (aunit == 0) // 사용자가 패배한 경우
	{
		int sum = 0;
		for (int e = 0; e < 6; e++)
		{
			if (a.unit[e].grade == 1)
				sum += 1;
			else if (a.unit[e].grade == 2)
				sum += 2;
			else if (a.unit[e].grade == 2)
				sum += 3;
		}
		cout << "-------------------------------------------------------------\n";
		cout << a.printname() << "패배\n";
		cout << "생명 포인트가 " << sum << " 차감되었습니다.\n"; 
		return 0;
	}
	else // 사용자가 승리한 경우
	{
		int sum = 0;
		for (int e = 0; e < 6; e++)
		{
			if (b.unit[e].grade == 1)
				sum += 1;
			else if (b.unit[e].grade == 2)
				sum += 2;
			else if (b.unit[e].grade == 2)
				sum += 3;
		}
		cout << "-------------------------------------------------------------\n";
		cout << b.printname() << "패배\n";
		cout << "생명 포인트가 " << sum << " 차감되었습니다.\n"; 
		return 1;
	}
    
}

int attack(int a) // 임의의 난수로 사용자의 유닛이 공격할 값을 정하는 함수
{
	int r = rand() % 100;
	int k;
	if (r >= 70) // 70%의 확률로 자신의 원래 공격력만큼 공격
		return a;
	else // 20%의 확률로 0~ 자신의 공격력만큼 공격
	{
		k = rand() % a;
		return k;
	}
}

void commatch(int* p, Com* com, int a) // 컴퓨터 플레이어간의 경기(combattle 함수)를 위해 matchnum에 따라 정렬하기 위한 함수
{
	int n = 2;
	for (int i = 0; i < Player::plnum - 1; i++)
	{
		for (int j = 0; j < a; j++)
		{
			if (n == com[j].printmatchnum())
			{
				p[i] = j;
				n++;
				break;
			}
		}
	}
}

int combattle(Com a, Com b)
{
	
	int aunit, bunit;
	int z = 0, x = 0;

	aunit = a.printunit();
	bunit = b.printunit();

	int life1 = a.unit[z].life, life2 = b.unit[x].life, damage; // 각 유닛의 체력과 임의로 결정되는 데미지값을 변수로 선언

	do
	{
		int n = 0;
		do
		{
			if (n % 2 == 0) // 번갈아가며 공격을 수행
			{
				damage = attack(a.unit[z].power);
				life2 -= damage;
				n++;
			}
			else
			{
				damage = attack(b.unit[x].power);
				life1 -= damage;
				n++;
			}
		} while (life1 > 0 && life2 > 0);

		if (life1 <= 0) // 앞 플레이어의 유닛이 아웃된 경우
		{
			aunit -= 1;
			z++;
			life1 = a.unit[z].life;
		}
		else if (life2 <= 0) // 뒤 플레이어의 유닛이 아웃된 경우
		{
			bunit -= 1;
			x++;
			life2 = b.unit[x].life;
		}
	} while (aunit != 0 && bunit != 0);

	// 경기 종료 후 승자 및 패자 처리
	if (aunit == 0) // 뒤 플레이어가 승리한 경우
		return 0;
	else if(bunit == 0)
		return 1; // 앞 플레이어가 승리한 경우

}

void rankinit(User* a, Com* com, int num)
{
	a->clearrank();
	for (int i = 0; i < num; i++)
	{
		if(com[i].printstatus() != 0)
		com[i].clearrank();
	}
}

void ranking(User* a, Com* com, int num)
{
	for (int y = 0; y < num; y++) // 먼저 컴퓨터 플레이어끼리 순위를 매김
	{
		if (com[y].printstatus() != 0)
		{
			for (int z = 0; z < num; z++)
			{
				if (com[y].printname() != com[z].printname()) // 플레이어 자신은 순위 비교 대상에서 제외 ( && 생명 포인트가 0보다 커야함)
				{
					if (com[z].printstatus() != 0) // 비교하고자 하는 플레이어의 상태가 0(게임 오버)이 아닌 경우
					{
						if (com[y].printlife() == com[z].printlife()) // 생명 포인트가 같은 경우
						{
							if (com[y].printmatchnum() < com[z].printmatchnum()) // matchnum으로 순위를 매김(동점자를 matchnum 내림차순으로 처리)
								com[y].setrank();
						}
						else if (com[y].printlife() < com[z].printlife()) // 생명 포인트가 낮으면 순위를 내림
							com[y].setrank();
					}

				}
			}
		}
	}
	for (int w = 0; w < num; w++) // 사용자와 컴퓨터 플레이어간의 순위를 매김
	{
		if (com[w].printstatus() != 0)
		{
			if (a->printlife() >= com[w].printlife()) // 사용자의 생명 포인트보다 낮은 플레이어는 순위를 내림
			{
				com[w].setrank();
			}
			else a->setrank();
		}
	}
}

void battleresult(User a, Com* com, int* p, int num)
{
	
	cout << "-------------------------------------------------------------\n";
	cout << "경기 결과\n";
	cout << "\n";
	cout << setw(10) << "순위";
	cout << setw(10) << "이름";
	cout << setw(15) << "생명포인트";
	cout << setw(10) << "변동";
	cout << "\n";
	cout << "-------------------------------------------------------------\n";
	for (int m = 1; m <= Player::plnum; m++)
	{
		if (m == a.printrank())
		{
			cout << setw(10) << m;
			cout << setw(10) << a.printname();
			cout << setw(15) << a.printlife();
			cout << setw(10) << p[0] - a.printrank(); 
			cout << "\n";
		}
		else
		{
			for (int t = 0; t < num; t++)
			{
				if (m == com[t].printrank() && com[t].printlife() !=0)
				{
					cout << setw(10) << m;
					cout << setw(10) << com[t].printname();
					cout << setw(15) << com[t].printlife();
					cout << setw(10) << p[t+1] - com[t].printrank(); 
					cout << "\n";
				}
			}
		}
	}

	p[0] = a.printrank();
	for (int i = 1; i < Player::plnum; i++)
	{
		p[i] = com[i - 1].printrank();
	}
}

void manual()
{
	const char* file = "32153350.txt";
	char m[32];
	int count = 0;

	ifstream fin;
	fin.open(file, ios::in | ios::binary); // 읽기 모드로 정해진 파일을 연다
	if (!fin)
	{
		cout << "파일을 열 수 없습니다.\n";
	}

	while (!fin.eof())
	{
		fin.read(m, 32);
		int n = fin.gcount();
		cout.write(m, n);
		count += n;
	}

	fin.close();
}

void printdatabase() // 모든 유닛의 정보를 출력하는 함수 (처음 선택에서 3번을 누르면 볼 수 있음)
{
	cout << "유닛 정보\n";
	cout << "=============================================================\n";
	cout << setw(8) << "이름";
	cout << setw(8) << "등급";
	cout << setw(10) << "공격력";
	cout << setw(8) << "체력";
	cout << setw(8) << "가격\n";
	cout << "-------------------------------------------------------------\n";

	for (int i = 0; i < 42; i++)
	{
		cout << setw(8) << un[i].name;
		cout << setw(8) << un[i].grade;
		cout << setw(10) << un[i].power;
		cout << setw(8) << un[i].life;
		cout << setw(8) << un[i].price;
		cout << "\n";
	}
	cout << "=============================================================\n";
}