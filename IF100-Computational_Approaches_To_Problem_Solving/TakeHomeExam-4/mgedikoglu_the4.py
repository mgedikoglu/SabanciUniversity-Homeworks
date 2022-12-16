
def getPartyName(prompt,parties): #didnt check english character
	party=input(f"Please enter the name of the {prompt} party: ").capitalize()
	while party:
		if party[0].isalpha()==True and party not in parties and " " not in party:
			parties.append(party)
			break
		else:
			party=input("Invalid party name. Please enter again: ").capitalize()
			continue



def getMenuOption():
	print("Menu:\n1. Enter results for a new city.\n2. Change results of a specific city.\n3. Show current results.\n4. Exit.")
	selected=input("Select one of the options (1-4): ")
	return selected


def getNewResults(data):
	info=[]
	city=input("Pease enter the name of the city: ").capitalize()
	while city:
		if city.isalpha()==True and city not in data:
			info.append(city)
			break
		else:
			city=input("Invalid city name. Please enter again: ").capitalize()
			continue
	results=input(f"Please enter results for {city}: ")
	results=results.split("-")
	for x in results:
		info.append(x)
	data.append(info)
	print(data)
	getMenuOption()



def changeResults(data):
	changed_city=input("Pease enter the name of the city: ").capitalize()
	while changed_city:
		for x in data:
			if changed_city in x and changed_city.isalpha()==True:
				changed_result=input(f"Please enter results for {changed_city}: ").split("-")
				x[1]=changed_result[0]
				x[2]=changed_result[1]
				x[3]=changed_result[2]

			else:
				changed_city=input("Invalid city name. Please enter again: ").capitalize()
	getMenuOption()

def showResults(dataset,parties):
	for city in dataset:
		for x in range(1,len(city)):
			city[x]=float(city[x])
	winner=max(city)
	print(winner)
	
	getMenuOption()
	

"""	party2=input("Please enter the name of the second party: ").upper()
	while party2:
		if party2[0].isalpha()==True and party2 not in parties:
			parties.append(party2)
			break
		else:
			party2=input("Invalid party name. Please enter again: ").upper()
			continue
	party3=input("Please enter the name of the third party: ").upper()
	while party3:
		if party3[0].isalpha()==True and party3 not in parties:
			parties.append(party3)
			break
		else:
			party3=input("Invalid party name. Please enter again: ").upper()
			continue
getPartyName()"""



#############################
## DO NOT MODIFY THIS CELL ##
## JUST RUN THIS WHEN YOU COMPLETE YOUR FUNCTIONS ##
#############################
####### MAIN PROGRAM ########
#############################

print("Welcome to this virtual local elections Python program.\n")

# get the names of the parties
partyNames = []                               # stores the valid party names
promptData = ["first", "second", "third"]
for i in range(3):
  getPartyName(promptData[i], partyNames)

# dataset variable initialization
citiesAndResults = []                         # stores the city-results information

# display the menu, get user's option, and process accordingly
option = getMenuOption()
while option != "4":
  if option == "1":
    getNewResults(citiesAndResults)           # function call to update citiesAndResults with a new city
  elif option == "2":
   changeResults(citiesAndResults)            # function call to update citiesAndResults for an existing city
  elif option == "3":
    showResults(citiesAndResults, partyNames) # function call to display current election results
  option = getMenuOption()

print("**********\nTerminating, good bye dear citizen!!! Do not forget to vote in elections :)")
