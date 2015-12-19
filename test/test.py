import json
import sys
from pprint import pprint
f = open(str(sys.argv[2]), "w")
with open(str(sys.argv[1])) as data_file:    
	data = json.load(data_file)
i=0
s=""
while True:
	try:
		s=data[i]["link"][0]
		print s
		f.write(s+"\n")
		i=i+1
	except IndexError:
		break
#print(data)
print s  # will return 'blabla'
f.close()
print str(sys.argv[1])
print str(sys.argv[2])
