#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void columncounter(char *line, int target_col, char *output, int max){
    int current_col=0;
    int comma_no=0;
    int index=0;

    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++){
        char c = line[i];

        if (c=='"') comma_no=!comma_no;

        else if (c ==',' && !comma_no){
            if (current_col==target_col) break;
            current_col++;
            index=0;
        }

        else if (current_col==target_col){
            if (index<max-1) output[index++] = c;
        }
    }
    output[index]='\0';
}

int main()
{
    FILE *fp=fopen("titanic.csv", "r");

    if (fp==NULL){
        printf("ERROR\n");
        return 1;
    }

    char line[1000];

    int male=0, female=0;
    int male_survived=0,female_survived=0;

    fgets(line, sizeof(line),fp);

    while (fgets(line,sizeof(line),fp))
    {
        char survived_str[10];
        char sex[10];

        columncounter(line,1,survived_str,sizeof(survived_str));
        columncounter(line,4,sex,sizeof(sex));

        int survived=atoi(survived_str);

        if (strcmp(sex,"male") == 0){
            male++;
            if (survived==1)
                male_survived++;
        }
        else if (strcmp(sex,"female") == 0){
            female++;
            if (survived == 1)
                female_survived++;
        }
    }

    fclose(fp);

    printf("Male %d\n", male);
    printf("Male alive %d\n", male_survived);
    printf("Female %d\n", female);
    printf("Female alive %d\n", female_survived);

    printf("Male survival percentage: %f%%\n", (double)male_survived/male*100);

    printf("Female survival percentage: %f%%\n", (double)female_survived/female*100);

    return 0;
}
