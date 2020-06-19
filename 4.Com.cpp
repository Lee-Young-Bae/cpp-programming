#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Header.h"

Com::Com() : Com(0) {}; // 위임 연산자

Com::Com(int n)
{
	kind = 'C';
	name = "Com";
	name.append(to_string(n+1));
}


void Com::buy(UnitData a) // 컴퓨터 플레이어가 유닛을 구매하는 과정
{
	if (this->printlife() != 0)
	{
		UnitData comshop[5];
		int buy = 0; // 컴퓨터 플레이어가 이번 턴에 구매한 유닛 수(0이 될때까지 구매를 반복)

		if (Player::turn <= 30) // 30턴 이상 넘어가면 3등급의 유닛도 상점에서 제공
		{
			if (Player::turn <= 20) // 20턴 이상 넘어가면 2등급의 유닛도 상점에서 제공
			{
				if (Player::turn <= 10) // 10턴 이하이면 1등급의 유닛만 상점에서 제공
				{
					for (int i = 0; i < 5; i++)
						comshop[i] = un[rand() % 14];
				}
				else for (int i = 0; i < 5; i++)
					comshop[i] = un[rand() % 28];
			}
			else for (int i = 0; i < 5; i++)
				comshop[i] = un[rand() % 42];
		}

		UnitData Max; // 가장 값이 비싼 유닛을 골라 구매하기 위한 구조체
		for (int v = 0; v < 4; v++)
		{
			if (comshop[v].price <= comshop[v + 1].price) // 상점에 제공된 유닛 중 가장 비싼 것을 고르는 과정
			{
				Max = comshop[v + 1];
			}
		}

			UnitData Min; // 가지고 있는 유닛 중 가장 저렴한 유닛을 골라 판매하기 위한 구조체
			int u; // 가장 저렴한 유닛의 번호를 기억한 후 판매할 때 사용
			for (int l = 0; l < 5; l++)
			{
				if (this->unit[l].price >= this->unit[l + 1].price)
				{
					Min = this->unit[l + 1];
					u = l;
				}
			}

			int num = 0; // 유닛 상점에 제공된 유닛과 플레이어가 가진 유닛이 일치하는 개수
			if (this->unit[5].name == "") // 유닛 개수가 꽉 차지 않은 경우
			{
				for (int c = 0; c < 5; c++)
				{
					for (int d = 0; d < 6; d++)
					{
						if (comshop[c].price <= this->printmoney()) // 충분한 가격을 가지고 있어야만 구매 가능
						{
							if (comshop[c].name == this->unit[d].name) // 이름이 같은 것이 있으면 우선 선택(빠른 강화를 위해)
							{
								num++;
								if (comshop[c].grade == this->unit[d].grade) // 등급이 같으면 중복 수만 더함
								{
									this->unit[d].dupli++;
									this->setmoney(2, comshop[c].price);
									buy++;
									break;
								}
								else
								{
									for (int e = 0; e < 6; e++) // 등급이 다르면 가장 앞 자리에 구매
									{
										if (this->unit[e].name == "")
										{
											this->unit[e] = comshop[c];
											this->setmoney(2, comshop[c].price);
											buy++;
											break;
										}
									}
								}
							}
						}
					}
				}
				if (num == 0) // 상점에 있는 유닛과 가지고 있는 유닛이 하나도 일치하지 않는 경우
				{
					if (Max.price <= this->printmoney()) // 충분한 가격을 가지고 있어야만 구매 가능
					{
						for (int e = 0; e < 6; e++) // 가장 가격이 비싼 유닛을 구매
						{
							{
								if (this->unit[e].name == "")
								{
									this->unit[e] = Max;
									this->setmoney(2, Max.price);
									break;
								}
							}
						}
					}
				}
			}
			else // 가지고 있는 유닛이 가득 차 더 이상 구매할 수 없는 경우
			{
				if (Max.price >= Min.price)
				{
					this->sell(u);
				}
			}
	}

}

void Com::sell(int n)
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

	if (n != 6)
	{
		for (int i = n; i <= 5; i++) // 뒤에 있는 배열 멤버들 앞으로 당기기
		{
			this->swap(i-1, i);
		}
	}
}

void Com::swap(int a, int b)
{
	UnitData tmp;
	tmp.name = this->unit[a].name;
	tmp.grade = this->unit[a].grade;
	tmp.power = this->unit[a].power;
	tmp.life = this->unit[a].life = tmp.life;
	tmp.price = this->unit[a].price = tmp.price;
	tmp.dupli = this->unit[a].dupli = tmp.dupli;

	this->unit[a].name = this->unit[b].name;
	this->unit[a].grade = this->unit[b].grade;
	this->unit[a].power = this->unit[b].power;
	this->unit[a].life = this->unit[b].life;
	this->unit[a].price = this->unit[b].price;
	this->unit[a].dupli = this->unit[b].dupli;

	this->unit[b].name = tmp.name;
	this->unit[b].grade = tmp.grade;
	this->unit[b].power = tmp.power;
	this->unit[b].life = tmp.life;
	this->unit[b].price = tmp.price;
	this->unit[b].dupli = tmp.dupli;
}