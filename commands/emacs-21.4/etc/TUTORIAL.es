Copyright (c) 1985 Free Software Foundation, Inc;  Vea al final las 
condiciones. Usted est� viendo el tutorial de Emacs.

Los comandos de Emacs generalmente ivolucran la tecla CONTROL (algunas
veces llamada CTRL O CTL) o la tecla META (algunas veces llamada EDIT o 
ALT). En lugar de escribir esto completamente en cada ocasi�n, usaremos 
las siguientes abreviaciones.

 C-<chr> significa mantener presionada la tecla CONTROL mientras digita el
         caracter <chr>. Por lo tanto C-f ser�: Mantenga presionada la 
	 tecla CONTROL y digite f.
 M-<chr> significa mantenga presionada la tecla META o EDIT o ALT mientras
 	 teclea <chr>. Si no hay teclas META, EDIT o ALT, en su lugar 
	 presione y libere la tecla ESC y luego digite <chr>. 
	 Escribimos <ESC> para la tecla ESC.

Nota importante: para finalizar la sesi�n de Emacs presione C-x C-c. 
(dos caracteres.) los caracteres ">>" al margen izquierdo indican 
instrucciones para que usted trate de usar un comando. Por ejemplo:  
<<Blank lines inserted around following line by help-with-tutorial>>
[Mitad de p�gina en blanco para prop�sitos did�cticos. El texto contin�a abajo]

[Middle of page left blank for didactic purposes.   Text continues below]
>> Ahora digite C-v (ver la proxima pantalla) para desplazarse a la 
	siguiente pantalla (h�galo manteniendo la tecla CONTROL oprimida
	mientras digita v). 
	Desde ahora usted deber�a hacer esto cada vez que termine de 
	leer la pantalla

Note que se superponen dos l�neas cuando usted se mueve de pantalla en 
pantalla; esto provee una continuidad para que pueda seguir leyendo el 
texto.

La primera cosa que necesita saber es como moverse de un lugar a otro en 
el texto. Usted ya sabe como adelantar una pantalla con C-v. Para mover 
atr�s una pantalla oprima M-v (mantenga oprimida la tecla META y digite v,
o presione <ESC>v si no tiene las teclas META, EDIT o ALT).

>>  Intente oprimir M-v y luego C-v, varias veces.

* RESUMEN
---------
        
Los siguientes comandos son �tiles para ver pantallas completas:

	C-v 	Avanzar una pantalla completa
	M-v 	Retroceder una pantalla completa
	C-l 	Limpiar la pantalla y mostrar todo el texto de nuevo, 
		moviendo el texto alrededor del cursor al centro de la 
		pantalla (Esto es control-L, no control-1.)

>> Encuentre el cursor, y note cual texto est� cerca a este.
   Luego oprima C-l.
   Encuentre el cursor otra vez y note que el mismo texto est� cerca al 
   cursor ahora.

* MOVIMIENTO B�SICO DE CURSOR
-----------------------------

Moverse de una pantalla completa a otra es �til, �pero c�mo moverse a
un lugar espec�fico dentro del texto en la pantalla?

Hay varias formas para que pueda hacerlo.  La forma m�s b�sica es usar los
comandos C-p, C-b, C-f, y C-n.  Cada uno de estos comandos mueve el cursor
una fila o columna en una direcci�n particular en la pantalla.
Aqu� hay una tabla mostrando estos cuatro comandos y las direcciones en 
que ellos mueven
                               
		        L�nea Anterior, C-P
				:
				:
   Atr�s, C-b.... Posici�n actual del cursor .... Adelante, C-f 
				:
				:
			L�nea siguiente, C-n

>> Mueva el cursor a la l�nea en la mitad del diagrama 
   usando C-n o C-p. Luego presione C-l para ver el 
   diagrama completo centrado en la pantalla.

Usted probablemente encontrar� f�cil recordarlos mediante las letras
P de Previous (anterior), N de Next (siguiente), B de Backward (atr�s) 
y F de Forward (adelante).
Estos son los comandos b�sicos de posicionamiento del cursor y estar� 
us�ndolos TODO el tiempo, ser�n de gran beneficio si los aprende a usar 
ahora.

>> Presione unas veces C-n para traer el cursor a esta l�nea.

>> Mu�vase en la l�nea con C-f y hacia arriba con C-p. 
   Observe lo que hace C-p cuando el cursor est� en la mitad de la l�nea.

Cada l�nea de texto termina con un caracter de nueva l�nea, esto sirve 
para separarla de la siguiente l�nea. La �ltima l�nea en su archivo debe 
tener una nueva l�nea al final (pero Emacs no requiere que esta lo tenga).

>> Intente usar C-b al comienzo de una l�nea. Deber�a moverse al 
   final de la l�nea previa. Esto es porque retrocede antes del caracter 
   de nueva l�nea.

C-f puede moverse por una nueva l�nea justo como C-b.

>> Presione algunas C-b m�s para que entienda donde se encuentra el cursor.
   Luego presione C-f para retornar al final de la l�nea.
   Al final presione una vez mas C-f para moverse a la siguiente l�nea.

Cuando pase el tope o el final de la pantalla, el texto m�s all� del borde
de la pantalla se mostrar�. Esto es llamado "desplazamiento"  Esto le 
permite a Emacs mover el cursor al lugar especificado en el texto sin 
moverlo fuera de la pantalla.

>> Intente mover el cursor fuera del borde de la pantalla con C-n y
   observe qu� pasa.

Si moverse por caracteres es muy lento, se puede mover por palabras. M-f
(META-F) mueve adelante una palabra y M-b mueva atr�s una palabra.

>> Oprima unas veces M-f y M-b

Cuando est� en la mitad de una palabra, M-f mueve al final de la palabra.
Cuando est� en un espacio entre dos palabras, M-f mueve al final de la
siguiente palabra.  M-b trabaja de la misma forma en la direcci�n opuesta.

>> Oprima unas veces M-f y M-b, intercale con C-f y C-b de tal forma que 
   observe la acci�n de M-f y M-b desde varios sitios dentro y entre 
   palabras.

Note el paralelo entre C-f y C-b de un lado y M-f y M-b del otro. 
Muy frecuentemente los caracteres Meta son usados para operaciones 
relacionadas, con las unidades definidas por el lenguaje
(palabras, oraciones y p�rrafos), mientras los caracteres Control operan 
sobre unidades que son independientes de lo que usted est�
editando (caracteres, l�neas, etc).

Este paralelo se aplica entre l�neas y oraciones: C-a y C-e para moverse
al comienzo o al final de la l�nea; y M-a y M-e para mover al comienzo o
al final de una oraci�n.

>> Intente unas veces C-a, y a continuaci�n C-e.
>> Intente unos M-a, y otros M-e.

Mire c�mo la repetici�n de C-a no hace nada, pero la repetici�n de M-a 
sigue moviendo una oraci�n adelante, aunque no son muy an�logas, cada una
parece natural.

