CC=gcc
CFLAGS=-Wall -pedantic -I -g
LIBS=-lm
DEPS=WE_main.h extern.h types.h const.h
OBJ=Initial.o Assign.o Reassign_Weight.o Cal_Dist_Coord.o BF_Sim.o Min1.o Min2.o Max.o COMB.o SPLIT.o Put_Ini_Stru.o Make_Ghost.o Check_State_A.o Check_State_B.o Switch.o Print_Info.o WE_main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

WE_main: $(OBJ)
	gcc -o ../$@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o *~
