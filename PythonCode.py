import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100

def SquareValue(v):
    return v * v

    # Prints a list of each sold item and the quantity sold
def CountItems():
    with open('InputFile.txt', 'r') as f: # opens file for reading / automatically closes
        listdata = f.readlines()

    listdata.sort()
        for item in listdata:             # prints items, deleting existing items
        print(item, " ", listdata.count(item))
        while True:
            listdata.remove(item)         # deletes repeats of the same item

    # Returns the number of items, given the item as a parameter
def ItemFrequency(v):
    with open('Inputfile.txt' 'r') as f: 
        listdata = f.readlines()

        itemcount = listdata.count(v)
        return itemcount

def BuildHistogram():
    with open('InputFile.txt', 'r') as f: # opens file for reading / automatically closes
        listdata = f.readlines()

    listdata.sort()
    g = open('frequency.dat', w)      # opens frequency.dat for writing
    for item in listdata:             # prints items, deleting existing items
        g.write(item, " ", listdata.count(item))
        while True:
            listdata.remove(item)         # deletes repeats of the same item
    g.close()                         # closes the file to avoid data leaks