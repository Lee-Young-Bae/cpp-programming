#include <iostream>
#include <fstream> // ���� ������� ���� �������
#include <iomanip> // �����ڸ� ����ϱ� ���� �������
#include <cstdlib> // ���� ������ �����ϱ� ���� �������
#include <ctime> // ���� ������ �����ϱ� ���� �������
#include <windows.h> // Sleep()�� �����ϱ� ���� �������
using namespace std;

#include "Header.h"
#include "Func.h"

void MyTeamInfo(User* a)
{
	int d;
	do
	{
	    cout << "���� �� ����\n";
		cout << "=============================================================\n";
		cout << setw(8) << "��ȣ";
		cout << setw(8) << "�̸�";
		cout << setw(8) << "���";
		cout << setw(10) << "���ݷ�";
		cout << setw(8) << "ü��";
		cout << setw(8) << "����";
		cout << setw(8) << "�ߺ�\n";
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

		cout << "���� ���� ����Ʈ : " << a->printlife() << "\n";
		cout << "���� �� : "  << a->printmoney() << "��" << "\n";

		
			cout << "\n1. ���� �ٲٱ�  2. �Ǹ�  3. ����<->�� ��ȯ  4. ������\n";
			cout << "���� : ";
			cin >> d;

			switch (d)
			{
			case 1:
			{
				cout << "\n�ٲ� �� ������ ������ �Է��� �ּ��� : ";
				int q, w;
				cin >> q >> w;
				if (a->unit[q - 1].name == "" || a->unit[w - 1].name == "")
				{
					cout << "�ٲ� �� �����ϴ�.\n";
				}
				else a->swap(q, w);
			}break;
			case 2:
			{
				cout << "\n�Ǹ��� ������ ��ȣ�� �Է��� �ּ��� : ";
				int e;
				cin >> e;
				a->sell(e);
			}break;
			case 3:
			{
				cout << "\n1�� = 1���� �� ��ġ�� �����ϴ�.\n";
				cout << "���ϴ� ���񽺸� ����ּ���.\n";
				cout << "1. ��->��������Ʈ   2. ��������Ʈ->��\n";
				cout << "���� : ";
				int r;
				cin >> r;
				if (r == 1)
				{
					cout << "���� ���� ���� ����Ʈ�� �ٲٽðڽ��ϱ�?\n";
					int t;
					cin >> t;
					if (t > a->printmoney())
					{
						cout << "������ �ִ� ����ŭ�� �ٲ� �� �ֽ��ϴ�.\n";
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
					cout << "���� ���� ����Ʈ�� ������ �ٲٽðڽ��ϱ�? : ";
					int t;
					cin >> t;
					if (t >= a->printlife())
					{
						cout << "���� ���� ����Ʈ - 1 ������ ���� �����մϴ�.\n";
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

int storerand[5]; // ���� ������ ������ �����ϴ� ���� �迭 ����

UnitData UnitShop(User a)
{
	int e;

	UnitData shop[5];

	if (shopbalance <= Player::turn) // ���� �ٲ� ��� (ó�� �湮�ϸ� ������ ���� ����)
	{
		if (Player::turn <= 50) // 20�� �̻� �Ѿ�� 3����� ���ֵ� �������� ����
		{
			if (Player::turn <= 20) // 10�� �̻� �Ѿ�� 2����� ���ֵ� �������� ����
			{
				if (Player::turn <= 10) // 10�� �����̸� 1����� ���ָ� �������� ����
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
			shop[f] = un[storerand[f]]; // ������ ������ �ش��ϴ� ������ �����ͺ��̽����� ã�� ������ ������
	}
	else
	{
		for (int t = 0; t < 5; t++)
			shop[t] = un[storerand[t]];
	}

	cout << "=============================================================\n";
	cout << "���� ����\n";
	cout << "(���� ������ �� �ϸ��� �������� �����˴ϴ�.)\n";
	cout << "���� ���� �� : " << a.printmoney() << "��";
	cout << "\n-------------------------------------------------------------\n";
	cout << setw(8) << "��ȣ";
	cout << setw(8) << "�̸�";
	cout << setw(8) << "���";
	cout << setw(10) << "���ݷ�";
	cout << setw(8) << "ü��";
	cout << setw(8) << "����";
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
		cout << "���Ÿ� ���ϴ� ������ ��ȣ�� �Է��� �ּ��� : ";
		cin >> e;
	} while (e < 1 || e>5);
	cout << shop[e - 1].name << "(��)�� �����մϴ�.\n";
	cout << "=============================================================\n";

	shopbalance = Player::turn + 1; // ���Ű� ������ shopbalance ������ �� ������ 1 �÷� ���� �� ���� �湮 �� ���� ���� ���ǿ� ���� �ʰ� ��
	return shop[e - 1];
}

void Matchnum(int *p,int i)
{
	int temp;

	for (int m = 0; m < i; m++) // �迭�� �� ����� ���� ������� �� ������
	{
		p[m] = m+1;
	}
	for (int s = 0; s < 20; s++) // ������ 20�� ����
	{
		int x = rand()% i;
		int y = rand()% i;

		if (x != y)
		{
			temp = p[x]; // ������ ���� x,y�� �̿��� �迭�� ������ ����
			p[x] = p[y];
			p[y] = temp;
		}
	}

}

void matchingresult(User a, Com* com, int num)
{
	if (Player::plnum % 2 == 0) // �÷��̾� ���� ¦���� ���
	{
		cout << a.printname() << " VS "  << com[find(com)].printname() << "\n"; // ����� �÷��̾�� ��� �÷��̾�� �̸� ������
		for (int i = 2; i <= Player::plnum; i++) // ������ ��ǻ�� �÷��̾�� ��Ģ�� ���� ����
		{
			for (int j = 0; j < num; j++)
			{
				if (i == com[j].printmatchnum()) // matchnum ������ ���� ���
				{
					if (i % 2 == 0) // ¦���̸� VS ǥ�ø� ����
						cout << com[j].printname() << " VS ";
					else cout << com[j].printname() << "\n"; // Ȧ���̸� ���� ����
					break;
				}
			}
		}
		
	}
	else // �÷��̾� ���� Ȧ���� ���
	{
		cout << a.printname() << " VS " << com[find(com)].printname() << "\n"; // ����� �÷��̾�� ��� �÷��̾�� �̸� ������
		for (int i = 2; i < Player::plnum; i++) // ������ ��ǻ�� �÷��̾�� ��Ģ�� ���� �����Ͽ� ���
		{
			for (int j = 0; j < num; j++)
			{
				if (i == com[j].printmatchnum()) // matchnum ������ ���� ���
				{
					if (i % 2 == 0) // ¦���̸� VS ǥ�ø� ����
					{
						cout << com[j].printname() << " VS ";
						if (i == Player::plnum - 1) // �������� ȥ�� ���� �ε����� ���
						{
							for (int i = 0; i < num; i++) // matchnum�� �ϳ� ���� �÷��̾�� ��Ī
							{
								if (com[j].printmatchnum() - com[i].printmatchnum() == 1)
									cout << com[i].printname() << "\n";
							}
							//cout << com[j-1].printname() << "\n";
						}
					}
					else cout << com[j].printname() << "\n"; // Ȧ���̸� ���� ����
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

	cout << "2�� �Ŀ� ��Ⱑ ���۵˴ϴ�.\n";
	//Sleep(2000);
	cout << a.printname() << "(���� ���� : " << aunit << ")"  "   VS   " << b.printname() << "(���� ���� : " << bunit << ")" << "�� ��⸦ �����մϴ�.\n";
	cout << "=============================================================\n";
	cout << "\n";
	cout << setw(20)<< left << a.printname();
	cout << setw(10) << "  VS  ";
	cout << setw(20) << right << b.printname();
	cout << "\n";
	
	int life1 = a.unit[z].life, life2 = b.unit[x].life, damage; // �� ������ ü�°� ���Ƿ� �����Ǵ� ���������� ������ ����

	do
	{
		
	    cout << "-------------------------------------------------------------\n";

		cout << setw(20) << left << z; // ���� ��ȣ(����) ���
		cout << setw(10) << " *** ";
		cout << setw(20) << right << x;
		cout << "\n";
		cout << setw(20) << left << a.unit[z].name; // ���� �̸� ���
		cout << setw(10) << " *** ";
		cout << setw(20) << right << b.unit[x].name;
		cout << "\n";
		if (a.unit[z].grade == 1) // ����� ���� ��� ���
			cout <<setw(20) <<left << "��";
		if (a.unit[z].grade == 2)
			cout << setw(20) << left << "�ڡ�";
		if (a.unit[z].grade == 3)
			cout << setw(20) << left << "�ڡڡ�";
		cout << setw(10) << " *** ";
		if (b.unit[x].grade == 1) // ��ǻ�� ���� ��� ���
			cout << setw(20) << right << "��";
		if (b.unit[x].grade == 2)
			cout << setw(20) << right << "�ڡ�";
		if (b.unit[x].grade == 3)
			cout << setw(20) << right << "�ڡڡ�";

		cout << "\n";
		cout << "\n";
		cout << setw(20) << left << "���� ü��";
		cout << setw(10) << "����(������)";
		cout << setw(20) << right << "���� ü��";
		cout << "\n";
		cout << "\n";

		int n = 0;
		do
		{
			if (n % 2 == 0) // �����ư��� ������ ����
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

		if (life1 <= 0) // ������� ������ �ƿ��� ���
		{
			cout << a.printname() << "�� " << a.unit[z].name << " �ƿ�!\n";
			aunit -= 1;
			z++;
			life1 = a.unit[z].life;
		}
		else if (life2 <= 0) // ��ǻ�� �÷��̾��� ������ �ƿ��� ���
		{
			cout << b.printname() << "�� " << b.unit[x].name << " �ƿ�!\n";
			bunit -= 1;
			x++;
			life2 = b.unit[x].life;
		}

		
		cout << "\n";
	} while (aunit != 0 && bunit != 0);
	
	// ��� ���� �� ���� �� ���� ó��
	if (aunit == 0) // ����ڰ� �й��� ���
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
		cout << a.printname() << "�й�\n";
		cout << "���� ����Ʈ�� " << sum << " �����Ǿ����ϴ�.\n"; 
		return 0;
	}
	else // ����ڰ� �¸��� ���
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
		cout << b.printname() << "�й�\n";
		cout << "���� ����Ʈ�� " << sum << " �����Ǿ����ϴ�.\n"; 
		return 1;
	}
    
}

int attack(int a) // ������ ������ ������� ������ ������ ���� ���ϴ� �Լ�
{
	int r = rand() % 100;
	int k;
	if (r >= 70) // 70%�� Ȯ���� �ڽ��� ���� ���ݷ¸�ŭ ����
		return a;
	else // 20%�� Ȯ���� 0~ �ڽ��� ���ݷ¸�ŭ ����
	{
		k = rand() % a;
		return k;
	}
}

void commatch(int* p, Com* com, int a) // ��ǻ�� �÷��̾�� ���(combattle �Լ�)�� ���� matchnum�� ���� �����ϱ� ���� �Լ�
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

	int life1 = a.unit[z].life, life2 = b.unit[x].life, damage; // �� ������ ü�°� ���Ƿ� �����Ǵ� ���������� ������ ����

	do
	{
		int n = 0;
		do
		{
			if (n % 2 == 0) // �����ư��� ������ ����
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

		if (life1 <= 0) // �� �÷��̾��� ������ �ƿ��� ���
		{
			aunit -= 1;
			z++;
			life1 = a.unit[z].life;
		}
		else if (life2 <= 0) // �� �÷��̾��� ������ �ƿ��� ���
		{
			bunit -= 1;
			x++;
			life2 = b.unit[x].life;
		}
	} while (aunit != 0 && bunit != 0);

	// ��� ���� �� ���� �� ���� ó��
	if (aunit == 0) // �� �÷��̾ �¸��� ���
		return 0;
	else if(bunit == 0)
		return 1; // �� �÷��̾ �¸��� ���

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
	for (int y = 0; y < num; y++) // ���� ��ǻ�� �÷��̾�� ������ �ű�
	{
		if (com[y].printstatus() != 0)
		{
			for (int z = 0; z < num; z++)
			{
				if (com[y].printname() != com[z].printname()) // �÷��̾� �ڽ��� ���� �� ��󿡼� ���� ( && ���� ����Ʈ�� 0���� Ŀ����)
				{
					if (com[z].printstatus() != 0) // ���ϰ��� �ϴ� �÷��̾��� ���°� 0(���� ����)�� �ƴ� ���
					{
						if (com[y].printlife() == com[z].printlife()) // ���� ����Ʈ�� ���� ���
						{
							if (com[y].printmatchnum() < com[z].printmatchnum()) // matchnum���� ������ �ű�(�����ڸ� matchnum ������������ ó��)
								com[y].setrank();
						}
						else if (com[y].printlife() < com[z].printlife()) // ���� ����Ʈ�� ������ ������ ����
							com[y].setrank();
					}

				}
			}
		}
	}
	for (int w = 0; w < num; w++) // ����ڿ� ��ǻ�� �÷��̾�� ������ �ű�
	{
		if (com[w].printstatus() != 0)
		{
			if (a->printlife() >= com[w].printlife()) // ������� ���� ����Ʈ���� ���� �÷��̾�� ������ ����
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
	cout << "��� ���\n";
	cout << "\n";
	cout << setw(10) << "����";
	cout << setw(10) << "�̸�";
	cout << setw(15) << "��������Ʈ";
	cout << setw(10) << "����";
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
	fin.open(file, ios::in | ios::binary); // �б� ���� ������ ������ ����
	if (!fin)
	{
		cout << "������ �� �� �����ϴ�.\n";
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

void printdatabase() // ��� ������ ������ ����ϴ� �Լ� (ó�� ���ÿ��� 3���� ������ �� �� ����)
{
	cout << "���� ����\n";
	cout << "=============================================================\n";
	cout << setw(8) << "�̸�";
	cout << setw(8) << "���";
	cout << setw(10) << "���ݷ�";
	cout << setw(8) << "ü��";
	cout << setw(8) << "����\n";
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