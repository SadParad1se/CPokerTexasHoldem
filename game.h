#ifndef CPOKER_GAME_H
#define CPOKER_GAME_H

#endif //CPOKER_GAME_H


void roundStart();
void gameSetup(int playersNumber, int defaultBet, int startingMoney, char name[15]);
int roundEnd();
void shufflePlayers();
int isGameFinished();
int getHumanId();
int AIdoAction(int playerId, int turn, int raised);
