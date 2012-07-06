//Added by AJ
typedef struct {
  int E1, S1, B1, E2, S2, B2;
  //int par_num;
} kuwahara;

typedef struct {
  int numb;
  double coord;  //distinguishing coordinate
  double prob;  //probability
  int tb0;  //start time for transition time
  double distA;
  double distB;
} particle;

typedef struct {
  int i;
  int j;
} excessfile;
