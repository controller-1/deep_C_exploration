/*c_asgn01.c
 *
 *      EE474 introductory C programming assignment #1
 *      Spring 2021
 *
 *     Student Name: Kevin Barreto STUDENT NAME and ID# 2070948
 *
 */

/*  Objectives:
       Gain experience and proficiency with C programming.


Format of assignment:
  1)  make a backup copy of this file
  2)  enter your name into the space above
  3)  Read through the comments below and
edit code into this file to solve the problems.
  4)  check your results against posted solution

Notes:   You are not required to use #defines for all constants
in this assignment but please do so for problem 3.

Printing:   Use the following functions to print unless
directed not to do so:

  print_int(int x)                prints out an integer
  print_usi(unsigned int x)       prints out an unsigned int
  print_newl()                    prints a "newline" character
  print_str(char *x)                 prints a string (pointed to by x)
  print_dble(double)              prints out a double precision floating point number

These functions are at the bottom of this file.  Feel free to study
them to see how they work.
*/
/*  #include some system library function prototypes */
      //  we will use printf()
#include <stdio.h>
//  also get math function
#include <math.h>
#include <string.h>    // for strlen (ONLY)
#include <stdlib.h>    // for random()


#define LINUX            1
//#define VISUALC          1

#define         CARD_ERROR      (char) 0xFF  //  a value that cannot be a card
#define         N_DECK          52           // standard # of cards in a deck
// data types
typedef int           shuffle;
//typedef unsigned char hand[7];

/* what is type typedef?:
https://www.tutorialspoint.com/cprogramming/c_typedef.htm
You can use it to give a type a new name. Example:
typedef unsigned char BYTE;
BYTE b1, b2;
*/



/*  function prototypes for simplified printing functions */
void print_int(int);
void print_usi(unsigned int);
void print_newl();
void print_str(char*);
void print_chr(char);
void print_dble(double);


// solution functions

/**********************************************************************
                 All variable declarations
**********************************************************************/

int i,j,k;      // these make good loop iterators.
int card, suit;

//  Random number seed.
//      try  43227 (player 1 has 4 10s)
int seed = 43227;

// Part 1.1
int start = 1;
int stop = 11;

// Part 1.2
int t1, t2;


// Part 2.0

shuffle cards[N_DECK][2];  // the data type is 'int' as renamed aboved with typedef

//  Part 2.2

char testhand[7]={0};


//Part 3.0

// Part 3.1
int dealt_cards[N_DECK] = {0}; // keeps track of which cards have been dealt

// Part 3.2

int dealer_deck_count = 0;  // how many cards have been dealt from a deck


// Part 3.3


/***********************************************************************
                      Function prototypes
**************************************************************************/
char* length_pad(char*, int);     // prob 1.4
int randN(int);                   // 2.1
void fill(shuffle[N_DECK][2]);             // 2.1
unsigned char convert(int card, int suit);  // 2.2
int valid_card(unsigned char card); // 2.2
int gcard(unsigned char card);   // 2.2
int gsuit(unsigned char card);   // 2.2
void names(int n, int j, char *answer);          // 2.3
void deal(int M, unsigned char hand[7], shuffle deck[N_DECK][2]);    // 3.2
void printhand(int M, char* hand, char* buff1);

int pairs(int M, unsigned char hand[]);

int trip_s(int M, unsigned char hand[]);
int four_kind(int M, unsigned char hand[]);



