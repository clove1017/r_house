// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <cstdio>
#include <string.h>
using namespace std;

class Table_Settings {
public:
    int num_players;
    int small_blind;
    int big_blind;
private:
    char card_suit(string card) {
        char suit = card[0];
        return suit;
    }
    string card_val(string card) {
        string val;
        val = card;
        val.erase(0, 1); //remove first char
        if (val == "A") {
            val = "14";
        }
        else if (val == "K") {
            val= "13";
        }
        else if (val == "Q") {
            val = "12";
        }
        else if (val == "J") {
            val = "11";
        }
        return val;
    }
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
public: 
    int* Judge(string player_hand[2], string table_cards[5]) {
        int hand_value[3];
        //int highest_hand[4] = { -1, -1, -1, -1 };
        string card_values[7];
        char card_suits[7];
        for (int i = 0; i < 5; i++) {
            card_suits[i] = card_suit(table_cards[i]);
            card_values[i] = card_val(table_cards[i]);
        }   
        int spades;
        int clubs;
        int hearts;
        int diamonds;
        int suit_count;
        card_suits[5] = card_suit(player_hand[0]);
        card_suits[6] = card_suit(player_hand[1]);
        card_values[5] = card_val(player_hand[0]);
        card_values[6] = card_val(player_hand[1]);
        //suits and values unpacked, begin hand evaluation
        // 
        //evaluate number of each suit:
        suit_count=spades = clubs = hearts = diamonds = 0;
        char flush_suit = 'x';
        for (int x = 0; x < 7; x++) {
            if (card_suits[x] == 'c') {
                clubs++;
                if (clubs >= 5) {
                    flush_suit = 'c';
                    suit_count = clubs;
                }
            }
            else if (card_suits[x] == 's') {
                spades++;
                if (spades >= 5) {
                    flush_suit = 's';
                    suit_count = spades;
                }
            }
            else if (card_suits[x] == 'h') {
                hearts++;
                if (hearts >= 5) {
                    flush_suit = 'h';
                    suit_count = hearts;
                }
            }
            else if (card_suits[x] == 'd') {
                diamonds++;
                if (diamonds >= 5) {
                    flush_suit = 'd';
                    suit_count = diamonds;
                }
            }
        }
        if (flush_suit != 'x') {
            //get high values of flush
            int flush_card_vals[7] = {0, 0, 0, 0, 0, 0, 0};
            for (int m = 0; m < 7; m++) {
                if (card_suits[m] == flush_suit) {
                    int z = -1;
                    while ((stoi(card_values[m])) > flush_card_vals[z+1] and z<6) {
                        z++;
                    }
                    for (int n = 1; n < z + 1; n++) {
                        flush_card_vals[n - 1] = flush_card_vals[n];
                    }
                    flush_card_vals[z] = stoi(card_values[m]);
                }
            }
            bool one = false;
            if (flush_card_vals[6] == 14) {
                bool one = true;
            }

            //check for straight flush
            int counter;
            for (int k = 0; k < 3; k++) {
                if (flush_card_vals[k] != 0) {
                    counter = 1;
                    if (one and flush_card_vals[k] == 2) {
                        counter++;
                    }
                    for (int j = k; j < 6; j++) {
                        if (flush_card_vals[j] + 1 == flush_card_vals[j + 1]) {
                            counter++;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            if (counter >= 5){
                if (flush_card_vals[6] == 14 and flush_card_vals[5] == 13 and flush_card_vals[4] == 12) {
                    hand_value[0] = 9;
                }
                else {
                    hand_value[0] = 8;
                }
            }
            else {
                hand_value[0] = 5;
            }
        }
        //end flush/straight_flush/royal_flush check

        //check for matching values
        int all_card_vals[14];
        memset(all_card_vals, 0, 14);
        for (int x = 0; x < 7; x++) {
            all_card_vals[stoi(card_values[x])]++;
        }
        int pair_vals[2] = { 0,0 };
        int three_of_kind_val = 0;
        int four_of_kind_val = 0;
        for (int i = 0; i < 14; i++) {
            if (all_card_vals[i] != 0) {
                if (all_card_vals[i] == 4){
                    hand_value[0] = 7;
                    four_of_kind_val = i;
                    break;
                }
                else if (all_card_vals[i] == 3) {
                    if (three_of_kind_val==0) {
                        three_of_kind_val = i;
                    }
                    else {
                        pair_vals[1] = pair_vals[0];
                        pair_vals[0] = three_of_kind_val;
                        three_of_kind_val = i;
                    }
                }
                else if (all_card_vals[i] == 2) {
                    pair_vals[1] = pair_vals[0];
                    pair_vals[0] = i;
                }
            }

        }
        if (three_of_kind_val != 0) {
            if (pair_vals[0] != 0) {
                hand_value[0] = 6;
            }
            else {
                hand_value[0] = 3;
            }
        }
        if (pair_vals[0] != 0) {
            if (pair_vals[1] != 0) {
                hand_value[0] = 2;
            }
            else {
                hand_value[0] = 1;
            }
        }
        //finish matching check

        //begin straight check (assume card_values have been ordered)
        int counter;
        bool one = false;
        if (card_values[6] == 14) {
            bool one = true;
        }
        for (int k = 0; k < 3; k++) {
            counter = 1;
            if (one and card_values[k] == 2) {
                counter++;
            }
            for (int j = k; j < 6; j++) {
                if (card_values[j] + 1 == card_values[j + 1]) {
                    counter++;
                }
                else {
                    break;
                }
            }
        }
        if (counter >= 5) {
            hand_value[0] = 4;
        }

        //remember to evaluate hand_value[1] and [2]
        return hand_value;
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
    string first_hand[2];
    first_hand[0] = player_hands[0][0];
    first_hand[1] = player_hands[0][1];
    table.Judge(first_hand, table_cards);
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
