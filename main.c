#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "game.h"
#include "time.h"

int playersSelection() {
    int playersNumber = 0;

    while (playersNumber == 0) {
        printf("Select how many friends will join you at the table (2 - 10): ");
        scanf("%d", &playersNumber);
        if (playersNumber >= 2 && playersNumber <= 10) return playersNumber;
        else {
            playersNumber = 0;
            printf("\nNumber of players must be between 2 and 10!\n");
        }

    }
    return 0;
}

int moneySelection() {
    int money = 0;

    while (money == 0) {
        printf("Select how much money will you start with (200 - 10 000): ");
        scanf("%d", &money);
        if (money >= 200 && money <= 10000) return money;
        else {
            money = 0;
            printf("\nStarting money value must be between 200 and 10 000!\n");
        }

    }
    return 0;
}

void translateCombination(float combinationValue) {
    if (combinationValue < 2) printf("(highest card)");
    else if (combinationValue < 3) printf("(one pair)");
    else if (combinationValue < 4) printf("(two pairs)");
    else if (combinationValue < 5) printf("(three of a kind)");
    else if (combinationValue < 6) printf("(straight)");
    else if (combinationValue < 7) printf("(flush)");
    else if (combinationValue < 8) printf("(fullhouse)");
    else if (combinationValue < 9) printf("(four of a kind)");
    else if (combinationValue < 10) printf("(straight flush)");
    else printf("(royal flush)");
}

void printCards(int playerId) {
    float combinationValue = checkCombinations(playerId);
    printf("cards: %d:%d, %d:%d", players[playerId].hand.card1.value, players[playerId].hand.card1.color,
           players[playerId].hand.card2.value, players[playerId].hand.card2.color);
    printf("\nYour combination: %.2f ", combinationValue);
    translateCombination(combinationValue);
    printf("\n");
}

void printHumanText(int playerId) {
    printf("\n\n\n");
    printf("Cards on the deck: \n");
    for (int i = 0; i < 5; ++i) {
        if (gameCards[i].value == 0) printf("- ");
        else printf("%d:%d ", gameCards[i].value, gameCards[i].color);
    }

    printf("\n\nHere are your cards: ");
    printCards(playerId);
    printf("\n");
    printf("Your money: %d", players[playerId].money);
    printf("\n\n");
    printf("What do you want to do (options 1-5)?\n");
    printf("1. fold, ");
    printf("2. call, ");
    printf("3. bet, ");
    printf("4. check, ");
    printf("5. quit game\n");
}

int getUsersChoice() {
    int choice = 0;

    while (choice == 0) {
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 5) return choice;
        else {
            choice = 0;
            printf("\nLook at the options..\n");
        }

    }
    return 0;
}

int getUsersBet() {
    int bet = 0;

    printf("Your bet: ");
    scanf("%d", &bet);
    printf("\n");
    if (bet >= 1) return bet;
    else return game.defaultBet;

}

void printActionMessage(int playerId, int choice, int raised) {
    if (choice == 1) printf("Player %s chose to FOLD!", players[playerId].name);
    else if (choice == 2) printf("Player %s chose to CALL %d!", players[playerId].name, raised);
    else if (choice == 3) printf("Player %s chose to RAISE %d!", players[playerId].name, raised);
    else if (choice == 4) printf("Player %s chose to CHECK!", players[playerId].name);
    printf("\n\n");
}

void printEndRoundStatistics() {
    printf("\n\n------------------- END OF THE ROUND -------------------\n\n");
    for (int i = 0; i < game.numOfPlayers; ++i) {
        if (players[i].inGame == 0) printf("Player %s is out of the game.", players[i].name);
        else {
            printf("Player %s has combination %.2f ", players[i].name, players[i].combination);
            translateCombination(players[i].combination);
            printf(" and has %d money. \n", players[i].money);
        }
    }
    printf("\n\n!!!Player %s is the WINNER and has %d money!!!", players[game.winner].name, players[game.winner].money);
}

char *nameSelection() {
    char *name;
    printf("Please enter your name: ");
    scanf( "%15[^\n]", name);
    printf("\nWelcome to the game %s!\n", name);
    return name;
}

int gameRound(int humanId, int turn) {
    int choice, raised = 0, moneyOnStart = game.pricePool;

    for (int i = 0; i < 9; ++i) { // max num of players is 10
        if (players[i].inGame == 0 || players[i].playing == 0) continue;  // inactive player

        if (i == humanId) {  // human round
            printHumanText(i);
            choice = getUsersChoice();

            if (choice == 1) {
                actionFold(i);
                printf("Exiting game... bye.");
                return -1;
            }

            else if (choice == 2) {
                if (raised == 0) {
                    actionCall(i, game.defaultBet);
                }
                else actionCall(i, raised);
            }

            else if (choice == 3) {
                int userBet = getUsersBet();
                if (userBet < raised) actionRaise(i, raised);
                else actionRaise(i, userBet);
            }

            else if (choice == 4) actionCheck(i);

            else {
                printf("Exiting game... bye.");
                return -1;
            }
        }

        else {  // AI round
            choice = AIdoAction(i, turn, raised);
        }
        if (moneyOnStart != game.pricePool) {
            raised = game.pricePool - moneyOnStart;
        }
        printActionMessage(i, choice, raised);

    }
    return 0;
}

int main() {
    srand(time(NULL));
    printf("Welcome to CPoker: Texas hold 'em!\n\n");
    // setting defaults
    char *name = nameSelection();
    int playersNumber = playersSelection();
    int startingMoney = moneySelection();
    int smallestBet = 25;

    gameSetup(playersNumber, smallestBet, startingMoney, name);

    //game phase
    int humanId, roundResult;


    printf("Game starts!\n\n");
    printf("Shuffling and dealing cards...\n");
    roundStart();
    humanId = getHumanId();
    printf("Everything is set.\n");
    printf("Here are your cards: ");
    printCards(humanId);
    printf("\n\n");

    // turn 0
    for (int i = 0; i < 2; ++i) {
        printf("\n\n-------------- turn %d, round %d --------------\n\n", 0, i+1);
        roundResult = gameRound(humanId, 0);
        if (roundResult == -1) return -1;

    }
    revealGameCards(0, 3);

    // turn 1
    for (int i = 0; i < 2; ++i) {
        printf("\n\n-------------- turn %d, round %d --------------\n\n", 1, i+1);
        roundResult = gameRound(humanId, 1);
        if (roundResult == -1) return -1;
    }
    revealGameCards(3, 1);

    // turn 2
    for (int i = 0; i < 2; ++i) {
        printf("\n\n-------------- turn %d, round %d --------------\n\n", 2, i+1);
        roundResult = gameRound(humanId, 2);
        if (roundResult == -1) return -1;
    }
    revealGameCards(4, 1);

    //turn 3
    for (int i = 0; i < 2; ++i) {
        printf("\n\n-------------- turn %d, round %d --------------\n\n", 3, i+1);
        roundResult = gameRound(humanId, 3);
        if (roundResult == -1) return -1;

    }
    roundEnd();
    printEndRoundStatistics();

    return 0;
}
