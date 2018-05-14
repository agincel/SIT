# Matt Gomez, Alex Massenzio, Adam Gincel
# PALIN.py (shoutouts to Sarah Palin)
#
# A program that returns the next palindrome after a given integer
# I pledge my honor that I have abided by the Stevens Honor System.

def findNextPalindrome(number):
    size = len(number) #number is a string
    if size % 2 == 1: #if our number is odd, get the center digit
        center = number[int(size / 2)]
    else:
        center = ''
    left = number[0:int(size / 2)]
    right = ''.join(reversed(left))
    reversedNumber = left + center + right
    if reversedNumber > number: #if it's greater
        print(reversedNumber)
    else:
        if center:
            if center < '9': #increment center by 1
                center = str(int(center) + 1)
                print(left + center + right)
                return
            else:
                center = '0'
        if left == len(left) * '9': #if all 9s
            print('1' + (len(number) - 1) * '0' + '1') #print in the form 10001
        else:
            left = increment(left) #otherwise increment left half then print
            print(left + center + ''.join(reversed(left)))

def increment(l):
    left = list(l)
    last = len(left) - 1
    while left[last] == '9': #can't be all 9s, so this will not go out of range
        left[last] = '0'
        last -= 1
    left[last] = str(int(left[last]) + 1) #increment
    return "".join(left)

numCases = int(input())
while numCases > 0:
    numCases -= 1
    findNextPalindrome(input())