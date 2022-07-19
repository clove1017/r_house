// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

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
        int deck_ind=0;
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
    string deal_card(){
        card_num = card_num + 1;
        return deck[card_num-1];
    }
};
int main()
{

    CardDeck new_deck = CardDeck();
    for (int i = 0; i < 52; i++) {
        printf("%s\n", new_deck.deck[i].c_str());
    }
    string card1 = new_deck.deal_card();
    cout << card1;
    string card2 = new_deck.deal_card();
    cout << card2;

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
