#include <gtk/gtk.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Declaration as global variables
GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button1;
GtkWidget	*label1;
GtkWidget	*label2;
GtkWidget	*radio1;
GtkWidget	*radio2;
GtkWidget	*radio3;
GtkWidget	*check1;
GtkWidget   *toggle1;
GtkWidget   *spin1;
GtkWidget   *switch1;
GtkWidget   *combo1;
GtkWidget	*color1;
GtkWidget   *entry1;
GtkWidget	*file1;
GtkWidget   *entry2;
GtkWidget   *button2;
GtkWidget	*scroll1;
GtkWidget	*menu1;
GtkWidget	*New;
GtkWidget	*save;
GtkWidget	*ScrollWindow;
GtkWidget	*ViewPort;
GtkWidget	*TextView;
GtkWidget	*saveText;
GtkTextBuffer *TextBuffer;

GtkBuilder	*builder;

void	on_changed_text(GtkTextBuffer *t);

char	tmp[1024]; //acts as a buffer for TextView

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // initialize Gtk
	// builder = gtk_builder_new();
	// gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

	builder = gtk_builder_new_from_file ("part1.glade");
	// gtk_builder_new_from_file(const gchar *filename ): builds GTK UI definition in the given file.
	// gtk_builder builds a widget from our glade file.

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);
	// gtk_builder(GtkBuilder* builder,gpointer user_data) connects the signals from the user to widget

	// Get Pointers to the widgets
	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
	radio1 = GTK_WIDGET(gtk_builder_get_object(builder, "radio1"));
	radio2 = GTK_WIDGET(gtk_builder_get_object(builder, "radio2"));
	radio3 = GTK_WIDGET(gtk_builder_get_object(builder, "radio3"));
	check1 = GTK_WIDGET(gtk_builder_get_object(builder, "check1"));
	toggle1 = GTK_WIDGET(gtk_builder_get_object(builder, "toggle1"));
	spin1 = GTK_WIDGET(gtk_builder_get_object(builder, "spin1"));
	switch1 = GTK_WIDGET(gtk_builder_get_object(builder, "switch1"));
	combo1 = GTK_WIDGET(gtk_builder_get_object(builder, "combo1"));
	entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
	color1 = GTK_WIDGET(gtk_builder_get_object(builder, "color1"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder, "file1"));
	scroll1 = GTK_WIDGET(gtk_builder_get_object(builder, "scroll1"));
	entry2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
	menu1 = GTK_WIDGET(gtk_builder_get_object(builder, "menu1"));
	New = GTK_WIDGET(gtk_builder_get_object(builder, "New"));
	save = GTK_WIDGET(gtk_builder_get_object(builder, "save"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	ScrollWindow = GTK_WIDGET(gtk_builder_get_object(builder, "ScrollWindow"));
	ViewPort = GTK_WIDGET(gtk_builder_get_object(builder, "ViewPort"));
	TextView = GTK_WIDGET(gtk_builder_get_object(builder, "TextView"));
	saveText = GTK_WIDGET(gtk_builder_get_object(builder, "saveText"));

	/*
	struct GtkAdjustment {
	    gdouble lower,
	    gdouble upper,
	    gdouble step_increment,
	    gdouble page_increment,
	    gdouble page_size
	};
	// alter the range of the scroll bar
	gtk_range_set_range (GTK_RANGE(scroll1), 0, 100);
	*/
	//-----------------------------------

	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextView));

	g_signal_connect(TextBuffer, "changed", G_CALLBACK(on_changed_text), NULL);


	strcpy(tmp, "Virtual contest is a way to take part in contest as close as possible to participation on time\
	 \n\nTo preserve a position, the GtkTextMark object is ideal. \n\nYou can think of a mark as an invisible cursor \
	or insertion point; it floats in the buffer, saving a position. \n\nIf the text surrounding the mark is deleted, \
	the mark remains in the position the text once occupied; if text is inserted at the mark, the mark ends up \
	either to the left or to the right of the new text, depending on its gravity. \n\nThe standard text cursor in \
	left-to-right languages is a mark with right gravity, because it stays to the right of inserted text.");

	gtk_text_buffer_set_text (TextBuffer, (const gchar *) tmp, (gint) - 1);

	gtk_widget_hide(saveText);

