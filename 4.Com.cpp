#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Header.h"

Com::Com() : Com(0) {}; // ���� ������

Com::Com(int n)
{
	kind = 'C';
	name = "Com";
	name.append(to_string(n+1));
}


void Com::buy(UnitData a) // ��ǻ�� �÷��̾ ������ �����ϴ� ����
{
	if (this->printlife() != 0)
	{
		UnitData comshop[5];
		int buy = 0; // ��ǻ�� �÷��̾ �̹� �Ͽ� ������ ���� ��(0�� �ɶ����� ���Ÿ� �ݺ�)

		if (Player::turn <= 30) // 30�� �̻� �Ѿ�� 3����� ���ֵ� �������� ����
		{
			if (Player::turn <= 20) // 20�� �̻� �Ѿ�� 2����� ���ֵ� �������� ����
			{
				if (Player::turn <= 10) // 10�� �����̸� 1����� ���ָ� �������� ����
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

		UnitData Max; // ���� ���� ��� ������ ��� �����ϱ� ���� ����ü
		for (int v = 0; v < 4; v++)
		{
			if (comshop[v].price <= comshop[v + 1].price) // ������ ������ ���� �� ���� ��� ���� ���� ����
			{
				Max = comshop[v + 1];
			}
		}

			UnitData Min; // ������ �ִ� ���� �� ���� ������ ������ ��� �Ǹ��ϱ� ���� ����ü
			int u; // ���� ������ ������ ��ȣ�� ����� �� �Ǹ��� �� ���
			for (int l = 0; l < 5; l++)
			{
				if (this->unit[l].price >= this->unit[l + 1].price)
				{
					Min = this->unit[l + 1];
					u = l;
				}
			}

			int num = 0; // ���� ������ ������ ���ְ� �÷��̾ ���� ������ ��ġ�ϴ� ����
			if (this->unit[5].name == "") // ���� ������ �� ���� ���� ���
			{
				for (int c = 0; c < 5; c++)
				{
					for (int d = 0; d < 6; d++)
					{
						if (comshop[c].price <= this->printmoney()) // ����� ������ ������ �־�߸� ���� ����
						{
							if (comshop[c].name == this->unit[d].name) // �̸��� ���� ���� ������ �켱 ����(���� ��ȭ�� ����)
							{
								num++;
								if (comshop[c].grade == this->unit[d].grade) // ����� ������ �ߺ� ���� ����
								{
									this->unit[d].dupli++;
									this->setmoney(2, comshop[c].price);
									buy++;
									break;
								}
								else
								{
									for (int e = 0; e < 6; e++) // ����� �ٸ��� ���� �� �ڸ��� ����
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
				if (num == 0) // ������ �ִ� ���ְ� ������ �ִ� ������ �ϳ��� ��ġ���� �ʴ� ���
				{
					if (Max.price <= this->printmoney()) // ����� ������ ������ �־�߸� ���� ����
					{
						for (int e = 0; e < 6; e++) // ���� ������ ��� ������ ����
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
			else // ������ �ִ� ������ ���� �� �� �̻� ������ �� ���� ���
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
	if (this->unit[n - 1].grade == 1) // �� �ݾ� �ޱ�
		this->setmoney(1, this->unit[n - 1].price - 1);
	else if (this->unit[n - 1].grade == 2)
		this->setmoney(1, this->unit[n - 1].price - 3);
	else if (this->unit[n - 1].grade == 3)
		this->setmoney(1, this->unit[n - 1].price - 5);

	this->unit[n - 1].name = ""; // �ش� ����ü �迭 �ڸ� ����
	this->unit[n - 1].grade = 0;
	this->unit[n - 1].power = 0;
	this->unit[n - 1].life = 0;
	this->unit[n - 1].dupli = 0;
	this->unit[n - 1].grade = 0;

	if (n != 6)
	{
		for (int i = n; i <= 5; i++) // �ڿ� �ִ� �迭 ����� ������ ����
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