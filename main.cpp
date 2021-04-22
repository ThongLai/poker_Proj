#include <iostream>
#include <string>

using namespace std;

#define SUITS 4
#define FACES 13
#define CARDS 52
#define CARDS_HAND 5

string suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
//string faces[CARDS] = { "Ace", "Two", "Three", "Four", "Five","Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen","King" };
string faces[CARDS] = { "A", "2", "3", "4", "5","6", "7", "8", "9", "10", "J", "Q","K" };

int current_card;

int test_case[10] = { 1,0 ,1,12 ,1,11 ,1,10 ,1,9 };
int test_case_0[10] = { 3,0, 3,1, 1,1, 2,0, 1,0 };
int test_case_1[10] = { 0,8, 2,12, 1,8, 2,8, 3,12 };



struct Player {
	int **hand;
};

struct n_Player {
	int*** hands;
	int *ranks;
	int *scores;
	//string name;
};



void mainMenu();
void Menu_n_player();
void Menu_dealer_1();
void Menu_dealer_2();

//Common Functions
void shuffleCards(int deck[SUITS][FACES]);
void printCardsShuffling(int deck[SUITS][FACES], string suits[], string faces[]);
void printHand(int** hand, string suits[SUITS], string faces[FACES]);
int** createHandTest(int deck[SUITS][FACES], int a[]);

void Search_deck(int deck[SUITS][FACES], int key, int& row_index, int& col_index);
int isAceComparing(int ace1, int ace2);
void SortInDescendingFaces(int** arr);
void displayStatusOfHand(int** hand);

//1 Player
int** dealingForHand(int deck[SUITS][FACES]);

//Hand check
int isFourOfAKind(int** hand);
int isFullHouse(int** hand);
int isFlush(int** hand);
int isStraight(int** hand);
int isStraightFlush(int** hand);
int isThreeOfAKind(int** hand);
int isTwoPairs(int** hand);
int isPair(int** hand);
int getHighestCard(int** hand);

//n Players
int*** dealingFornHands(int deck[SUITS][FACES], int n);
int getStatusOfHand(int** hand);
int* rankingHands(int*** hands, int n);
void evaluateHands(int* scores, int* ranks, int n);

int EqualStatusOfHands(int status, int** hand1, int** hand2);

//Dealer
void swap_card(int deck[SUITS][FACES], int** hand, int card_index);
bool dealerDrawsCardsRandomly(int deck[SUITS][FACES], int** dealer_hand);
bool dealerDrawsCardsWisely(int deck[SUITS][FACES], int** dealer_hand);

//delete pointers
void delete_hand(int **hand);
void delete_n_hand(int*** player, int n);


