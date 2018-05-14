import numpy

#Adam Gincel
#HW3.py 

# I pledge my honor that I have abided by the Stevens Honor System

# numpy.random.seed(9) #moderately close results with random seed 9, uncomment to see


#import from seq.txt
f = open("seq.txt", "r")
strIn = f.read()
f.close()
strInSplit = strIn.split(" ")
seq = []
for s in strInSplit:
    if (len(s) > 0):
        seq.append(int(s))
print("\n\nImported data from seq.txt. Length: " + str(len(seq)))

numStates = 3 #given
numTokens = 10 #given

arbitrarySmallNumber = 0.1

A = numpy.array([[numpy.random.uniform() for i in range(0, numStates)] for j in range(0, numStates)])
A = A / numpy.sum(A, 0)
A = A.transpose()

B = numpy.array([[numpy.random.uniform(0, 1) for _ in range(numStates)] for _ in range(numTokens)]) #create and normalize B
Bnorm = [[0 for i in range(numStates)] for j in range(numTokens)]
sumVert = [0 for j in range(numStates)]
for i in range(len(B)):
    for j in range(len(B[i])):
        sumVert[j] += B[i][j]
for i in range(len(B)):
    for j in range(len(B[i])):
        Bnorm[i][j] = B[i][j] / sumVert[j]

B = numpy.array(Bnorm)


C = [numpy.random.uniform(0, 1) for _ in range(numStates)]
Cnorm = []
sum = 0
for n in C:
    sum += n
for n in C:
    Cnorm.append(n / sum)
C = Cnorm

print("-------------------------------------------\nStarting A, B, C (aka pi) values: ")
print("A: \n" + str(A))
print("B: \n" + str(B))
print("C: \n" +  str(C))


# forward probability
def genForward(A, B, C):
    forwardProbabilities = []
    forwardProbabilities.append(B[seq[0] - 1] * C) #initial alpha
    for i in range(0, len(seq) - 1):
        token = seq[i + 1]
        alpha1 = numpy.dot(forwardProbabilities[-1], A[0]) * B[token - 1][0]
        alpha2 = numpy.dot(forwardProbabilities[-1], A[1]) * B[token - 1][1]
        alpha3 = numpy.dot(forwardProbabilities[-1], A[2]) * B[token - 1][2]
        sum = alpha1 + alpha2 + alpha3
        forwardProbabilities.append([alpha1 / sum, alpha2 / sum, alpha3 / sum])
    return forwardProbabilities

# backward probability
def genBackward(A, B):
    backwardProbabilities = []
    backwardProbabilities.append([1, 1, 1]) #start at the end with a thing of all 1s

    for i in range(1, len(seq)):
        rowToAppend = []

        for j in range(numStates):
            thingToAppend = numpy.sum(backwardProbabilities[i - 1] * A[j] * B[seq[len(seq) - 1 - i] - 1]) #add the previous * A[j] * B at the relevant seq token
            rowToAppend.append(thingToAppend)
        normalizedItemtoAppend = rowToAppend / numpy.sum(rowToAppend, 0) #normalize
        backwardProbabilities.append([normalizedItemtoAppend[0], normalizedItemtoAppend[1], normalizedItemtoAppend[2]])
    backwardProbabilities.reverse() #since this started at the end, reverse before proceeding
    return backwardProbabilities

def update(weightedChoices, seq):
    newA = [[arbitrarySmallNumber for _ in range(numStates)] for _ in range(numStates)]
    newB = [[arbitrarySmallNumber for _ in range(numStates)] for _ in range(numTokens)]
    for i in range(1, len(weightedChoices)):
        newA[weightedChoices[i - 1]][weightedChoices[i]] += 1

    for i in range(len(seq)):
        newB[seq[i] - 1][weightedChoices[i]] += 1

    # normalize A
    normA = []
    normB = []
    for i in range(numStates):
        sum = 0
        for j in range(numStates):
            sum += newA[i][j]
        normA.append([newA[i][0] / sum, newA[i][1] / sum, newA[i][2] / sum])

    # normalize B vertically
    sumVert = [0 for i in range(numStates)]
    for row in newB:
        sumVert[0] += row[0]
        sumVert[1] += row[1]
        sumVert[2] += row[2]
    for row in newB:
        normB.append([row[0] / sumVert[0], row[1] / sumVert[1], row[2] / sumVert[2]])
        
    return numpy.array(normA), numpy.array(normB)


print("\n-----------------------------------\nUpdate/Encode Step\n\n")

iterations = 50
try:
    iterations = int(input("How many iterations would you like? "))
except:
    print("Invalid input, using 50 iterations")



for iteration in range(iterations):
    forwardProbabilities = genForward(A, B, C) #generate forward and backwards, given A
    backwardProbabilities = genBackward(A, B)

    combinedProbabilities = numpy.array(forwardProbabilities) * numpy.array(backwardProbabilities)
    combinedProbabilities = combinedProbabilities / numpy.outer(numpy.sum(combinedProbabilities, 1), [1, 1, 1])

    weightedChoices = []
    for i in range(len(combinedProbabilities)):
        choice = numpy.random.choice([0, 1, 2], p=combinedProbabilities[i])
        weightedChoices.append(choice)

    print("Current Iteration: " + str(iteration))

    #print("weightedChoices: \n" + str(weightedChoices))
    
    A, B = update(weightedChoices, seq)

print("Final A: \n" + str(A))
print("Final B: \n" + str(B))

correctA = numpy.array([[0.75, 0.25, 0], [0.25, 0.5, 0.25], [0, 0.25, 0.75]])

forwardProbabilities = genForward(correctA, B, C) #generate forward and backwards, given A
backwardProbabilities = genBackward(correctA, B)

combinedProbabilities = numpy.array(forwardProbabilities) * numpy.array(backwardProbabilities)
combinedProbabilities = combinedProbabilities / numpy.outer(numpy.sum(combinedProbabilities, 1), [1, 1, 1])

weightedChoices = []
for i in range(len(combinedProbabilities)):
    choice = numpy.random.choice([0, 1, 2], p=combinedProbabilities[i])
    weightedChoices.append(choice)
A, B = update(weightedChoices, seq)

print("B using Given Matrix Solution: \n" + str(B))