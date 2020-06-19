#include <string>
using namespace std;

#ifndef HEADER_H
#define HEADER_H

class Player;

struct UnitData // 유닛들의 정보를 구조체 배열로 저장
{
	string name = ""; // 이름
	int grade = 0; // 등급 (1성, 2성, 3성)
	int power = 0; // 공격력
	int life = 0; // 체력
	int price = 0; // 가격
	int dupli = 0; // 플레이어가 가지는 유닛의 중복 개수
};
extern UnitData un[42];

class Player {
	int lifepoint = 20;
	int money = 5;
	int matchnum = 0; // 다른 플레이어와의 매칭을 위한 변수
	int rank = 1; // 순위
	int status = 1; // 게임 참여가 가능한지 확인하는 변수 (1이면 가능, 0이면 불가)
public:
	static int plnum; // 플레이어 수
	static int turn; // 진행되고 있는 턴 번호
	UnitData unit[6]; // 최대 6개까지 유닛을 가질 수 있도록 구조체 배열 선언
	void enhance(char m);
	void setlife(int m, int l) // lifepoint를 더하거나 빼는 함수
	{
		if (m == 1) // lifepoint를 더할 일이 있는 경우
			this->lifepoint += l;
		else if (m == 2) // lifepoint를 뺄 일이 있는 경우
			this->lifepoint -= l;
	}
	void setmoney(int m, int j) // 사용자의 돈을 더하거나 빼는 함수
	{
		if (m == 1) // 돈을 더할 일이 있는 경우
			this->money += j;
		else if (m == 2) // 돈을 뺄 일이 있는 경우
			this->money -= j;
	}
	void setmatchnum(int s) { this->matchnum = s; }  // 임의로 설정한 matchnum을 할당하는 함수
	void setrank() { this->rank +=1; } // 호출할 때마다 순위가 하나씩 늘어나는 함수
	void clearrank() { this->rank = 1; } // 새로 순위를 매길 때 기존 순위를 초기화하는 함수
	void out() { this->status = 0; this->matchnum = 10; this->rank = 10; } // 탈락자 처리 함수
	int printunit() // 플레이어가 가지고 있는 유닛의 개수를 출력하는 함수
	{
		int sum = 0;
		for (int u = 0; u < 6; u++)
		{
			if (this->unit[u].name != "")
				sum++;
		}
		return sum;
	}
	int unitsum(int a) // 가지고 있는 유닛의 등급을 모두 더하는 함수 (1 : 생명 포인트 차감 모드 // 2 : 승자 돈 획득 모드)
	{
		int sum = 0;
		if (a == 1)
		{
			for (int u = 0; u < 6; u++) // 패배한 플레이어는 승리한 플레이어의 유닛 등급만큼 생명 포인트 차감
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
			for (int u = 0; u < 6; u++) // 승리한 플레이어는 패배한 플레이어의 유닛 등급에 따라 계산한 값으로 돈 지급
			{
				if (this->unit[u].grade == 1) // 1성 유닛은 개당 3전 지급
					sum += 3;
				else if (this->unit[u].grade == 2) // 2성 유닛은 개당 5전 지급
					sum += 5;
				else if (this->unit[u].grade == 3) // 3성 유닛은 개당 7전 지급
					sum += 7;
			}
		}
		return sum;
	}
	int printmoney() { return this->money; } // 상태 표시에 필요한 가진 돈 출력
	int printlife() { return this->lifepoint; } // 상태 표시에 필요한 생명 포인트 출력
	int printmatchnum() { return this->matchnum; } // 매칭을 위한 각 사용자의 매칭넘버 출력
	int printrank() { return this->rank; } // 현재 순위 표시
	int printstatus() { return this->status; } // 게임 플레이 가능 여부를 표시
	virtual void buy(UnitData a) = 0;
	virtual void sell(int n) = 0;
	virtual void swap(int a, int b) = 0;
};

class User : public Player
{
	char kind;
	string name;
public:
	User(); // 기본 생성자
	User(string a); // 사용자의 이름을 매개변수로 하는 생성자
	~User() { ; } // 소멸자
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
	Com(); // 기본 생성자
	Com(int n); // 인자가 1개인 생성자
	~Com() { ; } // 소멸자
	string printname() { return this->name; }
	virtual void buy(UnitData a);
	virtual void sell(int n);
	virtual void swap(int a, int b);
};

#endif // !HEADER_H