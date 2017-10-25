#ifndef PA_5_ASSIGNMENT
#define PA_5_ASSIGNMENT

/*Standard Libraries Included*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Defined Macro Constants*/
#define ROLL_AGAIN 99
#define USE_ROLL_FOR_SCORE 100
#define USED 1
#define NOT_USED 0
#define VALID 2
#define NOT_VALID 0
#define HALF_FULL_HOUSE 3


/*Function Prototypes with Description Blocks*/

//SIDE NOTE: When I say an input parameter is an array, I mean that it
//the input parameter is the address of the first position in the array;
//as such, the input parameter could also be a pointer

/**************************************************************************
* Function: roll_again_or_score
* Description: This function prints out a menu to the user & asks
			   whether the user wants to roll again, use roll for score
			   combo, or view scorecard. Based on this choice,
			   roll_or_score value is modified via a pointer.
* Input parameters: Roll_or_score Pointer/Address & Scorecard Array
* Returns: Nothing
* Preconditions: Scorecard must be referring to contiguous memory
* Postconditions: Roll_or_score variable is modified, leading to logical
				  flow in main, depending on the value it is modifed to.
**************************************************************************/
void roll_again_or_score(int *roll_or_score_ptr, int scorecard[]);

/**************************************************************************
* Function: roll_dice_again
* Description: Prompts user for how many dice he/she would like to roll 
			   again, then which dice. The function then rerolls selected
			   dice and prints.
* Input parameters: Dice Array
* Returns: Nothing
* Preconditions: Dice must be referring to contiguous memory
* Postconditions: Dice[] array updated (if chosen)
**************************************************************************/
void roll_dice_again(int dice[]);

/**************************************************************************
* Function: select_score_option
* Description: Prompts user to select a scoring option (1-13). If player
			   has not used the option before AND the number is valid
			   (between 1 and 13), score_option is set to that number.
* Input parameters: Score_Option Pointer/Score_Used_Before Array
* Returns: Nothing
* Preconditions: Scorecard must be referring to contiguous memory
* Postconditions: Returns a VALID score_option selected; user cannot move
				  on unless a valid option was selected.
**************************************************************************/
void select_score_option(int *score_option_ptr, int score_used_before[]);

/**************************************************************************
* Function: print_score_menu
* Description: Prints off the Score Menu Options (1-13)
* Input parameters: None
* Returns: Nothing
* Preconditions: None
* Postconditions: Menu is printed.
**************************************************************************/
void print_score_menu(void);

/**************************************************************************
* Function: print_current_scorecard
* Description: This function simply prints off the user's CURRENT
			   scorecard at that stage in the game.
* Input parameters: Scorecard Array
* Returns: Nothing
* Preconditions: Scorecard must be referring to contiguous memory
* Postconditions: Current Scorecard is printed to user.
**************************************************************************/
void print_current_scorecard(int scorecard[]);

/**************************************************************************
* Function: upper_score_card
* Description: This function accept's the score option selected and uses
			   that score_option
* Input parameters: Scorecard, Dice_Value_Count, Score_Used_Before Arrays
					and the score_option selected (integer)
* Returns: Nothing
* Preconditions: Scorecard, Dice_Value_Count, and Score_Used_Before must 
			     be referring to contiguous memory. Option should be 
				 between 1-6 for switch statement to function properly.
* Postconditions: Scorecard is updated with the correct score in
				  the index position selected.
**************************************************************************/
void upper_score_card(int option, int scorecard[], int dice_value_count[],
	int score_used_before[]);

/**************************************************************************
* Function: lower_score_card
* Description: This function simply assigns the proper number of points
			   to the index (option) of scorecard[]. It then updates the
			   corresponding score_used_before index to USED.
* Input parameters: Roll_or_score Pointer/Address & Scorecard Array
* Returns: Nothing
* Preconditions: Scorecard, Dice_Value_Count, and Score_Used_Before must 
			     be referring to contiguous memory. Option should be 
				 between 7-13 for switch statement to function properly.
* Postconditions: Scorecard is updated with the correct score in
				  the index position selected.
**************************************************************************/
void lower_score_card(int option, int scorecard[], int dice_value_count[],
	int score_used_before[]);

/**************************************************************************
* Function: valid_or_not
* Description: This function checks to see if the user's score_option 
			   selection is actually valid. For instance, if the user 
			   actually has a Small Straight when they pick that option.
			   If they do, "valid" is modified to VALID. Otherwise, "valid"
			   remains NOT_VALID.
* Input parameters: Address of "Valid", Dice_Value_Count Array, and the
				    score_option selected by user
* Returns: Nothing
* Preconditions: Dice_Value_Count must be referring to contiguous memory
				 and *valid_ptr must be a valid address.
* Postconditions: "Valid" is indirectly modified.
**************************************************************************/
void valid_or_not(int *valid_ptr, int dice_value_count[], int option);

