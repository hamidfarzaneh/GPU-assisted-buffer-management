with open(".gitignore" ,"a+") as gitIgnoreFile:
	for i in range (10000):
		gitIgnoreFile.write("./temp/file" + str(i) + ".txt" + "\n")