int main()
{
	srand((int)time(0));
	int deck[SUITS][FACES];
	char user_input[2];

	do {
		system("cls");
		mainMenu();
		current_card = -1;
		
		cin >> user_input;
		cin.ignore(1000, '\n');

		switch (atoi(user_input))
		{
			case 0:
			{
				cout << endl << "	Good Bye!" << endl;
				system("pause");
				break;
			}
			case 1:
			{
				char user_input[2];
				while (true) {
					system("cls");
					Menu_dealer_1();

					cin >> user_input;
					cin.ignore(1000, '\n');

					if (atoi(user_input) != 0 && atoi(user_input) != 1) {
						cout << "	Wrong Input!" << endl;
						system("pause");
					}
					else
						break;
				}

			
				switch (atoi(user_input))
				{
					case 0:
					{
						system("cls");
						shuffleCards(deck);

						Player player;

						player.hand = dealingForHand(deck);
						//player.hand = createHandTest(deck, test_case);
						SortInDescendingFaces(player.hand);
						cout << endl;

						printHand(player.hand, suits, faces);
						cout << endl << endl;

						displayStatusOfHand(player.hand);

						cout << endl;
						delete_hand(player.hand);

						system("pause");
						break;
					}
					case 1: //Dealer mode
					{
						while (true) {
							system("cls");
							Menu_dealer_2();

							cin >> user_input;
							cin.ignore(1000, '\n');

							if (atoi(user_input) < 0 || atoi(user_input) > 2) {
								cout << "	Wrong Input!" << endl;
								system("pause");
							}
							else
								break;
						}

						shuffleCards(deck);
						//printCardsShuffling(deck, suits, faces);
						n_Player player;

						player.hands = dealingFornHands(deck, 2);

						switch (atoi(user_input))
						{
						case 0: //Easy
						{
							int turn = 0;
							while (turn < 3) {
								system("cls");

								//Dealer
								SortInDescendingFaces(player.hands[1]);
								cout << "Dealer: " << endl;
								printHand(player.hands[1], suits, faces);
								cout << endl;
								displayStatusOfHand(player.hands[1]);
								cout << endl;

								//Player
								SortInDescendingFaces(player.hands[0]);
								cout << "Player: " << endl;
								printHand(player.hands[0], suits, faces);
								cout << endl;
								displayStatusOfHand(player.hands[0]);
								system("pause");
								cout << endl;

								cout << "			*TURN " << turn + 1 << "*" << endl;
								//Player draws cards
								int* new_player_card = new int[2];
								Search_deck(deck, current_card + 1, new_player_card[0], new_player_card[1]);
								cout << "	You drawed this card: ";
								cout << "	(" << suits[new_player_card[0]] << ", " << faces[new_player_card[1]] << ")" << " " << endl;
								delete[]new_player_card;
								cout << endl;

								while (true) {
									cout << "Do you want to swap it with one of your card?... " << " 1: Yes. " << " 0: No. " << endl << "	Select: " << flush;
									cin >> user_input;
									cin.ignore(1000, '\n');

									if (atoi(user_input) != 0 && atoi(user_input) != 1) {
										cout << "	Wrong Input!" << endl;
										system("pause");
									}
									else
										break;
								}

								if (atoi(user_input) == 1)
								{
									while (true) {
										cout << "Type the card index that you want to be swapped... " << " (0) (1) (2) (3) (4) " << endl << "	Select: ";
										cin >> user_input;
										cin.ignore(1000, '\n');

										if (atoi(user_input) < 0 || atoi(user_input) > 4) {
											cout << "	Wrong Input! Choose the card index between 0 and 4." << endl;
											system("pause");
										}
										else
											break;
									}
									swap_card(deck, player.hands[0], atoi(user_input));

									cout << endl;
									cout << "__________________________________________________" << endl;

									cout << "	>> Player swapped a card. <<" << endl;
									cout << endl;

									SortInDescendingFaces(player.hands[0]);
									cout << "Player: " << endl;
									printHand(player.hands[0], suits, faces);
									cout << endl;
									displayStatusOfHand(player.hands[0]);

									cout << "__________________________________________________" << endl;
								}
								else
								{
									cout << endl;
									cout << "	>> Player did not want to swap. <<" << endl;
									cout << endl;
									current_card++;
								}
								system("pause");

								//Dealer draws cards
								cout << "\n\n\n";

								int* new_dealer_card = new int[2];
								Search_deck(deck, current_card + 1, new_dealer_card[0], new_dealer_card[1]);
								cout << "	Dealer drawed this card: ";
								cout << "  (" << suits[new_dealer_card[0]] << ", " << faces[new_dealer_card[1]] << ")" << " " << endl;
								delete[]new_dealer_card;

								if (dealerDrawsCardsRandomly(deck, player.hands[1])) {
									cout << "__________________________________________________" << endl;

									cout << "	>> Dealer swapped cards randomly... <<" << endl;
									cout << endl;

									SortInDescendingFaces(player.hands[1]);
									cout << "Dealer: " << endl;
									printHand(player.hands[1], suits, faces);
									cout << endl;
									displayStatusOfHand(player.hands[1]);

									cout << "__________________________________________________" << endl;
								}
								else {
									cout << "	>> Dealer did not want to swap. <<" << endl;
									cout << endl;
									current_card++;
								}
								system("pause");


								turn++;
							}

							player.ranks = rankingHands(player.hands, 2);

							system("cls");

							cout << "		**RESULT**" << endl;

							//Dealer
							SortInDescendingFaces(player.hands[1]);
							cout << "Dealer: " << endl;
							printHand(player.hands[1], suits, faces);
							cout << endl;
							displayStatusOfHand(player.hands[1]);
							cout << endl;

							//Player
							SortInDescendingFaces(player.hands[0]);
							cout << "Player: " << endl;
							printHand(player.hands[0], suits, faces);
							cout << endl;
							displayStatusOfHand(player.hands[0]);
							system("pause");
							cout << endl;


							cout << "\n\n\n";
							if (player.ranks[1] == 1)
								cout << "		***DEALER WIN***" << endl;
							else
								cout << "		***PLAYER WIN***" << endl;

							delete_n_hand(player.hands, 2);
							system("pause");
							break;							
						}
						case 1: //Medium
						{
							int turn = 0;
							while (turn < 3) {
								system("cls");

								//Dealer
								SortInDescendingFaces(player.hands[1]);
								cout << "Dealer: " << endl;
								printHand(player.hands[1], suits, faces);
								cout << endl;
								displayStatusOfHand(player.hands[1]);
								cout << endl;

								//Player
								SortInDescendingFaces(player.hands[0]);
								cout << "Player: " << endl;
								printHand(player.hands[0], suits, faces);
								cout << endl;
								displayStatusOfHand(player.hands[0]);
								system("pause");
								cout << endl;

								cout << "			*TURN " << turn + 1 << "*" << endl;
								//Player draws cards
								int* new_player_card = new int[2];
								Search_deck(deck, current_card + 1, new_player_card[0], new_player_card[1]);
								cout << "	You drawed this card: ";
								cout << "	(" << suits[new_player_card[0]] << ", " << faces[new_player_card[1]] << ")" << " " << endl;
								delete[]new_player_card;
								cout << endl;

								while (true) {
									cout << "Do you want to swap it with one of your card?... " << " 1: Yes. " << " 0: No. " << endl << "	Select: " << flush;
									cin >> user_input;
									cin.ignore(1000, '\n');

									if (atoi(user_input) != 0 && atoi(user_input) != 1) {
										cout << "	Wrong Input!" << endl;
										system("pause");
									}
									else
										break;
								}

								if (atoi(user_input) == 1)
								{
									while (true) {
										cout << "Type the card index that you want to be swapped... " << " (0) (1) (2) (3) (4) " << endl << "	Select: ";
										cin >> user_input;
										cin.ignore(1000, '\n');

										if (atoi(user_input) < 0 || atoi(user_input) > 4) {
											cout << "	Wrong Input! Choose the card index between 0 and 4." << endl;
											system("pause");
										}
										else
											break;
									}
									swap_card(deck, player.hands[0], atoi(user_input));

									cout << endl;
									cout << "__________________________________________________" << endl;
									
									cout << "	>> Player swapped a card. <<" << endl;
									cout << endl;

									SortInDescendingFaces(player.hands[0]);
									cout << "Player: " << endl;
									printHand(player.hands[0], suits, faces);
									cout << endl;
									displayStatusOfHand(player.hands[0]);

									cout << "__________________________________________________" << endl;
								}
								else
								{
									cout << endl;
									cout << "	>> Player did not want to swap. <<" << endl;
									cout << endl;
									current_card++;
								}
								system("pause");

								//Dealer draws cards
								cout << "\n\n\n";

								int* new_dealer_card = new int[2];
								Search_deck(deck, current_card + 1, new_dealer_card[0], new_dealer_card[1]);
								cout << "	Dealer drawed this card: ";
								cout << "  (" << suits[new_dealer_card[0]] << ", " << faces[new_dealer_card[1]] << ")" << " " << endl;
								delete[]new_dealer_card;

								if (dealerDrawsCardsWisely(deck, player.hands[1])) {
									cout << "__________________________________________________" << endl;

									cout << "	>> Dealer swapped a card. <<" << endl;
									cout << endl;

									SortInDescendingFaces(player.hands[1]);
									cout << "Dealer: " << endl;
									printHand(player.hands[1], suits, faces);
									cout << endl;
									displayStatusOfHand(player.hands[1]);

									cout << "__________________________________________________" << endl;
								}
								else {
									cout << "	>> Dealer did not want to swap. <<" << endl;
									cout << endl;
									current_card++;
								}
								system("pause");

						
								turn++;
							}

							player.ranks = rankingHands(player.hands, 2);

							system("cls");

							cout << "		**RESULT**" << endl;

							//Dealer
							SortInDescendingFaces(player.hands[1]);
							cout << "Dealer: " << endl;
							printHand(player.hands[1], suits, faces);
							cout << endl;
							displayStatusOfHand(player.hands[1]);
							cout << endl;

							//Player
							SortInDescendingFaces(player.hands[0]);
							cout << "Player: " << endl;
							printHand(player.hands[0], suits, faces);
							cout << endl;
							displayStatusOfHand(player.hands[0]);
							system("pause");
							cout << endl;


							cout << "\n\n\n";
							if (player.ranks[1] == 1)
								cout << "		***DEALER WIN***" << endl;
							else
								cout << "		***PLAYER WIN***" << endl;

							delete_n_hand(player.hands, 2);
							system("pause");
							break;
						}
						case 2: //Hard
						{
							int turn = 0;
							while (turn < 3) {
								system("cls");

								//Dealer
								SortInDescendingFaces(player.hands[1]);
								cout << "Dealer: " << endl;
								printHand(player.hands[1], suits, faces);
								cout << endl;
								displayStatusOfHand(player.hands[1]);
								cout << endl;

								//Player
								SortInDescendingFaces(player.hands[0]);
								cout << "Player: " << endl;
								printHand(player.hands[0], suits, faces);
								cout << endl;
								displayStatusOfHand(player.hands[0]);
								system("pause");
								cout << endl;

								cout << "			*TURN " << turn + 1 << "*" << endl;

								//Dealer draws cards
								int* new_dealer_card = new int[2];
								Search_deck(deck, current_card + 1, new_dealer_card[0], new_dealer_card[1]);
								cout << "	Dealer drawed this card: ";
								cout << "  (" << suits[new_dealer_card[0]] << ", " << faces[new_dealer_card[1]] << ")" << " " << endl;
								delete[]new_dealer_card;

								if (dealerDrawsCardsWisely(deck, player.hands[1])) {
									cout << "__________________________________________________" << endl;

									cout << "	>> Dealer swapped a card. <<" << endl;
									cout << endl;

									SortInDescendingFaces(player.hands[1]);
									cout << "Dealer: " << endl;
									printHand(player.hands[1], suits, faces);
									cout << endl;
									displayStatusOfHand(player.hands[1]);

									cout << "__________________________________________________" << endl;
								}
								else {
									cout << "	>> Dealer did not want to swap. <<" << endl;
									cout << endl;
									current_card++;
								}
								system("pause");


								turn++;
							}

							player.ranks = rankingHands(player.hands, 2);

							system("cls");

							cout << "		**RESULT**" << endl;

							//Dealer
							SortInDescendingFaces(player.hands[1]);
							cout << "Dealer: " << endl;
							printHand(player.hands[1], suits, faces);
							cout << endl;
							displayStatusOfHand(player.hands[1]);
							cout << endl;

							//Player
							SortInDescendingFaces(player.hands[0]);
							cout << "Player: " << endl;
							printHand(player.hands[0], suits, faces);
							cout << endl;
							displayStatusOfHand(player.hands[0]);
							system("pause");
							cout << endl;


							cout << "\n\n\n";
							if (player.ranks[1] == 1)
								cout << "		***DEALER WIN***" << endl;
							else
								cout << "		***PLAYER WIN***" << endl;

							delete_n_hand(player.hands, 2);
							system("pause");
							break;

						}
						}

						break;

					}
				}

				break;
			}
			case 2: 
			{
				char user_input[3];

				while (true) {
					system("cls");
					Menu_n_player();

					cin >> user_input;
					cin.ignore(1000, '\n');

					if (atoi(user_input) > 10 || atoi(user_input) < 1) {
						cout << "	Wrong Input! The maximum number of players is 10 " << endl;
						system("pause");
					}
					else
						break;

				}

				int n = atoi(user_input);
				n_Player players;
				players.scores = new int[n];

				for (int i = 0; i < n; i++)
					players.scores[i] = 0;

				do{
					system("cls");
					current_card = 0;
					shuffleCards(deck);

					players.hands = dealingFornHands(deck, n);
					//players.hands[1] = createHandTest(deck, test_case);
					//players.hands[0] = createHandTest(deck, test_case_0);
					//players.hands[4] = createHandTest(deck, test_case_0);

					for (int i = 0; i < n; i++) {
						SortInDescendingFaces(players.hands[i]);
						cout << "Player " << i + 1 << ": " << endl;
						printHand(players.hands[i], suits, faces);
						cout << endl;
						displayStatusOfHand(players.hands[i]);
						cout << endl;
					}

					players.ranks = rankingHands(players.hands, n);

					cout << endl << endl;
					cout << "	Rank: " << endl;

					for (int i = 0; i < n; i++) {
						cout << "	Player " << i + 1 << ": " << players.ranks[i] << endl;
					}

					evaluateHands(players.scores, players.ranks, n);

					delete_n_hand(players.hands, n);
					delete[] players.ranks;
					system("pause");

					cout << "\n\n\n";
					cout << "Continue to play?... " << " 1: Yes. " << " 0: No. " << endl;

					do {
						cin >> user_input;

						if (atoi(user_input) == 0 || atoi(user_input) == 1)
							break;
						else {
							cout << "	Wrong Input!" << endl;
							system("pause");
						}
					} while (true);

					if (atoi(user_input) == 0)
						break;

				} while (true);

				system("cls");
				int* winner = new int[n];
				int winner_score = players.scores[0], k = 1;
				winner[0] = 0;
				for (int i = 1; i < n; i++) {
					if (players.scores[i] > winner_score)
					{
						winner_score = players.scores[i];
						winner[0] = i;
						k = 1;
					}
					else if (players.scores[i] == winner_score)
					{
						winner[k++] = i;
					}
				}

				cout << "\n\n\n";
				cout << "	***SCORES*** " << endl;
				for (int i = 0; i < n; i++)
					cout << "	Player " << i + 1 << ": " << players.scores[i] << "  " << endl;
		
				cout << "\n\n\n";
				cout << "	 " << endl;
				cout << "	 ______________" << endl;
				cout << "	| ***WINNER*** |" << endl;
				cout << "	|              |" << endl;

				for (int i = 0; i < k; i++) {
					if(winner[i] == 9)
						cout << "	|   Player: " << winner[i] + 1 << " |" << endl;
					else
						cout << "	|   Player: " << winner[i] + 1 << "  |" << endl;

				}
				cout << "	|              |" << endl;
				cout << "	|______________|" << endl;


				cout << "\n\n\n";
				system("pause");
				delete[] winner;
				delete[]players.scores;
				break;
			}
			default:
				cout << "	Wrong Input!" << endl;
				system("pause");
		}
	} while (atoi(user_input) != 0);


	return 0;
}


