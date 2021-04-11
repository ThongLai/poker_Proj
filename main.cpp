#include <iostream>
#include <string>
using namespace std;

#define SUITS 4
#define FACES 13
#define CARDS 52

string suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
string faces[CARDS] = { "Ace", "Two", "Three", "Four", "Five","Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen","King" };

struct Player {
	string Hand_suits[5];
	string Hand_faces[5];
};


void shuffleCards(int deck[SUITS][FACES])
{
	int k = 0;
	for (int i = 0; i < SUITS; i++)
		for (int j = 0; j < FACES; j++)
			deck[i][j] = k++;

	for (int i = 0; i < CARDS; i++) {
		swap(deck[rand() % (SUITS)][rand() % (FACES)], deck[rand() % (SUITS)][rand() % (FACES)]);
	}
}

void linerSearch(int deck[SUITS][FACES], int n, int key,int &row_index ,int &col_index)
{
	int *p = (int*)deck;

	int i = 0;

	while (p[i] != key)
		i++;

	row_index = i / 13;
	if (i <= 12)
		col_index = i;
	else
		col_index = i % 13;
}

void printCardsShuffling(int deck[SUITS][FACES], string suits[], string faces[])
{
	for (int k = 0; k < CARDS; k++) {
		int i, j;
		linerSearch(deck, CARDS, k, i, j);

		cout << "(" << suits[i] << ", " << faces[j] << ")" << endl;
	}
}



void main()
{
	srand((int)time(0));
	int deck[SUITS][FACES];

	shuffleCards(deck);
	printCardsShuffling(deck, suits, faces);

	system("pause");
}