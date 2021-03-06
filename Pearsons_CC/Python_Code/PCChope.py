import sys
import math
import numpy as np
from xlrd import open_workbook
import xlwt
from random import randint
#import matplotlib.pyplot as plt

if len(sys.argv) < 2:
	print ("You must pass a data file like so: python geo.pyworks1 <data file>")
	sys.exit()
workbook = open_workbook(sys.argv[1])
worksheet = workbook.sheet_by_index(0)
first_array = []
second_array = []
pcc = []
geneone= []
genetwo = []
repeat = []
gene_name_question = input('What column are the gene names under: ')
gene_name_col = int(gene_name_question)
expression_col_question = input('How many time-points are there?: ')
expression_col = int(expression_col_question)
expression_col_a = range(0, expression_col)
expression_col_b = list(expression_col_a)
Expression_Profile_Columns = expression_col_b
Total_Iteration_Question = input('How many itterations would you like to run?: ')
Total_Iteration_a = int(Total_Iteration_Question)
# Second array value can not be zero for some reason. So instruct user that profile must start on second row
First_Row_In_Sheet = 1
Total_Iterations = Total_Iteration_a

def get_array_from_row(row):
	new_array = []

	for col in Expression_Profile_Columns:
		try:
			new_array.append(worksheet.cell(row, col).value)
		except:
			print ("[" + str(row) + "," + str(col) + "] [row, col] is invalid.")
			return None
	return new_array


def PCC(x, y):
#make phi(X)
	n = len(x)
	pDifX = []
	PpowX = []
	PdivX = []
	for i in range(0, n, 1):
		difX = x[0] - x[i]
		pDifX.append(difX)
		powPX = math.pow(pDifX[i], 2)
		PpowX.append(powPX)
		XdivN = PpowX[i] / (n- 1)
#I KNOW WHY!!!!! The "n" Dr.Foley is working only...
#...includes all numbers but the offset or x[0]
		PdivX.append(XdivN)
		PsumX = math.fsum(PdivX)
		PhiX = math.sqrt(PsumX)
#make phi(Y)
	m = len(y)
	pDifY = []
	PpowY = []
	PdivY = []
	for j in range(0, m, 1):
		difY = y[0] - y[j]
		pDifY.append(difY)
		powPY = math.pow(pDifY[j], 2)
		PpowY.append(powPY)
		YdivM = PpowY[j] / (m- 1)
		PdivY.append(YdivM)
		PsumY = math.fsum(PdivY)
		PhiY = math.sqrt(PsumY)
#PCC X-component 
	nXy = len(x)
	IdifX = [] 
	CompXY = []
	nY = len(y)
	IdifY = [] 
	ProdXY = []
	for ixy in range (0, nXy, 1):
		difix = x[0] - x[ixy]
		IdifX.append(difix)
		Xcomp = IdifX[ixy] / PhiX
#PCC Y-component 
		difiy = y[0] - y[ixy]
		IdifY.append(difiy)
		Ycomp = IdifY[ixy] / PhiY
#PCC multiply x,y
		XYProd = Xcomp * Ycomp
		ProdXY.append(XYProd)
	SumXY = math.fsum(ProdXY)
	PCCXY = SumXY / (n- 1)
	pcc.append(PCCXY)

	#print (PhiX)
	#print (PhiY)
	#print (PCCXY)
def output(filename, sheet1, list1):
	book = xlwt.Workbook()
	sh = book.add_sheet(sheet1)
	n = 0
	col_one = 'PCC Value'
	col_two = 'Gene 1'
	col_three = 'Gene 2'
	sh.write(0,0, col_one,)
	sh.write(0,1, col_two)
	sh.write(0,2, col_three)
	for m, e1 in enumerate(pcc, n+1):
		sh.write(m, 0, e1)
	for m, e2 in enumerate(geneone, n+1):
		sh.write(m, 1, e2)
	for m, e3 in enumerate(genetwo, n+1):
		sh.write(m, 2, e3)
	book.save(filename)

for count in range(0, Total_Iterations):
	try:

		random_row = randint(First_Row_In_Sheet, worksheet.nrows - 1)
		random_row2 = randint(First_Row_In_Sheet, worksheet.nrows - 1)
		first_array = get_array_from_row(random_row)
		second_array = get_array_from_row(random_row2)
		random_row_check = random_row == random_row2


		if first_array is None or second_array is None:
			repeat.append(1)
			raise
		if random_row_check == 1:
			repeat.append(random_row_check)
			raise 
		gene1 = worksheet.cell_value(rowx=random_row, colx=(gene_name_col -1))
		geneone.append(gene1)
		gene2 = worksheet.cell_value(rowx=random_row2, colx= (gene_name_col- 1))
		genetwo.append(gene2)

		PCC(first_array, second_array)

	except:
		Total_Iterations += 0
		pass




print ("Skipped Itterations: " + str(len(repeat)))
print ('Workbook Made')
#histogram = plt.hist(pcc, bins= 100)
#plt.show()
output('PCC_Results.xls', 'pcc_value', pcc)

print("Printing PCC Array\n")
print(pcc)

#print (histogram)



#x = [ 0.000000, -0.128000, -0.097000, -0.020000, -0.272000, -0.198000, -0.333000]
#y = [ 0.775000, 0.849000, 0.518000, 0.116000, -0.076000, -0.090000, 0.102000]
#PCC(x, y)


