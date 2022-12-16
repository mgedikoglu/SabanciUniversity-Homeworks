matrix = [[1,2,3,4], [2,4,6,8], [4,8,12,16], [8,16,24,32], [16,32,48,64]]

def subMatrix(listint,row,col):
	ls=[]
	listint=listint[-row:]
	for x in listint:
		a=x[-col:]
		ls.append(a)
	for y in ls:
		plain=""
		for x in y:
			plain+=str(x)+"\t"
		print(plain)

# MAIN CODE

rowNum=int(input("Enter rowNum: "))
colNum=int(input("Enter colNum: "))

while rowNum and colNum:
	if rowNum<=len(matrix) and colNum<=len(matrix[0]):
		subMatrix(matrix,rowNum,colNum)
		break
	else:
		print("rowNum and/or colNum number is too high!")
		rowNum=int(input("Enter rowNum: "))
		colNum=int(input("Enter colNum: "))




