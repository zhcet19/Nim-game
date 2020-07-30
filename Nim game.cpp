#include<bits/stdc++.h>
using namespace std;
#define PLAYER1 1
#define PLAYER2 2

/* A Structure to hold the two parameters of a move

A move has two parameters-
1) pile_index = The index of pile from which stone is
                    going to be removed
2) stones_removed = Number of stones removed from the
                        pile indexed = pile_index */
struct move
{
    int pile_index;
    int stones_removed;
};
void declareWinner(int Turn)
{
    if (Turn == PLAYER1)
        cout <<"\nplayer2 won\n\n";
    else
        cout <<"\nplayer1 won\n\n";
    return;
}
void showPiles (int piles[], int n)
{
    int i;
    cout <<"Current Game Status -> ";
    for (i=0; i<n; i++)
        cout << " " << piles[i];
    cout <<"\n";
    return;
}
 bool gameOver(int piles[], int n)
{
    int i;
    for (i=0; i<n; i++)
        if (piles[i]!=0)
            return (false);

    return (true);
}
int calculateNimSum(int piles[], int n)
{
    int i, nimsum = piles[0];
    for (i=1; i<n; i++)
        nimsum = nimsum ^ piles[i];
    return(nimsum);
}

void makeMove(int piles[], int n, struct move * moves)
  {   int i;
      int  nim_sum = calculateNimSum(piles, n);

       if (nim_sum != 0)
    {
        for (i=0; i<n; i++)
        {
            // removing of sticks from pile is allowed
             if ((piles[i] ^ nim_sum) < piles[i])
            {
                 (*moves).pile_index = i;
                 (*moves).stones_removed = piles[i]-(piles[i]^nim_sum);
                  piles[i] = (piles[i] ^ nim_sum);
                  break;
            }
        }
    }
    else{     // Create an array to hold indices of non-empty piles
             int non_zero_indices[n];
             int  count;

             for (i=0, count=0; i<n; i++)
                     if (piles[i] > 0)
                non_zero_indices [count++] = i;


        (*moves).pile_index = (rand() % (count));
        (*moves).stones_removed = 1 + (rand() % (piles[(*moves).pile_index]));
         piles[(*moves).pile_index] = piles[(*moves).pile_index] - (*moves).stones_removed;


        if (piles[(*moves).pile_index] < 0)
            {piles[(*moves).pile_index]=0; }

    }
    return;
  }



void playGame(int piles[], int n, int Turn)
{
    cout <<"\nGAME STARTS\n\n";
    struct move moves;

     while (gameOver (piles, n) == false)
    {
         showPiles(piles, n);
         makeMove(piles, n, &moves);
           if (Turn ==  PLAYER1)
        {
            cout <<"player1 removes " << moves.stones_removed << " stones from pile at index "
             << moves.pile_index << endl;
             Turn = PLAYER2 ;
        }
        else
        {
            cout <<" player2 removes "<< moves.stones_removed << " stones from pile at index "
            << moves.pile_index << endl;
            Turn= PLAYER1;
        }
    }
    showPiles(piles, n);
    declareWinner(Turn);
    return;
}




void knowWinnerBeforePlaying(int piles[], int n, int Turn)
{
     cout <<"Prediction before playing the game -> ";
    if (calculateNimSum(piles, n) !=0)
    {
        if (Turn == PLAYER1)
            cout <<"player1 will win\n";
        else
            cout <<"player2 will win\n";
    }
    else
    {
        if (Turn == PLAYER1)
            cout <<"player2 will win\n";
        else
            cout <<"player1 will win\n";
    }

    return;


}



int main(){
int piles[]={3,4,5};
int n = sizeof(piles)/sizeof(piles[0]);

// We will predict the results before playing
//player1 starts first

knowWinnerBeforePlaying(piles, n, PLAYER1);

// Let us play the game with player1 starting first
// and check whether our prediction was right or not
playGame(piles, n, PLAYER1);


return 0;
}