/**********************************************************************
                          main()
***********************************************************************/
int main()
{
/************************************************************************
                    Start code here                                     */

/************************************************************************
 *
 * PROBLEM 1,  C-Basics
 *
 */


// initialize random numbers.
//  change the seed for testing.  Use this value to compare results with
#ifdef VISUALC
srand(seed);
#endif
#ifdef LINUX
//srandom(seed);
#endif

print_str("Random seed: "); print_int(seed); print_newl();


// 1.1  Write a code to print out the 10 integers between 1 and 10 on separate lines:
print_str("Problem 1.1 Test Results: \n");

//  1.1 test code here ...
 for(i=start;i<stop;i++)
 {
     printf("%d\n",i);


 }


// 1.2 Modify 1.1 to print (after the 10 ints):
//   a) sum of the ints.  b) sum of the ints squared.

print_str("Problem 1.2 Test Results: \n");

//  1.2 code here ...

t1 = 0 ; t2 = 0;

for(i=start;i<stop;i++)
{
      // sum of ints
     t1 = t1 + i;
     // sum of square of ints
     t2 = t2 + pow(i,2);
}

//printf("TST: t1-%d\n", t1);

print_int(t1) ;  print_int(t2) ;   print_newl();


print_str("Problem 1.3 Test Results:\n");

// you code for 1.3 here ...
char *l1 = "sum: ";
char *l2 = "sum of squares: ";

print_str(l1) ; print_int(t1) ; print_newl();
print_str(l2) ; print_int(t2) ; print_newl();


/* Notes: See the following reference explaining the above syntax
https://dyclassroom.com/c/c-pointers-and-strings

Essentially a string is stored as an array holding each of the characters and the variable that
it is assigned to actually holds the address of the first element. Therefore, the above syntax is
correct. For example, the pointer variable char *l1 will store the address of the first element
in the string "sum: " which is "s".
*/



//  1.4  Write a fcn, char* length_pad(char *st, int n), which takes a string and adds
//       the right amount of spaces so that it's length is n.  It should return a pointer
//       the new string.  If the length of st is < n, use malloc() to get memory for a new,
//       longer string.
//

//  Add your length_pad function below main.

//   Modify 1.3 to use length_pad() so that the numbers are all starting in col 21
//      (i.e. all labels have length 20).

print_str("Problem 1.4 Test Results: \n");

print_str(length_pad(l1,20)) ; print_int(t1) ; print_newl();
print_str(length_pad(l2,20)) ; print_int(t2) ; print_newl();

// Check that truncation works....
// char *bogus = "Whats up my homie. How are you doing?";
// print_str(length_pad(bogus,20)); print_newl();



/************************************************************************
 * 2.0   Card games
 *
 *  A 'shuffle' is an array of N_DECK pairs of integers.   The first of the pair is the card type
(0-13 representing ace, 2, 3, .... King) and the second representing the suit (hearts, diamonds, clubs, spades).   Thus a pair of numbers (1-13)(1-4) describes a unique card in the deck.
 */




// 2.1 Write a function to fill a shuffle with N_DECK random integer pairs, BUT,
//     as with your playing cards, there must be exactly one of each pair in the
//     shuffle.
//    Use your function to print out all the "cards" of the shuffle, 7 cards per line.

print_str("Problem 2.1 Test Results: "); print_newl();

fill(cards);


// print out the random cards.
for(i=0;i<N_DECK;i++)
    {
    print_str(" [");
    print_int(cards[i][0]); print_str(" "); print_int(cards[i][1]) ;
    print_str("] ");
    if(!((i+1)%7)) print_newl();
    }
print_newl();


// 2.2    A 'hand' is an array of seven unsigned chars.  Each char represents one card.  We use a four bit field in the char for each of the two numbers above:  the four most significant bits [7...4] represent the card number (1-13) and the lower four [3...0] represent the suit.


//        Write functions to:  a)  convert two integers (from  a shuffle for example) into a char as above.
//                                    if the ints are invalid (e.g. convert(294802984,138142) is not a card)
//                                    return CARD_ERROR
//                             b)  test if a char equals a valid integer pair
//                             c)  get the integer suit from a char
//                             d)  get the integer card from a char

//        Both functions a and b must return CARD_ERROR if they get invalid input (such as suit > 4).

//        Write code which verifies these functions work properly and prints results.
//

//

print_str("Problem 2.2  Test Results: ");  print_newl();

//  your code for convert() (2.2.a) below main.
print_str("   2.2.a"); print_newl();
// to test, lets fill a hand up with some cards:
testhand[0] = convert(5,2);
testhand[1] = convert(15,2); // Oops!   15 is invalid card #
testhand[2] = convert(12,1);
testhand[3] = convert(6,3);
testhand[4] = convert(-1,7);  // Hey!  both -1 and 7 are invalid
testhand[5] = convert(10,4);
testhand[6] = convert(3,3);

// Let's check them carefully!
for (i =0; i<7; i++)
{
    if (testhand[i] == CARD_ERROR)
    {
        print_str(" check 1 card error: ");
        print_int(i);
        print_newl();
    }
}



// new test hand
testhand[0] = convert(1,1);  // Ace of Hearts
testhand[1] = convert(1,2);  // Ace of Diamonds
testhand[2] = convert(1,3);  // Ace of Clubs
testhand[3] = convert(1,4);  // Ace of Spades
testhand[4] = convert(11,2); // Jack of Diamonds
testhand[5] = convert(12,2); // Queen of Diamonds
testhand[6] = convert(13,4); // King of Spades

int i;
for (i=0; i<7; i++)
{
    if (testhand[i] == CARD_ERROR)
    {
        print_str(" check 2 card error: ");
        print_int(i); print_newl();
        exit(0);
    }
}



//  your code for convert() (2.2.a) below main.
print_str("   2.2.b"); print_newl();

unsigned char card1, card2;

card1 = 0xFF;  // an invalid card
card2 = convert(1,4); // ace of spades

if (valid_card(card1) == CARD_ERROR)
    print_str(" 0xFF is not a valid card\n");
else print_str(" Somethings wrong with 2.2.b\n");
if (valid_card(card2) == CARD_ERROR)
    print_str(" Somethings wrong with 2.2.b\n");
else print_str("8-bit version of Ace of Spades is a VALID card.\n");

//  your code for convert() (2.2.a) below main.
print_str("   2.2.c,d"); print_newl();


for(i=0;i<7;i++)
{
   int card = gcard(testhand[i]);  //    This part tests 2.2c,d
   int suit = gsuit(testhand[i]);
   print_str("card: "); print_int(card); print_str("   suit: "); print_int(suit);print_newl();
}

/////////////////  Part 3

char buffer[] = "   *empty*       ";


//  your code for convert() (2.2.a) below main.
print_str("Part 3.1 Test Results:");print_newl();

for(i=0;i<7;i++)
{
   card = gcard(testhand[i]);  //    This part tests 2.2c,d
   suit = gsuit(testhand[i]);
   print_str(" >>>>");
   print_int(i); print_str(": "); print_int(card);print_int(suit) ;
   names(card,suit,buffer); // convert card,suit to string name in buffer
   print_str(buffer);
   print_newl();
}
print_newl();

/*
 *     Test Part 3.2
 */

print_str("Part 3.2 Test Results:");print_newl();
print_str("Test the deal() function\n");
char buff[20]="";
for (i=0;i<3;i++)
{
    print_str("\n\n----testing deal: hand: "); print_int(i);print_newl();
    print_str("Deck count: ");print_int(dealer_deck_count); print_newl();
    deal(7,testhand,cards); // see Prob 2.1 for "cards"
    print_str("--------dealt hand: \n");
    printhand(7,testhand, buff);
    print_newl();
}


/*
 *     Test Part 3.3
 */

print_str("Part 3.3 Test Results:");print_newl();
print_str("Test the finding pokerhands function(s).\n");
unsigned char hands[10][7];   //array of 10 hands


dealer_deck_count = 0; // reset to full deck (hands should reappear)

int n_hands = 7;

for (i=0;i<n_hands;i++)
{
    deal(7,hands[i],cards);
}
print_str(" I have ");print_int(n_hands); print_str(" new hands\n");
for (i=0;i<n_hands;i++)
{
    int pct = pairs(7,hands[i]);
    int trips = trip_s(7,hands[i]);
    int fourk = four_kind(7,hands[i]);
    printf("I found %d pairs in hand %d\n",pct,i);
    printf("I found %d three-of-a-kinds in hand %d\n",trips,i);
    printf("I found %d four-of-a-kinds in hand %d\n",fourk,i);
    printf("Hand %d:\n",i);
    printhand(7,hands[i],buff);
    print_newl();
}


#ifdef VISUALC
getchar();
return 0;
#endif


//****************************************************************************
}  //  END OF MAIN



