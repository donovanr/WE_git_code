#!/bin/bash

# usage: run from directory where your in-progress modelname.snapshot file is.
# syntax: ./tools/status modelname.snapshot

MODELNAME=$(basename "$1" .snapshot)

N_ALL_PAR=$(grep nallpar input/${MODELNAME}.input | awk '{print $2}')
N_BIN=$(grep nbin input/${MODELNAME}.input | awk '{print $2}')
N_PAR=$(($N_ALL_PAR / $N_BIN))

# print the snapshot number and the weight of a particle in each bin in the most recently completed snapshot
sed -n 'H; /^snapshot/h; ${g;p;}' ${MODELNAME}.snapshot | awk -v Npar=$N_PAR 'NR%Npar==1'
