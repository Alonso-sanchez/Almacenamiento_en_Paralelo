import  urllib2

from operator import add
import json
from pyspark import SparkContext

response = urllib2.urlopen('http://144.202.34.148:6969/device/')
data = json.load(response)

def prom(V,estado):
	pro = 0
	for e in V:
		if (e!= None):
			pro += e
	print "El promedio de valores de la posicion ", estado," es ",pro/len(V)

if __name__ == "__main__":
	sc = SparkContext(appName="Promedio de angulos para las posiciones")
	def programa2(p):
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
		# ~ print izquierda,derecha,centro
		prom(izquierda,"izquierda")
		prom(centro,"centro")
		prom(derecha,"derecha")

a = sc.parallelize([1], 5).map(programa2).reduce(add)
print a

