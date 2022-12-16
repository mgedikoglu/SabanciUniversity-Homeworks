#FIRST INPUT

while True:
	products=input("Products in shopping cart: ")
	if products.count("_")>=4 and products.count("_")%4==0 and products.count("_")==(products.count(",")+1)*4:
		products=products.split(",")
		product_specs=["name","quantity", "fat", "carbohydrate", "protein"]
		product_values=[]
		for product in products:
			product_ls=product.split("_")
			product_dict=dict(zip(product_specs,product_ls))
			product_values.append(product_dict)
		break
	else:
		print("Invalid input for products, please enter in correct format.")
		continue


#SECOND INPUT

while True:
	members=input("Family members' informations: ")
	if members.count("_")>=3 and members.count("_")%3==0 and members.count("_") == (members.count(",")+1)*3:
		members=members.split(",")
		member_specs=["gender", "weight", "height", "age"]
		member_values=[]
		for member in members:
			member_ls=member.split("_")
			member_dict=dict(zip(member_specs,member_ls))
			member_values.append(member_dict)
		break
	else:
		print("Invalid input for family information, please enter in correct format.")
		continue

#CALCULATION

#fat

fat=0
for x in product_values:
	fat+=int(x["fat"])*int(x["quantity"])*9

#carbohydrate

carbohydrate=0
for x in product_values:
	carbohydrate+=int(x["carbohydrate"])*int(x["quantity"])*4

#protein

protein=0
for x in product_values:
	protein+=int(x["protein"])*int(x["quantity"])*4

#BEE
bee=0
for x in member_values:
	if x["gender"]=="M":
		bee+=66.5+13.8*int(x["weight"])+5.0*int(x["height"])-6.8*int(x["age"])
	elif x["gender"]=="F":
		bee+=655.1+9.6*int(x["weight"])+1.9*int(x["height"])-4.7*int(x["age"])


#FINAL
daily_fat=int(fat/(bee*0.3))
daily_carbohydrate=int(carbohydrate/(bee*0.5))
daily_protein=int(protein/(bee*0.2))


if daily_fat>0:
	print(f"These products will be enough for your family in terms of fat for {daily_fat} days.")
else:
	print("You need to add products with more fat to your shopping cart.")

if daily_carbohydrate>0:
	print(f"These products will be enough for your family in terms of carbohydrate for {daily_carbohydrate} days.")
else:
	print("You need to add products with more carb to your shopping cart.")

if daily_protein>0:
	print(f"These products will be enough for your family in terms of protein for {daily_protein} days.")
else:
	print("You need to add products with more protein to your shopping cart.")













