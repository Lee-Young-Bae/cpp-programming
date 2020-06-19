#include <iostream>
#include <string>
#include <iomanip> // �����ڸ� ����ϱ� ���� �������
using namespace std;

#include "Header.h"


User::User() : User("user") {};

User::User(string a)
{
	name = a;
	kind = 'M';
	cout << name << "�� ȯ���մϴ�.\n";
}

void Player::enhance(char m)
{
	for (int q = 0; q < 6; q++) // ������ �ִ� ������ ó������ ������ ������ ��ȭ�� ������ �ִ��� Ȯ��
	{
		if (this->unit[q].dupli == 2 && this->unit[q].grade <3) // �ߺ��� �� 3���� ������ ã�� ���
		{
			if (this->unit[q].grade == 1)
			{
				for (int w = 0; w < 14; w++)
				{
					if (this->unit[q].name == un[w].name && this->unit[q].grade == un[w].grade) // �����ͺ��̽����� �̸��� ����� ���� ������ ã��
					{
						this->unit[q] = un[w + 14]; // 14�ε��� ���� ������ ������ (14�� ���� ���Ҵ� ����� �ö� �ش� ����)
						for (int r = 0; r < 6; r++)
						{
							if (this->unit[q].name == this->unit[r].name && this->unit[q].grade == this->unit[r].grade && q != r) // ���� ���� �� �̹� ���� ����� ������ �ִ� ���
							{
								this->unit[r].dupli++;
								for (int h = q; h < 5; h++)
									this->unit[h] = this->unit[h + 1];
								break;
							}
						}
						if (m == 'M')
						{
							cout << "��ȭ�� ������ �ֽ��ϴ�.\n";
							cout << "=============================================================\n";
						}
					}
				}
			}
			else if (this->unit[q].grade == 2)
			{
				for (int w = 14; w < 28; w++)
				{
					if (this->unit[q].name == un[w].name && this->unit[q].grade == un[w].grade) // �����ͺ��̽����� �̸��� ����� ���� ������ ã��
					{
						this->unit[q] = un[w + 14]; // 14�ε��� ���� ������ ������ (14�� ���� ���Ҵ� ����� �ö� �ش� ����)
						for (int r = 0; r < 6; r++)
						{
							if (this->unit[q].name == this->unit[r].name && this->unit[q].grade == this->unit[r].grade && q != r) // ���� ���� �� �̹� ���� ����� ������ �ִ� ���
							{
								this->unit[r].dupli++;
								for (int h = q; h < 5; h++)
									this->unit[h] = this->unit[h + 1];
								break;
							}
						}
						if (m == 'M')
						{
							cout << "��ȭ�� ������ �ֽ��ϴ�.\n";
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
	if (this->unit[5].name != "") // ������ ���� ���� �� �̻� ������ �� ���� ���
	{
		cout << "������ ���� á���ϴ�.\n";
		cout << "������ 1�� �̻� ���� �ٽ� �õ��ϼ���.\n";
	}
	else if (a.price > this->printmoney())
			cout << "���� ���ڶ� �������� ���Ͽ����ϴ�.\n";
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
			if (this->unit[i].name == "") // ���� ����� �� ���� ������ ���� ����
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
		cout << "�߸��� �Է��Դϴ�.\n";
	else
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

		cout << n  << "�� ������ �Ǹ��߽��ϴ�.\n";
		cout << "(���� �� : " << this->printmoney() << ")\n";

		if (n != 6)
		{
			for (int i = n; i <= 5; i++) // �ڿ� �ִ� �迭 ����� ������ ����
			{
				this->swap(i, i + 1);
			}
		}
	}
}

void User::swap(int a, int b) // temp ����ü�� ���� �� �� ����ü�� ����� ���̴� ������� ���� �ٲٱ�
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




