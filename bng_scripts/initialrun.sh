#!/bin/bash

# usage:
#
# "./initialrun.sh xxx.bngl"
#
# where xxx.bngl is the BNG model.  this script will make all the net files etc
# needed for run_network to take over in the restart.sh script.

##################
# set parameters #
##################

# load up BNG Path and which run_network binary to use
. setenv.sh

MODEL_NAME=`basename "$1" .bngl`
. ./setparameters.sh $1


#########################
# actually do the thing #
#########################

# invoke BNG to run the model once and generate .net and .gdat files
${BNG_PATH}/BNG2.pl $1 2>/dev/null

# make a .net template file, that has all the info needed to restart thr system, except that it has (intentionally) a missing species block, that can be filled in on the fly
sed '/begin species/,/end species/d' ${MODEL_NAME}.net > template_no_species.net
wait

# make little files that contain the initial species and observables
sed -n '/begin species/,/end species/w initial-species' ${MODEL_NAME}.net
mv ${MODEL_NAME}.gdat initial-gdat 