//MENU
void mainMenu()
{
	cout << "	 _____________" << endl;
	cout << "	|    POKER    |" << endl;
	cout << "	|1: 1 player. |" << endl;
	cout << "	|2: n player  |" << endl;
	cout << "	|             |" << endl;
	cout << "	|0: Exit.     |" << endl;
	cout << "	|_____________|" << endl;
	cout << "	Select: ";
}

void Menu_n_player()
{
	cout << "	 _____________" << endl;
	cout << "	|    POKER    |" << endl;
	cout << "	|  Type n of  |" << endl;
	cout << "	|   players   |" << endl;
	cout << "	|             |" << endl;
	cout << "	|             |" << endl;
	cout << "	|_____________|" << endl;
	cout << "	Select n: ";
}

void Menu_dealer_1()
{
	cout << "	 ______________" << endl;
	cout << "	|     POKER    |" << endl;
	cout << "	| Do you want  |" << endl;
	cout << "	| to play with |" << endl;
	cout << "	| the dealer?  |" << endl;
	cout << "	|              |" << endl;
	cout << "	|    1: Yes    |" << endl;
	cout << "	|    0: No     |" << endl;
	cout << "	|______________|" << endl;
	cout << "	Select: ";
}

void Menu_dealer_2()
{
	cout << "	 _________________" << endl;
	cout << "	|      POKER      |" << endl;
	cout << "	|  Choose Levels: |" << endl;
	cout << "	|                 |" << endl;
	cout << "	|    0: Easy.     |" << endl;
	cout << "	|    1: Medium.   |" << endl;
	cout << "	|    2: Hard.     |" << endl;
	cout << "	|_________________|" << endl << endl;
	cout << "	Easy(*): You and The Dealer are able to draw cards in 3 turns, The Dealer will do it randomly." << endl << endl;
	cout << "	Medium(**): You and The Dealer are able to draw cards in 3 turns, but The Dealer will do it wisely." << endl << endl;
	cout << "	Hard(***): The Dealer is able to draw cards in 3 turns, but you are not." << endl << endl;
	cout << "	Select: ";
}


