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

# BioNetGen Path
BNG_PATH=/Users/ajsedgewick/BioNetGen-2.2.0-stable
MODEL_NAME=`basename "$1" .bngl`

#########################
# actually do the thing #
#########################

# invoke BNG to run the model once and generate .net and .gdat files
${BNG_PATH}/BNG2.pl $1 > /dev/null

sed -n '/begin species/,/end species/w initial-species' ${MODEL_NAME}.net
sed -n '/begin parameters/,/end parameters/w parameters' ${MODEL_NAME}.net
sed -n '/begin reactions/,/end reactions/w reactions' ${MODEL_NAME}.net

# gdat stuff
sed -n '/begin groups/,/end groups/w groups' ${MODEL_NAME}.net
mv ${MODEL_NAME}.gdat initial-gdat 
# ffuts tadg