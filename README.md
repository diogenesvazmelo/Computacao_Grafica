# Computacao_Grafica

Disciplina Eng de Computação CEFET-MG

### What to install

Run the following command to download the essential packages to build the application.

<code>sudo apt-get install build-essential</code> <br>

After installing the basic type the following command.

<code>sudo apt-get install libsdl2-dev libsdl2-image-dev</code> <br>

If for some unkown reason some package is missing, try to run the following command to find packages related to sdl2.
<code>apt-cache search libsdl2</code>
Remeber to get the "dev" version of the package.

### How to run

After installing all the necessary packages open a terminal and go to the TP01_SDL folder.
Run the command: <code>make</code>
That will compile the cpp files and generate the executable, it can be access in the <i>bin</i> folder, or simply by typing in the terminal: <code>./bin/game</code>
That will run the game.
