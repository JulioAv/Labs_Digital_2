'''------------------------------------------------------------------------------
Autor: Julio Avila
Programa: lab 3
Creado: 4 de agosto de 2021    
-------------------------------------------------------------------------------'''

'''------------------------------------------------------------------------------
-------------------------IMPORTAR LIBRERIAS--------------------------------------
------------------------------------------------------------------------------'''
import tkinter as tk            #se importa libreria de GUI
from tkinter import *           #se importa libreria de GUI
import serial                   #se importa libreria de comunicacion serial
import io
'''------------------------------------------------------------------------------
-----------------------DEFINICION DE OBJETOS------------------------------------
------------------------------------------------------------------------------'''
root = Tk()                     #se le da nombre al objeto principal

'''------------------------------------------------------------------------------
-----------------------DEFINICION DE PUERTO SERIAL-------------------------------
------------------------------------------------------------------------------'''
#DEFINICION DE PUERTO SERIAL
port1=serial.Serial('COM1')                                 #declarar puerto serial y braudeaje
#port1.port('COM1')
port1.baudrate = 9600                                       #set Baud rate to 9600
port1.bytesize = 8                                          # Number of data bits = 8
port1.parity   ='N'                                         # No parity
port1.stopbits = 1                                          # Number of Stop bits = 1
#port1.open()                                                #se abre puerto serial
#variable is stored in the root object
root.counter = 0                #se declara una variables en el objeto
prueba=0
'''------------------------------------------------------------------------------
-----------------------DEFINICION DE FUNCIONES-----------------------------------
------------------------------------------------------------------------------'''
#se define funcion para sumar
def Take_input():
    INPUT = inputtxt.get("1.0", "end-1c")
    print(INPUT)
    
      
l = Label(text = "What is 24 * 5 ? ")
inputtxt = Text(root, height = 10,
                width = 25,
                bg = "light yellow")
  
Output = Text(root, height = 5, 
              width = 25, 
              bg = "light cyan")
  
Display = Button(root, height = 2,
                 width = 20, 
                 text ="Show",
                 command = lambda:Take_input())
port1.write(b'input')   #se manda 1 en ascii
    print('2')

'''------------------------------------------------------------------------------
----------------------------CUERPO DE INTERFAZ-----------------------------------
------------------------------------------------------------------------------'''
#TITULO
titulo=tk.Label(root,text = "Interfaz comunicación serial") #texto como titulo de GUI
titulo.place(x=90, y=20)

#titulo de la ventana
root.title("LAB 3")                   #le pones titulo al objeto
root.minsize(400,300)                                           #le decis el tamaño a la ventana

#texto para indicar que hacen los botones
label = tk.Label(root, text = "Contador para el Portx del PIC") #texto para el cuadro de texto
label.place(x=115,y=50)

#boton de suma
b1 = Button(root, text="Suma", command=plus_clicked)
b1.place(x=150, y=75)

#boton de resta 
b2 = Button(root, text="Resta", command=minus_clicked)
b2.place(x=200,y=75)

#POTENCIOMETROS
#prueba=port1.read()
label_pots=tk.Label(root, text=port1.read())
label_pots.place(x=135, y=150)
print(port1.read())

#texto indicador
label1 = tk.Label(root, text = "Valor potenciometro 1")        #texto para el cuadro de texto
label1.place(x=70,y=110)                                       #ubicacion del texto para contador
pot1=tk.LabelFrame(root, text=port1.read())
pot1.place(x=70,y=125)

#POTENCIOMETRO2
#texto indicador
label2 = tk.Label(root, text = "Valor potenciometro 2")        #texto para el cuadro de texto
label2.place(x=210,y=110)                                      #ubicacion del texto para contador
pot2=tk.LabelFrame(root, text=port1.read())
pot2.place(x=260, y=110)
L = Label(root, text="No clicks yet.")                      
L.pack()

'''------------------------------------------------------------------------------
---------------------------------MAIN LOOP---------------------------------------
------------------------------------------------------------------------------'''
root.mainloop()