// Part 1.4
//  your function length_pad() here...

char* length_pad(char *st, int n)
{
    int length = strlen(st);
    char *newSt;
    int i = 0;

    if(length < n)
    {
        newSt = (char*) malloc((n+1)*sizeof(char));
        for(i=0;i<n;i++)
        {
            if(i<length)
            {
                *(newSt + i) = *(st + i);
            }
            else if( (i >= length) && (i < n-1))
            {
                *(newSt + i) = ' ';
            }
            else if(i=n-1)
            {
                *(newSt + i) = '\0';
            }
        }
        return newSt;
    }
    else if(length > n)
    {
        newSt = (char*) malloc((n+1)*sizeof(char));
        for(i=0;i<=n;i++)
        {
            if(i<n)
            {
                *(newSt + i) = *(st + i);
            }
            else if(i=n)
            {
                *(newSt + i) = '\0';
            }
        }
        return newSt;
    }
    else
    {
        return st;
    }
}


//Part 2.1
// your function fill() here ...
void fill(shuffle deck[N_DECK][2])
{
    int i = 0;
    int rand_card = 0;
    int card = 0;
    int suit = 0;
    int max2 = 13;                  // max number of each type of suit
    int card_counter2[52];          // count number of unique cards

    for(i=0;i<N_DECK;i++)
    {
        card_counter2[i] = 0;
    }

    i = 0;
    while(i < N_DECK)
    {
        rand_card = randN(N_DECK);      //random card from a new, un-shuffled deck
        card = (rand_card % max2);      //determine card type
        suit = (rand_card / max2) + 1;  //determine suit type
        if(card == 0)
        {
            card = 13;
            suit = suit - 1;
        }

        if(!card_counter2[rand_card-1]) //checks that the combination is a unique card in 52 deck
        {
            deck[i][0] = card;
            deck[i][1] = suit;

            card_counter2[rand_card-1] = 1;
            i++;
        }

    }
}


