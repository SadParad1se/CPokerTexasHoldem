#include "helpers.h"
#include <stdlib.h>


void fillCardsPile() {
    int cardCounter = 0;

    for (int i = 2; i < 15; ++i) {
        for (int j = 1; j < 5; ++j) {
            cardsPile[cardCounter].value = i;
            cardsPile[cardCounter].color = j;
            cardCounter++;
        }
    }
}

void shuffleCardsPile() {
    int n = 52;
    int j;
    for (int i = 0; i < n - 1; i++)
    {
        j = i + rand() / (RAND_MAX / (n - i) + 1);
        card t = cardsPile[j];
        cardsPile[j] = cardsPile[i];
        cardsPile[i] = t;
    }
}

card pickUpCard() {
    card chosenCard = {0,0};
    for (int i = 0; i < 52; ++i) {
        if (cardsPile[i].value != 0) {
            chosenCard = cardsPile[i];
            cardsPile[i].value = 0;
            return chosenCard;
        }
    }
    return chosenCard;
}

void discardCard(card chosenCard) {
    for (int i = 0; i < 52; ++i) {
        if (discardPile[i].value == 0) {
            discardPile[i] = chosenCard;
            return;
        }
    }
}

void dealCards() {
    for (int i = 0; i < 9; ++i) {
        if (players[i].inGame == 0) continue;
        players[i].hand.card1 = pickUpCard();
        players[i].hand.card2 = pickUpCard();
    }
}

void revealGameCards(int offset, int count) {
    discardCard(pickUpCard());
    for (int i = 0; i < count; ++i) {
        gameCards[offset + i] = pickUpCard();
    }
}

void actionFold(int playerId) {
    discardCard(players[playerId].hand.card1);
    discardCard(players[playerId].hand.card2);
    players[playerId].hand.card1.value = 0;
    players[playerId].hand.card1.color = 0;
    players[playerId].hand.card2.value = 0;
    players[playerId].hand.card2.color = 0;
    players[playerId].playing = 0;
}

void actionCall(int playerId, int amount) {
    if (amount > players[playerId].money) amount = players[playerId].money;
    players[playerId].money -= amount;
    players[playerId].bet += amount;
    game.pricePool += amount;
}

void actionRaise(int playerId, int amount) {
    if (amount > players[playerId].money) amount = players[playerId].money;
    players[playerId].money -= amount;
    players[playerId].bet += amount;
    game.pricePool += amount;
}

void actionCheck(int playerId) {

}

float isRoyalFlush(card *cards) {
    int previousValue = 0, previousColor = 0, continuous = 1, canHappen = 0;

    for (int i = 0; i < 7; ++i) {
        if (cards[i].value == 0) continue;
        if (canHappen == 1 || cards[i].value == 10) {
            canHappen = 1;
            if (previousValue + 1 == cards[i].value && previousColor == cards[i].color) {
                continuous++;
            }
            else continuous = 1;

            if (continuous == 5) return (float)0.1;
            previousValue = cards[i].value;
            previousColor = cards[i].color;
        }
    }
    return 0;
}

float isStraightFlush(card *cards) {
    int previousValue = 0, continuous = 1, color1 = 0, color2 = 0, color3 = 0, color4 = 0, color;

    for (int i = 0; i < 7; ++i) {
        if (cards[i].value == 0) continue;
        if (cards[i].color == 1) color1++;
        else if (cards[i].color == 2) color2++;
        else if (cards[i].color == 3) color3++;
        else color4++;
    }

    if (color1 >= 5) color = 1;
    else if (color2 >= 5) color = 2;
    else if (color3 >= 5) color = 3;
    else if (color4 >= 5) color = 4;
    else return 0;

    for (int k = 0; k < 7; ++k) {  // set value to zero for wrong colors
        if (cards[k].color != color) cards[k].value = 0;
    }

    if (cards[6].value == 14) {  // check if the straight is starting with ace
        previousValue = 1;
    }

    for (int i = 0; i < 7; ++i) {
        if (cards[i].value == 0) continue;
        if (previousValue == 0) previousValue = cards[i].value;
        if (previousValue + 1 == cards[i].value) {
            continuous++;
        }
        else if (previousValue == cards[i].value) continue;
        else continuous = 1;

        if (continuous == 5) {  // if we have 5 cards straight
            if (i < 6 && cards[i].value + 1 == cards[i + 1].value) {  // if we have 6 cards straight
                if (i < 5 && cards[i + 1].value + 1 == cards[i + 2].value) {  // if we have 7 cards straight
                    return (float)cards[i + 2].value / 100;
                }
                return (float)cards[i + 1].value / 100;
            }
            return (float)cards[i].value / 100;
        }
        previousValue = cards[i].value;
    }
    return 0;
}

