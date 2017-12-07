import matplotlib.pyplot as plt
import numpy as np

# Open best.log for reading
f = open("results/best.log", "r")

# Get number of generations and max number of players
N_GENERATIONS = int(f.readline())
N_PLAYERS = int(f.readline())

# Initialize arrays for plotting
buyingChance = np.zeros((28,3,N_GENERATIONS))
buildingChance = np.zeros((3,N_GENERATIONS))
payingJailChance = np.zeros((3,N_GENERATIONS))
tradingChance = np.zeros((3,N_GENERATIONS))
minimumBalance = np.zeros((3,N_GENERATIONS))
minimumCards = np.zeros((3,N_GENERATIONS))
winCount = np.zeros((N_GENERATIONS,1))
ownedProperties = np.zeros((28,1))

# Property name mapping
properties = {'Mediterranean Avenue' : 0,
              'Baltic Avenue' : 1,
              'Oriental Avenue' : 2,
              'Vermont Avenue' : 3,
              'Connecticut Avenue' : 4,
              'St. Charles Place' : 5,
              'States Avenue' : 6,
              'Virginia Avenue' : 7,
              'St. James Place' : 8,
              'Tennessee Avenue' : 9,
              'New York Avenue' : 10,
              'Kentucky Avenue' : 11,
              'Indiana Avenue' : 12,
              'Illinois Avenue' : 13,
              'Atlantic Avenue' : 14,
              'Ventnor Avenue' : 15,
              'Marvin Gardens' : 16,
              'Pacific Avenue' : 17,
              'North Carolina Avenue' : 18,
              'Pennsylvania Avenue' : 19,
              'Park Place' : 20,
              'Boardwalk' : 21,
              'Reading Railroad' : 22,
              'Pennsylvania Railroad' : 23,
              'B & O Railroad' : 24,
              'Short Line Railroad' : 25,
              'Electric Company' : 26,
              'Water Works' : 27}

# Feature mapping
features = {'Buying Chance' : buyingChance,
            'Building Chance' : buildingChance,
            'PayingJail Chance' : payingJailChance,
            'Trading Chance' : tradingChance,
            'Minimum Balance' : minimumBalance,
            'Minimum Cards' : minimumCards}

# Stage mapping
stages = {0 : 'early game',
          1 : 'mid game',
          2 : 'late game'}

# Plot Win Count
# opt = 'save' or 'show' plot
def plotWinCount(opt):
    plt.clf()
    plt.plot(winCount, 'ro')
    plt.ylabel('# Wins')
    plt.xlabel('Generation')
    plt.title('# Wins by generation')

    if opt is 'show':
        plt.show()
    if opt is 'save':
        plt.savefig('results/wincount.png')
    return

# Plot feature result
# feat in features
# stage = {0, 1, 2}
# opt = 'save' or 'show' plot
def plotResult(feat, stage, opt):
    plt.clf()

    plt.xlabel('Generation')

    if feat.split(" ")[1] == 'Chance':
        plt.gca().set_ylim([0,100])
        plt.ylabel('Chance (%)')
    if feat == 'Minimum Balance':
        plt.gca().set_ylim([0,500])
        plt.ylabel('Amount ($)')
    if feat == 'Minimum Cards':
        plt.gca().set_ylim([0,5])
        plt.ylabel('Amount (#)')

    if feat == 'Buying Chance':
        for key, value in properties.items():
            plt.clf()
            plt.plot(features[feat][value][stage])
            plt.title(key + " - " + feat + " (" + stages[stage] + ")" + "\n" +\
                      "(" + str(N_GENERATIONS) + " generations, " + str(N_PLAYERS) +" players)")
            if opt is 'show':
                plt.show()
            if opt is 'save':
                plt.savefig('results/'+key.replace(' ', '_')+'_'+feat.replace(' ','_')+'_'+stages[stage].replace(' ', '_')+'.png')
        return

    plt.plot(features[feat][stage])
    plt.title(feat + " (" + stages[stage] + ")" + "\n" +\
              "(" + str(N_GENERATIONS) + " generations, " + str(N_PLAYERS) +" players)")

    if opt is 'show':
        plt.show()
    if opt is 'save':
        plt.savefig('results/'+feat.replace(' ','_')+'_'+stages[stage].replace(' ', '_')+'.png')
    return

# Plot property histogram (how many times a property was owned by the winning player)
# opt = 'save' or 'show' plot
def plotProperties(opt):
    plt.clf()
    x = np.arange(28)
    plt.bar(x, ownedProperties)
    plt.xticks(x, properties, rotation='vertical')
    plt.ylabel('Times bought')
    plt.xlabel('Property')
    plt.title('Properties owned by best player at end of the game')
    plt.tight_layout()
    if opt is 'show':
        plt.show()
    if opt is 'save':
        plt.savefig('results/ownedProperties.png')
    return

# Read file
for gen in range(0, N_GENERATIONS):
    #f.readline()
    # Get player
    p = f.readline().rstrip()
    # Get win count
    winCount[gen] = f.readline().rstrip()
    # Get properties owned by player (for histogram)
    data = f.readline().rstrip()
    data = data.split(",")
    data.remove('')
    #print(data)
    for k in data:
        ownedProperties[properties[k]] += 1
    # Get feature value for each stage
    data = f.readline().rstrip()
    data = data.split(",")
    #print(data)
    for stage in range(0, 3):
        for c in range(0, 28):
            buyingChance[c][stage][gen] = data[0+(stage*6)+c]
        buildingChance[stage][gen] = data[1+(stage*6)]
        payingJailChance[stage][gen] = data[2+(stage*6)]
        tradingChance[stage][gen] = data[3+(stage*6)]
        minimumBalance[stage][gen] = data[4+(stage*6)]
        minimumCards[stage][gen] = data[5+(stage*6)]

# Plotting or saving to file
# Plot results
for k in range(0, 3):
    for key in features:
        plotResult(key, k, 'save')
# Plot win count
plotWinCount('save')
# Plot properties histogram
plotProperties('save')

# Close file
f.close()
