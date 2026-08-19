#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//serial in array
//arr[0] ded 1 alive der jonne
//0 to 8 male
//0 to 2 male but first class
//0 = 1st age category
//1 = 2nd age ....
//2 = 3rd age...
//evabe baki arrray. 3 to 5 2nd class,6 to 8 3rd _____
void columncounter(char *line, int target_col, char *output, int max){
    int current_col=0;
    int comma_no=0;
    int index=0;

    for(int i = 0; line[i] != '\0' && line[i] != '\n'; i++){
        char c = line[i];

        if(c=='"') comma_no=!comma_no;
        else if(c ==',' && !comma_no){
           if(current_col==target_col) break;
            current_col++;
            index=0;
        }

        else if(current_col==target_col){
            if(index<max-1) output[index++] = c;
        }
    }
     output[index] = '\0';
}

int main(){
    FILE *fp=fopen("newdata.csv", "r");
    int arr[2][18]={0};
    if (fp==NULL){
        printf("YOU DO NOT HAVE A FILE NAMED newdata.csv.\n YOU NEED TO RUN agecategory.c TO CREATE THAT\n");
        return 1;
    }
   
{   printf("here age category 1 is for 0 to 18,2 is or 18 to 40 and 3 is for 40 over years old\npeople with mising ages were counted into the 1st category\n\n\n");
    int alive,class,category;
    char line[1000];
    int genderdiff;
    int male=0, female=0;

    fgets(line, sizeof(line),fp);

    while (fgets(line,sizeof(line),fp))
    {
       char str_alive[10], str_class[10], str_sex[10], str_category[10];

         columncounter(line,1,str_alive,sizeof(str_alive));
         columncounter(line,2,str_class,sizeof(str_class));
         columncounter(line,4, str_sex,sizeof(str_sex));
         columncounter(line,12,str_category,sizeof(str_category));

        int alive=atoi(str_alive);
        int pclass=atoi(str_class);
        int category=atoi(str_category);

    
        if (strcmp(str_sex, "female") == 0) {
            genderdiff= 9;//array te female shuru hoise 9th index theke 
        }
        else if (strcmp(str_sex, "male") == 0) {
            genderdiff = 0;
        }
        else    continue;//jodi faka thake incase 
        

        int i= genderdiff+(pclass-1)*3+(category-1);

        arr[0][i]++;

        if (alive==1) arr[1][i]++;
  }


    /*for(int k=0;k<2;k++){
      for(int n=0;n<18;n++){
      printf("%d ",arr[k][n]);
    }
  }*/
    printf(" %-7s   %-6s  %-9s  %-7s    %-9s    %-13s \n", 
           "Gender", "pClass", "ageCategory", "Total", "alive", "Rate of survival");

    for (int i = 0; i < 18; i++) {
        char gen[20];
        if(i<9) strcpy(gen,"male");
        else strcpy(gen,"female");

        int calc=i%9;//gender bad dile ja thake
        int pclass=(calc/3)+1;//koto no class
        int category=(calc%3)+1;//koto no category
    //exp
    //index=8
    //mane, male,since<9
    //8%9=8
    //8/3 +1 = 2,so 3rd pclass
    //8%3 +1 = 3 so 3rd age category. 
    

        int total=arr[0][i];
        int alive=arr[1][i];

        double percentage=0.0;
        if (total>0) {
            percentage=((double)alive/total)*100.0;
        }

        printf("   %-9s  %-6d  %-9d  %-9d  %-9d  %12.2f%% \n", 
               gen,pclass,category,total,alive,percentage);
    }
}
    fclose(fp);

  
    return 0;
}
