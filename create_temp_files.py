for i in range (10000):
	with open("./temp/file" + str(i) + ".txt", "a+") as myfile:
		for j in range (i):
			myfile.write(str(j% 10)*128)
			myfile.write("\n");


