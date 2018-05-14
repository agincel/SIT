
def subset_rec(target, lst, used):
	if target == 0:
		return [True, used]
	if lst == []:
		return [False, []]
	result1 = subset_rec(target - lst[0], lst[1:], used + [lst[0]])
	result2 = subset_rec(target, lst[1:], used)
	if result1[0]:
		return result1
	elif result2[0]:
		return result2
	else:
		return [False, []]

def subset(target, lst):
	return subset_rec(target, lst, [])


def subset_sum(target, lst):
	fullSum = 0
	for i in lst:
		fullSum += i
	blst = [False]*(fullSum+1)
	blst[0] = True

	for i in lst:
		j = fullSum
		while j >= i:
			blst[j] = blst[j] or blst[j - i]
			j -= 1

	if target > fullSum:
		return False
	else:
		return blst[target]


print(subset_sum(50, [10, 10, 10, 10]))