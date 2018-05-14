import csv
import math

indices = []
with open('indices.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        finalR = [int(row[0]), int(row[1])]
        indices.append(finalR)

print("Indices stored.")



def getDS(x):
    currentIndex = -1
    for a in indices:
        currentIndex += 1
        if x >= a[0] and x <= a[1]:
            return currentIndex
    print("We didn't find that dataset")
    return -1

def gd(data, x): #"get data"
    ret = data[getDS(x)]
    return ret



readData = []
splitData = []




fileName = input("Input filename to read from:\n")
print("Reading in from " + fileName + "...")
try:
    with open(fileName, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            readData.append(row)
except Exception:
    print("Unable to read in from " + fileName + ". Does the file exist? Exiting.")
    exit()



print("Parsing data from " + fileName + "...")
for line in readData:
    finalL = []
    for item in line:
        try:
            finalL.append(int(item))
        except Exception:
            finalL.append(float(item))
    splitData.append(finalL)


#Find MIN/MAX/AVG Height and Weight
print("Finding min, max, and avg height and weight...")
minHeight = 999999
maxHeight = -1
avgHeight = 0
countHeight = 0
minWeight = 99999
maxWeight = -1
avgWeight = 0
countWeight = 0

for data in splitData:
    #306 is feet, 99 is unknown
    currentFeet = gd(data, 306)
    currentInch = gd(data, 308)

    if (currentFeet < 99 and currentInch < 99):
        countHeight += 1
        currentHeight = (currentFeet * 12) + currentInch
        if currentHeight < minHeight:
            minHeight = currentHeight
        if currentHeight > maxHeight:
            maxHeight = currentHeight
        avgHeight += currentHeight

    #310 is weight, 999 is unknown
    currentWeight = gd(data, 310)
    if currentWeight < 999:
        countWeight += 1
        if currentWeight < minWeight:
            minWeight = currentWeight
        if currentWeight > maxWeight:
            maxWeight = currentWeight
        avgWeight += currentWeight

avgHeight = float(avgHeight) / float(countHeight)
avgWeight = float(avgWeight) / float(countWeight)

print("Extracting relevant values...")
#42, 48, 63, 64, 68, 3673, 79, 114, 131, 136, 144, 163, 196, 217, 226, 230, 232, 294, 306, 308, 310
relevantData = []
for data in splitData:
    relevantDataLine = []
    #42 is census division from 1 to 9 aka 0 to 8
    censusDivision = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    censusDivision[gd(data, 42) - 1] = 1

    for a in censusDivision:
        relevantDataLine.append(a)

    #48 is number of persons in household from 1 to 17
    personsNormalized = float(gd(data, 48) - 1) / float(16)
    relevantDataLine.append(personsNormalized)

    #63 is "father in household" 0 for no 1 for yes0
    relevantDataLine.append(1 - (gd(data, 63) - 1))

    #64 is "mother in household" 0 or 1
    relevantDataLine.append(1 - (gd(data, 64) - 1))

    #68 is age from 18 to 89 or 90+
    ageDivision = [0, 0]
    if (gd(data, 68) < 90):
        ageDivision[0] = float(gd(data, 68) - 18) / float(71)
    else:
        ageDivision[1] = 1
    for a in ageDivision:
        relevantDataLine.append(a)

    #79 is sex, male or female 0 or 1
    relevantDataLine.append(gd(data, 79) - 1)

    #3673 is race/ethnicity from 1 to 5
    raceDivision = [0, 0, 0, 0, 0]
    raceDivision[gd(data, 3673) - 1] = 1
    for r in raceDivision:
        relevantDataLine.append(r)
    
    #114 is Marital status, 6 options
    maritalDivision = [0, 0, 0, 0, 0,0]
    maritalDivision[gd(data, 114) - 1] = 1
    for m in maritalDivision:
        relevantDataLine.append(m)

    #131 is Highest Grade or year of school completed, from 0 to 1 sliding scale from no school to master's 
    relevantDataLine.append((gd(data, 131) - 1) / float(13))

    #136: is working full time? 0 no 1 yes
    relevantDataLine.append(1 - (gd(data, 136) - 1))

    #144: is retired
    relevantDataLine.append(1 - (gd(data, 144) - 1))

    #163 is "employed in last 12 months"
    relevantDataLine.append(1 - (gd(data, 163) - 1))

    #196 is family income sliding from 0 to 1
    relevantDataLine.append((gd(data, 196) - 1) / float(20))

    #217 is has received food stamps
    relevantDataLine.append(1 - (gd(data, 217) - 1))

    #226 is currently covered by medicaid
    relevantDataLine.append(1 - (gd(data, 226) - 1))

    #230 is private health insurance
    relevantDataLine.append(1 - (gd(data, 230) - 1))

    #232 is self-perceived current health
    #going to assume unknown is "good", aka middle of the road
    if (gd(data, 232) == 9):
        relevantDataLine.append(float(2) / float(4))
    else:
        relevantDataLine.append((gd(data, 232) - 1) / float(4))
    
    #294 is has any close friends/family died in last 12 months
    #assuming unknown is just no 
    if (gd(data, 294) == 9):
        relevantDataLine.append(0)
    else:
        relevantDataLine.append(1 - (gd(data, 294) - 1))

    #306 is feet, 308 is inches. We use the min, max, and avg heights found in prior for loop
    currentFeet = gd(data, 306)
    currentInch = gd(data, 308)
    if (currentFeet < 99 and currentInch < 99):
        currentHeight = (currentFeet * 12) + currentInch
        relevantDataLine.append((currentHeight - minHeight) / float(maxHeight))
    else:
        #if unknown, assume the average weight
        relevantDataLine.append((avgHeight - minHeight) / float(maxHeight))
    
    #310 is weight -- we use the min, max, and avg weights found in prior for loop
    currentWeight = gd(data, 310)
    if currentWeight < 999:
        relevantDataLine.append((currentWeight - minWeight) / float(maxWeight))
    else:
        #if unknown, assume avg weight
        relevantDataLine.append((avgWeight - minWeight) / float(maxWeight))

    #313 is the actual thing we are predicting: "has drank at least one alcoholic drink before", 0 no 1 yes
    relevantDataLine.append(1 - (gd(data, 313) - 1))

    relevantData.append(relevantDataLine)

#print(relevantData[0])


from math import exp

def prediction(rowData, weights):
    yhat = 0
    for i in range(len(rowData) - 1):
        yhat += rowData[i] * weights[i]
    return (1.0 / (1.0 + exp(-yhat))) #sigmoid function

def logisticRegression(trainingSet, learningRate, numberIterations):
    weights = []
    for i in range(len(trainingSet[0]) - 1): #make list of weights starting at 0
        weights.append(0.0)

    for iteration in range(numberIterations):
        for row in trainingSet:
            yhat = prediction(row, weights)
            for i in range(len(row) - 1):
                weights[i] += learningRate * row[i] * (row[-1] - yhat) #row[-1] is the training set's answer to have they drank or not
        print("Regression iteration " + str(iteration + 1) + " out of " + str(numberIterations))
    return weights

def checkAccuracy(trainingSet, weights):
    numCorrect = 0
    for i in range(len(trainingSet)):
        prediction = 0
        for j in range(len(trainingSet[i]) - 1):
            prediction += trainingSet[i][j] * weights[j]
        if prediction <= 0:
            prediction = 0
        else:
            prediction = 1
        if prediction == trainingSet[i][-1]: #[i][-1] is the 313 of the given row
            numCorrect += 1
    return numCorrect



learningRate = float(input("Please enter a learning rate:\n"))
iterations = int(input("Please enter how any iterations of Logistic Regression you'd like:\n"))
print("Performing logistic regression to get list of weights...")
weights = logisticRegression(relevantData, learningRate, iterations)
print("\nDone! Weights: ")
print(weights)
print("\nChecking accuracy...")
numCorrect = checkAccuracy(relevantData, weights)
print("Number correct: " + str(numCorrect) + "/" + str(len(relevantData)) +  " -- that's " + str(round(float(numCorrect) / float(len(relevantData)) * 100, 4) ) + "%")
errorPercent = round((1 - (float(numCorrect) / float((len(relevantData))))) * 100, 4)
print("That makes for an error percentage of " + str(errorPercent) + "%")