La localizaci�n del cursor en el texto es tambi�n llamada "punto", en 
otras palabras el cursor muestra sobre la pantalla donde esta el punto
localizado dentro del texto.

Aqu� hay un resumen de operaciones simples del movimiento del cursor, 
incluyendo los comandos de movimiento en oraci�n y palabra:     

	C-f 	Moverse adelante un caracter
	C-d 	Moverse atr�s un caracter

	M-f 	Moverse adelante una palabra
	M-b 	Moverse atr�s una palabra

	C-n 	Moverse a la l�nea siguiente
	C-p 	Moverse a la l�nea anterior

	C-a 	Moverse al comienzo de la l�nea
	C-e 	Moverse al final de la l�nea

	M-a 	Moverse al comienzo de la oraci�n
	M-e 	Moverse al final de la oraci�n

>> Pruebe todos estos comandos unas veces para practicar.
   Estos comandos son los usados m�s frecuentemente.

Otros dos comandos de movimiento del cursor importantes son M-< (Meta  
Menor que), el cual se mueve al comienzo del texto entero, y M->( Meta
Mayor que), el cual se mueve al final del texto entero.

En la mayor�a de terminales, el "<" est� sobre la coma, por lo tanto usted
puede usar la tecla shift para generarlo. En estas terminales usted podr�
usar la tecla shift tambi�n al teclear M-<; sin la tecla shift, usted 
estar�a escribiendo M-coma.

>> Ahora pruebe M-<, para moverse al comienzo del tutorial.
   A continuaci�n use C-v repetidamente para regresar aqu�.

>> Ahora pruebe M->, para moverse el final del tutorial.
   Despu�s use M-v repetidamente para regresar aqu�.

Tambi�n puede mover el cursor con las teclas de la flecha si su
terminal tiene teclas de flecha. Recomendamos aprender C-b, C-f,
C-n y C-p por tres razones. Primero, ellos funcionan en todo tipo de 
terminales. Segundo, una vez usted gane pr�ctica usando Emacs, usted 
encontrar� que teclear estos caracteres Control es m�s r�pido que
usar teclas de flecha ( porque no tendr� que retirar sus manos de
la posici�n para teclear). Tercero, una vez tenga el h�bito de usar
estos comandos Control, tambi�n puede aprender f�cilmente a usar otros
comandos avanzados de movimiento de cursor.

La mayor�a de comandos de Emacs aceptan un argumento num�rico; para
la mayor�a de comandos esto sirve como un factor de repetici�n. La manera que 
a un comando usted da un factor de repetici�n es tecleando C-u y luego los 
d�gitos antes de introducir los comandos. Si usted tiene una tecla META 
( o EDIT o ALT), hay una manera alternativa para ingresar un argumento 
num�rico:  teclear los d�gitos mientras presiona la tecla META. 
Recomendamos aprender el m�todo C-u porque este funciona en cualquier terminal.
El argumento  num�rico es tambi�n llamado un "argumento prefijo", porque usted
teclea el argumento antes del comando al que se aplica.

Por ejemplo, C-u 8 C-f mueve hacia adelante ocho caracteres.
            
>> Pruebe usar C-n o C-p con un argumento num�rico, para mover el cursor
   a una l�nea cerca a esta con solo un comando.

La mayor�a de comandos usan argumentos num�ricos como un factor de repetici�n, 
pero algunos comandos lo usan de otra forma. Varios comandos (pero ninguno 
de los que ha aprendido hasta ahora) usan esto como una marca -- la 
presencia de un argumento prefijo, sin tener en cuenta su valor, hace 
que el comando act�e de forma diferente.

C-v y M-v son otro tipo de excepci�n. Cuando se les da un argumento, 
ellos desplazan la pantalla arriba o abajo esa cantidad de l�neas, en vez
de una pantalla completa. Por ejemplo, C-u 8 C-v desplaza la pantalla 8 
l�neas.

>> Pruebe tecleando C-u 8 C-v ahora.

Este debi� haber desplazado la pantalla hacia arriba 8 l�neas. 
Si usted quisiera desplazarla hacia abajo de nuevo, usted puede dar un 
argumento a M-v.

Si usted esta usando X Window, debe haber una �rea rectangular larga
llamada una barra de desplazamiento al lado izquierdo de la ventana de 
Emacs. Usted puede desplazar el texto al oprimir el bot�n del mouse en la 
barra de desplazamiento.

>> Pruebe presionando el bot�n del medio en la parte superior del area 
   resaltada en la barra de desplazamiento. Este debe desplazar el texto a
   una posici�n determinada por cu�n alto o bajo oprima el bot�n.

>> Intente mover el mouse arriba y abajo, mientras mantiene el bot�n el 
   medio presionado.  Usted ver� que el texto se desplaza arriba y abajo 
   a medida que mueve el mouse.



* CUANDO EMACS EST� BLOQUEADO
-----------------------------

Si Emacs deja de responder a sus comandos, usted puede detenerlo con 
seguridad al teclear C-g. Puede usar C-g para detener un comando 
que est� tomando mucho tiempo para ejecutarse.

Tambi�n puede usar C-g para descartar un argumento num�rico o el comienzo
de un comando que usted no quiere finalizar.

>> Escriba C-u 100 para hacer un argumento num�rico de 100, entonces
   pruebe C-g. Ahora pruebe C-f. Esto deber� mover s�lo un caracter, ya
   que usted cancel� el argumento con C-g.

Si usted ha digitado <ESC> por error, usted puede desecharlo con un C-g.


* COMANDOS DESACTIVADOS
-----------------------

Algunos comandos de Emacs son "desactivados" de manera que los usuarios 
principiantes no puedan usarlos por accidente.

Si usted prueba uno de los comandos desactivados, Emacs muestra un mensaje
informando cu�l comando era, y pregunt�ndole si usted quiere continuar y 
ejecutar el comando.

Si usted realmente quiere intentar el comando, oprima espacio como repuesta
a la pregunta. Normalmente, si usted no quiere ejecutar el comando 
desactivado, conteste la pregunta con "n".

>> Escriba C-x C-l (que es un comando desactivado), a continuaci�n escriba
   n para responder la pregunta.


* VENTANAS
----------

Emacs puede tener varias ventanas, cada una mostrando su propio texto. 
Explicaremos despu�s como usar m�ltiples ventanas. Ahora queremos 
explicar c�mo deshacerse de ventanas adicionales y volver a la edici�n 
b�sica en una ventana. Es sencillo:

	C-x 1 	Una ventana (i.e.,  elimina todas las otras ventanas).

Esto es Control x seguido por el d�gito 1. C-x 1 expande la ventana que 
contiene el cursor, para ocupar toda la pantalla. Esto borra todas las 
otras ventanas.

