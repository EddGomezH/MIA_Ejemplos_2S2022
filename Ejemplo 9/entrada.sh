# Archivo de Ejemplo 1
# MIA 2do Semestre 2022

# Creacion de primer disco
mkdisk -size=50 -unit=m -path=/home/mia/Disco1.dk

# Creacion particiones disco 1, 4 primarias
fdisk -Size=5 -path=/home/mia/Disco1.dk -unit=m -name=Particion1 -fit=ff
fdisk -Size=1024 -path=/home/mia/Disco1.dk -unit=k -name=Particion2
fdisk -Size=10 -unit=m -path=/home/mia/Disco1.dk -name=Particion3
fdisk -Size=25 -path=/home/mia/Disco1.dk -name=Particion4 -fit=wf -unit=m 

# Creacion de segundo y tercer disco
mkdisk -size=25 -fit=bf -unit=m -path="/home/mia/primer semestre/Disco2.dk"
mkdisk -unit=k -size=75 -path="/home/mia/primer semestre/entrada1/Disco3.dk"

# Creacion de particiones disco 2, 3 primarias 1 extendida
fdisk -Size=500 -unit=k -path="/home/mia/primer semestre/Disco2.dk" -name=Particion1 -fit=ff
fdisk -Size=1024 -path="/home/mia/primer semestre/Disco2.dk" -unit=k -name=Particion2
fdisk -Size=10 -unit=m -path="/home/mia/primer semestre/Disco2.dk" -name=Particion3
fdisk -unit=k -Size=4096 -path="/home/mia/primer semestre/Disco2.dk" -type=E -name=Particion4 -fit=wf  

# Creacion de particiones disco 3, 2 primarias, 1 extendida y 2 logicas
fdisk -Size=5000 -path="/home/mia/primer semestre/entrada1/Disco3.dk" -name=Particion1 -unit=b 
fdisk -Size=30 -path="/home/mia/primer semestre/entrada1/Disco3.dk" -unit=m -type=E -fit=bf -name=Particion2
fdisk -Size=5 -type=L -unit=m -path="/home/mia/primer semestre/entrada1/Disco3.dk" -name=Particion3
fdisk -type=L -unit=k -Size=4096 -path="/home/mia/primer semestre/entrada1/Disco3.dk" -name=Particion4
fdisk -Size=3 -path="/home/mia/primer semestre/entrada1/Disco3.dk" -name=Particion5 -unit=m 