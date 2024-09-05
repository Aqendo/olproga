import fnmatch
s = input()
tmpl = input()
res = fnmatch.filter([s], tmpl)
if res == []:
    print("NO")
else:
    print("YES")
