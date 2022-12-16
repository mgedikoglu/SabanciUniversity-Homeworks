ques=input("Do you have a problem in your life?: ").lower()
if ques=="yes":
	ques2=input("Can you do something about it?: ").lower()
	if ques2=="yes":
		print("Then do it")
	else:
		print("Then don't worry")
else:
	print("Then don't worry")