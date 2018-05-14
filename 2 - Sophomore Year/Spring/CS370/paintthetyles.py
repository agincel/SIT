length = int(input())
string = input()
strokes = 1
currentChar = string[0]
for c in string:
	if c != currentChar:
		strokes += 1
		currentChar = c
print(strokes)