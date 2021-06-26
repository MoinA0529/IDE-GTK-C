#include <gtk/gtk.h>
static void activate (GtkApplication* app,
                      gpointer user_data) {

    GtkWidget *window;

    window = gtk_application_window_new (app);
    // Creates a new GtkApplicationWindow

    gtk_window_set_title (GTK_WINDOW (window), "Window");
    // Used to set the title of the window

    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    // Used to set the default size of the window

    gtk_widget_show_all (window);
    //This function is only for use in widget implementations. Causes a widget to be mapped if it isn’t already
}

int main (int argc, char **argv) {
    /* In a GTK+ application, the purpose of the main() function is to create a GtkApplication object and run it.
     * In this example a GtkApplication pointer named app is called and then initialized
     * using gtk_application_new().
    */
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example",
                               G_APPLICATION_FLAGS_NONE);
    /* Concretely, gtk_init() is called in the default handler for the “startup” signal.
     * Therefore, GtkApplication subclasses should chain up in their “startup” handler
     * before using any GTK+ API(Application Programming Interface).

     * GNOME technologies make extensive use of "reverse DNS" style identifiers for applications.
     * One of the first things that you will need to do when developing an application is to
     * choose an appropriate identifier. For example, "org.gtk.example" or "org.gnome.gedit"
    */

    g_signal_connect (app, "activate",
                      G_CALLBACK (activate), NULL);
    /*
     * Connects a GCallback function to a signal for a particular object.
     * g_signal connects activate function to the "activate" signal
    */
    status = g_application_run (G_APPLICATION (app),
                                argc, argv);
    /* Runs the application
     * This function is intended to be run from main() and its return value is intended to be returned by main()
    */
    g_object_unref (app);
    /* Decreases the reference count of the object when its reference count drops to zero, the object is finalized
     * i.e. its memory is freed
     * Reference counts are used to deallocate objects that are no longer needed.
    */
    return status;
}
/*Within g_application_run the activate() signal is sent and we then proceed into the activate() function of
 * the application. Inside the activate() function we want to construct our GTK window, so that a window is
 * shown when the application is launched. The call to gtk_application_window_new() will create a
 * new GtkWindow and store it inside the window pointer.
 * The window will have a frame, a title bar, and window controls depending on the platform.
*/
