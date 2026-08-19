#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void columnncounter(char *line, int target_col, char *output, int max_len)
{
    int current_col = 0;
    int in_quotes = 0;
    int out_idx = 0;

    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++){
        char c = line[i];

        if (c == '"') in_quotes = !in_quotes; 
        else if (c == ',' && !in_quotes){
            if (current_col == target_col) break;
            current_col++;
            out_idx = 0;
        }
        else if (current_col == target_col){
            if (out_idx < max_len - 1) output[out_idx++] = c;
        }
    }
    output[out_idx] = '\0';
}

int main()
{
    FILE *fp = fopen("titanic.csv", "r");

    if (fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    char line[1000];

    int male = 0, female = 0;
    int male_survived = 0, female_survived = 0;

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp))
    {
        char survived_str[10];
        char sex[10];

        columncounter(line, 1, survived_str, sizeof(survived_str));
        columncounter(line, 4, sex, sizeof(sex));

        int survived = atoi(survived_str);

        if (strcmp(sex, "male") == 0)
        {
            male++;
            if (survived == 1)
                male_survived++;
        }
        else if (strcmp(sex, "female") == 0)
        {
            female++;
            if (survived == 1)
                female_survived++;
        }
    }

    fclose(fp);

    printf("Male: %d\n", male);
    printf("Male survived: %d\n", male_survived);
    printf("Female: %d\n", female);
    printf("Female survived: %d\n", female_survived);

    printf("Male survival percentage: %.2f%%\n", (double)male_survived / male * 100);

    printf("Female survival percentage: %.2f%%\n", (double)female_survived / female * 100);

    return 0;
}