float isFourOfAKind(card *cards) {
    for (int i = 0; i < 4; ++i) {  // has to be four because of checking cards[i+1], cards[i+2] and cards[i+3]
        if (cards[i].value == 0) continue;
        if (cards[i].value == cards[i+1].value && cards[i].value == cards[i+2].value && cards[i].value == cards[i+3].value) return (float)cards[i].value / 100;
    }
    return 0;
}

float isFullHouse(card *cards) {
    float threeOfAKindValue, pairValue = 0;

    if ((threeOfAKindValue = isThreeOfAKind(cards))) {
        for (int i = 0; i < 6; ++i) {  // has to be six because of checking cards[i+1]
            if (cards[i].value == 0) continue;
            if (cards[i].value == cards[i+1].value && (float)cards[i].value > pairValue && (float)cards[i].value/100 != threeOfAKindValue)
                pairValue = (float)cards[i].value;
        }
        if (pairValue > 0) return (threeOfAKindValue * 3) + (((float)pairValue / 100) * 2);
    }
    return 0;
}

float isFlush(card *cards) {
    int color1 = 0, color2 = 0, color3 = 0, color4 = 0;

    for (int i = 0; i < 7; ++i) {
        if (cards[i].value == 0) continue;
        if (cards[i].color == 1) color1++;
        else if (cards[i].color == 2) color2++;
        else if (cards[i].color == 3) color3++;
        else if (cards[i].color == 4) color4++;
    }

    if (color1 == 5 || color2 == 5 || color3 == 5 || color4 == 5) return (float)0.1;
    return 0;
}

float isStraight(card *cards) {
    int previousValue = 0, continuous = 1;

    if (cards[6].value == 14) {  // check if the straight is starting with ace
        previousValue = 1;
    }

    for (int i = 0; i < 7; ++i) {
        if (cards[i].value == 0) continue;
        if (previousValue == 0) previousValue = cards[i].value;
        if (previousValue + 1 == cards[i].value) {
            continuous++;
        }
        else if (previousValue == cards[i].value) continue;  // if it's the same card just pass
        else continuous = 1;

        if (continuous == 5) {  // if we have 5 cards straight
            if (i < 6 && cards[i].value + 1 == cards[i+1].value) {  // if we have 6 cards straight
                if (i < 5 && cards[i+1].value + 1 == cards[i+2].value) {  // if we have 7 cards straight
                    return (float)cards[i+2].value / 100;
                }
                return (float)cards[i+1].value / 100;
            }
            return (float)cards[i].value / 100;
        }
        previousValue = cards[i].value;
    }
    return 0;
}

float isThreeOfAKind(card *cards) {
    int threeOfAKindValue = 0;

    for (int i = 0; i < 5; ++i) {  // has to be five because of checking cards[i+1] and cards[i+2]
        if (cards[i].value == 0) continue;
        if (cards[i].value == cards[i+1].value && cards[i].value == cards[i+2].value && cards[i].value > threeOfAKindValue) threeOfAKindValue = cards[i].value;
    }
    if (threeOfAKindValue > 0) return (float)threeOfAKindValue / 100;
    return 0;
}

