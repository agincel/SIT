def isValid(c, d="-1"):
	if d == "-1":
		return c != "0"
	elif c == "1":
		return True
	elif c == "2":
		return d <= "6"
	else:
		return False

def recurse(s, start, end, memo):
	if start in memo:
		return memo[start]

	if end - start == 0:
		if isValid(s[start]):
			memo[start] = 1
			return 1
		else:
			memo[start] = 0
			return 0
	elif end - start == 1:
		if isValid(s[start], s[end]):
			if isValid(s[end]):
				memo[start] = 2
				return 2
			else:
				memo[start] = 1
				return 1
		elif isValid(s[start]):
			memo[start] = recurse(s, start+1, end, memo)
			return memo[start]
		else:
			return 0
	else:
		if isValid(s[start], s[start + 1]):
			memo[start] = recurse(s, start + 2, end, memo) + recurse(s, start + 1, end, memo)
			return memo[start]
		elif isValid(s[start]):
			memo[start] = recurse(s, start + 1, end, memo)
			return memo[start]
		else:
			memo[start] = 0
			return 0
s = ""
while s != "0":
	s = input()
	memo = {}
	if s != "0":
		print(recurse(s, 0, len(s) - 1, memo))
