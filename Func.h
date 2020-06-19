#ifndef FUNC_H 
#define FUNC_H

UnitData UnitShop(User a);
void MyTeamInfo(User* a);
extern int shopbalance;
void Matchnum(int* p, int i);
int find(Com* com);
void matchingresult(User a, Com* com, int num);
int battle(User a, Com b);
int attack(int a);
int combattle(Com a, Com b);
void commatch(int* p, Com* com, int a);
void battleresult(User a, Com* com, int* p, int num);
void rankinit(User* a, Com* com, int num);
void ranking(User* a, Com* com, int num);
void manual();
void printdatabase();
#endif