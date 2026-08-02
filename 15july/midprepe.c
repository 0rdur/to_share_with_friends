#include <stdio.h>
// the code is incomplete and only does the job of the first menu
int main()
{
    int id[10] = {111,222,333,444,555,666,777,888,999,1000};
    char guest[10][100];
    int room[10] = {1,1,1,2,2,2,2,3,3,3};
    // 1 means single, 2 double and 3 suite

    char date[10][20];
    int rent[10] = {500,500,500,1000,1000,1000,1000,1500,1500,1500};
    int occu[10] = {0};

    char menu, check, proceed;
    int no;

    do
    {
        printf("Press c to add a new reservation.\n");
        printf("Press q to quit.\n");

        scanf(" %c", &menu);

        if(menu == 'c')
        {
            printf("What type of room would you like?\n");
            printf("Press a for single, b for double and p for suite\n");

            scanf(" %c", &check);

            if(check == 'a')
            {
                for(int i = 0; i < 3; i++)
                {
                    if(occu[i] == 0)
                        printf("Room no %d is free\n", i+1);
                    else
                        printf("Room no %d is occupied\n", i+1);
                }
            }

            if(check == 'b')
            {
                for(int i = 3; i < 7; i++)
                {
                    if(occu[i] == 0)
                        printf("Room no %d is free\n", i+1);
                    else
                        printf("Room no %d is occupied\n", i+1);
                }
            }

            if(check == 'p')
            {
                for(int i = 7; i < 10; i++)
                {
                    if(occu[i] == 0)
                        printf("Room no %d is free\n", i+1);
                    else
                        printf("Room no %d is occupied\n", i+1);
                }
            }

            printf("Enter the room number you would like: ");
            scanf("%d", &no);

            if(no >= 0 && no < 10)
            {
                printf("Your rent will be %d\n", rent[no]);
                printf("Proceed? Enter Y for yes: ");
                scanf(" %c", &proceed);

                if(proceed == 'Y')
                {
                    printf("You have chosen room %d\n", no);
                    printf("Your reservation ID is %d\n", id[no]);
                    occu[no] = 1;
                }
            }
        }

    } while(menu != 'q');

    return 0;
}

