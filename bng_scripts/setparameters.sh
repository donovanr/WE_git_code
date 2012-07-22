#!/bin/bash

# this script sets parameters for restart.sh.  it is a separate scripts so that
# the grep etc calls are only made once each round, rather than for each
# particle
#
# usage: "./restart.sh xxx.bngl"
#
# where xxx.bngl is the BNG model set to run for N_BNG_STEPS steps
# with interval DT between them.

# base name of the model
MODEL_NAME=`basename "$1" .bngl`

# number of steps we let BNG run until start/stop
# this is set by "n_steps" in the bngl file of the BNG model
N_BNG_STEPS=$(cat ${MODEL_NAME}.bngl | grep 'n_steps=>' | cut -f4 -d '>' | cut -f1 -d ',')

# time step DT of BNG simulation in seconds
# these values are set in the bngl file of the BNG model
T_START=$(grep -Po 't_start=>\K.*?(?=,)' ${MODEL_NAME}.bngl)
T_END=$(grep -Po 't_end=>\K.*?(?=,)' ${MODEL_NAME}.bngl)
DT=$(echo "scale=5; ($T_END - $T_START)/$N_BNG_STEPS" | bc)

# load up BNG Path and which run_network binary to use
. setenv.sh

# expand the variables for the BNG call and save them to a file that restart.sh can steal
echo "${BNG_PATH}/bin/${RUN_NETWORK} -o ${MODEL_NAME} -p ssa -h"' $RANDOM'" -a 1e-8 -r 1e-8 -e -g "'./my_State ./my_State'" ${DT} ${N_BNG_STEPS}" > bngcall.sh
chmod +x bngcall.sh

# expand the variables for the cp call and save to a txt file for restart.sh
echo "cp ${MODEL_NAME}_end.net" 'my_State' > cpmodel.sh
chmod +x cpmodel.sh