#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    // builder = gtk_builder_new();
    // gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    builder = gtk_builder_new_from_file("glade/window_main.glade");
    //gtk_builder_new_from_file(const gchar *filename ): builds GTK UI definition in the given file. 
    //gtk_builder builds a widget from our glade file.
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    //gtk_builder(GtkBuilder* builder,gpointer user_data) connects the signals from the user to widget
    
    g_object_unref(builder);

    gtk_widget_show(window);
    //call this function to make the window visible
    
    gtk_main();
    //main: hand control to GTK main loop and process events(received from signals etc.)

    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
