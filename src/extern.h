double leftb,rightb,mmratio; //left and right borarders and maximun, minimum probability ratio
double wbin,pbin[MAX_N_BIN]; //wbin: width of bin, pbin[]: position of the bars to cut the space into bins
double startstate,endstate; //start and end states
double prob_success; //probability that has reached success state and been removed
int nbin,nallpar,npar[MAX_N_BIN],tmpnpar[MAX_N_BIN],isnapshot;
int nspecies;
int coord_ind;
size_t state_size;
particle par[MAX_N_BIN][MAX_N_PAR],tmppar[MAX_N_BIN][MAX_N_PAR]; //particle information
//kuwahara *rx_states; //lots of memory could be used here...
//kuwahara empt_state;// = {0, 0, 0, 0, 0, 0};
int **rx_states;
char **species_names;
char bngl_name[30]; //Max BNGL file name length is 25
int Fava[MAX_ALL_PAR];
excessfile Fexc[MAX_ALL_PAR];