float isTwoPairs(card *cards) {
    int pairCount = 0, pairValue1 = 0, pairValue2 = 0;

    for (int i = 0; i < 6; ++i) {  // has to be six because of checking cards[i+1]
        if (cards[i].value == 0) continue;
        if (cards[i].value == cards[i+1].value) {
            pairCount++;
            if (pairCount == 1) pairValue1 = cards[i].value;
            else if (pairCount == 2) pairValue2 = cards[i].value;
            else {
                if (cards[i].value > pairValue1) pairValue1 = cards[i].value;
                else if (cards[i].value > pairValue2) pairValue2 = cards[i].value;
            }
        }
    }
    if (pairCount >= 2) return ((float)pairValue1 + (float)pairValue2) / 100;
    return 0;
}

float isOnePair(card *cards) {
    int pairValue = 0;

    for (int i = 0; i < 6; ++i) {  // has to be six because of checking cards[i+1]
        if (cards[i].value == 0) continue;
        if (cards[i].value == cards[i+1].value && cards[i].value > pairValue) pairValue = cards[i].value;
    }
    if (pairValue > 0) return (float)pairValue / 100;
    return 0;
}

float isHighHand(int playerId) {
    float higherCard;

    if (players[playerId].hand.card1.value > players[playerId].hand.card2.value)
        higherCard = (float)players[playerId].hand.card1.value / 100;
    else higherCard = (float)players[playerId].hand.card2.value / 100;
    return higherCard;
}

float checkCombinations(int playerId) {
    float combinationValue, match;
    card combinationCards[7];

    for (int i = 0; i < 5; ++i) {
        combinationCards[i] = gameCards[i];
    }
    combinationCards[5] = players[playerId].hand.card1;
    combinationCards[6] = players[playerId].hand.card2;

    for(int i = 7 - 2; i >= 0; i--) {
        for(int j = 0; j <= i; j++) {
            if(combinationCards[j].value > combinationCards[j+1].value) {
                card t = combinationCards[j];
                combinationCards[j] = combinationCards[j+1];
                combinationCards[j+1] = t;
            }
        }
    }


    if ((match = isRoyalFlush(combinationCards))) combinationValue = match + 10;
    else if ((match = isStraightFlush(combinationCards))) combinationValue = match + 9;
    else if ((match = isFourOfAKind(combinationCards))) combinationValue = match + 8;
    else if ((match = isFullHouse(combinationCards))) combinationValue = match + 7;
    else if ((match = isFlush(combinationCards))) combinationValue = match + 6;
    else if ((match = isStraight(combinationCards))) combinationValue = match + 5;
    else if ((match = isThreeOfAKind(combinationCards))) combinationValue = match + 4;
    else if ((match = isTwoPairs(combinationCards))) combinationValue = match + 3;
    else if ((match = isOnePair(combinationCards))) combinationValue = match + 2;
    else combinationValue = isHighHand(playerId) + 0;

    return combinationValue;
}

void checkWinner() {
    float winningCombinations[game.numOfPlayers], highestCombination = 0;
    int winner;

    for (int i = 0; i < 9; ++i) {
        if (players[i].inGame == 0) continue;
        winningCombinations[i] = checkCombinations(i);
        players[i].combination = winningCombinations[i];
    }

    for (int i = 0; i < 9; ++i) {
        if (players[i].inGame == 0) continue;
        if (winningCombinations[i] > highestCombination) {
            highestCombination = winningCombinations[i];
            winner = i;
        }
        else if (winningCombinations[i] == highestCombination && winningCombinations[i] - 0.15 > 0) {
            if (isHighHand(i) > isHighHand(winner)) {
                highestCombination = winningCombinations[i];
                winner = i;
            }
        }
    }
    game.winner = winner;
}


void rewardWinner(int playerId) {
    players[playerId].money += game.pricePool;
    game.pricePool = 0;

    for (int i = 0; i < 9; ++i) {
        if (players[i].inGame == 0) continue;
        players[i].bet = 0;
    }
}
