#!/bin/bash

# this script runs BNG with run_network, starting at "initial_state".  it runs
# for one step of ssa, overwrites the old end.net file, and copies the new
# rnd.net file over the initial_state file.
#
# usage: "./restart.sh xxx.bngl initial_state"
#
# where xxx.bngl is the BNG model set to run for N_BNG_STEPS steps
# with interval DT between them.


#####################
# actually do stuff #
#####################


# call run_network to run the model for N_BNG_STEPS of size DT,
# restarting from the saved end.net file
./bngcall.sh > /dev/null
wait

# copy new end.net file (it gets overwritten by BNG) to old input data file
./cpmodel.sh

