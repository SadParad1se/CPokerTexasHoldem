#include "game.h"
#include "helpers.h"
#include <stdlib.h>


void shufflePlayers() {
    int n = game.numOfPlayers;
    int j;
    for (int i = 0; i < n - 1; i++)
    {
        j = i + rand() / (RAND_MAX / (n - i) + 1);
        player t = players[j];
        players[j] = players[i];
        players[i] = t;
    }
}

void roundStart() {
    shufflePlayers();
    fillCardsPile();
    shuffleCardsPile();
    dealCards();
}

void gameSetup(int playersNumber, int defaultBet, int startingMoney, char name[15]) {
    char *names[600] = {"James", "Willie", "Chad", "Zachary", "Mathew", "John", "Ralph", "Jacob", "Corey", "Tyrone", "Robert", "Lawrence", "Lee", "Herman", "Darren", "Michael", "Nicholas", "Melvin", "Maurice", "Lonnie", "William", "Roy", "Alfred", "Vernon", "Lance", "David", "Benjamin", "Kyle", "Roberto", "Cody", "Richard", "Bruce", "Francis", "Clyde", "Julio", "Charles", "Brandon", "Bradley", "Glen", "Kelly", "Joseph", "Adam", "Jesus", "Hector", "Kurt", "Thomas", "Harry", "Herbert", "Shane", "Allan", "Christopher", "Fred", "Frederick", "Ricardo", "Nelson", "Daniel", "Wayne", "Ray", "Sam", "Guy", "Paul", "Billy", "Joel", "Rick", "Clayton", "Mark", "Steve", "Edwin", "Lester", "Hugh", "Donald", "Louis", "Don", "Brent", "Max", "George", "Jeremy", "Eddie", "Ramon", "Dwayne", "Kenneth", "Aaron", "Ricky", "Charlie", "Dwight", "Steven", "Randy", "Troy", "Tyler", "Armando", "Edward", "Howard", "Randall", "Gilbert", "Felix", "Brian", "Eugene", "Barry", "Gene", "Jimmie", "Ronald", "Carlos", "Alexander", "Marc", "Everett", "Anthony", "Russell", "Bernard", "Reginald", "Jordan", "Kevin", "Bobby", "Mario", "Ruben", "Ian", "Jason", "Victor", "Leroy", "Brett", "Wallace", "Matthew", "Martin", "Francisco", "Angel", "Ken", "Gary", "Ernest", "Marcus", "Nathaniel", "Bob", "Timothy", "Phillip", "Micheal", "Rafael", "Jaime", "Jose", "Todd", "Theodore", "Leslie", "Casey", "Larry", "Jesse", "Clifford", "Edgar", "Alfredo", "Jeffrey", "Craig", "Miguel", "Milton", "Alberto", "Frank", "Alan", "Oscar", "Raul", "Dave", "Scott", "Shawn", "Jay", "Ben", "Ivan", "Eric", "Clarence", "Jim", "Chester", "Johnnie", "Stephen", "Sean", "Tom", "Cecil", "Sidney", "Andrew", "Philip", "Calvin", "Duane", "Byron", "Raymond", "Chris", "Alex", "Franklin", "Julian", "Gregory", "Johnny", "Jon", "Andre", "Isaac", "Joshua", "Earl", "Ronnie", "Elmer", "Morris", "Jerry", "Jimmy", "Bill", "Brad", "Clifton", "Dennis", "Antonio", "Lloyd", "Gabriel", "Willard", "Walter", "Danny", "Tommy", "Ron", "Daryl", "Patrick", "Bryan", "Leon", "Mitchell", "Ross", "Peter", "Tony", "Derek", "Roland", "Virgil", "Harold", "Luis", "Warren", "Arnold", "Andy", "Douglas", "Mike", "Darrell", "Harvey", "Marshall", "Henry", "Stanley", "Jerome", "Jared", "Salvador", "Carl", "Leonard", "Floyd", "Adrian", "Perry", "Arthur", "Nathan", "Leo", "Karl", "Kirk", "Ryan", "Dale", "Alvin", "Cory", "Sergio", "Roger", "Manuel", "Tim", "Claude", "Marion", "Joe", "Rodney", "Wesley", "Erik", "Tracy", "Juan", "Curtis", "Gordon", "Darryl", "Seth", "Jack", "Norman", "Dean", "Jamie", "Kent", "Albert", "Allen", "Greg", "Neil", "Terrance", "Jonathan", "Marvin", "Jorge", "Jessie", "Rene", "Justin", "Vincent", "Dustin", "Christian", "Eduardo", "Terry", "Glenn", "Pedro", "Javier", "Terrence", "Gerald", "Jeffery", "Derrick", "Fernando", "Enrique", "Keith", "Travis", "Dan", "Clinton", "Freddie", "Samuel", "Jeff", "Lewis", "Ted", "Wade", "Mary", "Katherine", "Josephine", "Ana", "Heidi", "Patricia", "Joan", "Thelma", "Renee", "Glenda", "Linda", "Ashley", "Shannon", "Ida", "Lydia", "Barbara", "Judith", "Sheila", "Vivian", "Viola", "Elizabeth", "Rose", "Ethel", "Roberta", "Courtney", "Jennifer", "Janice", "Ellen", "Holly", "Marian", "Maria", "Kelly", "Elaine", "Brittany", "Stella", "Susan", "Nicole", "Marjorie", "Melanie", "Caroline", "Margaret", "Judy", "Carrie", "Loretta", "Dora", "Dorothy", "Christina", "Charlotte", "Yolanda", "Jo", "Lisa", "Kathy", "Monica", "Jeanette", "Vickie", "Nancy", "Theresa", "Esther", "Laurie", "Mattie", "Karen", "Beverly", "Pauline", "Katie", "Terry", "Betty", "Denise", "Emma", "Kristen", "Maxine", "Helen", "Tammy", "Juanita", "Vanessa", "Irma", "Sandra", "Irene", "Anita", "Alma", "Mabel", "Donna", "Jane", "Rhonda", "Sue", "Marsha", "Carol", "Lori", "Hazel", "Elsie", "Myrtle", "Ruth", "Rachel", "Amber", "Beth", "Lena", "Sharon", "Marilyn", "Eva", "Jeanne", "Christy", "Michelle", "Andrea", "Debbie", "Vicki", "Deanna", "Laura", "Kathryn", "April", "Carla", "Patsy", "Sarah", "Louise", "Leslie", "Tara", "Hilda", "Kimberly", "Sara", "Clara", "Rosemary", "Gwendolyn", "Deborah", "Anne", "Lucille", "Eileen", "Jennie", "Jessica", "Jacqueline", "Jamie", "Terri", "Nora", "Shirley", "Wanda", "Joanne", "Gertrude", "Margie", "Cynthia", "Bonnie", "Eleanor", "Lucy", "Nina", "Angela", "Julia", "Valerie", "Tonya", "Cassandra", "Melissa", "Ruby", "Danielle", "Ella", "Leah", "Brenda", "Lois", "Megan", "Stacey", "Penny", "Amy", "Tina", "Alicia", "Wilma", "Kay", "Anna", "Phyllis", "Suzanne", "Gina", "Priscilla", "Rebecca", "Norma", "Michele", "Kristin", "Naomi", "Virginia", "Paula", "Gail", "Jessie", "Carole", "Kathleen", "Diana", "Bertha", "Natalie", "Brandy", "Pamela", "Annie", "Darlene", "Agnes", "Olga", "Martha", "Lillian", "Veronica", "Vera", "Billie", "Debra", "Emily", "Jill", "Willie", "Dianne", "Amanda", "Robin", "Erin", "Charlene", "Tracey", "Stephanie", "Peggy", "Geraldine", "Bessie", "Leona", "Carolyn", "Crystal", "Lauren", "Delores", "Jenny", "Christine", "Gladys", "Cathy", "Melinda", "Felicia", "Marie", "Rita", "Joann", "Pearl", "Sonia", "Janet", "Dawn", "Lorraine", "Arlene", "Miriam", "Catherine", "Connie", "Lynn", "Maureen", "Velma", "Frances", "Florence", "Sally", "Colleen", "Becky", "Ann", "Tracy", "Regina", "Allison", "Bobbie", "Joyce", "Edna", "Erica", "Tamara", "Violet", "Diane", "Tiffany", "Beatrice", "Joy", "Kristina", "Alice", "Carmen", "Dolores", "Georgia", "Toni", "Julie", "Rosa", "Bernice", "Constance", "Misty", "Heather", "Cindy", "Audrey", "Lillie", "Mae", "Teresa", "Grace", "Yvonne", "Claudia", "Shelly", "Doris", "Wendy", "Annette", "Jackie", "Daisy", "Gloria", "Victoria", "June", "Marcia", "Ramona", "Evelyn", "Edith", "Samantha", "Tanya", "Sherri", "Jean", "Kim", "Marion", "Nellie", "Erika", "Cheryl", "Sherry", "Dana", "Minnie", "Katrina", "Mildred", "Sylvia", "Stacy", "Marlene", "Claire"};
    game.numOfPlayers = playersNumber;
    game.defaultBet = defaultBet;

    for (int i = 0; i < 9; ++i) { // max players num is 10
        if (i == game.numOfPlayers) break; // so only wanted num of players is
        players[i].money = startingMoney;
        players[i].inGame = 1;
        players[i].playing = 1;

        if (i == 0) {
            players[i].name = name;
            players[i].human = 1;
        }
        else {
            players[i].name = names[rand() % 600];
            players[i].human = 0;
        }
    }
}

