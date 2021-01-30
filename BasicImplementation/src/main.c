#include <gtk/gtk.h>

GtkWidget *g_lbl_hello;
GtkWidget *g_lbl_count;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    gtk_builder_connect_signals(builder, NULL);
    //connects all of the signals in the project in glade under the signals tab


    // get pointers to the two labels
    g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_hello"));
    g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
    //gtk_builder_get_object() returns a pointer gobject* and this connects the labels
    //and the window_main

    g_object_unref(builder);
    gtk_widget_show(window);
    //gtk_widhet_show(GtkWidget *widget) must be called to make the window visible


    gtk_main();
    //main: hand control to GTK main loop and process events(received from signals etc.)
    return 0;
}

// called when button is clicked
void on_btn_hello_clicked()
{
    static unsigned int count = 0;
    char str_count[30] = {0};

    gtk_label_set_text(GTK_LABEL(g_lbl_hello), "Hello, world!");
    count++;
    sprintf(str_count, "%d", count);
    //sprintf(char *str, const char *string,...); is used to print the count on the widget
    //here str_count is used as the buffer string while count is printed

    gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
    //exits out of the application
}
