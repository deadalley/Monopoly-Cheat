import matplotlib.pyplot as plt
import numpy as np

f = open("results/best.log", "r")

N_GENERATIONS = int(f.readline())
N_PLAYERS = int(f.readline())

buyingChance = np.zeros((3,N_GENERATIONS))
buildingChance = np.zeros((3,N_GENERATIONS))
payingJailChance = np.zeros((3,N_GENERATIONS))
tradingChance = np.zeros((3,N_GENERATIONS))
minimumBalance = np.zeros((3,N_GENERATIONS))
minimumCards = np.zeros((3,N_GENERATIONS))

features = {'Buying Chance' : buyingChance,
            'Building Chance' : buildingChance,
            'Paying Jail Chance' : payingJailChance,
            'Trading Chance' : tradingChance,
            'Minimum Balance' : minimumBalance,
            'Minimum Cards' : minimumCards}

stages = {0 : 'early game',
          1 : 'mid game',
          2 : 'late game'}

def plotResult(feat, stage, opt):
    plt.clf()
    plt.plot(features[feat][stage])
    plt.ylabel('Chance (%)')
    plt.xlabel('Generation')
    plt.title(feat + " (" + stages[stage] + ")" + "\n" +\
              "(" + str(N_GENERATIONS) + " generations, " + str(N_PLAYERS) +" players)")
    if opt is 'show':
        plt.show()
    if opt is 'save':
        plt.savefig('results/'+feat.replace(' ','_')+'_'+stages[stage].replace(' ', '_')+'.png')
    return


for gen in range(0, N_GENERATIONS):
    #f.readline()
    p = f.readline().rstrip()
    data = f.readline().rstrip()
    data = data.split(",")
    #print(data)
    for stage in range(0, 3):
        buyingChance[stage][gen] = data[0+(stage*6)]
        buildingChance[stage][gen] = data[1+(stage*6)]
        payingJailChance[stage][gen] = data[2+(stage*6)]
        tradingChance[stage][gen] = data[3+(stage*6)]
        minimumBalance[stage][gen] = data[4+(stage*6)]
        minimumCards[stage][gen] = data[5+(stage*6)]

for k in range(0, 3):
    for key in features:
        plotResult(key, k, 'save')

f.close()
