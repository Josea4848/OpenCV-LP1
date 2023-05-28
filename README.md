# OpenCV-LP1
Segundo projeto para a disciplina de Linguagem de programação I, do curso de engenharia da computação. 

<h3>Instalação do SFML</h3>
<code>sudo apt-get install libsfml-dev</code> 
<h3>Comando para compilação</h3>
<code>g++ -o programa main.cpp Game.cpp Object.cpp Screen.cpp sound.cpp `pkg-config --cflags opencv4` `pkg-config --libs --static opencv4` -lsfml-system -lsfml-audio</code>  

