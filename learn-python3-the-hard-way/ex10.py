# ex.10
# print("age?", end=' ')
# age = input()
# print("height?", end=' ')
# height = input()
# print("weight?", end=' ')
# weight = input()
# print(f"So, age is {age}, height is {height} and weight is {weight}")


# ex.12
# age = input('age? ')
# height = input('height? ')
# weight = input('weight? ')
# print(f"So, age is {age}, height is {height} and weight is {weight}")

# # LearnXinYminutes: Python
# print('-5 // 2 ', -5 // 2)
# print('-5 // 3.0 ', -5 // 3.0)
# print('-7 % 3 ', -7 % 3)
# print('2**3 ', 2**3)
# print('not False: ', not False)
# print('bool(0) ', bool(0))
# print('bool(-6) ', bool(-6))
# print('0 and 3 ', 0 and 3)


# ex.13
# from sys import argv
# script, first, second, third = argv
# print('the script is called: ', script)
# print('your first variable is: ', first)
# print('your second variable is: ', second)
# print('your third variable is: ', third)


# ex.14
from sys import argv

script, user_name = argv
prompt = '>'

print(f"hi {user_name}, I'm the {script} script")
print("my questions:")
print(f"do you like me, {user_name}?")
likes = input(prompt)

print(f"where do you live, {user_name}?")
lives = input(prompt)

print(f"what's your computer, {user_name}?")
computer = input(prompt)

print(f"""
You said {likes} about me.
You live in {lives}.
You have a {computer} computer.
""")


