fruits = ('Apple', 'Oranges', 'Grapes')
fruits2 = tuple(('Apples', 'Oranges', 'Grapes'))
print(fruits2, type(fruits2))
A = list({1, 5, 9})
print(A)
B = tuple({1, 5, 9 })
print(B)
# dict, set
x = 1
x += 3
x -= 2
x = None
list("ABC")
dict([(3, "three"), (1, "one")])
print('.'.join(['toto', '12', 'password']))

print("1.4.8.2".split('.'))
print([int(x) for x in ('1', '29', '-3')])
# if elif else: 
if x: 
    if not x: 
        pass

age = 20
state = ""
if age <= 18: 
    state = "Kid"
elif age > 65: 
    state = "Retired"
else: 
    state = 'Active'

s = 0
i = 1
while i <= 100: 
    s = s + i ** 2
    i += 1
print(f"sum:{s}")

ss = 'Some text'
cnt = 0
for c in ss: 
    if c == 'e': 
        cnt += 1
print("found ", cnt, 'e')


lst = [11, 18, 9, 12, 23, 4, 17]
lost = []
for idx in range(len(lst)):
    val = lst[idx]
    if val > 15: 
        lost.append(val)
        lst[idx] = 15
print("modif: ", lst, "-lost: ", lost)
for idx, val in enumerate(lst): 
    print(idx, val)


class Shape: 
    def area(self): 
        pass
    def perimeter(self): 
        pass

class Rectangle(Shape): 
    static_field = 10
    @staticmethod
    def static_method(): 
        print("a static method")

    def __init__(self, width, height): 
        self.width = width
        self.height = height
    
    def area(self): 
        return self.width * self.height
    
    def perimeter(self): 
        return 2 * (self.width + self.height)
    
print(Rectangle.static_field)

import List

class Solution: 
    def minSubArryLen(self, target: int, nums: List[int]) -> int: 


class TreeNode: 
    def __init__(self, val = 0, left = None, right = None): 
        self.val = val
        self.left = left
        self.right = right
        


input a 
input B

diff = a - B
print diff

name = input("Enter your name:"); 
print("Hello ", name); 
print("Welcome to Educative")

age = int(input("Enter your age:"))
if age >= 18 : 
    print("you are eligible")
else : 
    print("You are not eligible")

number = input("Enter a positive number:")
sum += number % 10; 
number //= 10; 
if number > 10 and number < 1000 : 
    number = number // 10 

for a in [0, 1, 2, 3, 4]: 
    print(a)

for a in range(0, 101):
    print(a)

for a in range(0, 200, 2):
    print(a)

for a in range(7, 700, 7): 
    print(a)