//Common Function
void shuffleCards(int deck[SUITS][FACES])
{
	int k = 0;
	for (int i = 0; i < SUITS; i++)
		for (int j = 0; j < FACES; j++)
			deck[i][j] = k++;

	for (int i = 0; i < CARDS; i++) {
		int suit1 = rand() % (SUITS), face1 = rand() % (FACES), suit2 = rand() % (SUITS), face2 = rand() % (FACES);
		while (suit1 == suit2 && face1 == face2) {
			suit2 = rand() % (SUITS);
			face2 = rand() % (FACES);
		}

		swap(deck[suit1][face1], deck[suit2][face2]);
	}
}

void printCardsShuffling(int deck[SUITS][FACES], string suits[], string faces[])
{
	for (int k = 0; k < CARDS; k++) {
		int i, j;
		Search_deck(deck, k, i, j);

		cout << k + 1 << ": (" << suits[i] << ", " << faces[j] << ")" << endl;
	}
}

void printHand(int** hand, string suits[SUITS], string faces[FACES])
{
	for (int k = 0; k < CARDS_HAND; k++) {
		cout << "(" << suits[hand[k][0]] << ", " << faces[hand[k][1]] << ")" << " ";
	}
}

int** createHandTest(int deck[SUITS][FACES], int a[])
{
	int** hand = new int* [CARDS_HAND];
	for (int i = 0; i < CARDS_HAND; i++) {
		hand[i] = new int[2];
	}

	for (int i = 0; i < 10; i++) {
		hand[i / 2][i % 2] = a[i];
	}

	return hand;
}


