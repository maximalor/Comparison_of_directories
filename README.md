# my_project
Программа для нахождения дублирующихся директорий. Должна находить не только полные дубликаты, но и частичные (например, совпадают 95% файлов по количеству или 95% по суммарному объёму).

Описание: на вход программе дается две дирректории, если файлы в них совпадают на 95% или более, то сообщить об этом

Пример эксперементальной программы для сравнения двух файлов на идентичность.

  #include <stdio.h>
  #include <stdlib.h>
int main()
{ FILE *f1,*f2;
  int sym1,sym2,flag=1;
  
  f1=fopen("C:/Users/Max/Documents/test1/no_experiments1.jpg","r");  // файл no_experiments1.jpg из директории test1
  f2=fopen("C:/Users/Max/Documents/test2/1438463060538.jpg","r");    // файл 1438463060538.jpg из директории test2

  do{
    sym1=fgetc(f1);
    sym2=fgetc(f2);
    
    if (sym1!=sym2){
      printf("files different \n");
      flag=0;
      }

    if ((sym1==EOF)&&(sym2==EOF)){
       flag=0;
       printf("files the same \n");
       }
    if ((sym1==EOF)&&(sym2!=EOF)){
       flag=0;
       printf("files different \n");
       }
    if ((sym1!=EOF)&&(sym2==EOF)){
       flag=0;
       printf("files different \n");
       }

  }while(flag==1);
  
  fclose(f1);
  fclose(f2);
    return 0;
}
