def fuelNeeded(value): return 0 if 0 > int(int(value)/3)-2 else int(int(value)/3)-2 + fuelNeeded(int(int(value)/3)-2)
[totalMass,massFile] = [0,open("moduleMass.txt","r")]
for line in massFile: (mass = (lambda n=0: n + 0)) += fuelNeeded(line)
print(f'{for line in massFIle: totalMass += fuelNeeded(line)}')