void Search_deck(int deck[SUITS][FACES], int key, int& row_index, int& col_index)
{
	int i, j;
	for (i = 0; i < SUITS; i++) {
		for (j = 0; j < FACES; j++)
			if (deck[i][j] == key) {
				row_index = i;
				col_index = j;
				break;
			}

		j--;
		if (deck[i][j] == key)
			break;
	}
}

int isAceComparing(int ace1, int ace2)
{
	if (ace1 == 0 && ace2 != 0)
		return -1;
	else if (ace1 != 0 && ace2 == 0)
		return 1;
	else
		return 0;
}

void SortInDescendingFaces(int** arr)
{
	for (int i = 0; i < CARDS_HAND - 1; i++)
		for (int j = i + 1; j < CARDS_HAND; j++) {
			if (arr[i][1] < arr[j][1])
				swap(arr[i], arr[j]);
			if (arr[j][1] == 0 && arr[i][1] != 0)
				swap(arr[i], arr[j]);
		}
}

void displayStatusOfHand(int** hand)
{
	if (isStraightFlush(hand) != -1) {
		int index = isStraightFlush(hand);
		cout << "Straight Flush: " << suits[index % 10] << ", " << faces[(index - index % 10) / 10] << endl;
	}

	else if (isFourOfAKind(hand) != -1)
		cout << "Four Of A Kind: " << faces[isFourOfAKind(hand)] << endl;

	else if (isFullHouse(hand) != -1) {
		int index = isFullHouse(hand);
		if ((index - index % 10) / 10 <= 12)
			cout << "Full House: " << "Three of " << faces[(index - index % 10) / 10] << ", Two of " << faces[index % 10] << endl;
		else
			cout << "Full House: " << "Three of " << faces[(index - index % 100) / 100] << ", Two of " << faces[index % 100] << endl;
	}

	else if (isFlush(hand) != -1)
		cout << "Flush: " << suits[isFlush(hand)] << endl;

	else if (isStraight(hand) != -1)
		cout << "Straight: " << faces[isStraight(hand)] << endl;

	else if (isThreeOfAKind(hand) != -1)
		cout << "Three of A Kind: " << faces[isThreeOfAKind(hand)] << endl;

	else if (isTwoPairs(hand) != -1) {
		int index = isTwoPairs(hand);
		if ((index - index % 10) / 10 <= 12)
			cout << "Two Pairs: " << "Two of " << faces[(index - index % 10) / 10] << ", Two of " << faces[index % 10] << endl;
		else
			cout << "Two Pairs: " << "Two of " << faces[(index - index % 100) / 100] << ", Two of " << faces[index % 100] << endl;
	}

	else if (isPair(hand) != -1)
		cout << "Pair: " << faces[isPair(hand)] << endl;

	else if (getHighestCard(hand) != -1)
		cout << "Highest Card: " << faces[getHighestCard(hand)] << endl;

}


//1 Player
int** dealingForHand(int deck[SUITS][FACES])
{
	int** hand = new int* [CARDS_HAND];
	for (int i = 0; i < CARDS_HAND; i++) {
		hand[i] = new int[2];
	}

	int row = -1, col = 1;
	for (int k = 0; k < CARDS_HAND; k++) {
		int i, j;
		Search_deck(deck, ++current_card, i, j);
		hand[++row][--col] = i;
		hand[row][++col] = j;
	}

	return hand;
}


//Hand check
int isFourOfAKind(int** hand)
{
	if (hand[1][1] == hand[2][1] && hand[2][1] == hand[3][1]) 
		if (hand[0][1] == hand[1][1])
			return hand[0][1];

		else if (hand[4][1] == hand[3][1])
			return hand[4][1];
	

	return -1;
}

int isFullHouse(int** hand)
{
	if (hand[0][1] == hand[1][1] && hand[1][1] == hand[2][1] && hand[3][1] == hand[4][1])
		if (hand[3][1] < 10)
			return hand[0][1] * 10 + hand[3][1];
		else 
			return hand[0][1] * 100 + hand[3][1];

	else if (hand[0][1] == hand[1][1] && hand[2][1] == hand[3][1] && hand[3][1] == hand[4][1])
		if (hand[0][1] < 10)
			return hand[0][1] + hand[3][1] * 10;
		else
			return hand[0][1] + hand[3][1] * 100;

	return -1;
}

