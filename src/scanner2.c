#include <stdio.h>
#include <string.h>

int main (){

  double a;
  char c;
  FILE* fp;
  //char buffer[256];

  //scanf("%*d %*s %f",&b2);
  //is2 = (int)s2;
  fp=fopen("foo", "r");
  //fscanf(fp, "%*s %*s %*s");
  while((c=fgetc(fp)) != '\n') {}//skip line
  while((c=fgetc(fp)) != '\n') {}//skip line
  fscanf(fp,"%*e %lf", &a);
  fclose(fp);
  printf("I just read: %f aka %d", a, (int)a);
}
