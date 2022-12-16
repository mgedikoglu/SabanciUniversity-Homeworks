number=int(input("Please enter the number of values to be entered: "))

names=[]
years=[]
for x in range(number):
	name=input("Please enter a name: ")
	year=int(input(f"Please enter {name}'s' birth year: "))
	names.append(name)
	years.append(year)

a=years.index(min(years))
oldest=names[a]
print(f"The oldest person is {oldest}")
