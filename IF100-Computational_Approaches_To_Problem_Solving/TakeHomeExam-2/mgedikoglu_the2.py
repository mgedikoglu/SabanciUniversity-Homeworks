term=input("Please enter your current term: ")

if term.isdigit()==True:
	term=int(term)


	if term >=1:
		
		if term==1:
			print("Your Erasmus score cannot be calculated before the 2nd term.")
			quit()
		elif term>=2:
			credit=input("Please enter the total credits you earned before: ")
			if credit.isdigit()==True:
				credit=int(credit)
				
				if term==2:
					if credit>=34:
						True
					else:
						print("Your Erasmus score cannot be calculated before you took the required amount of credits.")
						quit()
				elif term==3:
					if credit>=49:
						True
					else:
						print("Your Erasmus score cannot be calculated before you took the required amount of credits.")
						quit()
				elif term>3:
					if credit>=58:
						True
					else:
						print("Your Erasmus score cannot be calculated before you took the required amount of credits.")
						quit()

			else:
				print("Invalid input for the credits earned before.")
				quit()

	else:
		print("Invalid input for the current term.")
		quit()


else:
	print("Invalid input for the current term.")
	quit()





"""----------SPS101----------"""


sps_letter=input("Please enter the SPS101 letter grade equivalents: ").upper()

if sps_letter[0] == ":" or sps_letter[-1] == ":" or sps_letter[0]== ";" or sps_letter[-1] == ";" or sps_letter.count(":") != sps_letter.count(";")+1:
	print("Invalid input for SPS101 letter grade sequence.")
	quit()



sps_letter_ls=sps_letter.split(";")
a=[]

"""Splits the string items in sps_letter_ls and add them to another list""" 

for x in sps_letter_ls:
	for y in x.split(":"):
		a.append(y)

"""Makes every following item a dictionary to access them easier for next step"""

for x in a:
	sps_dict={a[i]:a[i+1] for i in range(0,len(a)-1,2)}







"""----------AL102----------"""


al_letter=input("Please enter the AL102 letter grade equivalents: ").upper()

if al_letter[0] == ":" or al_letter[-1] == ":" or al_letter[0]== ";" or al_letter[-1] == ";" or al_letter.count(":") != al_letter.count(";")+1:
	print("Invalid input for AL102 letter grade sequence.")
	quit()


al_letter_ls=al_letter.split(";")
c=[]

"""Splits the string items in al_letter_ls and add them to another list""" 

for x in al_letter_ls:
	for y in x.split(":"):
		c.append(y)

"""Makes every following item a dictionary to access them easier for next step"""

for x in c:
	al_dict={c[i]:c[i+1] for i in range(0,len(c)-1,2)}





"""--------Grades--------"""

grades=input("Please enter your SPS101 and AL102 letter grades: ").upper()

if grades.count(",")!=1:
	print("Invalid input for SPS101 and AL102 letter grades.")
	quit()


grades_ls=grades.split(",")


if "-" in grades_ls:
	al_dict.update({"-":al_dict["C"]})


if not grades_ls[0] in sps_dict.keys():
	print("Your SPS101 letter grade couldn't be found in point-scale.")
	quit()

if not grades_ls[1] in al_dict.keys():
	print("Your AL102 letter grade couldn't be found in point-scale.")
	quit()




"""----------GPA---------"""


gpa=float(input("Please enter your current GPA: "))

if not gpa >=0 and gpa<=4:
	print("Your GPA needs to be in between 0-4.")
	quit()

if gpa<2.2:
	print("Your GPA needs to be at least 2.2.")
	quit()



"""-------------FINAL MATH PART-------------"""


sps_point=int(sps_dict[grades_ls[0]])

al_point=int(al_dict[grades_ls[1]])

english_score=(sps_point*0.4)+(al_point*0.6)
erasmus_score=(english_score*0.5)+(gpa*25*0.5)

print(f"Your final Erasmus score is, {erasmus_score}.")
















