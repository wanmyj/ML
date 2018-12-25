# week
weekStr = "SundayMondayTuesdayWednesdayThursdayFridaySaturday"
weekID = eval(input("please input week num"))
pos = weekID - 1
pos *= 3
print(weekStr[pos:pos+3])

for i in range(12):
    print(chr(9800+i)+'  ', end="")
print('\n')
