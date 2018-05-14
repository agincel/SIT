numKids = int(input())
rank = list(0 for i in range(0, numKids))
for i in range(0, numKids):
    rank[i] = int(input())
givenCandy = list(1 for i in range(0, numKids))
for i in range(1, numKids):
    for j in range(i, numKids):
        if rank[j - 1] > rank[j]:
            givenCandy[i - 1] += 1
        else:
            break
print(givenCandy)
    
    