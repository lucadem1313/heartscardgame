/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
*																						*
*		Hearts Card Game, Updated Jan. 8, 2016											*
*																						*
*		Created by Luca Demian															*
*																						*
*																						*
*		Released under MIT License														*
*																						*
*		Copyright (c) 2016 Luca Demian													*
*																						*
*		Permission is hereby granted, free of charge, to any person 					*
*		obtaining a copy of this software and associated documentation					*
*		files (the "Software"), to deal in the Software without 						*
*		restriction, including without limitation the rights to use,					*
*		copy, modify, merge, publish, distribute, sublicense, and/or					*
*		sell copies of the Software, and to permit persons to whom the				 	*
*		Software is furnished to do so, subject to the following conditions:			*
*																						*
*																						*
*		The above copyright notice and this permission notice shall be				 	*
*		included in all copies or substantial portions of the Software.					*
*																						*
*																						*
*		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,					*
*		EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES					*
*		OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.		*
*		IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR				*
*		ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,		*
*		TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE		*
*		OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.									*
*																						*
*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/



#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <windows.h>
using namespace std;


//spades, hearts, diamonds, clubs

//introduction animation screen
void intro()
{
	system("cls");
	string line1 = ".------..------..------..------..------..------.";
	string line2 = "|H.--. ||E.--. ||A.--. ||R.--. ||T.--. ||S.--. |";
	string line3 = "| :/\\: || (\\/) || (\\/) || :(): || :/\\: || :/\\: |";
	string line4 = "| (__) || :\\/: || :\\/: || ()() || (__) || :\\/: |";
	string line5 = "| '--'H|| '--'E|| '--'A|| '--'R|| '--'T|| '--'S|";
	string line6 = "`------'`------'`------'`------'`------'`------'";
	//string line = "";


	cout << line1 << endl;
	Sleep(300);
	cout << line2 << endl;
	Sleep(300);
	cout << line3 << endl;
	Sleep(300);
	cout << line4 << endl;
	Sleep(300);
	cout << line5 << endl;
	Sleep(300);
	cout << line6;
	Sleep(300);
	cout << "\n\nBy the marvelous Luca Demian!\n\n\n\n\n\n(C) 2016 Luca Demian, http://www.lucademian.com ";
	Sleep(3000);
	
}

//outputs instructions, and asks for number of players
void startGame(int &numPlayers)
{
	string directions = "The object of the game:\nPlayers don't want to end up with tricks containing hearts or the queen of spades, but they do want to end up with the jack of diamonds.\n\nHow many can play:\nFour to seven players (four players is the best!)\n\nThe cards:\nYou need a standard deck of 52 cards. Each player is dealt the same number of cards. So, if you have 4 players, each receives 13 cards (13 x 4 = 52). In each suit, the cards are ranked from the Ace, with the highest value, on down: K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, and 2.\n\nHow to deal:\nAfter the cards have been dealt, each player chooses three cards to pass to an opponent. Players pick their cards after they've looked at them, and before they've received cards from their opponents. At the fourth deal, players keep their own cards.\n\nHow to play:\nThe player holding the 2 of clubs card starts first. Each player after the lead must follow suit if he can. If he can't, he may play any card he wants.\nA player wins a trick when he plays the highest card of the suit that is led. The winner of the trick leads the next.\n\nHow to keep score:\nAfter all the cards have been played, players count up their tricks. Each player receives a penalty point for each heart card they have. The player who ends up with the queen of spades gets 13 points. Here's a bonus: the player who ends up with the jack of diamonds gets to subtract 10 points from his score.\nThe player with least number of points when any player reaches 50 points wins.";
	system("cls");
	cout << "This is the game of hearts.\n\n" << directions;
	cout << endl << endl;
	cout << "How many players in this game? (4-7, 4 reccommended)\n";
	cin >> numPlayers;

	//checks to make sure there are a valid number of players
	while(numPlayers < 4 || numPlayers > 7)
	{
		cout << endl << "Invalid number. How many players in this game? (4-7)\n";
		cin >> numPlayers;
	}
}

