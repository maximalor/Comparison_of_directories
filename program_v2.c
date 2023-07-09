#include <dirent.h>
#include <errno.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MY_DIRENT struct my_dirent

MY_DIRENT
{char file_name[100];
 int file_size;
 MY_DIRENT *next;
 MY_DIRENT *back;
};

MY_DIRENT*Add(MY_DIRENT *p,char d_name[100],char name_of_d[100])
{MY_DIRENT *head;
 head=(MY_DIRENT*)malloc(sizeof(MY_DIRENT));
 if(!p){
    head->back=NULL;
    head->next=NULL;
  }
 else
  {head->back=p;
   p->next=head;
   head->next=NULL;
  }
 strcpy(head->file_name,name_of_d);
 strcat(head->file_name,d_name);
 return head;
}

int proverka(MY_DIRENT*p1,MY_DIRENT*p2)
{FILE *f1,*f2;
int symbol1,symbol2;

f1=fopen(p1->file_name,"r");
f2=fopen(p2->file_name,"r");

if((f1)&&(f2)){
  do{
    symbol1=fgetc(f1);
    symbol2=fgetc(f2);

    if (symbol1!=symbol2){
      fclose(f1);
      fclose(f2);
      return 0;
      }

    if ((symbol1==EOF)&&(symbol2==EOF)){
     fclose(f1);
     fclose(f2);
     return 1;
     }
    if ((symbol1==EOF)&&(symbol2!=EOF)){
     fclose(f1);
     fclose(f2);
     return 0;
     }
    if ((symbol1!=EOF)&&(symbol2==EOF)){
     fclose(f1);
     fclose(f2);
     return 0;
     }
  }while(1);
}
else return 0;
}

int izmerenie(char file_name[100])
{FILE *f;
 int symbol,file_size=0;

 f=fopen(file_name,"r");

 if(f){
   do{
    symbol=fgetc(f);
    file_size++;
   }while(symbol!=EOF);
 }
 else return 0;

 return file_size;
}

void prn(MY_DIRENT*head)
{MY_DIRENT *p=head;
 while(p)
  { printf("%s \n",p->file_name);
    p=p->back;
  }
}


int main(void)
{
MY_DIRENT *p1=NULL,*p2=NULL,*head;
struct dirent* file_info;
DIR *direct_1, *direct_2;
int FLAG;
double sum1=0,sum2=0,size_sum1=0,size_sum2=0,sum_of_similar_files=0,size_of_similar_files=0;
char d_name_1[100],d_name_2[100];

printf("Vibirete rezhim:\n ");
printf(" 1- sravnenie po kolichestvu odinakovih failov\n ");
printf(" 2- sravnenie po sumarnomu objomu odinakovih failov\n ");
scanf("%d",&FLAG);

printf("\n Vvedite pervuju directoriju:\n ");
scanf("%s",d_name_1);
strcat(d_name_1,"\\"); 

printf("\n Vvedite vtoruju directoriju:\n ");
scanf("%s",d_name_2);
strcat(d_name_2,"\\"); 

if (((direct_1=opendir(d_name_1))!=NULL)&&((direct_2=opendir(d_name_2))!=NULL))
{
 while((file_info=readdir(direct_1)) != 0)
    { p1=Add(p1,file_info->d_name,d_name_1);
      p1->file_size=izmerenie(p1->file_name);
      size_sum1+=p1->file_size;
      sum1++;
    }

 while((file_info=readdir(direct_2)) != 0)
    { p2=Add(p2,file_info->d_name,d_name_2);
      p2->file_size=izmerenie(p2->file_name);
      size_sum2+=p2->file_size;
      sum2++;
    }
}

prn(p1);
printf("////////////////////////\n");
prn(p2);


if (FLAG==1){

  sum2=sum2-2;
  sum1=sum1-2;
  if (sum2>sum1)
  { sum_of_similar_files=sum1;
    sum1=sum2;
    sum2=sum_of_similar_files;
  }
  sum_of_similar_files=0;

  if ((sum2/sum1*100)<95)
  {
      printf("\nDirectories aren`t similar \n");
      return 0;
  }
  else
  {while(p1)
    {head=p2;
     while(head)
       {
         if(proverka(p1,head)==1)
           {strcpy(head->file_name,"");
            sum_of_similar_files++;
            head=head->back;
           }
          else head=head->back;
       }
     p1=p1->back;
    }
  }

  if ((sum_of_similar_files/sum1*100)<95)
  {   
      printf("\nDirectories aren`t similar \n");
      return 0;
  }
  else
  { 
     printf("\nDirectories are similar \n");
     return 0;
  }
}
else
{
  if (size_sum2>size_sum1)
  { size_of_similar_files=sum1;
    size_sum1=size_sum2;
    size_sum2=size_of_similar_files;
  }
  size_of_similar_files=0;

  if ((size_sum2/size_sum1*100)<95)
  {   
      printf("\nDirectories aren`t similar \n");
      return 0;
  }
  else
    {while(p1)
      {head=p2;
       while(head)
         {
           if(proverka(p1,head)==1)
             {strcpy(head->file_name,"");
              size_of_similar_files+=head->file_size;
              head=head->back;
             }
            else head=head->back;
         }
        p1=p1->back;
      }
    }

  if ((size_of_similar_files/size_sum1*100)<95)
  {   
      printf("\nDirectories aren`t similar \n");
      return 0;
  }
  else
  {  
     printf("\nDirectories are similar \n");
     return 0;
  }
}

}
