import random
with open("READ_REQUESTS.txt" ,"a+") as read_request_file:
	for i in range (5000):
		read_request_file.write("../temp/file" + str(random.randrange(0,10000)) + ".txt" + " read " + str(random.randrange(0,10)* i) +  "\n")


