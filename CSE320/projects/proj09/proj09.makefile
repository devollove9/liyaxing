proj09:  proj09.support.s /user/cse320/Projects/project09.driver.o /user/cse320/lib/reglib.o
	gcc proj09.support.s /user/cse320/Projects/project09.driver.o /user/cse320/lib/reglib.o -o proj09 

clean:
	rm -f proj09 proj09.*.o