//function takes in the vector of player hands, a player index, a suit, a card, and a boolean to change. Checks to make sure the card exists in the player's hand
void checkExists(vector<vector<vector<int>>> &playerHands, int i, int suit, int card, bool &passCard)
{
	//Checks through the playerHands vector to make sure the certain card is there
	for(int q = 0; q < playerHands[i][suit - 1].size(); q++)
	{
		if(playerHands[i][suit - 1][q] == card - 1)
		{
			passCard = true;
			break;
		}
		else
			passCard = false;
	}
}

//Fills deck with 4 suits, each with 13 cards in ascending order. Then it shuffles them
void fillDeck(vector<vector<int>> &deck)
{
	srand(time(NULL));

	//fills the deck vector with 4 suits
	for(int q = 0; q < deck.size(); q++)
	{
		vector<int> suit;
		deck[q] = suit;
	}

	//resizes each suit to be 13 cards
	for(int i = 0; i < deck.size(); i++)
	{
		deck[i].resize(13);
		//fills each suit with a card counting up
		for(int j = 0; j < deck[i].size(); j++)
		{
			deck[i][j] = j + 1;
		}

		random_shuffle(deck[i].begin(), deck[i].end());
	}
}

//Takes in the array of all player hands, and the full deck, and "deals" out the deck
void dealDeck(vector<vector<vector<int>>> &playerHands, vector<vector<int>> &deck)
{
	srand(time(NULL));
	int handSize = 52/(playerHands.size());
	int index, spadesSize, diamondSize, clubSize, heartSize;
	double random1, random2, random3, random4, randSum;

	//Adds 4 suit arrays for each player
	for(int i = 0; i < playerHands.size(); i++)
	{
		for(int j = 0; j < 4; j++)
		{
			vector<int> suit;
			playerHands[i].push_back(suit);
		}
	}

	int cycler = 0, card = 0;
	int dealableDeck = 52-(52%playerHands.size());
	bool flagUp = false;

	//keep dealing cards while there are cards left to deal
	while(dealableDeck > 0)
	{
		int suit = rand()%4;

		if(deck[suit][card] != -1)
			playerHands[cycler][suit].push_back(deck[suit][card]);
		else
			flagUp = true;

		deck[suit][card] = -1;
		cycler++;
		card++;
		dealableDeck--;
		if(flagUp)
		{
			cycler--;
			card--;
			dealableDeck++;
			flagUp = false;
		}
		if(cycler >= playerHands.size())
			cycler = 0;
		
		if(card >= 13)
			card = 0;
		
	}
	//Sorts each player's cards in ascending order
	for(int i = 0; i < playerHands.size(); i++)
	{
		for(int j = 0; j < playerHands[i].size(); j++)
		{
			sort(playerHands[i][j].begin(), playerHands[i][j].end());
		}
	}


		/*
		random1 = rand()%30;
		random2 = rand()%30;
		random3 = rand()%30;
		random4 = rand()%30;
		randSum = random1+random2+random3+random4;

		spadesSize = (random1/randSum)*handSize;
		diamondSize = (random2/randSum)*handSize;
		clubSize = (random3/randSum)*handSize;
		heartSize = (random4/randSum)*handSize;

		cout << endl<< handSize << "   " << randSum << "   " << random1 << "   " << random2 << "   " << random3 << "   " << random4;
		cout << "\n" << i << " Player - Spades size: " << spadesSize;
		cout << "\n" << i << " Player - diamonds size: " << diamondSize;
		cout << "\n" << i << " Player - club size: " << clubSize;
		cout << "\n" << i << " Player - heart size: " << heartSize;
		
		playerHands[i][0].resize(spadesSize);
		playerHands[i][1].resize(diamondSize);
		playerHands[i][2].resize(clubSize);
		playerHands[i][3].resize(heartSize);
		
		for(int j = 0; j < 4; j++)
		{
			

			for(int q = 0; q < playerHands[i][j].size(); q++)
			{
				index = rand()%(deck[j].size());
				while(deck[j][index] == -1)
				{
					index = rand()%(deck[j].size());
				}

				playerHands[i][j][q] = deck[j][index];
				deck[j][index] = -1;
			}
		}*/
}