int isFlush(int** hand)
{
	if (hand[0][0] == hand[1][0] && hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0] && hand[3][0] == hand[4][0])
		return hand[0][0];

	return -1;
}

int isStraight(int** hand)
{
	if (hand[1][1] - 1 == hand[2][1] && hand[2][1] - 1 == hand[3][1] && hand[3][1] - 1 == hand[4][1])
		if (hand[0][1] - 1 == hand[1][1] || hand[0][1] + 1 == hand[4][1] || hand[0][1] + 12 == hand[1][1])
			return hand[0][1];

	return -1;
}

int isStraightFlush(int** hand)
{
	int suit_index = isFlush(hand);
	int face_index = isStraight(hand);
	if (suit_index != -1 && face_index != -1)
		return face_index*10 + suit_index;

	return -1;
}

int isThreeOfAKind(int** hand)
{
	if (hand[0][1] == hand[1][1] && hand[1][1] == hand[2][1])
		return hand[0][1];

	else if (hand[1][1] == hand[2][1] && hand[2][1] == hand[3][1])
		return hand[1][1];

	else if (hand[2][1] == hand[3][1] && hand[3][1] == hand[4][1])
		return hand[2][1];

	return -1;
}

int isTwoPairs(int** hand)
{
	if (hand[0][1] == hand[1][1])
	{
		if (hand[2][1] == hand[3][1])
			if (hand[2][1] < 10)
				return hand[0][1] * 10 + hand[2][1];
			else
				return hand[0][1] * 100 + hand[2][1];

		else if (hand[3][1] == hand[4][1])
			if (hand[3][1] < 10)
				return hand[0][1] * 10 + hand[3][1];
			else
				return hand[0][1] * 100 + hand[3][1];
	}
	else if (hand[1][1] == hand[2][1] && hand[3][1] == hand[4][1])
	{
		if (hand[3][1] < 10)
			return hand[1][1] * 10 + hand[3][1];
		else
			return hand[1][1] * 100 + hand[3][1];
	}
	return -1;
}

int isPair(int** hand)
{
	if (hand[0][1] == hand[1][1])
		return hand[0][1];

	else if (hand[1][1] == hand[2][1])
		return hand[1][1];

	else if (hand[2][1] == hand[3][1])
		return hand[2][1];

	else if (hand[3][1] == hand[4][1])
		return hand[3][1];

	return -1;
}

int getHighestCard(int** hand)
{
	return hand[0][1];
}


//n Players
int*** dealingFornHands(int deck[SUITS][FACES], int n)
{
	int*** player = new int **[n];
	for (int i = 0; i < n; i++) {
		player[i] = new int* [CARDS_HAND];
		for (int j = 0; j < CARDS_HAND; j++)
			player[i][j] = new int[2];
	}

	for (int z = 0; z < CARDS_HAND; z++) {
		for (int m = 0; m < n; m++) {
			int i, j;
			int row = -1 + z, col = 1;
			Search_deck(deck, ++current_card, i, j);
			player[m][++row][--col] = i;
			player[m][row][++col] = j;
		}
	}

	return player;
}

int getStatusOfHand(int** hand)
{
	if (isStraightFlush(hand) != -1)
		return 8;

	else if (isFourOfAKind(hand) != -1)
		return 7;

	else if (isFullHouse(hand) != -1)
		return 6;

	else if (isFlush(hand) != -1)
		return 5;

	else if (isStraight(hand) != -1)
		return 4;

	else if (isThreeOfAKind(hand) != -1)
		return 3;

	else if (isTwoPairs(hand) != -1) 
		return 2;

	else if (isPair(hand) != -1)
		return 1;

	else if (getHighestCard(hand) != -1)
		return 0;
}

int* rankingHands(int*** hands, int n)
{
	int* ranks = new int[n];
	int* status = new int[n];

	for (int i = 0; i < n; i++)
		status[i] = getStatusOfHand(hands[i]);

	for (int i = 1; i < n + 1; i++) {
		int highesthand = status[0];
		int highestplayer = 0;
		int j;
		int equalhand = -1;
		for (j = 1; j < n; j++) {

			if (status[j] == -1)
				continue;

			if (status[j] == highesthand)
			{
				int comparing_hands = EqualStatusOfHands(highesthand, hands[highestplayer], hands[j]);
				if (comparing_hands == 1)
				{
					highesthand = status[j];
					highestplayer = j;
				}
				else if (comparing_hands == 0)
				{
					equalhand = j;
				}
			}
			else if (status[j] > highesthand)
			{
				highesthand = status[j];
				highestplayer = j;
			}
		}

		ranks[highestplayer] = i;
		status[highestplayer] = -1;

		if (equalhand != -1) {
			ranks[equalhand] = i;
			status[equalhand] = -1;
			i++;
		}
	}

	delete[]status;
	return ranks;
}

void evaluateHands(int *scores, int *ranks, int n)
{
	for (int i = 0; i < n; i++)
		scores[i] += (n + 1 - ranks[i]) * 100;
}