>> Mueva el cursor a esta l�nea y escriba C-u 0 C-l.
>> Escriba Control-h k Control-f.
   Mire como esta ventana se encoge, mientras una nueva aparece y 
   muestra documentaci�n sobre el comando Control-f.

>> Escriba C-x 1 y vea la ventana de listado de documentaci�n desaparecer.

Este comando es diferente a los otros comandos que usted ha aprendido en 
que este consiste de dos caracteres. Este comienza con el caracter Control-x. 
Hay toda una serie de comandos que comienzan con Control-x; muchos de 
ellos tienen que ver con ventanas, archivos, buffers y cosas 
relacionadas. Estos comandos son de una longitud de dos, tres o cuatro 
caracteres.

* INSERTANDO Y BORRANDO
-----------------------

Si usted quiere insertar un texto s�lo escr�balo. Los caracteres que 
usted puede ver, tales como A, 7, *, etc. Son tomados por Emacs como texto
e insertados inmediatamente. Oprima <Return> (la tecla Enter) para 
insertar un caracter de nueva l�nea.

Usted puede borrar el �ltimo caracter que escribi� oprimiendo <Delete>. 
<Delete> es una tecla, que puede estar marcada como "Del". En algunos
 casos la tecla "Backspace" sirve como <Delete>, �pero no siempre!

Generalmente <Delete> borra el caracter inmediatamente anterior a la
posici�n actual del cursor.

>> Haga esto ahora -- Teclee unos pocos caracteres, y b�rrelos con
   la tecla <Delete>. No se preocupe si este archivo cambia, no alterar� 
   el tutorial principal. Esta es su copia personal.

