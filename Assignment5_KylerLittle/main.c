/*************************************************************************
* Programmer: Kyler Little
* Class: CptS 121; Lab Section 11
* Programming Assignment: Programming Project 5
* Date: 10/17/2016                                                                    *
* Description: This assignment guides the user through a game of Yahtzee!
				(assuming that the user chooses to play). Initially,
				he/she is prompted to either read the rules, play a game,
				or exit. If he/she so chooses to play a game, then the
				user will be guided through a game of Yahtzee! There are
				two players, each playing 13 rounds. At the end, the
				winner is decided!
************************************************************************/

#include "yahtzee.h"
int main(void)
{
	/*VARIABLE DECLARATIONS*/
	//Arrays
	int dice[5] = { 0 },
		scorecard_p1[14] = { 0 }, scorecard_p2[14] = { 0 },
		score_used_before_p1[14] = { 0 },
		score_used_before_p2[14] = { 0 };
	//Ints
	int score_option = 0, menu_option = 0, number_of_rounds = 1,
		roll_again_or_use_score = 0, counter = 0,
		final_score_p1 = 0, final_score_p2 = 0;
	//Seed
	srand((unsigned int)time(NULL));
	/*seeds a value into the random number generator
	so that rand() function actually produces random numbers*/

	/*GAME EXECUTION*/
	do
	{
		system("cls"); //this will effectively delete the game_menu if 
		//the user enters an option outside of 1-3 and print a new one.

		// 1. Print Game Menu
		print_game_menu();
		// 2. Get a menu option from user; clear the screen.
		get_menu_option(&menu_option);
		if (menu_option == 1)
		{
			print_game_rules();
			system("pause");  //once done reading, press any key to continue
			menu_option = 5; //to reiterate do-while loop
		}
		else if (menu_option == 2)
		{
			while (number_of_rounds <= 26)  // 2 players, 13 rounds each
			{
				// 3. Play game; first clear screen. Will clear every time thru loop.
				system("cls");
				//PRINT MESSAGE ABOUT WHICH PLAYER THIS IS (1 or 2) & round
				printf("PLAYER %d \t \t ROUND %d (out of 13)\n", counter % 2 + 1, (number_of_rounds + 1) / 2);
				//Variables that must be "reset" each time thru the loop
				int number_of_rolls = 1, valid = NOT_VALID;
				int dice_value_count[7] = { 0 };
				// 4. Ask player to hit any key to continue on to roll dice.
				printf("To roll the five dice: ");
				system("pause");
				// 5. Roll five dice and display; add 1 to total number of rolls this round
				roll_dice(dice, 5);   //name of array supplies the address of the first entry of the array
				print_dice(dice, 5);
				
				
				roll_again_or_use_score = ROLL_AGAIN;  //enter loop
				while ((number_of_rolls < 3) && (roll_again_or_use_score == ROLL_AGAIN))
				{
					// 6. Print option list. 1. Roll dice again (which dice?) 2. Score. 3. View scorecard.
					if (counter % 2 == 0)  //PLAYER 1
					{
						roll_again_or_score(&roll_again_or_use_score, scorecard_p1);
					}
					else  //PLAYER 2
					{
						roll_again_or_score(&roll_again_or_use_score, scorecard_p2);
					}
					//if use score, exit loop before executing all this shit (maybe assign number_rolls = 3)
					if (roll_again_or_use_score == USE_ROLL_FOR_SCORE)
					{
						number_of_rolls = 3;  //this will allow user to exit while loop and score
					}
					else //roll_dice_again
					{
						roll_dice_again(dice);
						++number_of_rolls;
					} //once number_of_rolls == 3, then will exit loop
				}
				// 7. TIME TO SCORE YOUR SCORECARD!! Which score combo would you like to do?
				//roll_again_or_use_score = USE_ROLL_FOR_SCORE at this point
				print_score_menu();
				/*
				Basically, we we want to do here is set up logical flow.
				If score_used_before[option] == USED (indicating used before)
					Error message. "You have already used this option... Try another.\n"
				Else (not used before)
					If he/she actually has the point combo
						Assign them points
					Else, assign that score to 0
				SCORE_USED_BEFORE[option] == 1; //now, that person has used that score option
				*/
				count_dice_values(dice, 5, dice_value_count, 7);  //counting up NOW!! otherwise, it will continually add
				if (counter % 2 == 0)  //PLAYER 1
				{
					select_score_option(&score_option, score_used_before_p1);
					if (score_option <= 6)
					{
						upper_score_card(score_option, scorecard_p1, dice_value_count, score_used_before_p1);
					}
					else // 7 <= score_option <= 13
					{
						valid_or_not(&valid, dice_value_count, score_option); //valid check
						if (valid == VALID)
						{
							lower_score_card(score_option, scorecard_p1, dice_value_count, score_used_before_p1);
						}
						else
						{
							scorecard_p1[score_option] = 0;
							score_used_before_p1[score_option] = USED;
						}
					}
				}
				else  //PLAYER 2
				{
					select_score_option(&score_option, score_used_before_p2);
					if (score_option <= 6)
					{
						upper_score_card(score_option, scorecard_p2, dice_value_count, score_used_before_p2);
					}
					else // 7 <= score_option <= 13
					{
						valid_or_not(&valid, dice_value_count, score_option);
						if (valid == VALID)
						{
							lower_score_card(score_option, scorecard_p2, dice_value_count, score_used_before_p2);
						}
						else
						{
							scorecard_p2[score_option] = 0;
							score_used_before_p2[score_option] = USED;
						}
					}
				}
				++counter; //every time thru, will be other player
				++number_of_rounds;  //make sure both players have gone first
			}
			// 10. If total score of upper_scorecard >= 63, +35 to total score.
			bonus_or_not(scorecard_p1, 14);
			bonus_or_not(scorecard_p2, 14);
			// 11a. Calculate scores for both players.
			calculate_score(scorecard_p1, 14, &final_score_p1);
			calculate_score(scorecard_p2, 14, &final_score_p2);
			// 11b. Print scores for both players & print the winner.
			print_scores_and_winner(final_score_p1, final_score_p2);
			// 12. After system pause, repeat step 1. Implement input-validation loop. For ex,
			system("pause");
			menu_option = 6; //to reiterate thru do-while loop, possibly play again;
			// 13. Make sure scorecards are fresh, and number_of_rounds reset.
			// Initialize those variables within the loop.
		}
		else if (menu_option == 3)
		{
			system("cls");
			printf("LAME! You know you wanted to play Yahtzee... Maybe next time.\n");
		}
	} while ((menu_option < 1) | (menu_option > 3));
	// use a do while loop because it works best for user-validated input loops
	return 0;
}