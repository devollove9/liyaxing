proj09:  proj10.support.s proj10.driver.o /user/cse320/lib/reglib.o
	gcc proj10.support.s proj10.driver.o /user/cse320/lib/reglib.o -o proj09 
proj10.driver.o:
	gcc -Wall proj10.driver.c
clean:
	rm -f proj10 proj10.*.o