//asks each player what card to pass, and passes to the next player after all cards have been chosen
void passCards(vector<vector<vector<int>>> &playerHands, int turnNum)
{
	bool passCards = true;
	vector<vector<vector<int>>> cardsToPass(playerHands.size());

	//Adds 4 suits into the cardsToPass vector for each player
	for(int i = 0; i < playerHands.size(); i++)
	{
		for(int j = 0; j < 4; j++)
		{
			vector<int> suit;
			cardsToPass[i].push_back(suit);
		}
	}

	string playerPassTo;

	switch(turnNum%4)
	{
		case 1:
			playerPassTo = "on your right";
			break;
		case 2:
			playerPassTo = "on your left";
			break;
		case 3:
			playerPassTo = "across from you";
			break;
		case 0:
			passCards = false;
			break;
	}

	if(passCards)
	{
		//Runs the pass card code for each player
		for(int i = 0; i < playerHands.size(); i++)
		{
			system("cls");
			cout << "Hello Player " << i + 1 << ". Please choose 3 cards to pass to the player " << playerPassTo << ". Your cards are below:\n\n";

			//Outputs the titles for each suit
			for(int j = 0; j < playerHands[i].size(); j++)
			{
				switch(j)
				{
					case 0:
						cout << "\n\06: ";
						break;
					case 1:
						cout << "\n\03: ";
						break;
					case 2:
						cout << "\n\04: ";
						break;
					case 3:
						cout << "\n\05: ";
						break;
				}

				//Outputs each card from each suit. outputs a letter if it is a face card
				for(int q = 0; q < playerHands[i][j].size(); q++)
				{
					switch(playerHands[i][j][q] + 1)
					{
						case 11:
							cout << " J";
							break;
						case 12:
							cout << " Q";
							break;
						case 13:
							cout << " K";
							break;
						case 14:
							cout << " A";
							break;
						default:
							cout << " " << playerHands[i][j][q] + 1;
							break;
					}
				}
			}

			int card1suit, card2suit, card3suit, card1num, card2num, card3num;
			bool passCard1, passCard2, passCard3;

			cout << "\n\nPlease type in your three cards to pass:";
			cout << "\n\n\nSuit of card one (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
			cin >> card1suit;

			//makes sure the suit is valid
			while(card1suit > 4 || card1suit < 1)
			{
				cout << "\n\nINVALID. Suit of card one (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> card1suit;
			}
			cout << "\n\nNumber of card one (J = 11, Q = 12, K = 13, A = 14): ";
			cin >> card1num;

			//make sure the card number is valid
			while(card1num > 14 || card1num < 2)
			{
				cout << "\n\nINVALID. Number of card one (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> card1num;
			}
			cout << "\n\nSuit of card two: ";
			cin >> card2suit;

			//makes sure the suit is valid
			while(card2suit > 4 || card2suit < 1)
			{
				cout << "\n\nINVALID. Suit of card two (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> card2suit;
			}
			cout << "\n\nNumber of card two (J = 11, Q = 12, K = 13, A = 14): ";
			cin >> card2num;

			//make sure the card number is valid
			while(card2num > 14 || card2num < 2)
			{
				cout << "\n\nINVALID. Number of card two (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> card2num;
			}
			cout << "\n\nSuit of card three: ";
			cin >> card3suit;

			//makes sure the suit is valid
			while(card3suit > 4 || card3suit < 1)
			{
				cout << "\n\nINVALID. Suit of card three (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> card3suit;
			}
			cout << "\n\nNumber of card three (J = 11, Q = 12, K = 13, A = 14): ";
			cin >> card3num;

			//make sure the card number is valid
			while(card3num > 14 || card3num < 2)
			{
				cout << "\n\nINVALID. Number of card three (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> card3num;
			}


		/*	for(int q = 0; q < playerHands[i][card1suit - 1].size(); q++)
			{
				if(playerHands[i][card1suit - 1][q] == card1num - 1)
				{
					passCard1 = true;
					break;
				}

				else
					passCard1 = false;
			}*/
			checkExists(playerHands, i, card1suit, card1num, passCard1);
			checkExists(playerHands, i, card2suit, card2num, passCard2);
			checkExists(playerHands, i, card3suit, card3num, passCard3);

			//while the card is not in the player's suit, ask them to input the card
			while(!passCard1)
			{
				cout << "\n\nYour first card is not in your hand. Suit of card one (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> card1suit;

				//make sure the card suit is valid
				while(card1suit > 4 || card1suit < 1)
				{
					cout << "\n\nINVALID. Suit of card one (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
					cin >> card1suit;
				}
				cout << "\n\nNumber of card one (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> card1num;

				//make sure the card number is valid
				while(card1num > 14 || card1num < 2)
				{
					cout << "\n\nINVALID. Number of card one (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> card1num;
				}


				checkExists(playerHands, i, card1suit, card1num, passCard1);

			}

			//while the card is not in the player's suit, ask them to input the card
			while(!passCard2)
			{
				cout << "\n\nYour second card is not in your hand. Suit of card two (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> card2suit;

				//make sure the card suit is valid
				while(card2suit > 4 || card2suit < 1)
				{
					cout << "\n\nINVALID. Suit of card two (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
					cin >> card2suit;
				}
				cout << "\n\nNumber of card two (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> card2num;

				//make sure the card number is valid
				while(card2num > 14 || card2num < 2)
				{
					cout << "\n\nINVALID. Number of card two (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> card2num;
				}


				checkExists(playerHands, i, card2suit, card2num, passCard2);
			}

			//while the card is not in the player's suit, ask them to input the card
			while(!passCard3)
			{
				cout << "\n\nYour third card is not in your hand. Suit of card three (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> card3suit;

				//make sure the card suit is valid
				while(card3suit > 4 || card3suit < 1)
				{
					cout << "\n\nINVALID. Suit of card three (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
					cin >> card3suit;
				}
				cout << "\n\nNumber of card three (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> card3num;

				//make sure the card number is valid
				while(card3num > 14 || card3num < 2)
				{
					cout << "\n\nINVALID. Number of card three (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> card3num;
				}


				checkExists(playerHands, i, card3suit, card3num, passCard3);
			}

			if(i != playerHands.size() - 1)
			{
				if(passCard1) 
					cardsToPass[i][card1suit - 1].push_back(card1num - 1);
				if(passCard2)
					cardsToPass[i][card2suit - 1].push_back(card2num - 1);
				if(passCard3)
					cardsToPass[i][card3suit - 1].push_back(card3num - 1);
			}


		}
		//cycles through all the cards in the cardsToPass vector, and transfers them to the player's hand
		for(int i = 0; i < cardsToPass.size(); i++)
		{
			for(int j = 0; j < cardsToPass[i].size(); j++)
			{
				for(int q = 0; q < cardsToPass[i][j].size(); q++)
				{
					if(i != playerHands.size() - 1)
					{
						playerHands[i+1][j].push_back(cardsToPass[i][j][q]);
						playerHands[i][j].erase(std::remove(playerHands[i][j].begin(), playerHands[i][j].end(), cardsToPass[i][j][q]), playerHands[i][j].end());
					}
					else
					{
						playerHands[0][j].push_back(cardsToPass[i][j][q]);
						playerHands[0][j].erase(std::remove(playerHands[0][j].begin(), playerHands[0][j].end(), cardsToPass[i][j][q]), playerHands[0][j].end());
					}
				}
			}
		}
	}
}