int EqualStatusOfHands(int status, int** hand1, int** hand2)
{
	switch (status)
	{
	case 7:
	{
		int fourkind1 = isFourOfAKind(hand1);
		int fourkind2 = isFourOfAKind(hand2);

		if (isAceComparing(fourkind1, fourkind2) == -1)
			return -1;
		else if (isAceComparing(fourkind1, fourkind2) == 1)
			return 1;

		if (fourkind1 > fourkind2)
			return -1;
		else if (fourkind1 < fourkind2)
			return 1;
		else
		{
			int last_face1;
			int last_face2;

			if (hand1[0][1] != fourkind1)
				last_face1 = hand1[0][1];
			else
				last_face1 = hand1[4][1];

			if (hand2[0][1] != fourkind2)
				last_face2 = hand2[0][1];
			else
				last_face2 = hand2[4][1];


			if (isAceComparing(last_face1, last_face2) == -1)
				return -1;
			else if (isAceComparing(last_face1, last_face2) == 1)
				return 1;

			if (last_face1 > last_face2)
				return -1;
			else if (last_face1 < last_face2)
				return 1;
			else
				return 0;
		}

		break;
	}
	case 6:
	{
		int index1 = isFullHouse(hand1);
		int index2 = isFullHouse(hand2);
		int twokind1, threekind1, twokind2, threekind2;
		if ((index1 - index1 % 10) / 10 <= 12) {
			twokind1 = index1 % 10;
			threekind1 = (index1 - twokind1) / 10;

		}
		else {
			twokind1 = index1 % 100;
			threekind1 = (index1 - twokind1) / 100;
		}

		if ((index2 - index2 % 10) / 10 <= 12) {
			twokind2 = index2 % 10;
			threekind2 = (index2 - twokind2) / 10;

		}
		else {
			twokind2 = index2 % 100;
			threekind2 = (index2 - twokind2) / 100;
		}

		if (isAceComparing(threekind1, threekind2) == -1)
			return -1;
		else if (isAceComparing(threekind1, threekind2) == 1)
			return 1;

		if (threekind1 > threekind2)
			return -1;
		else if (threekind1 < threekind2)
			return 1;
		else
		{
			if (isAceComparing(twokind1, twokind2) == -1)
				return -1;
			else if (isAceComparing(twokind1, twokind2) == 1)
				return 1;

			if (twokind1 > twokind2)
				return -1;
			else if (twokind1 < twokind2)
				return 1;
			else
				return 0;
		}

		break;
	}
	case 3:
	{
		int threekind1 = isThreeOfAKind(hand1);
		int threekind2 = isThreeOfAKind(hand2);

		if (isAceComparing(threekind1, threekind2) == -1)
			return -1;
		else if (isAceComparing(threekind1, threekind2) == 1)
			return 1;


		if (threekind1 > threekind2)
			return -1;
		else if (threekind1 < threekind2)
			return 1;
		else
		{
			int sec_last_face1;
			int sec_last_face2;

			for (int i = 0; i < CARDS_HAND; i++)
			{
				if (hand1[i][1] != threekind1)
					sec_last_face1 = hand1[i][1];
				if (hand2[i][1] != threekind2)
					sec_last_face2 = hand2[i][1];
			}

			if (isAceComparing(sec_last_face1, sec_last_face2) == -1)
				return -1;
			else if (isAceComparing(sec_last_face1, sec_last_face2) == 1)
				return 1;

			if (sec_last_face1 > sec_last_face2)
				return -1;
			else if (sec_last_face1 < sec_last_face2)
				return 1;
			else
			{
				int last_face1;
				int last_face2;
				for (int i = 0; i < CARDS_HAND; i++)
				{
					if (hand1[i][1] != threekind1 && hand1[i][1] != sec_last_face1)
						last_face1 = hand1[i][1];
					if (hand2[i][1] != threekind2 && hand2[i][1] != sec_last_face2)
						last_face2 = hand2[i][1];
				}

				if (isAceComparing(last_face1, last_face2) == -1)
					return -1;
				else if (isAceComparing(last_face1, last_face2) == 1)
					return 1;

				if (last_face1 > last_face2)
					return -1;
				else if (last_face1 < last_face2)
					return 1;
				else
					return 0;
			}
		}

		break;
	}
	case 2:
	{
		int lowtwokind1 = isTwoPairs(hand1) % 10;
		int lowtwokind2 = isTwoPairs(hand2) % 10;
		int hightwokind1 = (isTwoPairs(hand1) - lowtwokind1) / 10;
		int hightwokind2 = (isTwoPairs(hand1) - lowtwokind1) / 10;

		if (isAceComparing(hightwokind1, hightwokind2) == -1)
			return -1;
		else if (isAceComparing(hightwokind1, hightwokind2) == 1)
			return 1;

		if (hightwokind1 > hightwokind2)
			return -1;
		else if (hightwokind1 < hightwokind2)
			return 1;
		else
		{
			if (isAceComparing(lowtwokind1, lowtwokind2) == -1)
				return -1;
			else if (isAceComparing(lowtwokind1, lowtwokind2) == 1)
				return 1;

			if (lowtwokind1 > lowtwokind2)
				return -1;
			else if (lowtwokind1 < lowtwokind2)
				return 1;
			else
			{
				int last_face1;
				int last_face2;

				for (int i = 0; i < CARDS_HAND; i++)
				{
					if (hand1[i][1] != hightwokind1 && hand1[i][1] != lowtwokind1)
						last_face1 = hand1[i][1];
					if (hand2[i][1] != hightwokind2 && hand2[i][1] != lowtwokind2)
						last_face2 = hand2[i][1];
				}

				if (isAceComparing(last_face1, last_face2) == -1)
					return -1;
				else if (isAceComparing(last_face1, last_face2) == 1)
					return 1;

				if (last_face1 > last_face2)
					return -1;
				else if (last_face1 < last_face2)
					return 1;
				else
					return 0;
			}
		}

		break;
	}
	case 1:
	{
		int pair1 = isPair(hand1);
		int pair2 = isPair(hand2);

		if (isAceComparing(pair1, pair2) == -1)
			return -1;
		else if (isAceComparing(pair1, pair2) == 1)
			return 1;

		if (pair1 > pair2)
			return -1;
		else if (pair1 < pair2)
			return 1;
		else
		{
			int i = 0, j = 0;
			int sec_high_card1 = hand1[i][1];
			int sec_high_card2 = hand2[j][1];

			while (sec_high_card1 == sec_high_card2 && i + 1 < 5 && j + 1 < 5) {
				sec_high_card1 = hand1[++i][1];
				sec_high_card2 = hand2[++j][1];

				while (sec_high_card1 == pair1 && i + 1 < 5)
					sec_high_card1 = hand1[++i][1];

				while (sec_high_card2 == pair2 && j + 1 < 5)
					sec_high_card2 = hand2[++j][1];
			}

			if (isAceComparing(sec_high_card1, sec_high_card2) == -1)
				return -1;
			else if (isAceComparing(sec_high_card1, sec_high_card2) == 1)
				return 1;

			if (sec_high_card1 > sec_high_card2)
				return -1;
			else if (sec_high_card1 < sec_high_card2)
				return 1;
			else
				return 0;

			break;
		}
	}
	default:
	{

		for (int i = 0; i < CARDS_HAND; i++)
		{
			int high_card1 = hand1[i][1];
			int high_card2 = hand2[i][1];

			if (isAceComparing(high_card1, high_card2) == -1)
				return -1;
			else if (isAceComparing(high_card1, high_card2) == 1)
				return 1;

			if (high_card1 > high_card2)
				return -1;
			else if (high_card1 < high_card2)
				return 1;
		}

		return 0;

		break;
	}
	}
}


