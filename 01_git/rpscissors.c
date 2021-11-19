/**
 * Description: Console Game Rock-Paper-Scissors
 * Author:      Nazarii Kurylko
 * Created:     19.1.2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* enumerations */
typedef enum {PC_WINNER=-1, NO_WINNER, USER_WINNER} WINNER;
typedef enum {ERROR=-1, SUCCESS=0} STATUS;

/*function declaration*/
static char read_user_choice();
static STATUS chek_choice(char choice);
static const char* get_full_choice(char choice);
static WINNER compare_results(char pc_choice, char user_choice);
static void print_results(char pc_choice, char user_choice, int result);
 
//main algorithm
int main()
{
    char user_choice = 'u'; /*unknown*/
    char pc_choice   = 'u'; /*unknown*/
    const char choice_range[] = {'r', 'p', 's'};/*rock, papaer, scissors*/
    WINNER result = NO_WINNER;
    
    /*initialise rand*/
    srand(time(0));
        
    /*repeat untill winner found*/
    while (NO_WINNER == result) 
    {
        printf("> Please choose: rock (r) - paper (p) - scissors (s)\n> ");
        
        /*read user choice*/
        user_choice = read_user_choice();
        
        /*verify if user choice is in range*/
        if (ERROR == chek_choice(user_choice))
        {
            continue;
        }
    
        /*pc choice*/
        pc_choice = choice_range[rand() % (sizeof choice_range /sizeof choice_range[0])] ;
        
        /*compare results*/ 
        result = compare_results(pc_choice, user_choice);

        /*print result*/
        print_results(pc_choice, user_choice, result);
    }
    return 0;
}

/*read user choices*/
static char read_user_choice()
{
    /*read user choice*/
    char line [256]; 
    if (    (fgets(line, sizeof line, stdin) == NULL) 
        || (line [1] != '\n')) 
    {
        return 'u'; /*unknown - choice is unclear*/
    }
    else
    {
        return line[0]; /*return first character*/
    }
}

/*comare the pc and user choices*/
static WINNER compare_results(char pc_choice, char user_choice)
{
    if (pc_choice == user_choice)
    {
        return NO_WINNER; /*nobody wins*/
    }
    else if(   (pc_choice == 'r' && user_choice == 's') 
            || (pc_choice == 'p' && user_choice == 'r') 
            || (pc_choice == 's' && user_choice == 'p'))
    {
        return PC_WINNER; /*pc win*/
    }
    else
    {
        return USER_WINNER; /*ps lose*/
    }
}

/*convet short to full description of user choice*/
static const char* get_full_choice(char choice)
{
    if      ('r' == choice)  return "rock";
    else if ('p' == choice)  return "paper";
    else if ('s' == choice)  return "scissors";
    else                     return "unknown choice";
}

/*verify if choice is in range*/
static STATUS chek_choice(char choice)
{
    if (   choice != 'r' 
        && choice != 'p' 
        && choice != 's')
    {
        //choice is not in range
        return ERROR;
    }
    return SUCCESS;
}

/*print results to comad line*/
static void print_results(char pc_choice, char user_choice, int result )
{
    printf( "> You choose %s, I choose %s\n", get_full_choice(user_choice), 
            get_full_choice(pc_choice) );

    if (USER_WINNER == result)
    {
        printf("> I lose: %s beats %s\n", get_full_choice(user_choice), 
        get_full_choice(pc_choice));
    }
    else if (PC_WINNER == result)
    {
        printf("> I win: %s beats %s\n",get_full_choice(pc_choice), 
        get_full_choice(user_choice));
    }
}
