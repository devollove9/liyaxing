#
# Project #4
#

proj04:  proj04.driver.o proj04.support.o
	gcc -lm -o proj04 proj04.driver.o proj04.support.o /user/cse320/lib/bitlib.o 
	
proj04.driver.o: proj04.driver.c /user/cse320/Projects/project04.support.h
	gcc -Wall -c -g proj04.driver.c    	    
	
proj04.support.o: proj04.support.c /user/cse320/Projects/project04.support.h      	 
	 gcc -Wall -c -g proj04.support.c -o proj04.support.o    	

clean:
	

