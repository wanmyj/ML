# pythonDraw.py

# import turtle
# turtle.setup(1050, 550, 100, 200)
# turtle.penup()
# turtle.fd(-250)
# turtle.pendown()
# turtle.pensize(25)
# turtle.pencolor('purple')
# turtle.seth(-40) #direction absolute coord. For relative angle turtle.left(an)
# for i in range(4):
#     turtle.circle(40, 80)
#     turtle.circle(-40, 80)
# turtle.circle(40, 40)
# turtle.fd(40)
# turtle.circle(16, 180)
# turtle.fd(80/3)
# turtle.done()

# turtle 1969 standard library
# A turtle is located at the center of windows
# windows layout : minimum unit: pixel

# import turtle
# turtle.colormode(255)
# turtle.left(45)
# turtle.fd(150)
# turtle.right(135)
# turtle.fd(300)
# turtle.left(135)
# turtle.fd(150)
# turtle.done()

# import turtle
# turtle.pensize(10)
# turtle.pencolor('black')
# turtle.fd(100)
# turtle.right(90)
# turtle.fd(100)
# turtle.right(90)
# turtle.fd(100)
# turtle.right(90)
# turtle.fd(100)

# turtle.done()
# import turtle
# turtle.pensize(10)
# turtle.pencolor('black')
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.fd(100)
# turtle.right(80)
# turtle.done()

# # daydayup
# dayup = 1
# dayfactor = .01
# for i in range(356):
#     if i%7 in [6,0]:
#         dayup *= (1-dayfactor)
#     else:
#         dayup *= (1+dayfactor)
# print("strength {:.2f}".format(dayup))

def dayUP(df):
    dayup = 1
    for i in range(365):
        if i%7 in [6,0]:
            dayup *= .99
        else:
            dayup *= (1+df)
    return dayup

dayfactor = .01
while dayUP(dayfactor) < 37.78:
    dayfactor += .0001
print(dayfactor)

