#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "Header.h"
#include "Func.h"

int Player::plnum = 1; // static ��� ���� �ܺ� �ʱ�ȭ
int Player::turn = 1; // static ��� ���� �ܺ� �ʱ�ȭ
extern int shopbalance = 1; // �� �Ͽ� ���� ���ָ� ���� ������ ������ �� �ֵ��� �ϴ� ��������

int main()
{
	int n, num, c;
	string name;

	srand((unsigned int)time(NULL));
	
	cout << "�� ���� ���� ���ӿ� ���� ���� ȯ���մϴ�.\n";
	cout << "=============================================================\n";
	cout << "�̸��� �Է��� �ּ��� : ";
	cin >> name;
	User user(name);
	User* puser = &user; // ����� ��ü ������ ����
	do
	{
		cout << "=============================================================\n";
		cout << "1. ���� ����      2. ���� ���       3. ���� ����       4.����\n";
		cout << "\n���� :";
		cin >> n;
	
	

	if (n == 1)
	{
		do
		{
			cout << "���ϴ� ��� �÷��̾��� ���� �Է��� �ּ���(�ִ� 7) : ";
			cin >> num;
		} while (num > 7);
		
		cout << "=============================================================\n";
		Com* com = new Com[num]; // ������ ��ü �迭 ����
		for (int i = 0; i < num; i++)
			com[i] = Com(i); // ����ڿ��� �Է¹��� ������ŭ ��ǻ�� �÷��̾� ��ü ����
		Player::plnum += num;
		int* tmp = new int[Player::plnum]; // ���� ���� Ȯ���� ���� ���� ������ �����ϴ� ���� �迭
		for (int k = 0; k < Player::plnum; k++)
		{
			tmp[k] = 1; // ���� ������ ���� ù ��° ���� ���� �迭�� ����� ��� 1�� �ʱ�ȭ
		}
		do
		{
			cout << Player::turn << "��° ���� ���۵Ǿ����ϴ�. (���� �÷��̾� : " << Player::plnum << ")\n";
			cout << "1. ��� ����      2. ���� ����      3. ���� ��\n";
			cout << "���� : ";
			cin >> c;
			if (c == 1) // ��� ����
			{
				if (user.unit[0].name == "")
				{
					cout << "������ ������ ������ �� �����ϴ�.\n";
				}
				else
				{
					UnitData e; // ���� ����ü
					for (int t = 0; t < num; t++) // ��ǻ�� �÷��̾��� ���� ����
					{
						if (com[t].printstatus() != 0)
							com[t].buy(e);
					}

					if (user.printstatus() == 0) // ���� �����Ǿ����� matchnum�� ���� �ٱ� ���ڷ� ������ ������ �������� �ʵ��� ��
					{
						user.setmatchnum(10);
					}
					else user.setmatchnum(0);

					int h = Player::plnum - 1;
					int* p = new int[h]; // ��ǻ�� �÷��̾��� ����ŭ ���� ���� �迭 ����(���� ������ ���)
					Matchnum(p, h); // ���� �迭 p�� 1~�÷��̾� ���� ���ڸ� �ְ� ����

					int m = 0;
					for (int o = 0; o < num; o++) // ��ǻ�� �÷��̾ �÷��� �����ϸ� ���� �ο�
					{
						if (com[o].printstatus() != 0)
						{
							com[o].setmatchnum(p[m]);
							m++;
						}
					}

					cout << "=============================================================\n";
					cout << "������ ��Ī ���\n";
					cout << "\n";

					matchingresult(user, com, num); // ��Ī ����� ǥ���ϴ� �Լ� ȣ��
					cout << "=============================================================\n";

					//����� �÷��̾� VS ��ǻ�� �÷��̾�
					int j = find(com);
					if (battle(user, com[j]) == 0) // ����ڰ� �й��� ���
					{
						user.setlife(2, com[j].unitsum(1));
						com[j].setmoney(1, user.unitsum(2));
						cout << "���� ���� ����Ʈ : " << user.printlife() << "\n";
						if (user.printlife() <= 0)
						{
							user.out();
							goto ending;
						}
					}
					else // ����ڰ� �¸��� ���
					{
						com[j].setlife(2, user.unitsum(1));
						user.setmoney(1, com[j].unitsum(2));
						cout << "���� ���� ����Ʈ : " << com[j].printlife() << "\n";
						if (com[j].printlife() <= 0)
						{
							com[j].out();
							cout << com[j].printname() << "Ż��!\n";
							Player::plnum--;
							if (Player::plnum == 1)
								goto ending;
						}
					}

					// ��ǻ�� �÷��̾� VS ��ǻ�� �÷��̾�
					
					if (h+1 != 2)
					{
						int k = Player::plnum - 2;
						int* u = new int[k];
						commatch(u, com, num); // ��ǻ�� �÷��̾��� matchnum�� ������� ����

						if (Player::plnum % 2 == 0) // ��ǻ�� �÷��̾��� ���� Ȧ���� ��� (��ü �÷��̾�� ¦���� ���)
						{
							for (int i = 0; i < k; i += 2)
							{
								int t = u[i], y = u[i + 1];
								if (combattle(com[t], com[y]) == 1) // �տ� ��ġ�� ��ǻ�� �÷��̾ �¸��� ���
								{
									com[y].setlife(2, com[t].unitsum(1));
									com[t].setmoney(1, com[y].unitsum(2));
									if (com[y].printlife() <= 0)
									{
										com[y].out();
										cout << com[y].printname() << "Ż��!\n";
										Player::plnum--;
									}
								}
								else  // �ڿ� ��ġ�� ��ǻ�� �÷��̾ �¸��� ���
								{
									com[t].setlife(2, com[y].unitsum(1));
									com[y].setmoney(1, com[t].unitsum(2));
									if (com[t].printlife() <= 0)
									{
										com[t].out();
										cout << com[t].printname() << "Ż��!\n";
										Player::plnum--;
									}
								}
							}
						}
						else // ��ǻ�� �÷��̾��� ���� ¦���� ��� (��ü �÷��̾��� ���� Ȧ��)
						{
							if (k == 1) // ��ü �÷��̾��� ���� 3���̸� ���� �迭 u[1]�� �����ǹǷ� ������ �÷��̾ �ٸ��� ó��
							{
								int t = u[k - 1], y = 1;
								for (int r = 0; r < num; r++)
								{
									if (com[r].printmatchnum() == 1) // �� ���� matchnum�� ���� �÷��̾ ���� ã�� ��⸦ ��Ī��
									{
										y = r;
										break;
									}
								}
								if (combattle(com[t], com[y]) == 1) // �տ� ��ġ�� ��ǻ�� �÷��̾ �¸��� ���
								{
									com[t].setmoney(1, com[y].unitsum(2));
									if (com[y].printlife() <= 0)
									{
										com[y].out();
										cout << com[y].printname() << "Ż��!\n";
										Player::plnum--;
									}
								}
								else
								{
									com[t].setlife(2, com[y].unitsum(1));
									if (com[t].printlife() <= 0)
									{
										com[t].out();
										cout << com[t].printname() << "Ż��!\n";
										Player::plnum--;
									}
								}
							}
							else
							{
								for (int i = 0; i < k - 1; i += 2)
								{
									int t = u[i], y = u[i + 1];
									if (combattle(com[t], com[y]) == 1) // �տ� ��ġ�� ��ǻ�� �÷��̾ �¸��� ���
									{
										com[y].setlife(2, com[t].unitsum(1));
										com[t].setmoney(1, com[y].unitsum(2));
										if (com[y].printlife() <= 0)
										{
											com[y].out();
											cout << com[y].printname() << "Ż��!\n";
											Player::plnum--;
										}
									}
									else // �ڿ� ��ġ�� ��ǻ�� �÷��̾ �¸��� ���
									{
										com[t].setlife(2, com[y].unitsum(1));
										com[y].setmoney(1, com[y].unitsum(2));
										if (com[t].printlife() <= 0)
										{
											com[t].out();
											cout << com[t].printname() << "Ż��!\n";
											Player::plnum--;
										}
									}
								}

								int t = u[k - 1], y = u[k - 2]; // ������ �÷��̾�� ���� �ε��� �÷��̾�� ���
								if (combattle(com[t], com[y]) == 1) // �տ� ��ġ�� ��ǻ�� �÷��̾ �¸��� ���
								{
									com[t].setmoney(1, com[y].unitsum(2));
								}
								else
								{
									com[t].setlife(2, com[y].unitsum(1));
									if (com[t].printlife() <= 0)
									{
										com[t].out();
										cout << com[t].printname() << "Ż��!\n";
										Player::plnum--;
									}
								}
							}
						}
					}
					
					rankinit(puser, com, num);
					ranking(puser, com, num);
					battleresult(user, com, tmp, num);
					
					cout << "=============================================================\n";
					Player::turn++;
					delete[]p;
				}
			}
			else if (c == 2) // ���� ����
			{
				user.buy(UnitShop(user)); // ���ϰ��� UnitData�� ���� ���� �Լ��� �ҷ��� �� ���ϵ�(����ڰ� ��) ���� ������ user.buy()�� ���� ����
			}
			else if (c == 3) // ���� �� ���� (���� �ٲٱ�, �Ǹ�, ����<->�� ��ȯ)
			{
			    MyTeamInfo(puser);
			}
		} while (Player::plnum != 1); // �÷��̾ 1���� �� ������ �ݺ�

	ending:
		cout << Player::turn << "�� ���� ";
		if (user.printstatus() == 1)
		{
			cout << user.printname() << "(��)�� ����Ͽ����ϴ�. �����մϴ�!\n";
		}
		else
		{
			cout << "Ż���ϼ̽��ϴ�.\n";
		}
		delete[] com; // �������� �Ҵ���� ��ǻ�� �÷��̾� �迭 �ݳ�
		delete[] tmp; 
		cout << "���� ����\n";
	}
	if (n == 2)
	{
		manual(); // �ؽ�Ʈ ������ ���̳ʸ� ���� ���� ���� ��� ���
	}
	if (n == 3)
	{
		printdatabase(); // ��� ������ ������ ����ϴ� �Լ� ȣ��
	}
	} while (n != 4);
}