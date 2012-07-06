#include <stdio.h>
#include <string.h>

int main (){

  double e1, s1, b1, e2, s2, b2;
  int is2;
  FILE* fp;

  scanf("%*s %*s");
  scanf("%*d %*s %f",&e1);
  scanf("%*d %*s %f",&s1);
  scanf("%*d %*s %f",&b1);
  scanf("%*d %*s %f",&e2);
  scanf("%*d %*s %f",&s2);
  scanf("%*d %*s %f",&b2);
  is2 = (int)s2;

  fp=fopen("foo", "w");
  fprintf(fp,"Found: %d, %d, %d, %d, %e, %d\n",(int)e1, (int)s1, (int)b1,
          (int)e2, (double)is2, (int)b2);
  fclose(fp);

}
