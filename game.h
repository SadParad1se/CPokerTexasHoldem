#ifndef _GAME_H_INCLUDED
#define _GAME_H_INCLUDED

void roundStart();
void gameSetup(int playersNumber, int defaultBet, int startingMoney, char name[15]);
int roundEnd();
void shufflePlayers();
int isGameFinished();
int getHumanId();
int AIdoAction(int playerId, int turn, int raised);

#endif //_GAME_H_INCLUDED
