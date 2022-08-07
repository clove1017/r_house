// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Table_Settings {
public:
    int num_players;
    int small_blind;
    int big_blind;
public:
    Table_Settings() {
        //initialize the table 
        cout << "Set the number of players (min 2, max 8): ";
        cin >> num_players;
        while (num_players > 8 or num_players < 2){
            cout << "Set the number of players (min 2, max 8): ";
            cin >> num_players;
        }
        cout << "Set the small blind (must be greater than 0): ";
        cin >> small_blind;
        while (small_blind < 0) {
            cout << "Set the small blind (must be greater than 0): ";
            cin >> small_blind;
        }
        cout << "Set the big blind (must be greater than " <<small_blind << "): ";
        cin >> big_blind;
        while (big_blind < small_blind) {
            cout << "Set the big blind (must be greater than " << small_blind << "): ";
            cin >> big_blind;
        }

    }
};

class CardDeck {
public:
    string deck[52];
    int card_num;
public:
    void shuffle_deck() {
        srand(time(NULL));
        int new_card_index;
        string swap_card;
        for (int i = 0; i < 52; i++) {
            new_card_index = rand() % 52;
            swap_card = deck[new_card_index];
            deck[new_card_index] = deck[i];
            deck[i] = swap_card;
        }
    }
public:
    CardDeck() {
        //create the cards in the deck
        string cards[13] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
        string suits[4] = { "c","s","h","d" };
        string new_card;
        int deck_ind = 0;
        for (int i = 0; i < 13; i++) {
            for (int x = 0; x < 4; x++) {
                new_card = string() + suits[x] + cards[i];
                deck[deck_ind] = new_card;
                deck_ind = deck_ind + 1;
            }
        }
        //first shuffle
        shuffle_deck();
        //set the card number
        card_num = 0;

    }
public:
    string deal_card() {
        card_num = card_num + 1;
        return deck[card_num - 1];
    }
};

class Judge {
    string hands_in_play;
    string cards_on_table;
    public Judge(string player_hands, string table_cards) {

    }

};

int main()
{

    CardDeck deck = CardDeck();
    //for (int i = 0; i < 52; i++) {
      //  printf("%s\n", new_deck.deck[i].c_str());
    //}
    //string card1 = new_deck.deal_card();
    //cout << card1;
    //string card2 = new_deck.deal_card();
    //cout << card2;


    //prepare table
    Table_Settings table = Table_Settings();
    string player_hands[8][2];

    //deal cards to players
    for (int x = 0; x < 2; x++) {
        for (int i = 0; i < table.num_players; i++) {
            player_hands[i][x] = deck.deal_card();
        }
    }
    for (int i = 0; i < table.num_players; i++) {
        cout << player_hands[i][0] + string(" ")+ player_hands[i][1] + "\n";
    }

    //deal table cards
    string table_cards[5];
    getchar();
    for (int i = 0; i < 5; i++) {
        if (i < 3) {
            table_cards[i] = deck.deal_card();
            cout << table_cards[i] + "\n";
        }
        else {
            getchar();
            table_cards[i] = deck.deal_card();
            cout << table_cards[i] + "\n";
        }
    }

    //judge the winner 

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
