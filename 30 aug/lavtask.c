#include<stdio.h>
typedef struct{
  int id;
  char name[100];
  float mid;
  float final;
  float total;
}*course_roaster;

int size(courseroaster *p){
  for(int i=0;i<150;i++){
    if(p[i]==NULL){break;}
  }
  return i;
}

void enterstudent(courseroaster *p){
  char c;
  int i=0;
  while(i<150){
  scanf("%c",&c);
  if(c=='q') break;
  scanf("%d",p->id);
  fgets(stdin,100,p->name);
  scanf("%f %f %f",&p->mid,&p->final,&p->total)
  
}

int main(){
  course_roaster student[150]=NULL;



}
