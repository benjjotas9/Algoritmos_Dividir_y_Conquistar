import csv
import random

# Parametros
num_datos = 10**6  # Número de datos a generar
rango_min = 0      
rango_max = 10000 
archivo_csv = 'datos_aleatorios.csv'

# Generar datos aleatorios
datos = [random.randint(rango_min, rango_max) for _ in range(num_datos)]

# Escribir datos en un archivo CSV
with open(archivo_csv, mode='w', newline='') as archivo:
    escritor_csv = csv.writer(archivo)
    for dato in datos:
        escritor_csv.writerow([dato])

print(f'Datos generados y guardados en {archivo_csv}')
