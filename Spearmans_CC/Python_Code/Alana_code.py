import pandas as pd
from scipy import stats
import random

#import excel file using pandas
df = pd.read_excel("SampleData.xls", "Sheet1")

#create class pairedgenes to contain all info about gene
        
class pairedGenes(object):
    def __init__(self):
        self.distance = 'distance'
        self.stats = 'stats'

print('Welcome! I will correlate spearman\'s cc for you.')
#get random pair numbers from user
random_pairs = int(input('Please enter the number of random pairs desired: '))

#create a dictionary to maintain info on what genes have been used
genesUsed = {}

#run spearmans on random genes until random pairs value is reached
i = 0
print('Randomly pairing genes now...')
if i < random_pairs:
    #get random pair of genes
    gene1 = df.loc[randint(0,len(df))]
    gene2 = df.loc[randint(0,len(df))]
    #while random pairs are unique
    while gene1[0] + gene2[0] not in genesUsed:
        #append pvalue and rho to class of genes
        pairedGene.stats = stats.spearmanr(gene1[1:len(gene1)], gene2[1:len(gene2)])
        print(pairedGene.stats)
        genesUsed = {gene1[0]+ gene2[0] : i}
        i += 1
        #sort the genes based on their distance from one another
        #account for chromosomal position?
        PairedGenes.distance = gene1[-1] - gene2[-1]

print('Finished calculating')

#write PairedGenes information to excel file
#-----------------------------------------------
