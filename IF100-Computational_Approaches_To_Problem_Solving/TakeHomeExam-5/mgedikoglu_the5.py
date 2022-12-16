#Mustafa Enes Gedikoglu 27779

def levenshtein(str1, str2):
  size_x = len(str1) + 1
  size_y = len(str2) + 1
  matrix = []
  for i in range(size_x):
    temp = [0]*size_y
    matrix.append(temp)
  for i in range(size_x):
    matrix[i][0] = i
  for i in range(size_y):
    matrix[0][i] = i
  for x in range(1, size_x):
      for y in range(1, size_y):
          if str1[x-1] == str2[y-1]:
              matrix [x][y] = min(matrix[x-1][y] + 1, matrix[x-1][y-1], matrix[x][y-1] + 1)
          else:
            matrix [x][y] = min(matrix[x-1][y] + 1, matrix[x-1][y-1] + 1, matrix[x][y-1] + 1)
  return(matrix[size_x - 1][size_y - 1])

def wordcount(text):
  plain=""
  count={}
  for x in text:
    x=x.lower()
    x=x.strip(".,';:!?\n#\"\t")
    if x!=" ":
      plain+=x
    else:
      if plain in count:
        count[plain]+=1
        plain=""
      else:
        count[plain]=1
        plain=""
  return count

def min_levens(string,count):
  ls=[]
  for k in count:
    t=levenshtein(k,string)
    ls.append(t)
  return min(ls)

def new_dict(res,count):
  equal_dict={}
  for k,v in count.items():
    t=levenshtein(x,k)
    if t==res:
      equal_dict[k]=v
  return equal_dict

def last_one(res):
  ma_list=[]
  c=max(res.values())
  for k,v in res.items():
    if res[k]==c:
      ma_list.append(k)
  ma_list.sort()
  return ma_list

#----MAIN CODE----

file=open("book.txt","r")
countdict=wordcount(file.read())
file.close()

string=input("Please enter the word/words you want to check: ")
while string!="exit()":
  strink=string.split(" ")
  new_string=""
  for x in strink:
    a=min_levens(x,countdict)
    if a==0:
      new_string+=x+" "
    else:
      b=new_dict(a,countdict)
      c=last_one(b)
      new_string+=c[0]+" "
  new_string=new_string[:-1]
  if new_string == string:
    print("String you entered is correctly written!")
  else:
    print(f"Did you mean: {new_string}")
  string=input("Please enter the word/words you want to check: ")
else:
  print("See you next time...")

