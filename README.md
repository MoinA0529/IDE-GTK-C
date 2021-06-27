# IDE devpt. in GTK/C

This is repository of the software development project I did under Prof. Debadatta Mishra of Computer \
Science and Engineering Department. 
\
I have used gtk library, GTK applications are written in C, while the Graphic User Interfaces designed \
using the software Glade.\
Glade is used to lay out all of the graphical elements and widgets, it is used to create xml file format for GUI \
However the final *editor.c* does not require xml file as it is designed using only GTK library, C \
\
Do read the documentation above titled as GTK/C development project.pdf \
 \
The above set file editor consists of progress of the project so far. The project intended to create an Integrated Development Environment.\
\
To run the application under the folder type the following in terminal. \
You may also need to install gcc and gtk library.\
\
`sudo apt-get install gcc` \
*and*
`sudo apt-get install libgtk-3-dev` \
*or*
`sudo apt-get install gtk+2.0` \
Then run the following commands \
`sh compile.sh editor` \
*or*
``gcc `pkg-config --cflags gtk+-3.0` -o editor editor.c `pkg-config --libs gtk+-3.0`` \
And to run the editor \
`./editor`
\
I used the instructions from the following website, which contains concise resources for understanding and implementing applications.\
Reference Documents :
 - [Kevin O'Kane](http://www.cs.uni.edu/~okane/youtube.html) 
 - [Prognotes](https://prognotes.net/2016/03/gtk-3-c-code-hello-world-tutorial-using-glade-3/) 
 - [GnomeGtk](https://developer.gnome.org/gtk3/stable/) 
 - [gedit(textEditor)](https://github.com/GNOME/gedit) 