from random import shuffle

ouf = open("input.txt", "w")
A = list(range (1000))
shuffle(A)
for i in A:
	ouf.write("1 " + str(i) + "\n")
ouf.close()