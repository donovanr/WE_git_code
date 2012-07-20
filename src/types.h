typedef struct {
  int numb;
  double coord;  /* distinguishing coordinate */
  double prob;  /* probability */
  int tb0;  /* start time for transition time */
  double distA;
  double distB;
} particle;

typedef struct {
  int i;
  int j;
} excessfile;
