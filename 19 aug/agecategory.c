#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void columncounter(char *line, int target_col, char *output, int max){
    int current_col=0;
    int no_comma=0;
    int index=0;

    for (int i = 0; line[i] != '\0'; i++){
        char c = line[i];

        if (c=='"') no_comma=!no_comma;

        else if (c ==',' && !no_comma){
            if (current_col==target_col) break;
            current_col++;
            index=0;
        }

        else if (current_col==target_col){
            if (index<max - 1) output[index++] = c;
        }
    }
    output[index]='\0';
}

int differal(int age){
  if(0<=age && age<=18) return 1;
  else if(age<=40) return 2;
  else if(age>40) return 3;
}

int main()
{   printf("missing ages were taken as 0 and categorized into 1st age category\n");
    FILE *fp=fopen("titanic.csv", "r");

    if (fp==NULL){
        printf("ERROR\n");
        return 1;
    }

    char line[2000];

    FILE *fout = fopen("newdata.csv","w");
    fclose(fout);
    fout=fopen("newdata.csv","a");

    fgets(line, sizeof(line),fp);

    line[strcspn(line,"\r\n")]='\0';
    fprintf(fout,"%s,age_category\n",line);

    while (fgets(line,sizeof(line),fp)){
        line[strcspn(line,"\r\n")]='\0';
        char boyosh[10];
        columncounter(line,5,boyosh,sizeof(boyosh));

        int age=atoi(boyosh);
        int category=differal(age);

        
        fprintf(fout,"%s,%d\n",line,category);

    }

    fclose(fp);
    fclose(fout);

    return 0;
}
