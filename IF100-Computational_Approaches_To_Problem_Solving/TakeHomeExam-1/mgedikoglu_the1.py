'''Inputs'''
door = int(input("Please enter the number of digits in padd-lock: "))
computer = int(input("Please enter the password length of the PC: "))
data = float(input("Please enter the file size you want to transfer (GB): "))

'''Calculating the need time for every input and total time'''
door_time = (10 ** door) / 1000
computer_time = (14 ** computer) / 600000
data_time = (data * 1024) / 60
second = door_time + computer_time + data_time

'''Converting second to hour, minute and second '''
hour = second // (60*60)
second %= (60*60)
minute = second // 60
second %= 60

print("You need to distract the guard's attention for",int(hour), "hour(s),", int(minute) , "minute(s) and", format(second, ".2f") , "second(s).")
