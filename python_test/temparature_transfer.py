## temparature transfer

#tempConvert.py
''' multiline 
comment'''

TempStr = input("please input a temparature value with symbol:")
if TempStr[-1] in ['F', 'f']:
    C = (eval(TempStr[0:-1]) - 32)/1.8
    print("the converted temp is {:.2f}C".format(C))
elif TempStr[-1] in ['C', 'c']:
    F = 1.8*eval(TempStr[0:-1]) + 32
    print("the converted temp is {:.2f}F".format(F))
else:
    print("invalid input")



TempStr = input()
if TempStr[1:4] in ['RMB']:
    C = eval(TempStr[4:]/6.78
    print("USD{:.2f}".format(C))
elif TempStr[1:4] in ['USD']:
    F = eval(TempStr[4:]*6.78
    print("RMB{:.2f}".format(F))