//Dealer
void swap_card(int deck[SUITS][FACES], int** hand, int card_index)
{
	int i, j;
	Search_deck(deck, ++current_card, i, j);
	hand[card_index][0] = i;
	hand[card_index][1] = j;
}

bool dealerDrawsCardsRandomly(int deck[SUITS][FACES], int** dealer_hand)
{
	
	if (rand() % 2) {
		swap_card(deck, dealer_hand, rand() % 5);
		return true;
	}
	else
		return false;
}

bool dealerDrawsCardsWisely(int deck[SUITS][FACES], int** dealer_hand)
{
	int* new_card = new int[2];
	int** new_hand = new int* [CARDS_HAND];
	for (int i = 0; i < CARDS_HAND; i++)
		new_hand[i] = new int[2];

	int** highest_hand = new int* [CARDS_HAND];
	for (int i = 0; i < CARDS_HAND; i++)
		highest_hand[i] = new int[2];

	for (int i = 0; i < CARDS_HAND; i++) {
		highest_hand[i][0] = dealer_hand[i][0];
		highest_hand[i][1] = dealer_hand[i][1];
	}

	int i, j;
	Search_deck(deck, current_card + 1, i, j);
	new_card[0] = i;
	new_card[1] = j;

	for (int k = CARDS_HAND - 1; k > -1; k--)
	{
		for (int i = 0; i < CARDS_HAND; i++) {
			new_hand[i][0] = dealer_hand[i][0];
			new_hand[i][1] = dealer_hand[i][1];
		}

		new_hand[k][0] = new_card[0];
		new_hand[k][1] = new_card[1];
		SortInDescendingFaces(new_hand);

		/*cout << endl;
		printHand(new_hand, suits, faces);
		cout << endl;
		printHand(highest_hand, suits, faces);*/
		
		
		int status1 = getStatusOfHand(new_hand);
		int status2 = getStatusOfHand(highest_hand);

		if (status1 > status2) {
			for (int i = 0; i < CARDS_HAND; i++) {
				highest_hand[i][0] = new_hand[i][0];
				highest_hand[i][1] = new_hand[i][1];
			}
		}
		else if (status1 == status2)
		{
			if (EqualStatusOfHands(status1, highest_hand, new_hand) == 1) {
				for (int i = 0; i < CARDS_HAND; i++) {
					highest_hand[i][0] = new_hand[i][0];
					highest_hand[i][1] = new_hand[i][1];
				}
			}
		}

	}
	delete[] new_card;
	delete_hand(new_hand);


	int highest_status = getStatusOfHand(highest_hand);
	int dealer_status = getStatusOfHand(dealer_hand);

	if (highest_status > dealer_status) {
		for (int i = 0; i < CARDS_HAND; i++) {
			dealer_hand[i][0] = highest_hand[i][0];
			dealer_hand[i][1] = highest_hand[i][1];
		}
		current_card++;
		delete_hand(highest_hand);
		return true;
	}
	else if (highest_status == dealer_status)
	{
		if (EqualStatusOfHands(highest_status, dealer_hand, highest_hand) == 1) {
			for (int i = 0; i < CARDS_HAND; i++) {
				dealer_hand[i][0] = highest_hand[i][0];
				dealer_hand[i][1] = highest_hand[i][1];
			}
			current_card++;
			delete_hand(highest_hand);
			return true;
		}
	}


	delete_hand(highest_hand);
	return false;
}


//Delete pointers
void delete_hand(int** hand)
{
	for (int i = 0; i < CARDS_HAND; i++)
		delete[] hand[i];
	delete[] hand;
}

void delete_n_hand(int*** player, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < CARDS_HAND; j++)
			delete[] player[i][j];
		delete[] player[i];
	}

	delete[] player;
}