Cuando una l�nea de texto se hace muy grande para una sola l�nea en la
pantalla, la l�nea de texto es "continuada" en una segunda l�nea. Un
backslash ("\") en el margen derecho indica que la l�nea ha sido 
continuada.

>> Inserte texto hasta que llegue al margen derecho, y siga insertando.
   Ver� a continuaci�n aparecer una l�nea.

>> Use <Delete> para borrar el texto hasta que la l�nea de nuevo quepa
   en la pantalla. La l�nea de continuaci�n se pierde.

Puede borrar un caracter de Nueva l�nea justo como cualquier otro 
caracter. Al borrar un caracter de Nueva l�nea entre dos l�neas 
las combina en una sola. Si el resultado de la combinaci�n de l�neas es
demasiado largo para caber en el ancho de la pantalla, ser� mostrada 
una l�nea de continuaci�n.

>> Mueva el cursor al comienzo de una l�nea y oprima <Delete>. Esto 
   unir� esta l�nea con la anterior.

>> Oprima <Return> para reinsertar la nueva l�nea que borr�.

Recuerde que a la mayor�a de los comandos de Emacs se les puede dar un 
factor de repetici�n, esto incluye caracteres de texto. Repetir un 
caracter de texto lo inserta varias veces.

>> Ahora trate esto -- teclee C-u 8 * para insertar ********.

Usted ha aprendido la manera m�s b�sica de teclear algo en Emacs
y corregir errores. Puede borrar por palabras o por l�neas. Este es un
resumen de las operaciones de borrado:

	<Delete> 	borra el caracter justo antes que el cursor
	C-d		borra el siguiente caracter despu�s del cursor 

	M-<Delete> 	Elimina la palabra inmediatamente antes del cursor
	M-d        	Elimina la siguiente palabra antes del cursor

	C-k  		Elimina desde el cursor hasta el fin de la l�nea  
	M-k  		Elimina hasta el final de la oraci�n actual.

Note que <Delete> y C-d contra M-<Delete> y M-d extienden el paralelo
iniciado por C-f y M-f (bien, <Delete> no es realmente una tecla de 
control, pero no nos preocuparemos ahora por eso). C-k y M-k son como
C-e y M-e, en ciertas forma, en que las l�neas son oraciones opuestas.

Tambi�n puede eliminar cualquier parte del buffer con un m�todo uniforme.
Mu�vase a un extremo de esa parte, y digite C-@ o C-SPC (cualquiera de 
los dos). Mu�vase al extremo de esa parte y teclee
C-w. Eso elimina todo el texto entre las dos posiciones. 

>> Mueva el cursor a la letra T al inicio del p�rrafo anterior.
>> Teclee C-SPC. Emacs debe mostrar el mensaje "Mark set" en la parte de 
   abajo de la pantalla.
>> Mueva el cursor a la x en "extremo", en la segunda l�nea del p�rrafo.
>> Teclee C-w. Esto eliminar� el texto que comienza desde la T, y 
   termina justo antes de la x.

La diferencia entre "eliminar" y "borrar" es que el texto "eliminado"
puede ser reinsertado, mientras que las cosas "borradas" no pueden
ser reinsertados.

La reinserci�n de texto eliminado es llamada "yanking".  Generalmente,
los comandos que pueden remover mucho texto lo eliminan (configurados de
esta forma para poder recuperarlo), mientras que los comandos que 
remueven un solo caracter, o solamente l�neas en blanco o espacios, 
hacen un borrado (sin que usted pueda recuperar dicho texto).

>> Mueva el cursor al comienzo de una l�nea que no est� desocupada. Luego
   digite C-k para eliminar el texto de esa l�nea.
>> Oprima C-k por segunda vez. Usted ver� que elimina la nueva
   l�nea que sigue a esa.

Note que al oprimir C-k una sola vez elimina el contenido de la l�nea , y
un segundo C-k elimina la l�nea misma, y hace que todas las otras l�neas 
se muevan hacia arriba. C-k trata un argumento num�rico especialmente: 
Elimina ese n�mero de l�neas y sus contenidos. Esto no es una simple 
repetici�n. C-u 2 C-k elimina dos l�neas y sus nuevas l�neas, tecleando 
C-k dos veces no hace esto.

Recuperar texto eliminado es llamado "yanking". (Piense en esto como si 
estuviera recuperando, reinsertando, alg�n texto que fue eliminado). 
Puede recuperar el texto eliminado o bien en el mismo sitio de d�nde fue 
eliminado o en otro lugar en el buffer, o inclus en un archivo diferente.
Puede reinsertar el texto varias veces, lo que hace m�ltiples copias del
mismo.

El comando para recuperar es C-y. Este reinserta el  �ltimo texto 
eliminado, en la posici�n actual del cursor. 

>>Int�ntelo; oprima C-y para recuperar el texto.

Si usted tecleea muchos C-k s seguidos, todo el texto eliminado es salvado
junto, de forma tal que un C-y lo recuperar� todo de una sola vez.

>>Haga esto ahora, oprima C-k varias veces.

Ahora para recuperar ese texto eliminado:

>> Teclee C-y. Entonces baje el cursor unas pocas l�neas y oprima C-y de 
nuevo. Ahora sabe como copiar un texto.

�Qu� hacer si usted tiene alg�n texto que quiere recuperar, pero elimina
otro antes de recuperarlo? C-y recuperar�a la eliminaci�n m�s reciente,
pero el texto previo no est� perdido. Puede regresar a �ste usando el 
comando M-y. Despu�s de haber tecleado C-y para conseguir la eliminaci�n
m�s reciente, escribiendo M-y reemplaza el texto recuperado con la 
eliminaci�n previa. Tecleando M-y una y otra vez traer� las 
eliminaciones anteriores. Cuando usted ha encontrado el texto que 
buscaba, usted no tiene que hacer nada para conservarlo.S�lo siga con 
su edici�n, dejando el texto recuperado donde est�.

Si usted digita M-y suficientes veces, usted regresa al punto inicial
(la eliminaci�n m�s reciente)

>> Elimine una l�nea mu�vase, elimine otra l�nea.
   Luego oprima C-y para recuperar la segunda l�nea eliminada.
   Entonces oprima M-y, y ser� reemplazada por la primera l�nea eliminada.
   Oprima m�s veces M-y y vea lo que sucede. Siga haci�ndolo hasta que la
   segunda l�nea eliminada regrese, y entonces unas pocas m�s. Si usted 
   quiere, puede tratar de darle a M-y argumentos positivos y negativos.


* DESHACER 
----------

Si hace un cambio al texto, y luego decide que fue un error,
puede deshacer el cambio con el comando deshacer C-x u.

Normalmente, C-x u deshace los cambios hechos por un comando; si repite
varias veces seguidas C-x u, cada repetici�n deshar� un comando 
adicional.
 
Pero hay dos excepciones: comandos que no cambian el texto no cuentan 
(esto incluye los comandos de movimiento del cursor y el comando de 
desplazamiento), y los caracteres de autoinserci�n son usualmente  manejados
en grupos de hasta 20 (estos es para reducir el numero de C-x u que tiene que 
realizar para deshacer una inserci�n en el texto).

>> Elimine esta l�nea con C-k, despu�s C-x u deber�a reaparecerla.

C-_ es un comando alterno para deshacer, este trabaja igual que C-x u, 
pero es m�s f�cil de usar varias veces seguidas. La desventaja 
de C-_ es que en algunos teclados no es obvio como se genera. Por esto
proveemos C-x u tambi�n. En algunas terminales, usted puede oprimir C-_ 
al digitar / mientras oprime CONTROL.

Un argumento num�rico para C-_ o C-x u act�a como un factor de repetici�n.

Usted puede deshacer el borrado de texto de la misma forma que si lo 
hubiera eliminado. La diferencia entre eliminar algo y borrarlo se hace
visible cuando lo recupera con C-y; no hay diferencia para deshacer.


* ARCHIVOS
----------

Para hacer permanente el texto que edite, lo debe colocar en un 
archivo. De otra manera, este se se perder� cuando cierre Emacs.
Para poder poner su texto en un archivo, usted debe "encontrar" el 
archivo antes de ingresar el texto (esto tambi�n es llamado "visitar" 
el archivo.) 

Encontrar un archivo significa que usted puede observar su contenido 
dentro de Emacs. Esto de cierta forma, es como si usted estuviera editando
el archivo. Aunque los cambios que usted haga usando Emacs no ser�n
permanentes hasta que "salve" el archivo. Esto es para no dejar un archivo
 a medio cambiar en el sistema cuando usted no quiere. Incluso cuando 
usted salve, Emacs dejar� el archivo original bajo un nombre cambiado en 
caso de que luego usted decida que sus cambios fueron un error. 

Si mira cerca del final de la pantalla podr� ver una l�nea que 
comienza y termina con guiones, y comienza con "--:-- TUTORIAL" o algo 
as�. Esta parte de la pantalla normalmente muestra el nombre del archivo 
que est� visitando. En este momento usted est� visitando un archivo 
llamado "TUTORIAL" que es su borrador personal del tutorial de Emacs. Cuando
encuentre un archivo con Emacs, el nombre del archivo aparecer� en ese 
mismo sitio.

Una cosa especial acerca del comando para encontrar un archivo, es que 
usted tendr� que decir cual archivo desea. Decimos que el comando
"lee un argumento desde la terminal" (en este caso, el argumento es 
el nombre del archivo). Despu�s de generar el comando:

	C-x C-f   Encontrar un archivo

Emacs le pide que digite el nombre del archivo. El nombre de archivo que 
digite aparecer� en la l�nea final de la pantalla. A la l�nea final de la 
pantalla se le denomina minibuffer cuando es usada para este tipo de entradas.
Puede usar comandos de edici�n ordinarios de Emacs para editar el nombre 
del archivo.

Cuando est� ingresando el nombre del archivo (o cualquier otra
informaci�n al minibuffer) usted puede cancelar el comando con C-g.

>> Oprima C-x C-f, luego oprima C-g. Esto cancela el minibuffer y 
   tambi�n cancela el comando C-x C-f que estaba usando el 
   minibuffer. As� que no encontrar� archivo alguno.

Cuando usted haya finalizado de ingresar el nombre del archivo, oprima 
<Return> para terminarlo. Entonces el comando C-x C-f trabaja y encuentra
el archivo que usted escogi�. El minibuffer desaparece cuando el comando 
C-x C-f termina. 

Despu�s aparece el contenido del archivo en la pantalla y usted puede editarlo.
Cuando quiera hacer cambios permanentes, teclee el comando

	C-x C-s   Salvar el archivo

Este copia el texto de Emacs al archivo. La primera vez que usted haga 
esto, Emacs renombrar� el archivo original con un nuevo nombre para que 
este no se pierda. El nuevo nombre se obtendr� adicionando "~"
al final del nombre del archivo original.

Cuando la operaci�n de salvar haya terminado, Emacs mostrar� el 
nombre del archivo escrito. Usted deber�a salvar frecuentemente, para que
no pierda mucho trabajo si el sistema deja de funcionar.

>> Presione C-x C-s, salvando la copia del tutorial.  Esto deber�a 
   imprimir "Wrote...TUTORIAL" al final de la pantalla.

NOTA: En algunos sistemas, oprimir C-x C-s dejar� inm�vil la pantalla y 
usted no podr� ver m�s respuesta de Emacs. Esto indica que una 
"caracter�stica" del sistema operativo llamada ''control de flujo'' 
est� interceptando el comando C-s y no permiti�ndole llegar a Emacs. 
Para descongelar la pantalla, presione C-q. Entonces consulte la secci�n 
"entrada espont�nea para b�squeda incremental'' en el manual de 
Emacs para encontrar informaci�n de c�mo tratar con esta "caracter�stica".

Usted puede encontrar un archivo existente para verlo o editarlo, 
tambi�n puede hacerlo con un archivo que no existe. Esta es la forma 
de crear un archivo en Emacs: encuentre el archivo, comenzar� vac�o, luego 
comience a introducir el texto al archivo. Cuando invoque "salvar" el archivo, 
Emacs crear� realmente el archivo con el texto que introdujo. Desde ah�, 
usted puede considerarse estar editando un archivo existente.


* BUFFERS
---------

Si visita un segundo archivo con C-x C-f, el primer archivo permanece en 
Emacs. Usted puede volver al primer encontr�ndolo de nuevo con C-x C-f. De 
esta forma usted puede mantener un gran n�mero de archivos en Emacs.

>> Cree un archivo llamado "foo" presionando C-x C-f foo <Return>
   luego inserte alg�n texto, ed�telo, y salve "foo" presionando C-x 
   C-s. Finalmente presione C-x C-f TUTORIAL <Return> para regresar al 
   tutorial.

Emacs almacena cada archivo de texto dentro de un objeto llamado 
"buffer". Al encontrar un archivo se crea un nuevo buffer dentro de 
Emacs. Para mirar la lista de los buffers que existen actualmente en 
su sesi�n de Emacs, presione:

	C-x C-b   Lista de Buffers

>> Intente ahora C-x C-b.

Mire como cada buffer tiene un nombre, y adem�s puede tener un nombre de 
archivo para el archivo que contiene. Algunos Buffers no corresponden a 
archivos; por ejemplo, el buffer llamado "*Buffer List*" no tiene ning�n 
archivo. Este es el buffer que tiene la lista de buffers que fue creado
por C-x C-b. CUALQUIER archivo de texto que vea en una ventana de Emacs, 
es siempre parte de alg�n Buffer.

>> Presione C-x 1 para deshacerse de la lista de buffers.

Si usted hace cambios al texto de un archivo, y luego encuentra otro 
archivo, esto no salva el primer archivo. Estos cambios permanecer�n 
dentro de Emacs en el buffer del archivo. La creaci�n o edici�n del 
segundo buffer de archivo no afecta al primero. Esto es muy �til pero 
significa que necesita una forma conveniente para salvar el archivo del 
primer buffer. Ser�a una molestia tener que volver a este con C-x C-f
para salvarlo con C-x C-s as� que tenemos
 
	C-x s 	Guardar algunos buffers
 
C-x s le pregunta sobre cada buffer que contenga cambios que usted no
ha salvado.  Le pregunta por cada buffer si salvarlo o no.
 
>> Inserte una l�nea de texto, y teclee C-x s.
   Esto deber�a preguntarle si desea salvar el buffer llamado TUTORIAL.
   Conteste si a la pregunta presionando "y".
 
* EXTENDIENDO EL CONJUNTO DE COMANDOS
-------------------------------------
 
Hay much�simos m�s comandos de Emacs que podr�an ser posiblemente
puestos en todos los caracteres control y meta. Emacs puede lograrlo
usando el comando X (eXtendido).  Este viene de dos formas:

	C-x 	Caracter eXtendido seguido por un caracter.
        M-x 	Comando eXtendido por nombre. Seguido por un nombre largo.
 
Estos comandos son generalmente �tiles pero usados menos que los
comandos que usted hasta ahora ha aprendido. Hasta ahora ha visto dos
de estos: los comandos de archivo C-x C-f para encontrar y C-x C-s
para salvar. Otro ejemplo es el comando para terminar la sesi�n de
Emacs -- este es el comando C-x C-c ( no se preocupe por perder los 
cambios que usted haya hecho; C-x C-c ofrece salvar cada archivo alterado
antes de que este elimine a Emacs.)
 
C-z es el comando para salir de Emacs *temporalmente*-- para que usted
pueda regresar a la misma sesi�n de Emacs despu�s.
 	
En sistemas que lo permiten C-z "suspende" Emacs; esto es, se retorna
al shell pero no se destruye Emacs.  En los shells m�s comunes, usted
puede reanudar Emacs con el comando `fg' o con `%emacs'.
 		
En sistemas que no se implemente el suspendido, C-z crea un subshell
que corre bajo Emacs para darle la opci�n de correr otros programas y
regresar a Emacs despu�s; esto en realidad no "sale" de Emacs. En este
caso, el comando shell `exit' es la v�a usual para regresar a Emacs
desde el subshell.
 
El momento para usar C-x C-c es cuando usted est� listo para salir. 
Es adem�s el paso correcto para salir de Emacs llamado bajo programas de
manejo de correo y otra variedad de utilidades, puesto que ellos no
saben c�mo lidiar con la suspensi�n de Emacs. En circunstancias normales,
si usted no va a salir, es mejor suspender Emacs con C-z en lugar de 
salir de este.
 
 Existen varios comandos C-x. Aqu� hay una lista de algunos que usted
ha aprendido:

	C-x C-f 	Encontrar archivo.
        C-x C-s 	Salvar archivo.
        C-x C-b 	Lista de buffers.
        C-x C-c 	Salir de Emacs.
        C-x 1 		Borrar todo menos una ventana.
        C-x u 		Deshacer.
 
Los comandos llamados eXtendidos son comandos usados con menos frecuencia
o comandos que son usados �nicamente en ciertos modos. Un ejemplo es
el comando replace-string, el cual globalmente reemplaza una cadena
con otra. Cuando usted teclea M-x, Emacs le pregunta al final de la
pantalla con M-x y usted debe escribir el nombre del comando; en este
caso "replace-string". Solo escriba "repl s<TAB>" y Emacs completar�
el nombre. Finalice el nombre del comando con <Return>.
 
 El comando replace-string requiere dos argumentos -- la cadena a
reemplazar, y la cadena para reemplazarla.  Usted debe terminar cada 
argumento con <Return>.
 
>> Mueva el cursor hacia la l�nea en blanco dos l�neas debajo de esta. A
   continuaci�n escriba 
   M-x repl s<Return>cambiado<Return>alterado<Return>.
 
Note c�mo esta l�nea ha cambiado: usted reemplaza la palabra
c-a-m-b-i-a-d-o con "alterado" en cada ocurrencia, despu�s de la
posici�n inicial del cursor.
 
* AUTO SALVADO
--------------
 
Cuando usted ha hecho cambios en un archivo, pero usted no ha salvado
estos todav�a, estos podr�an perderse si su sistema deja de funcionar. Para
protegerlo de esto, Emacs peri�dicamente escribe un archivo "auto salvado"
para cada archivo que usted est� editando. El nombre del
archivo auto salvado tiene un # al principio y al final; por ejemplo, si su 
archivo se llama "hola.c", su archivo auto salvado es "#hola.c#".  Cuando 
usted salva por la v�a normal, Emacs borra su archivo de auto salvado.
 
Si el sistema deja de funcionar usted puede recuperar su edici�n de 
auto salvado encontrando el archivo normal (el archivo que  estuvo editando, 
no el archivo de auto salvar) y entonces presionando M-x recover file<Return>.
Cuando le pregunte por la confirmaci�n, teclee yes<Return> para ir y 
recuperar la informaci�n del auto-salvado.
 
* �REA ECO
----------
 
Si Emacs ve que usted est� presionando comandos de multicaracteres
lentamente, este le muestra estos al final de la pantalla en un �rea
llamada "�rea de eco". El �rea de eco contiene la l�nea final de la pantalla.
 
* L�NEA DE MODO
---------------
 
La l�nea inmediatamente encima del �rea de eco es llamada el "l�nea de modo"
dice algo as�:

--:** TUTORIAL           (Fundamental)--l730--58%---------
 
Esta l�nea da informaci�n �til acerca de el estado de Emacs y del
texto que usted est� editando.
 
Usted ya sabe qu� significa el nombre del archivo -- este es el
archivo que usted ha encontrado.  --NN%-- indica posici�n actual en el
texto; esto significa que NN porciento del texto est� encima de la
parte superior de la pantalla. Si el principio del archivo est� en la
pantalla, este dir� --Top-- en vez de --00%--. Si el final del texto est�
en la pantalla, este dir� --Bot--.  Si usted est� mirando un texto tan
peque�o que cabe en la pantalla, el modo de l�nea dir� --All--.
 
La L y los d�gitos indican la posici�n de otra forma: ellos dan el
n�mero de l�nea actual del punto.
 
Las estrellas cerca del frente significan que usted ha hecho cambios
al texto. Exactamente despu�s de que usted visite o salve un archivo,
esa parte del modo de l�nea no muestra estrellas, solo los guiones.
 
La parte del modo de l�nea dentro de los par�ntesis es para indicarle
en qu� modo de edici�n est� usted. El modo por defecto es Fundamental,
el cual es el que usted est� usando ahora. Este es un ejemplo de un
"modo mayor".
 
Emacs tiene diferentes modos mayores. Algunos de estos est�n
hechos para editar diferentes lenguajes y/o clases de texto, tales como
modo Lisp, modo de Texto, etc.  En cualquier  momento solamente un modo
mayor est� activo, y su nombre se encuentra siempre en el modo
de l�nea donde "Fundamental" est� ahora.
 
Cada modo mayor hace que algunos comandos act�en diferente
por ejemplo, hay comandos para crear comentarios en un programa, y como
cada lenguaje de programaci�n tiene una idea diferente de c�mo debe verse
un comentario, cada modo mayor tiene que insertar comentarios de
forma distinta. Cada modo mayor es el nombre de un comando 
extendido, que es como usted puede cambiar a ese modo. Por ejemplo, 
M-x fundamental-mode es un comando para cambiar al modo fundamental.

Si usted va a editar un texto en espa�ol, tal como este archivo, 
probablemente tendr� que usar el modo de texto.

>> Teclee M-x text-mode<Return>.  

No se preocupe, ninguno de los comandos de Emacs que ha aprendido cambia
de manera significativa.  Pero usted puede ver que M-f y M-b tratan a los
ap�strofes como parte de las palabras.  Previamente, en modo Fundamental,
M-f y M-b trataban los ap�strofes como separadores de palabras.

Los modos mayores usualmente hacen cambios sutiles como el 
anterior: La mayor�a de comandos hacen "el mismo trabajo" en cada modo 
mayor, pero funcionan un poco diferente.

Para ver documentaci�n en su modo mayor actual, teclee C-h m.

>> Use C-u C-v una vez o mas para llevar esta l�nea cerca de la 
   parte superior de la pantalla.

>> Teclee C-h m, para ver c�mo el modo de texto difiere del modo 
   Fundamental.

>> Teclee C-x 1 para eliminar la documentaci�n de la pantalla.

Los modos mayores son llamados as� porque tambi�n hay modos menores.
Los modos menores no son alternativas para los modos mayores, apenas
modificaciones menores de estas.  Cada modo menor puede ser activado o
desactivado por si mismo, independiente de todos los otros modos 
menores, e independiente de su modo mayor.  Entonces usted puede no usar
modos menores, o un modo menor o alguna combinaci�n de varios modos 
menores.

Un modo menor que es muy �til, especialmente para editar textos en
idiomas humanos, es el modo Auto Fill.  Cuando este modo es encendido,
Emacs rompe la l�nea entre palabras autom�ticamente cuando quiera que
inserte texto y haga una l�nea que es bastante ancha.

Usted puede activar el modo Auto Fill al hacer M-x auto fill mode<Return>.
Cuando el modo este activado, usted puede desactivarlo nuevamente usando
M-x autofill mode<Return>.
Si el modo est� desactivado, este comando lo activa, y si el modo est�
activado, este comando lo desactiva. Decimos que el comando "cambia el
modo".

>> Teclee M-x auto fill mode<Return> ahora.  Luego inserte una l�nea
   de "asdf " repetidas veces hasta que la vea dividida en dos l�neas. 
   Usted debe intercalar espacios porque Auto Fill s�lo rompe 
   l�neas en espacios.

El margen es usualmente puesto en 70 caracteres, pero usted puede
cambiarlo con el comando C-x f. Usted debe dar el margen deseado
como un argumento num�rico.

>> Teclee C-x f con un argumento de 20.  (C-u 2 0 C-x f).
   Entonces teclee alg�n texto y vea como Emacs llena con este l�neas de
   20 caracteres.  Entonces ponga de nuevo el margen a 70 usando otra 
   vez C-x f.

Si usted hace cambios en el medio de un p�rrafo, el modo Auto Fill no
lo rellenar� por usted.
Para rellenar el p�rrafo, teclee M-q (Meta-q) con el cursor dentro de
ese p�rrafo.

>>Mueva el cursor al p�rrafo anterior y teclee M-q.

* BUSCANDO
----------

Emacs puede hacer b�squedas de cadenas (estas son grupos de caracteres
contiguos o palabras) hacia adelante a trav�s del texto o para atr�s
en el mismo.  La b�squeda de una cadena es un comando de movimiento de 
cursor; esto mueve el cursor al pr�ximo lugar donde esa cadena aparece.

El comando de b�squeda de Emacs es diferente a los comandos de b�squeda
de los dem�s editores, en que este es "incremental".  Esto significa que
la b�squeda ocurre mientras usted teclea la cadena para buscarla.

El comando para iniciar una b�squeda es C-s para b�squeda hacia adelante,
y C-r para la b�squeda hacia atr�s.  �PERO ESPERE! no intente esto ahora.

Cuando teclee C-s usted ver� que la cadena "I-search" aparece como un 
llamado en el �rea de eco.  Esto le dice que Emacs est� en lo que se
conoce como b�squeda incremental, esperando que usted teclee la cosa que
quiere buscar.  <Return> termina una busqueda.

>> Ahora teclee C-s para comenzar la b�squeda.  LENTAMENTE, una letra a
   la vez, teclee la palabra 'cursor', haciendo pausa despu�s de cada
   caracter para notar lo que pasa con el cursor.
   Ahora ha buscado "cursor", una vez.
>> Ahora teclee C-s de nuevo, para buscar la pr�xima aparici�n de
   "cursor".
>> Ahora presione <Delete> cuatro veces y mire como se mueve el cursor.
>> Teclee <Return> para terminar la b�squeda.

�Vi� lo que ocurri�? Emacs, en una b�squeda incremental, trata de ir a la 
ocurrencia de la cadena que usted ha tecleado hasta el momento.  Para ir
a la pr�xima ocurrencia de "cursor" solo teclee C-s de nuevo.  Si tal  
ocurrencia no existe, Emacs pita y le dice que la b�squeda actual est�
fallando (failing).  C-g tambi�n termina la b�squeda.

NOTA: En algunos sistemas, oprimir C-x C-s dejar� inm�vil la pantalla y 
usted no podr� ver m�s respuesta de Emacs. Esto indica que una 
"caracter�stica" del sistema operativo llamada ''control de flujo'' 
est� interceptando el comando C-s y no permiti�ndole llegar a Emacs. 
Para descongelar la pantalla, presione C-q. Entonces consulte la secci�n 
"entrada espont�nea para b�squeda incremental'' en el manual de 
Emacs para encontrar informaci�n de c�mo tratar con esta "caracter�stica".

Si usted est� en medio de una b�squeda incremental y teclea <Delete>,
usted notara que el �ltimo caracter de la cadena buscada es borrado y
la b�squeda vuelve al �ltimo sitio de la b�squeda.  Por ejemplo, suponga 
que usted ha tecleado "c", para buscar la primera ocurrencia de "c".  
Ahora, si teclea "u", el cursor se mover� a la primera ocurrencia de 
"cu".  Ahora teclee <Delete>.  Esto borra la "u" de la cadena buscada,
y el cursor vuelve a la primera ocurrencia de "c".

Si usted est� en medio de una b�squeda y teclea un caracter 
control o meta (con algunas pocas excepciones-- los caracteres que son 
especiales en una b�squeda, tales como C-s y C-r), la b�squeda es 
terminada.

El C-s inicia una exploraci�n que busca alguna ocurrencia de la cadena 
buscada DESPU�S de la posici�n actual del cursor.  Si usted quiere buscar
algo anterior en el texto, teclee en cambio C-r.  Todo lo que hemos 
dicho sobre C-s tambi�n se aplica a C-r, excepto que la direcci�n de la
b�squeda es invertida.

* M�LTIPLES VENTANAS 
--------------------

Una de las agradables caracter�sticas de Emacs es que usted puede mostrar m�s
de una ventana en la pantalla al mismo tiempo.

>> Mueva el cursor a esta l�nea y teclee C-u 0 C-l.

>> Ahora teclee C-x 2 que divide la pantalla en dos ventanas. Ambas 
   ventanas muestran este tutorial.  El cursor permanece en la ventana 
   superior.

>> Teclee C-M-v para desplazar la ventana inferior.  (Si usted no 
   tiene una tecla Meta real, teclee ESC C-v) 

>> Teclee C-x o ("o" para "otro") para mover el cursor a la ventana 
   inferior.
>> Use C-v y M-v en la ventana inferior para desplazarla.  Siga 
   leyendo estas direcciones en la ventana superior.

>> Teclee C-x o de nuevo para mover el cursor de vuelta a la ventana 
   superior.  El cursor en la ventana superior est� justo donde estaba
   antes.

Usted puede continuar usando C-x o Para cambiar entre las ventanas. Cada
 ventana tiene su propia posici�n del cursor, pero �nicamente una 
ventana actual muestra el cursor. Todos los comandos de edici�n comunes
se aplican a la ventana en que est� el cursor. Nosotros la llamamos 
"ventana seleccionada".

El comando C-M-v es muy �til cuando usted est� editando un texto en una
 ventana y usando la otra ventana como referencia. Usted puede mantener
 el cursor siempre en la ventana donde est� editando, y avanzar a la 
otra ventana secuencialmente con C-M-v.

C-M-v es un ejemplo de un car�cter CONTROL-META. Si usted tiene una 
tecla Meta real, usted puede oprimir C-M-v Sosteniendo a la vez CONTROL
y META mientras oprime v. No importa cual tecla oprima primero CONTROL o META.
Porque las dos teclas act�an modificando los caracteres que usted digita.
Si usted no tiene una tecla META real, y en vez de esta usa ESC, el 
orden importa: usted debe digitar ESC seguido de Control-v, porque 
Control-ESC v no trabajar�. Esto es porque ESC es un car�cter que tiene
valor en s� mismo, no es una tecla modificadora.

>> digite C-x 1 (en la parte de arriba de la ventana) para deshacerse 
   de la ventana del final.

(Si usted hubiera digitado C-X 1 en la ventana inferior, esto eliminar�a la 
superior. Piense en este comando como "mantener s�lo una ventana -- la 
ventana en la cual estoy".)

Usted no tiene que mostrar el mismo buffer en ambas ventanas. Si usted 
usa C-x C-f para encontrar un archivo en una ventana, la otra ventana 
no cambia. Usted puede encontrar un archivo en cada ventana 
independientemente.

Aqu� hay otra forma para usar dos ventanas para mostrar dos cosas 
diferentes:

>> Digite C-x 4 C-f seguido del nombre de uno de sus archivos. 
   Finalice con <Return>. Vea que el archivo especificado aparece en la 
   ventana inferior. El cursor v� all� tambi�n.

>> Digite C-x o para regresar a la ventana superior, y C-x 1 para borrar
   la ventana inferior.

* NIVELES RECURSIVOS DE EDICI�N
--------------------------------

Algunas veces usted entrar� a lo que es llamado un "nivel recursivo 
de edici�n". Esto est� indicado por par�ntesis cuadrados en la l�nea de modo
, rodeando los par�ntesis del nombre del modo mayor. Por ejemplo, 
usted probablemente vea [(Fundamental)] en vez de (Fundamental)

Para salir de los niveles recursivos de edici�n, presione ESC ESC ESC. 
Este es un comando de "salida" para todo prop�sito. Usted tambi�n lo 
puede usar para eliminar ventanas extras, y salir del minibuffer.

>> Digite M-x para entrar a un minibuffer; Entonces digite ESC ESC ESC 
   para salir.

Usted no puede usar C-g para salir de los "niveles recursivos de 
edici�n". Esto es porque C-g es usado para cancelar comandos y 
argumentos DENTRO del nivel recursivo de edici�n.

* CONSIGUIENDO MAS AYUDA
------------------------

En este tutorial hemos tratado de ofrecer suficiente informaci�n para 
que usted empiece a usar Emacs. Hay tanto disponible en Emacs que 
ser�a imposible explicar todo aqu�, sin embargo, usted puede querer 
aprender m�s sobre Emacs, ya que este tiene muchas otras caracter�sticas 
�tiles. Emacs provee comandos para leer documentaci�n acerca de los 
comandos de Emacs. Estos comandos de "ayuda" todos comienza con el 
caracter Control-h, que es llamado el caracter de ayuda (help).

Para usar las caracter�sticas de ayuda, digite el caracter C-h, y 
entonces un car�cter diciciendo qu� tipo de ayuda quiere. Si usted est�
REALMENTE perdido digite c-h ? y Emacs le dir� qu� tipo de ayuda puede 
ofrecerle. Si usted ha digitado C-h y decide que no quiere ninguna 
ayuda, digite C-g para cancelarlo.

(Algunos sitios cambian el significado del car�cter C-h. Ellos realmente
no deber�an hacer esto como una pol�tica para todos los 
usuarios, as� que usted tiene argumentos para quejarse al administrador 
del sistema. Mientras tanto, s� C-h no muestra un mensaje de ayuda en
el final de la pantalla, intente digitar la tecla F1 o en su lugar M-x 
help <Return>).

La caracter�stica m�s b�sica en la AYUDA es C-h c. Digite C-h, el 
caracter c y un caracter de comando o una secuencia de comando; entonces 
Emacs muestra una muy breve descripci�n del comando.

>> Digite C-h c C-p.
   El mensaje debe ser algo como
	 C-p runs the command previous-line

Esto le dice el "nombre de la funci�n". Los nombres de funci�n son 
usados principalmente para adecuar y extender Emacs. Pero ya que los 
nombres de las funciones son seleccionados para indicar lo que el comando
hace, ellos tambi�n pueden servir como una breve documentaci�n --
suficiente para recordarle los comandos que ha aprendido.

Los comandos de m�ltiples caracteres tales como C-x C-s y (s� usted no 
tiene las teclas META o EDIT o ALT) <Esc>v, est�n permitidos tambi�n 
despu�s de C-h c.

Para conseguir m�s informaci�n sobre un comando use C-h k en vez de 
C-h c.

>> Digite C-h k C-p.

Esto muestra la documentaci�n de la funci�n, al igual que el nombre, en
una ventana de Emacs. Cuando usted haya terminado de leer el resultado, 
digite C-x 1 para deshacerse del texto de ayuda. No tiene que hacer esto 
ahora. Usted puede hacer algunas ediciones mientras se refiere al texto 
de ayuda, y entonces digitar C-x 1.

Aqu� hay algunas otras opciones �tiles de C-h:

   C-h f	Describe una funci�n. Usted digita el nombre de la 
		funci�n.

>> Intente digitar C-h f previous-line<Return>.
   Esto imprime toda la informaci�n que Emacs tiene sobre la funci�n que 
   implementa el comando C-p

De forma similar el comando C-h v imprime la documentaci�n de variables
cuyos valores pueden ser especificados para configurar el comportamiento
de Emacs. Necesita teclear el nombre de la variable cuando Emacs lo
pregunte.

   C-h a 	Comando Apropos. Digite una palabra y Emacs har� una 
		lista de todos los comandos que contengan la palabra 
		digitada. Todos Estos comandos pueden ser invocados con 
		Meta-x.  Para algunos comandos, el comando Apropos 
		tambi�n listar� una secuencia de uno a dos caracteres 
		la cual correr� el mismo comando.

>> Digite C-h a file<Return>.

Esto muestra en otra ventana una lista de todos los comandos M-x con
la palabra "file" en sus nombres. Usted ver� comandos de caracteres como
C-x C-f listados adem�s de los nombres de los comandos correspondientes 
tales como find-file.

>> Digite C-M-v para desplazar la ventana de ayuda. Haga esto unas pocas 
   veces.

>> Digite C-x 1 para borrar la ventana de ayuda.

   C-h i        Leer manuales en l�nea (a.k.a. Info). Este comando lo
		lleva a un buffer especial llamado '*info*' en el cual
		puede leer manuales en l�nea de los paquetes instalados 
		en su sistema.  Teclee m emacs <Return> para leer el 
		manual de Emacs.  Si usted nunca ha usado Info antes, 
		teclee ? y Emacs lo llevara a un tour guiado de las 
		facilidades del modo Info.  Una vez que haya finalizado
		este tutorial, deber�a consultar el manual Info de Emacs
		como su primera fuente de documentaci�n.


* CONCLUSI�N
------------

Recuerde, Para salir permanentemente de Emacs use C-x C-c. Para salir a un 
Shell temporalmente, de forma que usted puede volver a Emacs despu�s, use C-z.

Este tutorial intenta ser entendible para todos los usuarios 
nuevos, as� que si encuentra algo confuso, no se siente y se culpe a s�
mismo - �Qu�jese!

* COPIADO
---------

Este tutorial desciende de una larga l�nea de tutoriales de Emacs
comenzando con el escrito por Stuart Cracraft para el Emacs original.
La versi�n en espa�ol fue traducida por estudiantes del Gimnasio Fidel Cano 
(un colegio en Santaf� de Bogot�, Colombia):

	Carlos Alberto L�pez Troncoso
	Andr�s Felipe Mancipe Galvis
	Lina Fernanda Pinto Garc�a
	Liliana Carolina Quiti�n Cede�o
	Leonardo Ram�rez Vargas <leonardoramirez@latinmail.com>
	Juan David Vargas Botero <cyberbob1164@hotmail.com>
	Juan Pablo Yela Gall�n
	Jorge Enrique C�rdenas Carrillo <platypus_life@hotmail.com>

adem�s la versi�n en espa�ol ha sido revisada y corregida por:
	Pablo Reyes <reyes_pablo@hotmail.com>
	Igor T�mara <ikks@bigfoot.com>
	Melissa Giraldo de T�mara <melagira@yahoo.com>
	Vladimir T�mara <vtamara@gnu.org>

Por favor, en caso de duda, s�lo es v�lido el original en ingl�s de la
siguiente nota de derechos de reproducci�n (que puede encontrar en el
archivo TUTORIAL).

Copyright (c) 1985, 1996 Free Software Foundation

   Se permite a cualquiera hacer o distribuir copias literales de este
   documento como se recibe, en cualquier medio, siempre que la nota de
   derechos de reproducci�n y la nota de permiso se preserven, y que el 
   distribuidor permita que el que la recibe hacer distribuci�n posterior 
   como lo permite esta nota.

   Se permite distribuir versiones modificadas de este documento, o
   porciones de este, bajo las condiciones anteriores, siempre que
   ellas tengan nota visible especificando qui�n fue el �ltimo en
   alterarlas.

Las condiciones para copiar Emacs mismo son m�s complejas, pero con el
mismo esp�ritu.  Por favor lea el archivo COPYING y entonces
distribuya copias de GNU Emacs a sus amigos.  �Ayude a erradicar el
obstruccionismo del software "propietaro" usando, escribiendo, y
compartiendo software libre!