// Part 2.2
//  your code for convert() here

unsigned char  convert(int card, int suit)
{
    unsigned char code;
    card <<= 4;
    code = (card|suit);

    int flag = valid_card(code);
    if(flag==CARD_ERROR)
    {
        printf("Whoah there. Check your inputs, buddy.\n");
        return CARD_ERROR;
    }

    return code;
}
//Notes: What is going on above? Recall when passing in variables into function the function makes copies for use
//within the function, unless we are using pointers to the original variables which we are not. we create a
//variable 'code' to store the results. << syntax is bit shifting where we are physically manipulating the bits
//at the address of variable copies. For example, if card = 5 then at the address in base 2 we see 00000101.
//Shift 4 places to the left by card<<=4 which results in 01010000. Then use bitwise operator OR (|) to combine
//the two variables. See following reference:
//    https://www.tutorialspoint.com/ansi_c/c_bits_manipulation.htm


// Test if a card byte is a valid card
int valid_card(unsigned char card)
{
    int template1 = 15;                     // Sets bits at variable to 0000 1111
    int template2 = 240;                    // Sets to 1111 0000
    int suittype = (card&template1);        // Sets bits that match in BOTH variables
    int cardtype = (card&template2);
    cardtype >>= 4;                         // Need to shift to the right 4 bits to get correct value

    if((cardtype<1) || (cardtype>13))
    {
        return CARD_ERROR;
    }
    if((suittype<1) || (suittype>4))
    {
        return CARD_ERROR;
    }

    return 0;
}
// your code for gsuit and gcard here

int gcard(unsigned char card)
{
    //Check if valid first
    if(valid_card(card)==CARD_ERROR)
    {
        printf("Whoah there. Check your inputs, buddy.\n");
        return CARD_ERROR;
    }

    card >>= 4;                             // Dont need to keep 1st nibble so just shift right 4 bits
    int cardtype = (int)card;
    return cardtype;
}

int gsuit(unsigned char card)
{
    //Check if valid first
    if(valid_card(card)==CARD_ERROR)
    {
        printf("Whoah there. Check your inputs, buddy.\n");
        return CARD_ERROR;
    }

    card <<= 4;                             // Shift left 4 bits to 'erase' 2nd nibble then shift back
    card >>= 4;
    int suittype = (int)card;
    return suittype;
}



//Part 3.1:
//  Your code for names() here