int roundEnd() {
    checkWinner();
    rewardWinner(game.winner);
    return isGameFinished();
}

int isGameFinished() {
    int gameIsFinished = 1;
    for (int i = 0; i < game.numOfPlayers - 1; ++i) {
        if (players[i].inGame && players[i].money > 0) {
            gameIsFinished = 0;
            break;
        }
    }
    return gameIsFinished;
}

int AIdoAction(int playerId, int turn, int raised) {
    float cardsValue;
    int choice = 0;
    cardsValue = checkCombinations(playerId);

    if (turn == 0) {
        if (cardsValue < 0.03) {
            actionFold(playerId);
            choice = 1;
        }
        else if (cardsValue < 3) {
            actionCall(playerId, game.defaultBet);
            choice = 2;
        }
        else {
            actionRaise(playerId, players[playerId].money);
            choice = 3;
        }
    }

    else if (turn == 1) {
        if (cardsValue < 3) {
            if (raised > game.pricePool) {
                actionCall(playerId, raised);
                choice = 2;
            }
            else {
                actionCall(playerId, game.defaultBet);
                choice = 2;
            }
        }
        else {
            actionRaise(playerId, players[playerId].money/10);
            choice = 3;
        }
    }

    else if (turn == 2) {
        if (cardsValue < 3) {
            if (raised > game.pricePool) {
                actionFold(playerId);
                choice = 1;
            }
        }
        else if (cardsValue < 5) {
            if (raised > game.pricePool) {
                actionCall(playerId, raised);
                choice = 2;
            }
            else {
                actionCall(playerId, game.defaultBet + 100);
                choice = 2;
            }
        }
        else {
            if (players[playerId].money < 500) {
                actionRaise(playerId, players[playerId].money);
                choice = 3;
            }
            else {
                actionRaise(playerId, players[playerId].money/4);
                choice = 3;
            }

        }
    }

    else if (turn == 3) {
        if (cardsValue < 5) {
            if (raised  == 0) {
                actionCheck(playerId);
                choice = 4;
            }
            else {
                actionCall(playerId, raised);
                choice = 2;
            }
        }
        else {
            actionRaise(playerId, players[playerId].money);
            choice = 3;
        }
    }
    else {
        actionRaise(playerId, players[playerId].money);
        choice = 3;
    }

    return choice;
}

int getHumanId() {
    for (int i = 0; i < game.numOfPlayers - 1; ++i) {
        if (players[i].human == 1) return i;
    }
    return -1;
}