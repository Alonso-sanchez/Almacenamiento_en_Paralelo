import  urllib2
import json
from pyspark import SparkContext

fecha1 ="2020-12-10T19:22:18"
fecha2 ="2020-12-10T19:30:23"
response = urllib2.urlopen('http://144.202.34.148:6969/device/mayor?fecha1='+fecha1+'.000Z&fecha2='+fecha2+'.000Z')
data = json.load(response)

def wmenormayor(V, pos):
	if(V!=[]):
		mayor = V[0]
		menor = V[0]
		i = 0
		while i < len(V):
			if V[i] <= menor:
				menor = V[i]
			else:
				mayor = V[i]
			i += 1
		print ("El mayor angulo de la posicion ",pos," es: ",mayor," y el menor es :",menor)
	else:
		print("No hay valor para ",pos)

if __name__ == "__main__":
	sc = SparkContext(appName="Mayor de las posiciones")
	def programa1(p):
		izquierda = []
		centro = []
		derecha = []
		for e in data:
			if (e.get('estado') == "Izquierda"):
				izquierda += [e.get('angulo')]
			elif(e.get('estado') == "Derecha"):
				derecha += [e.get('angulo')] 
			else:
				centro += [e.get('angulo')]
		wmenormayor(izquierda,"izquierda")
		wmenormayor(centro,"centro")
		wmenormayor(derecha,"derecha")

sc.parallelize([1], 4).map(programa1).collect()
