to use this code:

- cd to the src directory and issue make to compile the source
- cd to the bng_scripts directory and edit setenv.sh to set the path to your installation of BioNetGen (needs version 2.2.0-stable), and the run_network executable that will work on your system
- run WE from the main folder (where WE_main is) using the runWE.sh script.  there are a few example systems included in the input folder. usage:

    ./runWE.sh input/model.input > model.snapshot

if you don't redirect the output to a snapshot file, the output will be to STDOUT, ie the terminal screen.  there is a lot of output, so watch out.
- the snapshot file lists the status of the system at each time step, in terms of the progress coordinate.
- to view the progress of the WE run, check the err.log file.