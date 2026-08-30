#include <stdio.h>
#include <string.h>

typedef struct{
    int studentID;
    char studentName[101];

    float midtermMark;
    float finalMark;
    float totalMark;

} Student;

void prompt(Student *studentPtr)
{
    printf("Student ID: ");
    scanf("%d", &studentPtr->studentID);
    getchar();
    printf("Student Name: ");
    fgets(studentPtr->studentName,101,stdin);

    studentPtr->studentName[strcspn(studentPtr->studentName, "\n")] = '\0';

    printf("Midterm Mark: ");
    scanf("%f", &studentPtr->midtermMark);

    printf("Final Mark: ");
    scanf("%f", &studentPtr->finalMark);

    studentPtr->totalMark =studentPtr->midtermMark +studentPtr->finalMark;
}


void displayStudent(const Student *studentPtr)
{
    printf("\n");
    printf("Student ID   : %d\n", studentPtr->studentID);
    printf("Student Name : %s\n", studentPtr->studentName);
    printf("Midterm Mark : %.2f\n", studentPtr->midtermMark);
    printf("Final Mark   : %.2f\n", studentPtr->finalMark);
    printf("Total Mark   : %.2f\n", studentPtr->totalMark);
}


int findstudent(const Student roster[],int size,int search){
    int i;
    for (i = 0; i < size; i++){
        if (roster[i].studentID == search)
            return i;
    }

    return -1;
}


int findtop(const Student roster[],int size)
{
    int i;
    int top;
    if (size == 0)
        return -1;
    top = 0;
    for (i = 1; i < size; i++){
        if (roster[i].totalMark > roster[top].totalMark)
            top = i;
    }
    return top;
}


void displayroster(const Student roster[],int size){
    int i;
    if (size == 0){
        printf("\n nothing to shoow\n");
        return;
    }

    printf("\n========== FULL ROASTER ==========\n");

    for (i = 0; i < size; i++){
        printf("\nStudent %d:\n", i + 1);

        displayStudent(&roster[i]);
    }
}


int main(void){
    Student courseRoster[150];
    int rosterSize = 0;
    int choice;
    do{
        printf("\n");
        printf("              OPTIONS\n====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Full Roster\n");
        printf("3. Find Student by ID\n");
        printf("4. Show Top Student\n");
        printf("5. Quit\n");

        printf("Enter what you want to do by the numbers of the listed options: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:{
                int searchID;
                prompt(&courseRoster[rosterSize]);
                searchID = courseRoster[rosterSize].studentID;

                if (findstudent(courseRoster,rosterSize,searchID) != -1){
                    printf("he already exists");
                   // courseRoster[rosterSize]==NULL;
                    break;
                }
                rosterSize++;
                printf("adding done\n");
                break;
            }


            case 2:{
                displayroster(courseRoster,rosterSize);
                break;
            }

            case 3:{
                int search;
                int index;
 
                printf("Enter the id of the student you want to search ");
                scanf("%d",&search);

                index = findstudent(courseRoster,rosterSize,search);

                if (index == -1){
                    printf("student with ID %d was not found.\n",search);
                }
                else{
                    displayStudent(&courseRoster[index]);
                }
                break;
            }
            case 4:{
                int top;
                top = findtop(courseRoster,rosterSize);
                if (top== -1){
                    printf("Roster is empty. ");
                }
                else{
                    printf("\nTop Student:\n");

                    displayStudent(&courseRoster[top]);
                }
                break;
            }
            case 5:{
                break;
            }
            default:{
                printf("Invalid choice.\n");
            }
        }
    }
    while (choice != 5);
    return 0;
}
