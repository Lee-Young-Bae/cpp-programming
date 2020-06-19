#include <string>
using namespace std;

#ifndef HEADER_H
#define HEADER_H

class Player;

struct UnitData // ���ֵ��� ������ ����ü �迭�� ����
{
	string name = ""; // �̸�
	int grade = 0; // ��� (1��, 2��, 3��)
	int power = 0; // ���ݷ�
	int life = 0; // ü��
	int price = 0; // ����
	int dupli = 0; // �÷��̾ ������ ������ �ߺ� ����
};
extern UnitData un[42];

class Player {
	int lifepoint = 20;
	int money = 5;
	int matchnum = 0; // �ٸ� �÷��̾���� ��Ī�� ���� ����
	int rank = 1; // ����
	int status = 1; // ���� ������ �������� Ȯ���ϴ� ���� (1�̸� ����, 0�̸� �Ұ�)
public:
	static int plnum; // �÷��̾� ��
	static int turn; // ����ǰ� �ִ� �� ��ȣ
	UnitData unit[6]; // �ִ� 6������ ������ ���� �� �ֵ��� ����ü �迭 ����
	void enhance(char m);
	void setlife(int m, int l) // lifepoint�� ���ϰų� ���� �Լ�
	{
		if (m == 1) // lifepoint�� ���� ���� �ִ� ���
			this->lifepoint += l;
		else if (m == 2) // lifepoint�� �� ���� �ִ� ���
			this->lifepoint -= l;
	}
	void setmoney(int m, int j) // ������� ���� ���ϰų� ���� �Լ�
	{
		if (m == 1) // ���� ���� ���� �ִ� ���
			this->money += j;
		else if (m == 2) // ���� �� ���� �ִ� ���
			this->money -= j;
	}
	void setmatchnum(int s) { this->matchnum = s; }  // ���Ƿ� ������ matchnum�� �Ҵ��ϴ� �Լ�
	void setrank() { this->rank +=1; } // ȣ���� ������ ������ �ϳ��� �þ�� �Լ�
	void clearrank() { this->rank = 1; } // ���� ������ �ű� �� ���� ������ �ʱ�ȭ�ϴ� �Լ�
	void out() { this->status = 0; this->matchnum = 10; this->rank = 10; } // Ż���� ó�� �Լ�
	int printunit() // �÷��̾ ������ �ִ� ������ ������ ����ϴ� �Լ�
	{
		int sum = 0;
		for (int u = 0; u < 6; u++)
		{
			if (this->unit[u].name != "")
				sum++;
		}
		return sum;
	}
	int unitsum(int a) // ������ �ִ� ������ ����� ��� ���ϴ� �Լ� (1 : ���� ����Ʈ ���� ��� // 2 : ���� �� ȹ�� ���)
	{
		int sum = 0;
		if (a == 1)
		{
			for (int u = 0; u < 6; u++) // �й��� �÷��̾�� �¸��� �÷��̾��� ���� ��޸�ŭ ���� ����Ʈ ����
			{
				if (this->unit[u].grade == 1)
					sum += 1;
				else if (this->unit[u].grade == 2)
					sum += 2;
				else if (this->unit[u].grade == 3)
					sum += 3;
			}
		}
		else if (a == 2)
		{
			for (int u = 0; u < 6; u++) // �¸��� �÷��̾�� �й��� �÷��̾��� ���� ��޿� ���� ����� ������ �� ����
			{
				if (this->unit[u].grade == 1) // 1�� ������ ���� 3�� ����
					sum += 3;
				else if (this->unit[u].grade == 2) // 2�� ������ ���� 5�� ����
					sum += 5;
				else if (this->unit[u].grade == 3) // 3�� ������ ���� 7�� ����
					sum += 7;
			}
		}
		return sum;
	}
	int printmoney() { return this->money; } // ���� ǥ�ÿ� �ʿ��� ���� �� ���
	int printlife() { return this->lifepoint; } // ���� ǥ�ÿ� �ʿ��� ���� ����Ʈ ���
	int printmatchnum() { return this->matchnum; } // ��Ī�� ���� �� ������� ��Ī�ѹ� ���
	int printrank() { return this->rank; } // ���� ���� ǥ��
	int printstatus() { return this->status; } // ���� �÷��� ���� ���θ� ǥ��
	virtual void buy(UnitData a) = 0;
	virtual void sell(int n) = 0;
	virtual void swap(int a, int b) = 0;
};

class User : public Player
{
	char kind;
	string name;
public:
	User(); // �⺻ ������
	User(string a); // ������� �̸��� �Ű������� �ϴ� ������
	~User() { ; } // �Ҹ���
	string printname() { return this->name; }
	friend void MyTeamInfo(User* a);
	virtual void buy(UnitData a);
	virtual void sell(int n);
	virtual void swap(int a, int b);
};

class Com : public Player
{
	char kind;
	string name;
public:
	Com(); // �⺻ ������
	Com(int n); // ���ڰ� 1���� ������
	~Com() { ; } // �Ҹ���
	string printname() { return this->name; }
	virtual void buy(UnitData a);
	virtual void sell(int n);
	virtual void swap(int a, int b);
};

#endif // !HEADER_H