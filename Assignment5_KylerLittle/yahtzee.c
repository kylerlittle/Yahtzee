#include "yahtzee.h"

void print_game_menu(void)
{
	printf("1. Print game rules.\n");
	printf("2. Start a game of Yahtzee.\n");
	printf("3. Exit.\n");
}
void get_menu_option(int *menu_option_ptr)
{
	printf("Please select option 1, 2, or 3.\n");
	scanf("%d", menu_option_ptr);
}
void print_game_rules(void)
{
	printf("The Rules of Yahtzee:\n\n");
	printf("The scorecard used for Yahtzee is composed of two sections.\n");
	printf("A upper section and a lower section. A total of thirteen boxes\n");
	printf("or thirteen scoring combinations are divided amongst the\n");
	printf("sections. The upper section consists of boxes that are scored\n");
	printf("by summing the value of the dice matching the faces of the\n");
	printf("box. If a player rolls four 3's, then the score placed in the\n");
	printf("3's box is the sum of the dice which is 12. Once a player has\n");
	printf("chosen to score a box, it may not be changed and the combination\n");
	printf("is no longer in play for future rounds. If the sum of the scores\n");
	printf("in the upper section is greater than or equal to 63, then 35\n");
	printf("more points are added to the players overall score as a bonus.\n");
	printf("The lower section contains a number of poker like combinations.\n");
	printf("For more information & specific score combinations, follow:\n");
	printf("this link: http://yahtzee.silentmatt.com/instructions \n\n");
}
void roll_dice(int dice[], int size)
{
	int index = 0;
	for (index = 0; index < size; ++index)
	{
		dice[index] = rand() % 6 + 1;
	}
}
void roll_dice_again(int dice[])
{
	int n = 0, index = 0, die_number;
	printf("HOW MANY DICE would you like to roll again?\n");
	do
	{
		scanf("%d", &n);
		if ((n > 0) | (n <= 5))
		{
			printf("WHICH DICE would you like to roll again?\n");
			while (index < n)
			{
				scanf("%d", &die_number);
				dice[die_number - 1] = rand() % 6 + 1;
				++index;
			}
		}
		else if (n == 0)
		{
			printf("You probably should have just picked a score combo... but ALRIGHTY THEN.\n");
		}
		else //not valid
		{
			printf("Not a valid option!\n");
		}
	} while ((n < 0) | (n > 5));
	print_dice(dice, 5);
}
void print_dice(int *dice_ptr, int size)
{
	int index = 0;
	for (index = 0; index < size; ++index)
	{
		printf("DIE %d: %d\t", index + 1, *(dice_ptr + index));
	}
	printf("\n");
}
void count_dice_values(int dice[], int size_dice, int count_array[], int size_count)
{
	int index = 0, new_index = 0;
	while (index < size_dice)
	{
		new_index = dice[index++];   //dice value is assigned to new_index
		count_array[new_index] += 1;  //count_array adds 1 to "count" in the location of new_index (the rolled value)
	}
}
void roll_again_or_score(int *roll_or_score_ptr, int scorecard[])
{
	int option = 0;
	do
	{
		printf("1. Roll again.\n");
		printf("2. Use roll for one of the game combinations.\n");
		printf("3. View current scorecard.\n");
		printf("Please select either option 1, option 2, or option 3.\n");
		scanf("%d", &option);
		if (option == 1)
		{
			*roll_or_score_ptr = ROLL_AGAIN;
		}
		else if (option == 2)
		{
			*roll_or_score_ptr = USE_ROLL_FOR_SCORE;
		}
		else if (option == 3)
		{
			print_current_scorecard(scorecard);
			system("pause");
			option = 4; //to go back thru loop.
		}
	} while ((option < 1) | (option > 3));
}
void print_score_menu(void)
{
	printf("1. Sum of 1's\t 7. Three-of-a-kind\n");
	printf("2. Sum of 2's\t 8. Four-of-a-kind\n");
	printf("3. Sum of 3's\t 9. Full House\n");
	printf("4. Sum of 4's\t 10. Small Straight\n");
	printf("5. Sum of 5's\t 11. Large Straight\n");
	printf("6. Sum of 6's\t 12. Yahtzee\n");
	printf("\t 13. Chance\n");
}
void print_current_scorecard(int scorecard[])
{
	printf("\n1. Sum of 1's: %d\t\t 7. Three-of-a-kind: %d\n", scorecard[1], scorecard[7]);
	printf("2. Sum of 2's: %d\t\t 8. Four-of-a-kind: %d\n", scorecard[2], scorecard[8]);
	printf("3. Sum of 3's: %d\t\t 9. Full House: %d\n", scorecard[3], scorecard[9]);
	printf("4. Sum of 4's: %d\t\t 10. Small Straight: %d\n", scorecard[4], scorecard[10]);
	printf("5. Sum of 5's: %d\t\t 11. Large Straight: %d\n", scorecard[5], scorecard[11]);
	printf("6. Sum of 6's: %d\t\t 12. Yahtzee: %d\n", scorecard[6], scorecard[12]);
	printf("\t\t 13. Chance: %d\n", scorecard[13]);
}
void select_score_option(int *score_option_ptr, int score_used_before[])
{
	do
	{
		printf("Please select a scoring option <1-13>: ");
		scanf("%d", score_option_ptr);
		if (score_used_before[*score_option_ptr] == NOT_USED)
		{
			system("cls");
		}
		else  //score_used_before has nonzero entry, meaning score combo has already been used
		{
			printf("OOOPS! You've already used that option. Try another!\n");
			*score_option_ptr = 14; //will go thru loop again
		}
	} while ((*score_option_ptr < 1) | (*score_option_ptr > 13));
}
int sum_num(int value, int n)
{
	return value * n;
}
void upper_score_card(int option, int scorecard[], int dice_value_count[],
	int score_used_before[])
{
	// we know score combo hasn't been used before
	// because select_score_option validates this
	score_used_before[option] = USED;
	scorecard[option] = sum_num(dice_value_count[option], option);
}
void lower_score_card(int option, int scorecard[], int dice_value_count[],
	int score_used_before[])
{
	score_used_before[option] = USED;
	int index = 0, sum = 0;
	switch (option)
	{
	case 7:  //3 OF A KIND
	case 8:  //4 OF A KIND
	case 13: //CHANCE
		for (index = 0; index <= 5; ++index)
		{
			sum += sum_num(dice_value_count[index + 1], index + 1);
		}
		scorecard[option] = sum;
		break;
	case 9:  //FULL HOUSE
		scorecard[option] = 25;
		break;
	case 10: //SMALL STRAIGHT
		scorecard[option] = 30;
		break;
	case 11: //LARGE STRAIGHT
		scorecard[option] = 40;
		break;
	case 12: //YAHTZEE
		scorecard[option] = 50;
		break;
	}
}
void valid_or_not(int *valid_ptr, int dice_value_count[], int option)
{
	int index = 0, index2 = 0, check = 0;
	switch (option)
	{
	case 7:  //3 OF A KIND
		while ((*valid_ptr == NOT_VALID) && (index <= 5))
		{
			if (dice_value_count[index + 1] >= 3)
			{
				*valid_ptr = VALID;
			}
			++index;
		}
		break;
	case 8:  //4 OF A KIND
		while ((*valid_ptr == NOT_VALID) && (index <= 5))
		{
			if (dice_value_count[index + 1] >= 4)
			{
				*valid_ptr = VALID;
			}
			++index;
		}
		break;
	case 9:  //FULL HOUSE
		while ((check == 0) && (index <= 5))
		{
			if (dice_value_count[index + 1] == 2)
			{
				check = HALF_FULL_HOUSE;
			}
			++index;
		}
		if (check = HALF_FULL_HOUSE)
		{
			while ((*valid_ptr == NOT_VALID) && (index2 <= 5))
			{
				if (dice_value_count[index + 1] == 3)
				{
					*valid_ptr = VALID;
				}
				++index2;
			}
		}
		break;
	case 10: //SMALL STRAIGHT
		if (((dice_value_count[index + 1] >= 1) && (dice_value_count[index + 2] >= 1)
			&& (dice_value_count[index + 3] >= 1) && (dice_value_count[index + 4] >= 1))
			| ((dice_value_count[index + 2] >= 1) && (dice_value_count[index + 3] >= 1)
				&& (dice_value_count[index + 4] >= 1) && (dice_value_count[index + 5] >= 1))
			| ((dice_value_count[index + 3] >= 1) && (dice_value_count[index + 4] >= 1)
				&& (dice_value_count[index + 5] >= 1) && (dice_value_count[index + 6] >= 1)))
		{
			*valid_ptr = VALID;
		}
	case 11: //LARGE STRAIGHT
		if (((dice_value_count[index + 1] >= 1) && (dice_value_count[index + 2] >= 1)
			&& (dice_value_count[index + 3] >= 1) && (dice_value_count[index + 4] >= 1)
			&& (dice_value_count[index + 5] >= 1))
			| ((dice_value_count[index + 2] >= 1) && (dice_value_count[index + 3] >= 1)
				&& (dice_value_count[index + 4] >= 1) && (dice_value_count[index + 5] >= 1)
				&& (dice_value_count[index + 6] >= 1)))
		{
			*valid_ptr = VALID;
		}
	case 12: //YAHTZEE
		while ((*valid_ptr == NOT_VALID) && (index <= 5))
		{
			if (dice_value_count[index + 1] == 5)
			{
				*valid_ptr = VALID;
			}
			++index;
		}
		break;
	case 13: //CHANCE
		*valid_ptr = VALID;
		break;
	}
}
void bonus_or_not(int upper_scorecard[], int size)
{
	int index = 0, sum = 0;
	for (index = 1; index < (size/2); ++index)
	{
		sum += upper_scorecard[index];
	}
	if (sum >= 63)
	{
		upper_scorecard[6] += 35; //add 35 to 6th index value; will be used to calculate score later
	}
}
void calculate_score(int scorecard[], int size, int *score_ptr)
{
	int index = 0;
	for (index = 1; index < size; ++index)
	{
		*score_ptr += scorecard[index];
	}
}
void print_scores_and_winner(int score_p1, int score_p2)
{
	printf("Score of Player 1: %d\n", score_p1);
	printf("Score of Player 2: %d\n\n", score_p2);
	if (score_p1 > score_p2)
	{
		printf("PLAYER 1 WINS!\n");
	}
	else if (score_p1 < score_p2)
	{
		printf("PLAYER 2 WINS!\n");
	}
	else  //its a tie
	{
		printf("You both tied! Wow!\n");
	}
	printf("THANKS FOR PLAYING!!! :)\n");
}