import math
import numpy

# Adam Gincel
# hw2.py
# CS559 - Machine Learning
# I pledge my honor that I have abided by the Stevens Honor System.

#always get the same random numbers
numpy.random.seed(77)

#generate random tuple, each value in range from 0 to max
def getTuple(max):
	return [numpy.random.uniform(0, max), numpy.random.uniform(0, max), numpy.random.uniform(0, max)]


upperBound = int(input("Test on dataset from 0 to: "))

print("Defining datasets...")
#we'll do 1000 datapoints for datasets 1 and 2
ds1 = []
ds2 = []


trainingSetSize = int(input("Training set size? "))
testSetSize = int(input("Test set size? "))


for i in range(0, trainingSetSize):
	ds1.append(getTuple(upperBound)) #ds1 uses U(0, 2)

for i in range(0, testSetSize):
	ds2.append(getTuple(upperBound)) #ds2 uses U(0, 3)

#generate output dataset from 1 by doing sum of greatest integer of each input, if sum is even y is 0, if sum is odd y is 1
output1 = []
output2 = []
print("Generating outputs...")
for i in range(0, trainingSetSize):
	t1 = ds1[i]
	t1Sum = int(t1[0]) + int(t1[1]) + int(t1[2])
	output1.append(t1Sum % 2)

for i in range(0, testSetSize):
	t2 = ds2[i]
	t2Sum = int(t2[0]) + int(t2[1]) + int(t2[2])
	output2.append(t2Sum % 2)


finalDS1 = []
finalDS2 = []

print("Normalizing datasets and appending outputs...")
for i in range(0, len(ds1)):
	c1 = [ds1[i][0] / upperBound, ds1[i][1] / upperBound, ds1[i][2] / upperBound, output1[i]]
	finalDS1.append(c1)

for i in range(0, testSetSize):
	c2 = [ds2[i][0] / upperBound, ds2[i][1] / upperBound, ds2[i][2] / upperBound, output2[i]]
	finalDS2.append(c2)

# ^^^ dataset generation
# vvv neural network
 
def initializeNetwork(numberInputs, n_hidden, numberOutputs):
	network = []
	hiddenLayer = []
	for i in range(n_hidden):
		hiddenLayerAddition = {'weights': []}
		for j in range(numberInputs + 1):
			hiddenLayerAddition['weights'].append(numpy.random.randn()) #randomly start weights with normal distribution
		hiddenLayer.append(hiddenLayerAddition)
	network.append(hiddenLayer)

	outputLayer = []
	for i in range(numberOutputs):
		outputLayerAddition = {'weights': []}
		for j in range(n_hidden + 1):
			outputLayerAddition['weights'].append(numpy.random.randn()) #randomly start weights with normal distribution
		outputLayer.append(outputLayerAddition)

	network.append(outputLayer)
	return network

def activate(weights, inputs):
	activation = weights[-1]
	for i in range(len(weights) - 1):
		activation += weights[i] * inputs[i]
	return activation

def sigmoid(activation):
	return 1.0 / (1.0 + numpy.exp(-activation))

def sigmoid_derivative(output):
	return output * (1.0 - output)

def relu(activation):
	if activation > 0:
		return activation
	else:
		return 0

def relu_derivative(activation):
	if activation > 0:
		return 1
	else:
		return 0

def forwardPropagate(network, row):
	inputs = row

	new_inputs = []
	for hiddenNode in network[0]:
		activation = activate(hiddenNode['weights'], inputs)
		hiddenNode['output'] = relu(activation)
		new_inputs.append(hiddenNode['output'])
	inputs = new_inputs

	new_inputs = []
	for outputNode in network[1]:
		activation = activate(outputNode['weights'], inputs)
		outputNode['output'] = sigmoid(activation)
		new_inputs.append(outputNode['output'])
	inputs = new_inputs

	return inputs

def backwardPropagateError(network, expected):
	for i in reversed(range(len(network))):
		layer = network[i]
		errors = []
		if i != len(network)-1:
			for j in range(len(layer)):
				error = 0.0
				for neuron in network[i + 1]:
					error += (neuron['weights'][j] * neuron['delta'])
				errors.append(error)
		else:
			for j in range(len(layer)):
				neuron = layer[j]
				errors.append(expected[j] - neuron['output'])
		for j in range(len(layer)):
			neuron = layer[j]
			neuron['delta'] = errors[j] * relu_derivative(neuron['output'])
 
def updateWeights(network, row, learningRate):
	for i in range(len(network)):
		inputs = row[:-1]
		if i != 0:
			inputs = [neuron['output'] for neuron in network[i - 1]]
		for neuron in network[i]:
			for j in range(len(inputs)):
				neuron['weights'][j] += learningRate * neuron['delta'] * inputs[j]
			neuron['weights'][-1] += learningRate * neuron['delta']

def trainNetwork(network, train, learningRate, iterations, numberOutputs):
	print("Training network with learning rate " + str(learningRate) + " for " + str(iterations) + " iterations.")

	f = open("output.txt", "w") #clear output.txt
	f.write("")
	f.close()

	f = open("output.txt", "a") #append to output.txt
	for iteration in range(iterations):
		sum_error = 0
		for row in train:
			outputs = forwardPropagate(network, row)
			expected = [0 for i in range(numberOutputs)]
			expected[row[-1]] = 1
			
			for i in range(len(expected)):
				if outputs[i] != 0:
					sum_error += -numpy.log(numpy.abs(outputs[i])) * expected[i] #cross entropy
			sum_error /= len(outputs) #avg cross entropy
			backwardPropagateError(network, expected)
			updateWeights(network, row, learningRate)
		f.write(str(sum_error) + "\n") #add current error to outputs.txt
		if ((iteration + 1) % 5 == 0):
			print("Iteration: " + str(iteration + 1) + "\t|\tError: " + str(round(sum_error, 5)))
	f.close()
			

# Make a prediction with a network
def predict(network, row):
	outputs = forwardPropagate(network, row)
	return outputs.index(max(outputs))

numberInputs = len(finalDS1[0]) - 1
numberOutputs = 2 #0 or 1
numberHiddenLayers = int(input("Number of hidden layers? "))
network = initializeNetwork(numberInputs, numberHiddenLayers, numberOutputs)

userLearningRate = float(input("Learning rate? "))
userIterations = int(input("How many iterations? "))
trainNetwork(network, finalDS1, userLearningRate, userIterations, numberOutputs)

totalRows = 0
totalRight = 0

print("Predicting over training set:")
for row in finalDS1:
	prediction = predict(network, row)
	totalRows += 1
	if (row[-1] == prediction):
		totalRight += 1

print("Got " + str(totalRight) + "/" + str(totalRows) + " (" + str(numpy.round(totalRight/totalRows, 5) * 100) + "%) correct on the training set")

totalRows = 0
totalRight = 0

print("Predicting over test set:")
for row in finalDS2:
	prediction = predict(network, row)
	totalRows += 1
	if (row[-1] == prediction):
		totalRight += 1

print("Got " + str(totalRight) + "/" + str(totalRows) + " (" + str(numpy.round(totalRight/totalRows, 5) * 100) + "%) correct on the non-training set")

f = open("weights.txt", "w") #clear weights.txt, then output the network to it
f.write("")
f.close()

f = open("weights.txt", "a")
f.write("Hidden nodes: \n")
for hiddenNode in network[0]:
	f.write("> " + str(hiddenNode) + "\n")
f.write("\nOutput nodes: \n")
for outputNode in network[1]:
	f.write("> " + str(outputNode) + "\n")

f.close()
print("Exported network to weights.txt")