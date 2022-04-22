#ifndef _HELPERS_H_INCLUDED
#define _HELPERS_H_INCLUDED

typedef enum {spade = 1, heart = 2, diamond = 3, club = 4} colors;
typedef enum {two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13, ace = 14} values;

typedef struct card {
    colors color;
    values value;
} card;

typedef struct hand {
    card card1;
    card card2;
} hand;

typedef struct player {
    hand hand;
    int money;
    int bet;
    int inGame;  // is participating in the game
    int playing;
    int human;
    char *name;
    float combination;
} player;

struct game {
    int pricePool;
    int defaultBet;
    int winner;
    int numOfPlayers;
} game;

struct player players[10];
struct card gameCards[5];
struct card cardsPile[52];
struct card discardPile[52];

void fillCardsPile();
void shuffleCardsPile();
card pickUpCard();
void discardCard(card chosenCard);
void dealCards();
void revealGameCards(int offset, int count);

void actionFold(int playerId);
void actionCall(int playerId, int amount);
void actionRaise(int playerId, int amount);
void actionCheck(int playerId);

float isRoyalFlush(card *cards);
float isStraightFlush(card *cards);
float isFourOfAKind(card *cards);
float isFullHouse(card *cards);
float isFlush(card *cards);
float isStraight(card *cards);
float isThreeOfAKind(card *cards);
float isTwoPairs(card *cards);
float isOnePair(card *cards);
float isHighHand(int playerId);

float checkCombinations(int playerId);
void checkWinner();
void rewardWinner(int playerId);

#endif //_HELPERS_H_INCLUDED
