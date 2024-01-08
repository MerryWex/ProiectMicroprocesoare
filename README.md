# ProiectMicroprocesoare

Proiect Sisteme Specializate cu Microprocesoare - ATM Anul IV Sem I
*Echipa 23*

Membri:
 - Ionel Ana-Maria 
 - Grigore Maria-Emilia

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Proiectul constă în construirea unui circuit electronic care, prin intermediul unei interfețe grafice și a unui senzor de rotație, să manipuleze aprinderea și stingerea unor becuri LED.
 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Elemente componente:**
 

 - Microcontroller FRDM-KL25Z;
 - Breadboard;
 - Mini breadboard;
 - Senzor de rotație (potențiometru);
 - 3 becuri LED: roșu, galben, verde;
 - 3 rezistențe;
 - Fire de conexiune.


 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Scopul proiectului este de a aprinde becurile LED conectate pe breadboard în funcție de poziția cursorului senzorului de rotație, astfel (bold = aprins, italic = stins):

 - interval 0 - 1.1 V: **verde**, *galben*, *roșu*;
 - interval 1.1 - 2.2 V: **verde**, **galben**, *roșu*;
 - interval 2.2 - 3.3 V: **verde**, **galben**, **roșu**;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;O altă funcționalitate implementată este aprinderea becului LED integrat pe placă într-o secvență de culori care se schimbă la intervalul de 461ms, în ordinea: alb, verde, turcoaz, galben.
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Totodată, sunt implementate și alte funcționalități conexe, disponibile ca opțiuni în interfața grafică:

 - Modificarea ordinii secvenței de culori a becului LED integrat;
 - Aprinderea/stingerea becurilor LED de pe breadboard în mod individual;
 - Aprinderea/stingerea becurilor LED de pe breadboard în mod simultan;
 - Modificarea baud rate-ului;
 - Modificarea vitezei de schimbare a culorilor din secvența becului LED integrat.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Pentru rularea proiectului, sunt necesare platforma Keil uVision și suport pentru Python3 (modulele PySide6, pyserial și pyqtgraph). 
