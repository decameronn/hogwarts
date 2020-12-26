
# ex.1
print("I'd much rather you 'not'.")
print('I "said" do not.')

# ex.3
print("hens", 25 + 30 / 6)
print("roosters", 100 - 25 * 3 % 4)
# < has lower precedence than +/-. + first, - second, then comparison
# PEMDAS  PE(M&D)(A&S)
print(3.2 + 2.5 < 5 - 7)
print(5 >= -2.45)

# ex.4
cars_driven = 100
space_in_a_car = 3.5
capacity = cars_driven * space_in_a_car
print('capacity: ', capacity)

# ex.5
name = 'zed'
age = 39
height = 1.8
print(f"Let's talk about {name}.")
print(f"he's {age} years old.")
print("he's ", round(height), "m height.")
print("he's " + str(round(height)) + "m height.")


# ex.6
print('\n##### ex. 6')

types_of_ppl = 10
x = f"there are {types_of_ppl} types of people"
binary = 'binary'
do_not = "don't"
y = f"those who know {binary} and those who {do_not}"
print(x)
print(y)
print(f"I said: {x}")
print(f"I also said: '{y}' ")
hilarious = True
joke_eval = "Isn't that funny? {}"
print(joke_eval.format(hilarious))


# ex.7
print('\n##### ex. 7')

print("Mary had a little lamb")
print("its fleece was white as {}.".format('snow'))
print("And everywhere that mary went.")
print("." * 10)

end1 = "C"
end2 = "h"
end3 = "e"
end4 = "e"
end5 = "s"
end6 = "e"
end7 = "B"
end8 = "u"
end9 = "r"
end9 = "g"
end10 = "h"
end11 = "e"
end12 = "r"

# end=' ' removes \n it seems
print(end1 + end2 + end3 + end4 + end5 + end6, end=' ')
print(end7 + end8 + end9 + end10 + end11 + end12)


# ex.8
print('\n##### ex. 8')

formatter = "{} {} {} {}"
print(formatter.format(1, 2, 3, 4))
print(formatter.format('one', 'two', 'three', 'four'))
print(formatter.format(True, False, True, False))
print(formatter.format(formatter, formatter, formatter, formatter))
print(formatter.format(
    "Try your",
    "Own text here",
    "Maybe a poem",
    "Or a song about fear."
))


# ex.9
print('\n##### ex. 9')

days = "Mon Tue Wed Thu Fri Sat Sun"
months = "Jan\nFeb\nMar\nApr\nMay\nJun\nJul\nAug"

print("Days: ", days)
print("Months: ", months)

print(
    '''
There's something going on here.
With the three double-quotes.
We'll be able to type as much as we like.
Even 4 lines if we want, or 5, or 6.
''')