/**************************************************************************
* Function: print_game_menu
* Description: This function simply prints the start-up menu. Play game,
			   view rules, or exit.
* Input parameters: None.
* Returns: Nothing
* Preconditions: None.
* Postconditions: Game menu is printed.
**************************************************************************/
void print_game_menu(void);

/**************************************************************************
* Function: get_menu_option
* Description: This function prompts the user to enter for either option
			   1, 2, or 3 and assigns this value to where menu_option_ptr
			   points.
* Input parameters: Menu_Option pointer
* Returns: Nothing
* Preconditions: menu_option_pointer is a valid address
* Postconditions: menu_option is indirectly modified
**************************************************************************/
void get_menu_option(int *menu_option_ptr);

/**************************************************************************
* Function: print_game_rules
* Description: Prints the rules for the game of Yahtzee
* Input parameters: None
* Returns: Nothing
* Preconditions: None
* Postconditions: None
**************************************************************************/
void print_game_rules(void);

/**************************************************************************
* Function: roll_dice
* Description: This function generates a random number between 1-6
			   and assigns one to every entry in the dice array
* Input parameters: Dice Array and size of dice array
* Returns: Nothing
* Preconditions: Dice must be referring to contiguous memory.
* Postconditions: Dice Array has random values between 1-6 as its entries.
**************************************************************************/
void roll_dice(int dice[], int size);

/**************************************************************************
* Function: print_dice
* Description: This function prints off the dice values from the dice 
			   array in one line of text.
* Input parameters: Dice Array, size of dice array
* Returns: Nothing
* Preconditions: Dice_ptr must be referring to contiguous memory
* Postconditions: Dice Values are printed to screen
**************************************************************************/
// precondition: dice_ptr must be referring to contiguous memory
void print_dice(int *dice_ptr, int size);

/**************************************************************************
* Function: count_dice_values
* Description: This function counts up how many times a particular dice 
			   was rolled (i.e. the values 1-6) and stores the frequency
			   to the corresponding entry in a parallel array called
			   count_array, where the indices of the count_array are the
			   possible dice values (1-6).
* Input parameters: Dice & Count Arrays, size of both arrays
* Returns: Nothing
* Preconditions: Dice/Count must be referring to contiguous memory
* Postconditions: Count_array is modified.
**************************************************************************/
void count_dice_values(int dice[], int size_dice, int count_array[], int size_count);

/**************************************************************************
* Function: sum_num
* Description: Returns n*value. Ideally used where value is the value of
			   the entry in the count_array (the frequency) and n is the
			   index of the count_array (representing the dice rolled).
			   Thus, if three 6s were rolled, 18 would be the sum_num.
* Input parameters: Value and n (integers)
* Returns: The "sum"
* Preconditions: None
* Postconditions: Sum is returned.
**************************************************************************/
// value is the value in count_array; n is the number of the index
int sum_num(int value, int n);

/**************************************************************************
* Function: bonus_or_not
* Description: This function determines whether or not the user scored 63 or
			   more points in the "upper" section of his/her scorecard. If so,
			   35 points are added to their score. In this case, 35 points are
			   simply added to the 6th index of score_card
* Input parameters: Scorecard Array & size
* Returns: Nothing
* Preconditions: Scorecard must be referring to contiguous memory
* Postconditions: Scorecard array is the same or has 35 more points added
			      to the 6th entry.
**************************************************************************/
void bonus_or_not(int upper_scorecard[], int size);

/**************************************************************************
* Function: calculate_score
* Description: This function simply calculates the total score, which ends
			   up being the sum of the entries of scorecard. It assigns
			   this sum to where score_ptr points.
* Input parameters: Score Pointer/Address, Scorecard Array, and the size
					of that array
* Returns: Nothing
* Preconditions: Scorecard must be referring to contiguous memory,
				 score_ptr is a valid address
* Postconditions: Score is indirectly modified.
**************************************************************************/
void calculate_score(int scorecard[], int size, int *score_ptr);

/**************************************************************************
* Function: print_scores_and_winner
* Description: This function compares the two scores of the players
			   and declares a winner. The larger score wins. It prints out
			   a fun little message to the winner.
* Input parameters: Scores of both players
* Returns: Nothing
* Preconditions: None
* Postconditions: Scores & winner printed to screen.
**************************************************************************/
void print_scores_and_winner(int score_p1, int score_p2);

#endif