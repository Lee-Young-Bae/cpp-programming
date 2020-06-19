#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "Header.h"
#include "Func.h"

int Player::plnum = 1; // static 멤버 변수 외부 초기화
int Player::turn = 1; // static 멤버 변수 외부 초기화
extern int shopbalance = 1; // 한 턴에 같은 유닛만 유닛 상점에 출현할 수 있도록 하는 전역변수

int main()
{
	int n, num, c;
	string name;

	srand((unsigned int)time(NULL));
	
	cout << "팀 전략 전투 게임에 오신 것을 환영합니다.\n";
	cout << "=============================================================\n";
	cout << "이름을 입력해 주세요 : ";
	cin >> name;
	User user(name);
	User* puser = &user; // 사용자 객체 포인터 선언
	do
	{
		cout << "=============================================================\n";
		cout << "1. 게임 시작      2. 게임 방법       3. 유닛 정보       4.종료\n";
		cout << "\n선택 :";
		cin >> n;
	
	

	if (n == 1)
	{
		do
		{
			cout << "원하는 상대 플레이어의 수를 입력해 주세요(최대 7) : ";
			cin >> num;
		} while (num > 7);
		
		cout << "=============================================================\n";
		Com* com = new Com[num]; // 포인터 객체 배열 생성
		for (int i = 0; i < num; i++)
			com[i] = Com(i); // 사용자에게 입력받은 개수만큼 컴퓨터 플레이어 객체 생성
		Player::plnum += num;
		int* tmp = new int[Player::plnum]; // 순위 변동 확인을 위해 기존 순위를 저장하는 정수 배열
		for (int k = 0; k < Player::plnum; k++)
		{
			tmp[k] = 1; // 순위 변동이 없는 첫 번째 턴을 위해 배열의 멤버를 모두 1로 초기화
		}
		do
		{
			cout << Player::turn << "번째 턴이 시작되었습니다. (남은 플레이어 : " << Player::plnum << ")\n";
			cout << "1. 경기 시작      2. 유닛 상점      3. 나의 팀\n";
			cout << "선택 : ";
			cin >> c;
			if (c == 1) // 경기 시작
			{
				if (user.unit[0].name == "")
				{
					cout << "유닛이 없으면 입장할 수 없습니다.\n";
				}
				else
				{
					UnitData e; // 더미 구조체
					for (int t = 0; t < num; t++) // 컴퓨터 플레이어의 유닛 구매
					{
						if (com[t].printstatus() != 0)
							com[t].buy(e);
					}

					if (user.printstatus() == 0) // 게임 오버되었으면 matchnum을 범위 바깥 숫자로 설정해 순서가 배정되지 않도록 함
					{
						user.setmatchnum(10);
					}
					else user.setmatchnum(0);

					int h = Player::plnum - 1;
					int* p = new int[h]; // 컴퓨터 플레이어의 수만큼 동적 정수 배열 생성(순서 배정에 사용)
					Matchnum(p, h); // 정수 배열 p에 1~플레이어 수의 숫자를 넣고 섞음

					int m = 0;
					for (int o = 0; o < num; o++) // 컴퓨터 플레이어가 플레이 가능하면 순서 부여
					{
						if (com[o].printstatus() != 0)
						{
							com[o].setmatchnum(p[m]);
							m++;
						}
					}

					cout << "=============================================================\n";
					cout << "무작위 매칭 결과\n";
					cout << "\n";

					matchingresult(user, com, num); // 매칭 결과를 표시하는 함수 호출
					cout << "=============================================================\n";

					//사용자 플레이어 VS 컴퓨터 플레이어
					int j = find(com);
					if (battle(user, com[j]) == 0) // 사용자가 패배한 경우
					{
						user.setlife(2, com[j].unitsum(1));
						com[j].setmoney(1, user.unitsum(2));
						cout << "남은 생명 포인트 : " << user.printlife() << "\n";
						if (user.printlife() <= 0)
						{
							user.out();
							goto ending;
						}
					}
					else // 사용자가 승리한 경우
					{
						com[j].setlife(2, user.unitsum(1));
						user.setmoney(1, com[j].unitsum(2));
						cout << "남은 생명 포인트 : " << com[j].printlife() << "\n";
						if (com[j].printlife() <= 0)
						{
							com[j].out();
							cout << com[j].printname() << "탈락!\n";
							Player::plnum--;
							if (Player::plnum == 1)
								goto ending;
						}
					}

					// 컴퓨터 플레이어 VS 컴퓨터 플레이어
					
					if (h+1 != 2)
					{
						int k = Player::plnum - 2;
						int* u = new int[k];
						commatch(u, com, num); // 컴퓨터 플레이어의 matchnum값 순서대로 정렬

						if (Player::plnum % 2 == 0) // 컴퓨터 플레이어의 수가 홀수인 경우 (전체 플레이어는 짝수인 경우)
						{
							for (int i = 0; i < k; i += 2)
							{
								int t = u[i], y = u[i + 1];
								if (combattle(com[t], com[y]) == 1) // 앞에 배치된 컴퓨터 플레이어가 승리한 경우
								{
									com[y].setlife(2, com[t].unitsum(1));
									com[t].setmoney(1, com[y].unitsum(2));
									if (com[y].printlife() <= 0)
									{
										com[y].out();
										cout << com[y].printname() << "탈락!\n";
										Player::plnum--;
									}
								}
								else  // 뒤에 배치된 컴퓨터 플레이어가 승리한 경우
								{
									com[t].setlife(2, com[y].unitsum(1));
									com[y].setmoney(1, com[t].unitsum(2));
									if (com[t].printlife() <= 0)
									{
										com[t].out();
										cout << com[t].printname() << "탈락!\n";
										Player::plnum--;
									}
								}
							}
						}
						else // 컴퓨터 플레이어의 수가 짝수인 경우 (전체 플레이어의 수는 홀수)
						{
							if (k == 1) // 전체 플레이어의 수가 3명이면 동적 배열 u[1]이 생성되므로 마지막 플레이어를 다르게 처리
							{
								int t = u[k - 1], y = 1;
								for (int r = 0; r < num; r++)
								{
									if (com[r].printmatchnum() == 1) // 앞 순서 matchnum을 가진 플레이어를 직접 찾아 경기를 매칭함
									{
										y = r;
										break;
									}
								}
								if (combattle(com[t], com[y]) == 1) // 앞에 배치된 컴퓨터 플레이어가 승리한 경우
								{
									com[t].setmoney(1, com[y].unitsum(2));
									if (com[y].printlife() <= 0)
									{
										com[y].out();
										cout << com[y].printname() << "탈락!\n";
										Player::plnum--;
									}
								}
								else
								{
									com[t].setlife(2, com[y].unitsum(1));
									if (com[t].printlife() <= 0)
									{
										com[t].out();
										cout << com[t].printname() << "탈락!\n";
										Player::plnum--;
									}
								}
							}
							else
							{
								for (int i = 0; i < k - 1; i += 2)
								{
									int t = u[i], y = u[i + 1];
									if (combattle(com[t], com[y]) == 1) // 앞에 배치된 컴퓨터 플레이어가 승리한 경우
									{
										com[y].setlife(2, com[t].unitsum(1));
										com[t].setmoney(1, com[y].unitsum(2));
										if (com[y].printlife() <= 0)
										{
											com[y].out();
											cout << com[y].printname() << "탈락!\n";
											Player::plnum--;
										}
									}
									else // 뒤에 배치된 컴퓨터 플레이어가 승리한 경우
									{
										com[t].setlife(2, com[y].unitsum(1));
										com[y].setmoney(1, com[y].unitsum(2));
										if (com[t].printlife() <= 0)
										{
											com[t].out();
											cout << com[t].printname() << "탈락!\n";
											Player::plnum--;
										}
									}
								}

								int t = u[k - 1], y = u[k - 2]; // 마지막 플레이어는 이전 인덱스 플레이어와 경기
								if (combattle(com[t], com[y]) == 1) // 앞에 배치된 컴퓨터 플레이어가 승리한 경우
								{
									com[t].setmoney(1, com[y].unitsum(2));
								}
								else
								{
									com[t].setlife(2, com[y].unitsum(1));
									if (com[t].printlife() <= 0)
									{
										com[t].out();
										cout << com[t].printname() << "탈락!\n";
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
			else if (c == 2) // 유닛 상점
			{
				user.buy(UnitShop(user)); // 리턴값이 UnitData인 유닛 상점 함수를 불러온 후 리턴된(사용자가 고른) 유닛 정보를 user.buy()를 통해 구매
			}
			else if (c == 3) // 나의 팀 정보 (순서 바꾸기, 판매, 생명<->돈 교환)
			{
			    MyTeamInfo(puser);
			}
		} while (Player::plnum != 1); // 플레이어가 1명이 될 때까지 반복

	ending:
		cout << Player::turn << "턴 끝에 ";
		if (user.printstatus() == 1)
		{
			cout << user.printname() << "(이)가 우승하였습니다. 축하합니다!\n";
		}
		else
		{
			cout << "탈락하셨습니다.\n";
		}
		delete[] com; // 동적으로 할당받은 컴퓨터 플레이어 배열 반납
		delete[] tmp; 
		cout << "게임 종료\n";
	}
	if (n == 2)
	{
		manual(); // 텍스트 파일을 바이너리 모드로 열어 게임 방법 출력
	}
	if (n == 3)
	{
		printdatabase(); // 모든 유닛의 정보를 출력하는 함수 호출
	}
	} while (n != 4);
}