//the trick code
void trick(vector<vector<vector<int>>> &playerHands, vector<vector<vector<int>>> &playerDiscard, int turnNum, int &playerStart, int &trickSuit)
{
	system("cls");
	vector<vector<int>> trickCards;

	//Puts 4 suit vectors into the trickCards vector
	for(int i = 0; i < 4; i++)
	{
		vector<int> suit;
		trickCards.push_back(suit);
	}
	
	//int trickSuit;
	string trickSuitText;
	int cardIn;
	int topCard = 0;
	int trickWinner;
	int suitIn;
	switch(trickSuit)
	{
		case 0:
			trickSuitText = "spades";
			break;
		case 1:
			trickSuitText = "hearts";
			break;
		case 2:
			trickSuitText = "diamonds";
			break;
		case 3:
			trickSuitText = "clubs";
			break;
	}

	int i = playerStart;
	bool passCard;
	for(int w = 0; w < playerHands.size(); w++)
	{
		system("cls");

		if(i == playerStart)
		{
			if(turnNum == 1)
			{
				cout << "Hello player " << i + 1 << ". You must play the 2 of clubs, but just as a heads up, here are your cards: ";

				//Outputs all card suits and all cards in those suits for the player's hand
				for(int j = 0; j < playerHands[i].size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}
					
					//Outputs all cards for each suit
					for(int q = 0; q < playerHands[i][j].size(); q++)
					{
						switch(playerHands[i][j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << playerHands[i][j][q] + 1;
								break;
						}
					}
				}
				cardIn = 2;
				trickSuit = 3;
				passCard = true;
				cout << endl << endl;
				trickCards[trickSuit].push_back(cardIn - 1);
				playerHands[i][trickSuit].erase(std::remove(playerHands[i][trickSuit].begin(), playerHands[i][trickSuit].end(), cardIn - 1), playerHands[i][trickSuit].end());
				system("pause");
			}
			else
			{
				cout << "Hello Player " << i + 1 << ". Please choose a suit to play for this trick.";
				cout << "\n\nYour cards:";

				//Outputs all suits, and all cards in each suit for the player's cards
				for(int j = 0; j < playerHands[i].size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}

					//Outputs all cards for each suit
					for(int q = 0; q < playerHands[i][j].size(); q++)
					{
						switch(playerHands[i][j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << playerHands[i][j][q] + 1;
								break;
						}
					}
				}
				cout << "\n\nThe cards in the middle:";

				//Outputs all suits and all cards in each suit for the cards in the middle
				for(int j = 0; j < trickCards.size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}

					//Outputs all cards for each suit
					for(int q = 0; q < trickCards[j].size(); q++)
					{
						switch(trickCards[j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << trickCards[j][q] + 1;
								break;
						}
					}
				}
				int trickInTemp = 0;
				cout << "\n\nPlease choose which suit to play for this trick (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> trickInTemp;
				while(trickInTemp > 4 || trickInTemp < 1)
				{
					cout << "\n\nINVALID. Please choose which suit to play for this trick (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
					cin >> trickInTemp;
				}
				trickSuit = trickInTemp - 1;
				switch(trickSuit)
				{
					case 0:
						trickSuitText = "spades";
						break;
					case 1:
						trickSuitText = "hearts";
						break;
					case 2:
						trickSuitText = "diamonds";
						break;
					case 3:
						trickSuitText = "clubs";
						break;
				}
				cout << "\n\nPlease choose which " << trickSuitText << " card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> cardIn;

				//Makes sure the user's card input is valid and makes them continue to enter until it is
				while(cardIn > 14 || cardIn < 2)
				{
					cout << "INVALID. Please choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> cardIn;
				}
				checkExists(playerHands, i, trickSuit + 1, cardIn, passCard);
				

				//Runs while the player does not have the inputted card, and makes them re-enter it
				while(!passCard)
				{
					cout << "\n\nThat card is not in your hand. Please choose which " << trickSuitText << " card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> cardIn;

					//Makes sure the user's card input is valid and makes them continue to enter until it is
					while(cardIn > 14 || cardIn < 2)
					{
						cout << "INVALID. Please choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
						cin >> cardIn;
					}
					checkExists(playerHands, i, trickSuit + 1, cardIn, passCard);
				}

				if(cardIn > topCard)
				{
					topCard = cardIn;
					trickWinner = i;
				}
				if(passCard)
				{
					trickCards[trickSuit].push_back(cardIn - 1);
					playerHands[i][trickSuit].erase(std::remove(playerHands[i][trickSuit].begin(), playerHands[i][trickSuit].end(), cardIn - 1), playerHands[i][trickSuit].end());
				}
			}
		}
		else
		{
			if(playerHands[i][trickSuit].size() > 0)
			{
				

				cout << "Hello Player " << i + 1 << ". Please choose a card of the suit " << trickSuitText << " to put in the middle.";

				cout << "\n\nYour cards:";

				//Outputs all suits, and all cards in each suit for the player's cards
				for(int j = 0; j < playerHands[i].size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}

					//Outputs all cards for each suit
					for(int q = 0; q < playerHands[i][j].size(); q++)
					{
						switch(playerHands[i][j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << playerHands[i][j][q] + 1;
								break;
						}
					}
				}
				cout << "\n\nThe cards in the middle:";

				//Outputs all suits and all cards in each suit for the cards in the middle
				for(int j = 0; j < trickCards.size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}

					//Outputs all cards for each suit
					for(int q = 0; q < trickCards[j].size(); q++)
					{
						switch(trickCards[j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << trickCards[j][q] + 1;
								break;
						}
					}
				}

				cout << "\n\nPlease choose which " << trickSuitText << " card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> cardIn;

				//Makes sure the user's card input is valid and makes them continue to enter until it is
				while(cardIn > 14 || cardIn < 2)
				{
					cout << "INVALID. Please choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> cardIn;
				}
				checkExists(playerHands, i, trickSuit + 1, cardIn, passCard);
				

				//Runs while the player does not have the inputted card, and makes them re-enter it
				while(!passCard)
				{
					cout << "\n\nThat card is not in your hand. Please choose which " << trickSuitText << " card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> cardIn;

					//Makes sure the user's card input is valid and makes them continue to enter until it is
					while(cardIn > 14 || cardIn < 2)
					{
						cout << "INVALID. Please choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
						cin >> cardIn;
					}
					checkExists(playerHands, i, trickSuit + 1, cardIn, passCard);
				}

				if(cardIn > topCard)
				{
					topCard = cardIn;
					trickWinner = i;
				}
				if(passCard)
				{
					trickCards[trickSuit].push_back(cardIn - 1);
					playerHands[i][trickSuit].erase(std::remove(playerHands[i][trickSuit].begin(), playerHands[i][trickSuit].end(), cardIn - 1), playerHands[i][trickSuit].end());
				}
			}
			else
			{
				cout << "Hello Player " << i + 1 << ". You don't have any " << trickSuitText << " to put in the middle. Please choose a suit to play instead.";
				cout << "\n\nYour cards:";

				//Outputs player's cards seperated by suit
				for(int j = 0; j < playerHands[i].size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}

					//Outputs all cards for the suit
					for(int q = 0; q < playerHands[i][j].size(); q++)
					{
						switch(playerHands[i][j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << playerHands[i][j][q] + 1;
								break;
						}

					}
				}
				cout << "\n\nThe cards in the middle:";

				//Outputs all cards in the middle, seperated by suit
				for(int j = 0; j < trickCards.size(); j++)
				{
					switch(j)
					{
						case 0:
							cout << "\n\06: ";
							break;
						case 1:
							cout << "\n\03: ";
							break;
						case 2:
							cout << "\n\04: ";
							break;
						case 3:
							cout << "\n\05: ";
							break;
					}

					//Outputs all cards for each suit
					for(int q = 0; q < trickCards[j].size(); q++)
					{
						switch(trickCards[j][q] + 1)
						{
							case 11:
								cout << " J";
								break;
							case 12:
								cout << " Q";
								break;
							case 13:
								cout << " K";
								break;
							case 14:
								cout << " A";
								break;
							default:
								cout << " " << trickCards[j][q] + 1;
								break;
						}
					}
				}
				cout << "\n\nYou do not have any " << trickSuitText << ". Please enter which suit to play instead (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
				cin >> suitIn;

				//Makes the user re-enter the suit while it does not have cards or is to big/small
				while(suitIn > 4 || suitIn < 1 || playerHands[i][suitIn - 1].size() < 1)
				{
					cout << "\n\nINVALID. Suit of card one (spades = 1, hearts = 2, diamonds = 3, clubs = 4): ";
					cin >> suitIn;
				}
				cout << "\n\nPlease choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
				cin >> cardIn;

				//Makes the user re-enter the card while it is too big/small
				while(cardIn > 14 || cardIn < 2)
				{
					cout << "INVALID. Please choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> cardIn;
				}

				checkExists(playerHands, i, suitIn, cardIn, passCard);

				//While the inputted card is not in the player's hand, they must re-enter it
				while(!passCard)
				{
					cout << "\n\nThat card is not in your hand. Please choose which " << trickSuitText << " card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
					cin >> cardIn;

					//The user must re-enter the card while it is too big/small
					while(cardIn > 14 || cardIn < 2)
					{
						cout << "INVALID. Please choose which card to put in the middle (J = 11, Q = 12, K = 13, A = 14): ";
						cin >> cardIn;
					}
					checkExists(playerHands, i, suitIn, cardIn, passCard);
				}

				if(passCard)
				{
					trickCards[suitIn - 1].push_back(cardIn - 1);
					playerHands[i][suitIn - 1].erase(std::remove(playerHands[i][suitIn - 1].begin(), playerHands[i][suitIn - 1].end(), cardIn - 1), playerHands[i][suitIn - 1].end());
				}
			}
		}

		i++;

		if(i > playerHands.size() - 1)
			i = 0;

	}

	//These for loops transfers all the cards from the trick into the winner's "discard pile"
	for(int i = 0; i < trickCards.size(); i++)
	{
		for(int j = 0; j < trickCards[i].size(); j++)
		{
			playerDiscard[trickWinner][i].push_back(trickCards[i][j]);
		}
	}
	system("cls");
	cout << "The trick is over, and player " << trickWinner + 1 << " won. Get ready for the next one!\n\n";
	//system("pause");
	Sleep(1000 * 2);
	cout << "Game is broken. Please restart. Apologies for the inconvenience";
	playerStart = trickWinner;
	
}

