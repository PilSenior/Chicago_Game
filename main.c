

/*
Name Surname: YOUR_NAME_SURNAME
ID: YOUR_ID

Q1) Which loop type did you use, pre-test or post-test? 
What is the difference between pre-test and posttest loop?
    BEN kendi kodumda hem pre-test (while) hem de post-test (do-while) kullandım.
    Pre-test loop, koşul sağlanmadan önce test edilir ve koşul sağlanmazsa döngü hiç çalışmaz. 
    Post-test loop ise koşul sağlanmadan önce en az bir kez çalışır ve ardından koşul test edilir. 
    Bu nedenle, post-test loop her zaman en az bir kez çalışır, pre-test loop ise koşula bağlı olarak sıfır veya daha fazla kez çalışabilir.


Q2) What is the datatype of the random number you generated in this function?
    ben rand() fonksiyonunu kullanarak 1 ile 6 arasında bir sayı üretiyorum. rand() fonksiyonu int türünde bir sayı döndürür, 
    bu nedenle ürettiğim rastgele sayının veri tipi int'tir.
    
Q3)What is the return type of this function that you used? Why?
    play_user() fonksiyonunun dönüş tipi int'tir. Çünkü bu fonksiyon
    oyuncunun o round'daki skorunu hesaplayıp döndürmesi gerekiyor.
    main() içinde bu değer user_total'a ekleniyor. Skor sayısal bir
    değer olduğu için int kullanmak en uygun tiptir.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_a_dice(void);
int play_user(int target);
int play_computer(int target);
void scoresheet(int comp_total, int user_total);
int calculate_score(int dice1, int dice2);


int roll_a_dice()
{
    return (rand() % 6) + 1;
}

int play_user(int target)
{
    int roll_no = 1;
    int dice1;
    int dice2;
    int hits = 0;
    char choice = 'Y';

    while (roll_no <= 3 && choice != 'N' && choice != 'n')
    {
        dice1 = roll_a_dice();
        dice2 = roll_a_dice();

        printf("You got [Dice 1]: %d [Dice 2]: %d\n", dice1, dice2);

        int is_hit = (calculate_score(dice1, dice2) == target);

        if (is_hit)
        {
            hits++; // Hedefi vurdukça katlayarak artır
        }
        else if (!is_hit)
        {
            hits = 0; // Hedefi kaçırdığın an seri bozulur, her şey sıfırlanır
        }

        int round_total = hits * target;
        int roll_score = is_hit ? target : 0;
        printf("Your score: %d Total score: %d\n", roll_score, round_total);

        if (roll_no < 3)
        {
            do
            {
                printf("Shall I roll for you again (Y/N)? ");
                scanf(" %c", &choice);
                if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    printf("Invalid input, Try Again!\n");
            } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
        }
        roll_no++;
    }

    return (hits > 0) ? hits * target : 0;
}

int play_computer(int target)
{
    int roll_no = 1;
    int dice1;
    int dice2;
    int sum = target - 1; /* Initialize to target - 1 to ensure at least one roll */
    int hits = 0;
    int round_total = 0;
    int roll_score;

    while (roll_no <= 3 && sum == target - 1)
    {
        dice1 = roll_a_dice();
        dice2 = roll_a_dice();
        sum = dice1 + dice2;

        if (roll_no == 1)
        {
            printf("I rolled them and I got\n");
        }
        else
        {
            printf("Rolled again!\n");
        }
        printf("[Dice 1]: %d [Dice 2]: %d\n", dice1, dice2);

        int is_hit = (calculate_score(dice1, dice2) == target) ? 1 : 0;

        if (is_hit)
            hits++;
        else
            hits = 0;
        round_total = hits * target;
        roll_score = is_hit ? target : 0;
        roll_no++;
    }
    printf("My score: %d Total score: %d\n", roll_score, round_total);
    return round_total;
}

void scoresheet(int comp_total, int user_total)
{
    printf("=============================\n");
    printf("My score    Your score\n");
    printf("%d           %d\n", comp_total, user_total);
}

int calculate_score(int dice1, int dice2)
{
    return dice1 + dice2;
}

int main()
{
    int n;
    int user_total = 0;
    int comp_total = 0;
    int user_start_d1;
    int user_start_d2;
    int comp_start_d1;
    int comp_start_d2;
    int user_start_sum;
    int comp_start_sum;
    int user_round_score;
    int comp_round_score;
    int round = 1;
    int user_starts;

    srand((unsigned int)time(NULL));

    printf("Welcome to Chicago game.\n");
    printf("Let's get started!\n");

    /* Decide who starts by comparing totals, reroll if totals are equal. */
    do
    {
        comp_start_d1 = roll_a_dice();
        comp_start_d2 = roll_a_dice();
        user_start_d1 = roll_a_dice();
        user_start_d2 = roll_a_dice();

        comp_start_sum = comp_start_d1 + comp_start_d2;
        user_start_sum = user_start_d1 + user_start_d2;

        printf("I have rolled the dice and got %d and %d!\n", comp_start_d1, comp_start_d2);
        printf("I have rolled the dice for you, and you got %d and %d!\n", user_start_d1, user_start_d2);
    } while (comp_start_sum == user_start_sum);

    user_starts = (user_start_sum > comp_start_sum);

    do
    {
        printf("How many rounds would you like to play? ");
        scanf("%d", &n);

        if (n < 1 || n > 11)
        {
            printf("%d is an invalid number of rounds, maximum valid number of rounds is 11. Try Again.\n", n);
        }
    } while (n < 1 || n > 11);

    while (round <= n)
    {
        int target = round + 1;

        if (user_starts)
        {
            printf("\nRound %d -- Your Turn: (Target = %d)\n", round, target);
            user_round_score = play_user(target);
            user_total += user_round_score;

            printf("\nRound %d -- My Turn: (Target = %d)\n", round, target);
            comp_round_score = play_computer(target);
            comp_total += comp_round_score;
        }
        else
        {
            printf("\nRound %d -- My Turn: (Target = %d)\n", round, target);
            comp_round_score = play_computer(target);
            comp_total += comp_round_score;

            printf("\nRound %d -- Your Turn: (Target = %d)\n", round, target);
            user_round_score = play_user(target);
            user_total += user_round_score;
        }

        printf("\nOur scoresheet after round %d:\n", round);
        scoresheet(comp_total, user_total);

        round++;
    }

    printf("\n");
    if (user_total > comp_total)
    {
        printf("YOU ARE THE WINNER!!\n");
    }
    else if (comp_total > user_total)
    {
        printf("I AM THE WINNER!!\n");
    }
    else
    {
        printf("NO WINNER FOR THIS GAME!\n");
    }

    return 0;
}