char * card_names[]={"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
char * suit_names[]={"Hearts","Diamonds","Clubs","Spades"};

void names(int card, int suit, char *answer)
 {
     int ind1 = card - 1;
     int ind2 = suit - 1;
     int length1 = strlen(*(card_names + ind1));
     int length3 = strlen(*(suit_names + ind2));
     char mid[] = " of ";
     int length2 = strlen(mid); // string length of " of "
     int tlen = length1 + length2 + length3;
     int i = 0;
     for(i=0;i<=tlen;i++)
     {
         if(i < length1)
         {
             *(answer + i) = card_names[ind1][i];  // x[][] alternate syntax for pointer to pointer
         }
         else if( (i >= length1) && (i < length1+length2))
         {
             *(answer + i) = mid[i - length1];
         }
         else if((i >= length1+length2) && (i < tlen))
         {
             *(answer + i) = suit_names[ind2][i-(length1+length2)];
         }
         else
         {
             *(answer + i) = '\0';
         }
     }

     return;

 }


// Part 3.2

void deal(int M, unsigned char hand[7], int deck[N_DECK][2])
{
    int i = dealer_deck_count;
    int ind1 = dealer_deck_count + M;
    int card;
    int suit;
    for(i=dealer_deck_count; i<ind1; i++)
    {
        card = deck[i][0];
        suit = deck[i][1];
        hand[i - dealer_deck_count] = convert(card,suit);
    }
    dealer_deck_count = dealer_deck_count + M;
    return;
}


/*
 * Print out a hand of cards
 */
void printhand(int M, char* hand, char* buff1)
{

   int i = 0;
   int card = 0;
   int suit = 0;
   for(i=0;i<M;i++)
   {
       card = gcard(hand[i]);
       suit = gsuit(hand[i]);
       names(card,suit,buff1);
       print_str(buff1);
       printf("\n");
   }
}


int pairs(int M, unsigned char hand[])
{
    int sorted_card[M];     // array to hold sorted cards
    int i = 0;
    int j = 0;
    int swap = 0;
    int num_pairs = 0;      // number of pairs/triples/quadruples
    int repeat_count = 0;   // repeat counter
    int replim = 1;         // number of times repeatable allowed

    for(i=0;i<M;i++)
    {
        sorted_card[i] = gcard(hand[i]);
    }

    //Sort from lowest to highest values
    // Bubble sort
    for(i=0;i<M-1;i++)
    {
        for(j=0;j<M-1;j++)
        {
            if(sorted_card[j]>sorted_card[j+1])
            {
                swap = sorted_card[j];
                sorted_card[j] = sorted_card[j+1];
                sorted_card[j+1] = swap;
            }
        }
    }

    // Counter algorithm
    for(i=0;i<M-1;i++)
    {
        if((sorted_card[i]==sorted_card[i+1]) && (repeat_count<replim))
        {
            num_pairs = num_pairs + 1;
            repeat_count = repeat_count + 1;
        }
        else if(sorted_card[i] != sorted_card[i+1])
        {
            repeat_count = 0;
        }
    }
    return num_pairs;
}



int trip_s(int M, unsigned char hand[])
{
    int sorted_card[M];
    int i = 0;
    int j = 0;
    int swap = 0;
    int num_pairs = 0;
    int repeat_count = 0;
    int replim = 1;

    for(i=0;i<M;i++)
    {
        sorted_card[i] = gcard(hand[i]);
    }

    //Sort from lowest to highest values
    // Bubble sort
    for(i=0;i<M-1;i++)
    {
        for(j=0;j<M-1;j++)
        {
            if(sorted_card[j]>sorted_card[j+1])
            {
                swap = sorted_card[j];
                sorted_card[j] = sorted_card[j+1];
                sorted_card[j+1] = swap;
            }
        }
    }

    for(i=0;i<M-2;i++)
    {
        if((sorted_card[i]==sorted_card[i+1]) && (sorted_card[i+1]==sorted_card[i+2]) && (repeat_count<replim))
        {
            num_pairs = num_pairs + 1;
            repeat_count = repeat_count + 1;
        }
        else if(sorted_card[i] != sorted_card[i+1])
        {
            repeat_count = 0;
        }
    }
    return num_pairs;
}



int four_kind(int M, unsigned char hand[])
{
    int sorted_card[M];
    int i = 0;
    int j = 0;
    int swap = 0;
    int num_pairs = 0;
    int repeat_count = 0;
    int replim = 1;

    for(i=0;i<M;i++)
    {
        sorted_card[i] = gcard(hand[i]);
    }

    //Sort from lowest to highest values
    // Bubble sort
    for(i=0;i<M-1;i++)
    {
        for(j=0;j<M-1;j++)
        {
            if(sorted_card[j]>sorted_card[j+1])
            {
                swap = sorted_card[j];
                sorted_card[j] = sorted_card[j+1];
                sorted_card[j+1] = swap;
            }
        }
    }

    for(i=0;i<M-1;i++)
    {
        if((sorted_card[i]==sorted_card[i+1]) && (sorted_card[i+1]==sorted_card[i+2]))
        {
            if((sorted_card[i+2]==sorted_card[i+3]) && (repeat_count<replim))
            {
                num_pairs = num_pairs + 1;
                repeat_count = repeat_count + 1;
            }
        }
        else if(sorted_card[i] != sorted_card[i+1])
        {
            repeat_count = 0;
        }
    }
    return num_pairs;
}



/**************************************************************************
  simplified I/O and other functions for this assignment
***************************************************************************/
void print_int(int x)
  {
  printf(" %d ",x);
  }
void print_usi(unsigned int x)
  {
  printf(" %d",x);
  }
void print_dble(double x)
  {
  printf(" %f",x);
  }
void print_newl()
  {
  printf("\n");
  }
void print_str(char *x)
  {
  printf("%s",x);
  }
void print_chr(char x)
  {
  printf("%c",x);
  }

int randN(int n)   //  return a random integer between 1 and n
  {
  double x;
  x = 1.0 + (double) n * rand() / RAND_MAX;
  return((int)x);
  }
/* Notes on rand() and RAND_MAX:
https://linuxhint.com/rand-function-in-c-language/
rand() is a pseudo random number generator so not truly random but good enough.
RAND_MAX is a macro defined in stdlib.h header file.
The range of rand() is from 0 to RAND_MAX. RAND_MAX  is greater than or equal to 32767
*/