//-----------------------------------
	gtk_widget_show(window);
	// call this function to make the window visible
	gtk_main();
	//main: hand control to GTK main loop and process events(received from signals etc.)
	return EXIT_SUCCESS;
	// called when window is closed
}

//******************  Handler Functions for the Widgets   ***********************//

void on_button1_clicked (GtkButton *b) {
	char buffer[128];
	gdouble val = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin1));
	sprintf(buffer, "spin button val = %d", (int)val);
	gtk_label_set_text(GTK_LABEL(label1), (const gchar*) buffer);
}

void on_radio1_toggled(GtkRadioButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Radio 1 toggled Active");
	else gtk_label_set_text (GTK_LABEL(label2), (const gchar* ) "Radio 1 toggled Inactive");
}

void on_radio2_toggled(GtkRadioButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Radio 2 toggled Active");
	else gtk_label_set_text (GTK_LABEL(label2), (const gchar* ) "Radio 2 toggled Inactive");
}

void on_radio3_toggled(GtkRadioButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Radio 3 toggled Active");
	else gtk_label_set_text (GTK_LABEL(label2), (const gchar* ) "Radio 3 toggled Inactive");
}

void on_check1_toggled(GtkCheckButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Check1 toggled Active");
	else gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Check1 toggled Inactive");
}
// handler function for toggle button
void on_toggle1_toggled(GtkToggleButton *b) {
	gboolean T = gtk_toggle_button_get_active(b);
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "toggle1 toggled Active");
	else gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "toggle1 toggled Inactive");
}
// handler function for switch
void on_switch1_state_set(GtkSwitch *s) {
	gboolean T = gtk_switch_get_active(s);
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Switch1 toggled Active");
	else gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Switch1 toggled Inactive");
}

void on_entry1_changed(GtkEntry *e) {
	char buffer[128];
	sprintf(buffer, "entry = %s", gtk_entry_get_text(e));
	gtk_label_set_text(GTK_LABEL(label1), (const gchar*) buffer);
}

void on_combo1_changed(GtkComboBox *c) {
	printf("combo1 changed\n");
}

void on_color1_color_set (GtkColorButton *c) {
	GdkRGBA color;
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(c), &color);
	printf("red %f\n", color.red);
	printf("green %f\n", color.green);
	printf("blue %f\n", color.blue);
	printf("alpha %f\n", color.alpha);
	// To change the scrollbar background
	// gtk_widget_override_background_color (scroll1, GTK_STATE_FLAG_NORMAL, &color);
}

void on_file1_file_set(GtkFileChooserButton *f) {
	printf("file name = %s\n", gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f)) );
	printf("folder name = %s\n", gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(f)) );
}

void on_scroll1_value_changed(GtkRange *r) {
	gdouble x = gtk_range_get_value (r);
	printf("scroll = %d\n", (int) x );
}

void on_entry2_changed(GtkEntry *e) {
	char buffer[128];
	sprintf(buffer, "entry = %s", gtk_entry_get_text(e));
	gtk_label_set_text(GTK_LABEL(label1), (const gchar*) buffer);
}

void on_button2_clicked(GtkButton *b) {
	gtk_editable_delete_text(GTK_EDITABLE(entry2), 0, -1);
}// 0 means from the start -1 means to the end
void on_New_activate(GtkMenuItem *m) {
	printf("New activated\n");
}
void on_New_select(GtkMenuItem *m) {
	printf("New selected\n");
}
void on_New_deselect(GtkMenuItem *m) {
	printf("New deselected\n");
}


void on_saveText_clicked(GtkButton *b) {

	GtkTextIter begin, end;
	gchar * text;

	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer), &end, (gint) - 1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer), &begin, &end, TRUE);
	printf("Using Save and Print button-------\n%s\n--------\n", text);
	gtk_widget_hide(saveText);
}
void on_changed_text(GtkTextBuffer *t) {
	printf("...........\n");
	gtk_widget_show(saveText);
}
void on_save_activate(GtkMenuItem *m) {
	GtkTextIter begin, end;
	gchar * text;
	//g_print("here\n");
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer), &end, (gint) - 1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer), &begin, &end, TRUE);
	printf("Using save in Menu-------\n%s\n--------\n", text);
	gtk_widget_hide(saveText);
}
