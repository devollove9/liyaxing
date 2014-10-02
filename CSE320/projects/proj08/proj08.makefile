proj08:  proj08.support.s proj08.driver.c /user/cse320/lib/reglib.o
	gcc proj08.support.s proj08.driver.c -o proj08 

clean:
	rm -f proj08 proj08.*.o
