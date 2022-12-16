file=open("scores.txt","r")
a=file.readlines()
file.close()

b=[]
for x in a:
	x=x.strip("\n")
	b.append(x)

points={}
for match in b:
	matchls=match.split(" ")
	team1=matchls[0]
	team2=matchls[3]
	score1=matchls[1]
	score2=matchls[2]

	if team1 not in points:
		points[team1]=0
	if team2 not in points:
		points[team2]=0
	
	if score1>score2:
		points[team1]+=3
	elif score1<score2:
		points[team2]+=3
	elif score1==score2:
		points[team1]+=1
		points[team2]+=1

val_list=[]
print("TeamName\tPTS")

for v in points.values():
	val_list.append(v)

val_list.sort(reverse=True)

for val in val_list:
	for k in points:
		if points[k]==val:
			print(f"{k}\t{val}")







