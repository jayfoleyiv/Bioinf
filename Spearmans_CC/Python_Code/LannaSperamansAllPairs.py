class PairedGene(object):
    def __init__(self):
        self.stats = stats

from random import randint
from scipy import stats
import pandas as pd
df = pd.read_excel("SampleData.xls", "Sheet1")

print(df)

print('I will calculate spearmans cc for you!')

#get random pair numbers from user

#create a dictionary to maintain info on what genes have been used
genesUsed = {}
calculatedGenes = []

print('Calculating statistics now...')

i = 0
while i < len(df):
    j = 0
    while j < len(df):
        gene1 = df.loc[i]
        print(gene1)
        gene2 = df.loc[j]
        print(gene2)
        if gene1[0]+ gene2[0] not in genesUsed:
            if gene1[0] != gene2[0]:
                pairedGene = PairedGene()
                pairedGene.stats = stats.spearmanr(gene1[1:len(gene1)], gene2[1:len(gene2)])
                print(pairedGene.stats)
                genesUsed.update ({gene1[0]+ gene2[0] : pairedGene.stats})
                calculatedGenes.append(pairedGene)
        j += 1
    i += 1

print('Statistics calculated!')
print(genesUsed)
print(calculatedGenes)

df = pd.DataFrame(genesUsed)
writer = pd.ExcelWriter('pandas_simple.xlsx', engine = 'xlsxwriter')
df.to_excel(writer, sheet_name='Sheet1')
writer.save()

for gene in calculatedGenes:
    print(gene.stats)
