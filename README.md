# Monopoly Cheat

This project was developed as a final assignment for a course of Evolutionary Algorithms at the University of São Paulo. It consists of a genetic algorithm designed to determine the optimal strategy to a Monopoly-like game.

## Execution
* `make all`: compiles entire AG code
* `make run`: compiles changed .cpp files and runs the program. Two files are generated in /results: best.log and init_values.log
* `make clean`: cleans .o files and /obj folder
* `make log`: runs Python script to plot results (given that best.log) exists in /results
* `make clr-log`: clears .log files from /results
* `make clr-results`: clears .png files from /results
* `make val`: runs program with Valgrind

## Configuring the AG
The main parameters for running the AG are found in *agmanager.h*:
* **PLAYERS_PER_ROUND** *(2 to 6)*: determines how many players play per turn (Monopoly allows from 2 up to 6 players).
* **MAX_PLAYERS** *(unrestricted)*: max number of generated individuals. Increasing this number can greatly affect execution time, given that the number of executions is determined by a combination of MAX_PLAYERS with PLAYERS_PER_ROUND.
* **N_GENERATIONS** *(unrestricted)*: max number of generations run by the AG.
* **MUTATION** *(0 to 100)*: mutation percentage applied by the AG.

## Configuring plot options
Plotting the results is handled by *plot_results.py*. Each defined plot function takes an argument *opt* = {'save', 'show'}. Other parameters should be handled by the code.

## Results
Uploaded results to the /results folder in this repo are coded as following:
* **mutXXpprYY:** XX% mutation chance; YY players per round (each game contains YY players)
* **genXXmaxYY-vZZ**: XX number of generations; YY number of players (individuals) generated; ZZ version

## Developers
Lucas Tognoli: https://github.com/LucasTognoli
Henrique Grando: https://github.com/henriquegrando
Jéssica Aissa: https://github.com/deadalley

## References
* https://www.youtube.com/watch?v=ubQXz5RBBtU
* https://www.dropbox.com/s/sme0ezqsb69yg7k/Hannah-monopoly-plots.pdf?dl=0
* http://monopoly.cdbpdx.com/DPBB3/
* https://d33i9xhtscn2ox.cloudfront.net/images/00009-02.jpg
