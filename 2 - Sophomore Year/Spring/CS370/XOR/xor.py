import itertools

f = open("cipher.txt", "r")
s = f.read()
originalArray = s.split(",")

keyFile = open("keys.txt", "r")

answerArray = []
answers = []
i = 0
alpha = "a b c d e f g h i j k l m n o p q r s t u v w x y z"
alphaP = "a b c d e f g h i j k l m n o p q r s t u v w x y z ( ) . ! , 1 2 3 4 5 6 7 8 9 ; A B C D E F G H I J K L M N O P Q R S T U V W X Y Z \' \n"
#keyArray = itertools.combinations_with_replacement(alpha.split(), 3)
#keyArray = keyFile.read().split()
keyArray = ["god"]

for key in keyArray:
    for e in originalArray:
        answerArray.append(chr(int(e) ^ ord(key[i])))
        i = (i + 1) % 3
    answers.append(answerArray)
    answerArray = []

for answer in answers:
    isPotentialSolution = True
    allC = 0
    notC = 0
    for c in answer:
        allC += 1
        if c not in alphaP:
            notC += 1
    if (notC / allC) <= .1:
        for c in answer:
            print(c, end="")
        print("\n")
