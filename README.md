# Project-files

This is a text editor, which is with regard to a project I was doing with Prof. Debadatta Mishra of CSE dept.
I have used gtk library, GTK applications are written in C, while the user interfaces are designed with an application called Glade.
Glade is used to lay out all of the graphical elements and widgets, it is in xml file format.

The above set directory text-editor-menu-bar is the implementation of some progress of the project. The project intended to create an Integrated development environment.

To run the application under the folder type the following in terminal
You may also need to install gcc and gtk library.

`sudo apt-get install libgtk-3-dev`
*and*
`sudo apt-get install gtk+2.0`

Then run the following commands

`sh compile.sh editor`

`./editor`

I used the instructions from the following website, which contains concise resources for understanding and implementing basic glade application.
https://prognotes.net/2016/03/gtk-3-c-code-hello-world-tutorial-using-glade-3/