//the main
int main(){
	system("color F0");
	intro();
	int scoreLimitReacher;
	int numPlayers;
	startGame(numPlayers);
	bool scoreBelowLimit = true;
	
	vector<int> scores(numPlayers);
	
	//this keeps repeating the game cycle while all players scores are below the limit
	while(scoreBelowLimit)
	{
		bool handsAboveZero = true;
		vector<vector<int>> fullDeck(4);
		fillDeck(fullDeck);

		vector<vector<vector<int>>> playerHands(numPlayers);
		vector<vector<vector<int>>> playerDiscard(numPlayers);
		dealDeck(playerHands, fullDeck);

		//These two for loops create the vectors for each suit of cards in each players discard
		for(int i = 0; i < playerDiscard.size(); i++)
		{
			for(int j = 0; j < 4; j++)
			{
				vector<int> suit;
				playerDiscard[i].push_back(suit);
			}
		}


		int turnNum = 1;
	
		int playerStart = 0;
		int trickStart = 3;
		int turnCounter = 1;

		passCards(playerHands, turnNum);

		//These for loops look through each player's hand and decide which player starts the trick based on who has the 2C
		for(int i = 0; i < playerHands.size(); i++)
		{
			for(int j = 0; j < playerHands[i].size(); j++)
			{
				for(int q = 0; q < playerHands[i][j].size(); q++)
				{
					if(playerHands[i][j][q] == 1 && j == 3)
						playerStart = i;
				}
			}
		}

		//This calculates the scores for each player
		for(int i = 0; i < playerDiscard.size(); i++)
		{
			for(int j = 0; j < playerDiscard[i].size(); j++)
			{
				for(int q = 0; q < playerDiscard[i][j].size(); q++)
				{
					if(playerDiscard[i][j][q] == 11 && j == 0)
						scores[i] += 13;
					if(playerDiscard[i][j][q] == 10 && j == 2)
						scores[i] -= 10;
				}
				scores[i] += playerDiscard[i][j].size();
			}
		}

		//This trips the scoreBelowLimit boolean if the score is no longer below the limit. For loop cycles through each player's score
		for(int i = 0; i < scores.size(); i++)
		{
			if(scores[i] >= 50)
			{
				scoreLimitReacher = i;
				scoreBelowLimit = false;
			}
		}

		//This runs while all player's hands have more than 0 cards
		while(handsAboveZero)
		{
			//this for loop checks through each player's hand to make sure they have more than 0 cards
			for(int i = 0; i < playerHands.size(); i++)
			{
				if(playerHands[i][0].size() < 1 && playerHands[i][1].size() < 1 && playerHands[i][2].size() < 1 && playerHands[i][3].size() < 1)
					handsAboveZero = false;
			
			}

			trick(playerHands, playerDiscard, turnNum, playerStart, trickStart);
			turnNum += 1;
		}
	}

	cout << "Thank you for playing! The scores are as follows: \n";

	//Cycles through and outputs each player's score
	for(int i = 0; i < scores.size(); i++)
	{
		cout << "\n\n\tPlayer " << i + 1 << ": " << scores[i];
	}

	return(0);
}
