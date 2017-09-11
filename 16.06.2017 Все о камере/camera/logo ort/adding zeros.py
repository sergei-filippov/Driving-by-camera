bineryF = open("binery.txt","r")
counterx = 1
countery = 0
octet = ""


while countery < 32:    
    row = bineryF.readline()    # read line by line
    while counterx < 96+11:    #цифры и пробелы
        if row[counterx] == " ":    
            countback = counterx
            countback-=1;
            while row[countback] != " ":
                octet = row[countback] + octet        
                countback-=1
            while len(octet) < 8:
                octet = "0" + octet
                if len(octet) == 8:
                    counterx+=1
                    break
                bineryz = open("binery_zeros.txt","w")
                bineryz.write(octet+" ")
                
                
                


            
                
            
