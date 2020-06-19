#include <iostream>
#include <string>
#include <iomanip> // 조작자를 사용하기 위한 헤더파일
using namespace std;

#include "Header.h"


User::User() : User("user") {};

User::User(string a)
{
	name = a;
	kind = 'M';
	cout << name << "님 환영합니다.\n";
}

void Player::enhance(char m)
{
	for (int q = 0; q < 6; q++) // 가지고 있는 유닛의 처음부터 끝까지 조사해 강화할 유닛이 있는지 확인
	{
		if (this->unit[q].dupli == 2 && this->unit[q].grade <3) // 중복이 총 3개인 유닛을 찾은 경우
		{
			if (this->unit[q].grade == 1)
			{
				for (int w = 0; w < 14; w++)
				{
					if (this->unit[q].name == un[w].name && this->unit[q].grade == un[w].grade) // 데이터베이스에서 이름과 등급이 같은 유닛을 찾음
					{
						this->unit[q] = un[w + 14]; // 14인덱스 뒤의 유닛을 가져옴 (14번 뒤의 원소는 등급이 올라간 해당 유닛)
						for (int r = 0; r < 6; r++)
						{
							if (this->unit[q].name == this->unit[r].name && this->unit[q].grade == this->unit[r].grade && q != r) // 만약 유닛 중 이미 같은 등급의 유닛이 있는 경우
							{
								this->unit[r].dupli++;
								for (int h = q; h < 5; h++)
									this->unit[h] = this->unit[h + 1];
								break;
							}
						}
						if (m == 'M')
						{
							cout << "강화된 유닛이 있습니다.\n";
							cout << "=============================================================\n";
						}
					}
				}
			}
			else if (this->unit[q].grade == 2)
			{
				for (int w = 14; w < 28; w++)
				{
					if (this->unit[q].name == un[w].name && this->unit[q].grade == un[w].grade) // 데이터베이스에서 이름과 등급이 같은 유닛을 찾음
					{
						this->unit[q] = un[w + 14]; // 14인덱스 뒤의 유닛을 가져옴 (14번 뒤의 원소는 등급이 올라간 해당 유닛)
						for (int r = 0; r < 6; r++)
						{
							if (this->unit[q].name == this->unit[r].name && this->unit[q].grade == this->unit[r].grade && q != r) // 만약 유닛 중 이미 같은 등급의 유닛이 있는 경우
							{
								this->unit[r].dupli++;
								for (int h = q; h < 5; h++)
									this->unit[h] = this->unit[h + 1];
								break;
							}
						}
						if (m == 'M')
						{
							cout << "강화된 유닛이 있습니다.\n";
							cout << "=============================================================\n";
						}
					}
				}
			}
		}
	}
}

void User::buy(UnitData a)
{
	if (this->unit[5].name != "") // 유닛이 가득 차서 더 이상 구매할 수 없는 경우
	{
		cout << "유닛이 전부 찼습니다.\n";
		cout << "유닛을 1개 이상 비우고 다시 시도하세요.\n";
	}
	else if (a.price > this->printmoney())
			cout << "돈이 모자라 구매하지 못하였습니다.\n";
	else 
	{
		for (int i = 0; i < 6; i++)
		{
			if (this->unit[i].name == a.name && this->unit[i].grade == a.grade)
			{
				this->unit[i].dupli++;
				this->setmoney(2, a.price);
				break;
			}
			if (this->unit[i].name == "") // 유닛 목록의 맨 끝에 구매한 유닛 포함
			{
				this->unit[i] = a;
				this->setmoney(2, a.price);
				break;
			}
		}
		this->enhance(this->kind);
	}
}

void User::sell(int n)
{
	if (this->unit[n-1].name == "")
		cout << "잘못된 입력입니다.\n";
	else
	{
		if (this->unit[n - 1].grade == 1) // 판 금액 받기
			this->setmoney(1, this->unit[n - 1].price - 1);
		else if (this->unit[n - 1].grade == 2)
			this->setmoney(1, this->unit[n - 1].price - 3);
		else if (this->unit[n - 1].grade == 3)
			this->setmoney(1, this->unit[n - 1].price - 5);
		
		this->unit[n - 1].name = ""; // 해당 구조체 배열 자리 비우기
		this->unit[n - 1].grade = 0;
		this->unit[n - 1].power = 0;
		this->unit[n - 1].life = 0;
		this->unit[n - 1].dupli = 0;
		this->unit[n - 1].grade = 0;

		cout << n  << "번 유닛을 판매했습니다.\n";
		cout << "(남은 돈 : " << this->printmoney() << ")\n";

		if (n != 6)
		{
			for (int i = n; i <= 5; i++) // 뒤에 있는 배열 멤버들 앞으로 당기기
			{
				this->swap(i, i + 1);
			}
		}
	}
}

void User::swap(int a, int b) // temp 구조체를 선언 후 앞 구조체의 멤버를 붙이는 방식으로 순서 바꾸기
{
		UnitData tmp;
		tmp.name = this->unit[a - 1].name;
		tmp.grade = this->unit[a - 1].grade;
		tmp.power = this->unit[a - 1].power;
		tmp.life = this->unit[a - 1].life = tmp.life;
		tmp.price = this->unit[a - 1].price = tmp.price;
		tmp.dupli = this->unit[a - 1].dupli = tmp.dupli;

		this->unit[a - 1].name = this->unit[b - 1].name;
		this->unit[a - 1].grade = this->unit[b - 1].grade;
		this->unit[a - 1].power = this->unit[b - 1].power;
		this->unit[a - 1].life = this->unit[b - 1].life;
		this->unit[a - 1].price = this->unit[b - 1].price;
		this->unit[a - 1].dupli = this->unit[b - 1].dupli;

		this->unit[b - 1].name = tmp.name;
		this->unit[b - 1].grade = tmp.grade;
		this->unit[b - 1].power = tmp.power;
		this->unit[b - 1].life = tmp.life;
		this->unit[b - 1].price = tmp.price;
		this->unit[b - 1].dupli = tmp.dupli;
}




