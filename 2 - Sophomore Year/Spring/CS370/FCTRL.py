



def getZeroes(x):
	exp = 1
	fact = 5
	zeroes = 0

	while fact <= x:
		zeroes += int(x / fact)
		exp += 1
		fact = pow(5, exp)

	return zeroes


print(getZeroes(50))
print(getZeroes(8735373))