class PairedGene(object):
    def __init__(self):
        self.stats = stats
        self.distance = distance
        
from random import randint
from scipy import stats
import pandas as pd
import math

print('I will calculate spearmans cc and distance for you!')
print()
print('Please note, data sheet must have titles in the first row and first column!')
print()
sheet = input('Please enter the name of the data sheet for SCC, followed by the extension: ')

#read sheet input by user
df = pd.read_excel(sheet, "Sheet1")
cols = [i for i in range(len(df.columns))]

#convert all non numerical values to nan, including absent values and strings
df.iloc[:,1:] = df.iloc[:,1:].apply(pd.to_numeric, errors='coerce').values

print(df)
calcpairedgenes = {}

for i in len(df.rows):
    gene1 = df[i]
    #get 10 rows before and after
    for j in range(1:10):
        geneneg = df[i-j]
        #calculate spearmans
        #create a new function
        pairedGene = new PairedGene()
        pairedGene.stats = stats
        calcpairedgenes.update ({gene1+ geneneg : pairedGene})
        #end function
        genepos = df[i+j]
        #calculate spearmans
        pairedGene = new PairedGene()
        pairedGene.stats = stats
        calcpairedgenes.update ({gene1+ genepos : pairedGene})
        
sheet = input('Please enter the name of the data sheet for distance, followed by the extension: ')

#read sheet input by user
df = pd.read_excel(sheet, "Sheet1")
cols = [i for i in range(len(df.columns))]

#convert all non numerical values to nan, including absent values and strings
df.iloc[:,1:] = df.iloc[:,1:].apply(pd.to_numeric, errors='coerce').values
       
for i in len(df.rows):
    gene1 = df[i]
    #get 10 rows before and after
    for j in range(1:10):
        geneneg = df[i-j]
        #calculate distance
        #create a new function
        pairedGene = calcpairedgenes.get(gene1 + geneneg)
        pairedGene.distance = distance
        calcpairedgenes.update ({gene1+ geneneg : pairedGene})
        #end function
        genepos = df[i+j]
        #calculate distance
        pairedGene = calcpairedgenes.get(gene1 + genepos)
        pairedGene.distance = distance
        calcpairedgenes.update ({gene1+ genepos : pairedGene})
