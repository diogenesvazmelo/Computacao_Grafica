# Computacao_Grafica

Disciplina Eng de Computação CEFET-MG

### What to install

Run the following command to download the essential packages to build the application.

<code>sudo apt-get install build-essential</code> <br>

After installing the basic packages, type the following command.

<code>sudo apt-get install libsdl2-dev libsdl2-image-dev</code> <br>

If for some unkown reason some package is missing, try to run the following command to find packages related to sdl2.
<code>apt-cache search libsdl2</code>
Remeber to get the "dev" version of the package.

### How to run

After installing all the necessary packages open a terminal and go to the TP01_SDL folder.
Run the command: <code>make</code>
That will compile the cpp files and generate the executable, it can be access in the <i>bin</i> folder, or simply by typing in the terminal: <code>./bin/game</code>
That will run the game.


### How to run on Windows
Download the latest version of SDL2 -devel -mingw from <link>https://www.libsdl.org/download-2.0.php</link>.
Also download the development library "SDL_image" -devel -mingw frow <link>https://www.libsdl.org/projects/SDL_image/</link>.

If you want to use SDL with Codeblocks, follow this tutorial here: <link>https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/codeblocks/</link> and do the same to link the development library "SDL_image" with Codebloks.

For other questions visit <link>https://wiki.libsdl.org/FAQWindows</link>.
