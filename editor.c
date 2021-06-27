#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include <errno.h>
#include <stdlib.h>


// GtkWidget *dialog;
// GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
// gint res;

// dialog = gtk_file_chooser_dialog_new ("Open File",
//                                       parent_window,
//                                       action,
//                                       _("_Cancel"),
//                                       GTK_RESPONSE_CANCEL,
//                                       _("_Open"),
//                                       GTK_RESPONSE_ACCEPT,
//                                       NULL);

// res = gtk_dialog_run (GTK_DIALOG (dialog));
// if (res == GTK_RESPONSE_ACCEPT)
//   {
//     char *filename;
//     GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
//     filename = gtk_file_chooser_get_filename (chooser);
//     open_file (filename);
//     g_free (filename);
//   }

// gtk_widget_destroy (dialog);


// SEARCH_BAR, OPEN_DIALOG, NEW_DIALOG are Mnemonic widget - Mnemonics are underlined characters in the
// label used for keyboard navigation
// Structure for Search bar


typedef struct _SEARCH_BAR {
	GtkWidget *searchEntry;
	GtkWidget *searchButton;
	GtkWidget *nextButton;
	GtkWidget *quitButton;
	GtkWidget *textView;
} SEARCH_BAR;

// Structure for Find and replace
// typedef struct _FIND_REPLACE {
// 	GtkWidget *searchEntry;
// 	GtkWidget *replaceEntry;
// 	GtkWidget *searchButton;
// 	GtkWidget *replaceButton;
// 	GtkWidget *quitButton;
// 	GtkWidget *textView_R;
// 	GtkWidget *textView_F;
// } REPLACE_BAR;

// Initial dialog when the app is launched
typedef struct _OPEN_DIALOG {
	GtkWidget *window;
	GtkTextBuffer *buffer;
	gchar *filename;
} OPEN_DIALOG;


// The structure of the window when a new file is opened or created
typedef struct _NEW_DIALOG {
	GtkWidget *window;
	GtkWidget *statusBar; // Only displayed when new file is opened/created
	GtkWidget *textView;
	GtkTextBuffer *buffer;
} NEW_DIALOG;

// *** FUNCTION DECLARATIONS ***

// Functions for replace
// void replace_button_clicked(GtkWidget *replace_button);

// void replaceUtil (GtkTextView *text_view, const gchar *text, const gchar *text1, GtkTextIter *iter);

// Function for save menu item
void save_dialog_selected(GtkWidget *widget, OPEN_DIALOG *save);

// Function for new menu item
void new_dialog_selected(GtkWidget *widget , NEW_DIALOG *new);

// Function for open menu item
void open_dialog_selected(GtkWidget *widget, OPEN_DIALOG *open);

// Function for search bar - find
void find(GtkTextView *text_view, const gchar *text, GtkTextIter *iter);

//Function for search bar - close
void close_button_clicked (GtkWidget *close_button, SEARCH_BAR *sbar);

// Function for search bar - display
void display_search_bar(GtkWidget *widget, SEARCH_BAR *sbar);

// Function for search bar - search
void search(GtkWidget *search, SEARCH_BAR *sbar);

// Function for search bar - next
void next_button_clicked(GtkWidget *next, SEARCH_BAR *sbar);

// About menu item is clicked
void about(GtkWidget *widget, gpointer data);


// Following three functions are invoked when Copy/Cut/Paste are selected from menu
void copy_to_clipboard(GtkWidget *widget, GtkTextBuffer *buffer);
void cut_to_clipboard(GtkWidget *widget, GtkTextBuffer *buffer);
void paste_from_clipboard(GtkWidget *widget, GtkTextBuffer *buffer);

// Functions for status bar Ln:__ Col: __
void update_status_bar(GtkTextBuffer *buffer, GtkStatusbar *status_bar);
void cursor_change(GtkTextBuffer *buffer, const GtkTextIter *new_location,
                   GtkTextMark *mark, gpointer data);

int main(int argc, char *argv[]) {
	// Window layout pointers
	GtkWidget *window;
	GtkWidget *vbox; // VBox is a container that organizes child widgets into a single column.
	GtkWidget *hbox; // organizes ssearch bar into a single row
	GtkWidget *status_bar;

	GtkClipboard *clipboard;

	// Text view variable definitions
	GtkWidget *text_view;
	GtkWidget *scrolled_window;
	GtkTextBuffer *buffer;

	// Search bar
	SEARCH_BAR search_bar;

	//Accel group
	GtkAccelGroup *accel_group = NULL;

	// Menubar layout definitions
	GtkWidget *MenuBar = gtk_menu_bar_new();

	// File menu and its layout definitions
	GtkWidget *FileMenu = gtk_menu_new();
	GtkWidget *file;
	GtkWidget *new;
	GtkWidget *open;
	GtkWidget *save;
	GtkWidget *quit;

	// Edit menu and its layout definitions
	GtkWidget *EditMenu = gtk_menu_new();
	GtkWidget *edit;
	GtkWidget *copy;
	GtkWidget *cut;
	GtkWidget *paste;

	// Option menu and its layout definitions
	GtkWidget *OptionsMenu = gtk_menu_new();
	GtkWidget *options;
	GtkWidget *find;

	// Help menu and its layout definitions
	GtkWidget *HelpMenu = gtk_menu_new();
	GtkWidget *help;
	GtkWidget *about;

	// initialize Gtk
	// builder = gtk_builder_new();
	// gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);


	// gtk_builder(GtkBuilder* builder,gpointer user_data) connects the signals from the user to widget

	// Get Pointers to the widgets
	gtk_init(&argc, &argv);

	// gtk_builder_new_from_file(const gchar *filename ): builds GTK UI definition in the given file.
	// gtk_builder builds a widget from our glade file.

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_window_set_title(GTK_WINDOW(window), "editor");

	vbox = gtk_vbox_new(FALSE, 2);
	hbox = gtk_hbox_new(FALSE, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	// FileMenu
	file = gtk_menu_item_new_with_mnemonic("_File");
	new = gtk_menu_item_new_with_label("New");
	open = gtk_menu_item_new_with_label("Open");
	save = gtk_menu_item_new_with_label("Save");
	quit = gtk_menu_item_new_with_label("Quit");

	// Linking File menu and its menu items and defining shortcuts
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), FileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(FileMenu), new);
	//gtk_widget_add_accelerator(new, "activate", accel_group,
	//                           GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(FileMenu), open);
	//gtk_widget_add_accelerator(open, "activate", accel_group,
	//                           GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(FileMenu), save);
	//gtk_widget_add_accelerator(save, "activate", accel_group,
	//                           GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(FileMenu), quit);
	//gtk_widget_add_accelerator(quit, "activate", accel_group,
	//                           GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), file);

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

	// EditMenu
	edit = gtk_menu_item_new_with_mnemonic("_Edit");
	cut = gtk_menu_item_new_with_label("Cut");
	copy = gtk_menu_item_new_with_label("Copy");
	paste = gtk_menu_item_new_with_label("Paste");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit), EditMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), cut);
	//gtk_widget_add_accelerator(cut, "activate", accel_group,
	//                           GDK_x, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), copy);
	//gtk_widget_add_accelerator(copy, "activate", accel_group,
	//                           GDK_c, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(EditMenu), paste);
	//gtk_widget_add_accelerator(paste, "activate", accel_group,
	//                           GDK_v, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), edit);

	// Options menu
	options = gtk_menu_item_new_with_mnemonic("_Options");
	find = gtk_menu_item_new_with_label("Find");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(options), OptionsMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(OptionsMenu), find);
	//gtk_widget_add_accelerator(find, "activate", accel_group,
	//                           GDK_f, GDK_CONTROL_MASK,
	//                           GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), options);

	// Help menu
	help = gtk_menu_item_new_with_mnemonic("_Help");
	about = gtk_menu_item_new_with_label("About");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), HelpMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(HelpMenu), about);

	gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), help);

	gtk_box_pack_start(GTK_BOX(vbox), MenuBar, FALSE, FALSE, 0);


	// Text view
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	text_view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
	gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, 1, 1, 0);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

	search_bar.textView = text_view;
	search_bar.searchEntry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), search_bar.searchEntry, TRUE, TRUE, 0);

	//search button
	search_bar.searchButton = gtk_button_new_with_label("Search");
	gtk_box_pack_start(GTK_BOX(hbox), search_bar.searchButton, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(search_bar.searchButton), "clicked",
	                 G_CALLBACK(search), &search_bar);


	// next button
	search_bar.nextButton = gtk_button_new_with_label("Next");
	gtk_box_pack_start(GTK_BOX(hbox), search_bar.nextButton, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(search_bar.nextButton), "clicked",
	                 G_CALLBACK(next_button_clicked), &search_bar);


	// close button
	search_bar.quitButton = gtk_button_new_with_label("Close");
	gtk_box_pack_start(GTK_BOX(hbox), search_bar.quitButton, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(search_bar.quitButton), "clicked",
	                 G_CALLBACK(close_button_clicked), &search_bar);

	// Initializing Open Dialog
	OPEN_DIALOG openDialog;
	openDialog.window = window;
	openDialog.buffer = buffer;

	// Initiallizing new dialog
	NEW_DIALOG newDialog;
	newDialog.window = window;
	newDialog.buffer = buffer;
	newDialog.textView = text_view;

	// Initializing save dialog
	OPEN_DIALOG saveDialog;
	saveDialog.window = window;
	saveDialog.buffer = buffer;

	// Initializing status bar
	status_bar = gtk_statusbar_new();
	gtk_box_pack_end(GTK_BOX(vbox), status_bar, FALSE, FALSE, 0);

	newDialog.statusBar = status_bar;

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(copy), "activate", G_CALLBACK(copy_to_clipboard), buffer);
	g_signal_connect(G_OBJECT(cut), "activate", G_CALLBACK(cut_to_clipboard), buffer);
	g_signal_connect(G_OBJECT(about), "activate", G_CALLBACK(about), (gpointer)window);
	g_signal_connect(G_OBJECT(paste), "activate", G_CALLBACK(paste_from_clipboard), buffer);
	g_signal_connect(G_OBJECT(find), "activate", G_CALLBACK(display_search_bar), &search_bar);
	g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(open_dialog_selected), &openDialog);
	g_signal_connect(G_OBJECT(new), "activate", G_CALLBACK(new_dialog_selected), &newDialog);
	g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(save_dialog_selected), &saveDialog);
	g_signal_connect(buffer, "changed", G_CALLBACK(update_status_bar), status_bar);
	g_signal_connect_object(buffer, "mark_set", G_CALLBACK(cursor_change), status_bar, 0);

	gtk_widget_show_all(window);

	gtk_widget_hide(search_bar.searchEntry);
	gtk_widget_hide(search_bar.searchButton);
	gtk_widget_hide(search_bar.nextButton);
	gtk_widget_hide(search_bar.quitButton);
	gtk_widget_hide(text_view);
	gtk_widget_hide(status_bar);

	update_status_bar(buffer, GTK_STATUSBAR(status_bar));

	gtk_main();
	// called when window is closed
	// call the function to make the window visible

	return 0;
}

// Function for save menu item
void save_dialog_selected(GtkWidget *widget, OPEN_DIALOG *sdlog) {

	GtkWidget *dialog;
	gint response;
	GtkTextBuffer *buffer;
	if (strcmp( gtk_window_get_title(GTK_WINDOW(sdlog->window)) , "Untitled") == 0) {

		dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(sdlog->window),
		                                     GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_SAVE,
		                                     GTK_RESPONSE_APPLY, GTK_STOCK_CANCEL,
		                                     GTK_RESPONSE_CANCEL, NULL);

		response = gtk_dialog_run(GTK_DIALOG(dialog));

		if (response == GTK_RESPONSE_APPLY) {
			gchar *filename;
			gchar *contents;
			GtkTextIter start, end;
			filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			buffer = sdlog->buffer;
			gtk_text_buffer_get_bounds(buffer, &start, &end);
			contents = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
			g_file_set_contents(filename, contents, -1, NULL);
			gtk_window_set_title(GTK_WINDOW(sdlog->window), filename);
			sdlog->filename = filename;
		}
		else if (response == GTK_RESPONSE_CANCEL) {
			gtk_widget_destroy(dialog);
			return;
		}
		gtk_widget_destroy(dialog);
	}
	else {
		GtkTextIter start, end;
		const gchar *filename = gtk_window_get_title(GTK_WINDOW(sdlog->window));
		gchar *contents;
		gtk_text_buffer_get_bounds(sdlog->buffer, &start, &end);
		contents = gtk_text_buffer_get_text(sdlog->buffer, &start, &end, FALSE);
		g_file_set_contents(filename, contents, -1, NULL);
	}
}

// Function for new menu item
void new_dialog_selected(GtkWidget *widget , NEW_DIALOG *ndlog) {
	gtk_widget_show(ndlog->textView);
	gtk_widget_show(ndlog->statusBar);
	gtk_window_set_title(GTK_WINDOW(ndlog->window), "Untitled");
	gtk_text_buffer_set_text(ndlog->buffer, "", -1);
}

// Function for open menu item
void open_dialog_selected(GtkWidget *widget, OPEN_DIALOG *odlog) {
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Open File",
	                                      GTK_WINDOW(odlog->window),
	                                      GTK_FILE_CHOOSER_ACTION_OPEN,
	                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	                                      NULL);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		gchar *filename;
		gchar *contents;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		g_file_get_contents(filename, &contents, NULL, NULL);
		gtk_text_buffer_set_text(odlog->buffer, contents, -1);
		gtk_window_set_title(GTK_WINDOW(odlog->window), filename);
		odlog->filename = filename;
		g_free (filename);
	}
	gtk_widget_destroy(dialog);
}

// Function for search bar - find
void find(GtkTextView *text_view, const gchar *text, GtkTextIter *iter) {
	GtkTextIter mstart, mend;
	gboolean found;
	GtkTextBuffer *buffer;
	GtkTextMark *last_pos;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
	found = gtk_text_iter_forward_search (iter, text, 0, &mstart, &mend, NULL);
	if (found) {
		gtk_text_buffer_select_range (buffer, &mstart, &mend);
		last_pos = gtk_text_buffer_create_mark (buffer, "last_pos", &mend, FALSE);
		gtk_text_view_scroll_mark_onscreen (text_view, last_pos);
	}
}

//Function for search bar - close
void close_button_clicked(GtkWidget *close_button, SEARCH_BAR *sbar) {
	gtk_widget_hide(sbar->searchEntry);
	gtk_widget_hide(sbar->searchButton);
	gtk_widget_hide(sbar->nextButton);
	gtk_widget_hide(sbar->quitButton);
}

// Function for search bar - display
void display_search_bar(GtkWidget *widget, SEARCH_BAR *sbar) {
	gtk_widget_show(sbar->searchEntry);
	gtk_widget_show(sbar->searchButton);
	gtk_widget_show(sbar->nextButton);
	gtk_widget_show(sbar->quitButton);
}

// Function for search bar - search
void search(GtkWidget *search, SEARCH_BAR *sbar) {
	const gchar *text;
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	text = gtk_entry_get_text (GTK_ENTRY (sbar->searchEntry));
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (sbar->textView));
	gtk_text_buffer_get_start_iter (buffer, &iter);

	find (GTK_TEXT_VIEW (sbar->textView), text, &iter);
}

// Function for search bar - next
void next_button_clicked(GtkWidget *next, SEARCH_BAR *sbar) {
	const gchar *text;
	GtkTextBuffer *buffer;
	GtkTextMark *last_pos;
	GtkTextIter iter;
	text = gtk_entry_get_text(GTK_ENTRY (sbar->searchEntry));
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (sbar->textView));
	last_pos = gtk_text_buffer_get_mark (buffer, "last_pos");
	if (last_pos == NULL) return;
	gtk_text_buffer_get_iter_at_mark(buffer, &iter, last_pos);
	find(GTK_TEXT_VIEW(sbar->textView), text, &iter);
}

// About menu item is clicked
void about(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Moin Ahmed's EDITOR");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "\n HELLO WORLD \n");
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
}

// Following three functions are invoked when Copy/Cut/Paste are selected from menu
void copy_to_clipboard(GtkWidget *widget, GtkTextBuffer *buffer) {
	GtkClipboard *clipboard;
	clipboard = gtk_clipboard_get(GDK_NONE);
	gtk_text_buffer_copy_clipboard(buffer, clipboard);
}
void cut_to_clipboard(GtkWidget *widget, GtkTextBuffer *buffer) {
	GtkClipboard *clipboard;
	clipboard = gtk_clipboard_get(GDK_NONE);
	gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);
}
void paste_from_clipboard(GtkWidget *widget, GtkTextBuffer *buffer) {
	GtkClipboard *clipboard;
	clipboard = gtk_clipboard_get(GDK_NONE);
	gtk_text_buffer_paste_clipboard(buffer, clipboard, NULL, TRUE);
}

// Functions for status bar Ln:__ Col: __
void update_status_bar(GtkTextBuffer *buffer, GtkStatusbar *statusbar) {
	gchar *msg;
	gint row;
	gint col;
	GtkTextIter iter;
	gtk_statusbar_pop(statusbar, 0);
	gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));
	row = gtk_text_iter_get_line(&iter);
	col = gtk_text_iter_get_line_offset(&iter);
	msg = g_strdup_printf("Col: %d Ln: %d", col + 1, row + 1);
	gtk_statusbar_push(statusbar, 0, msg);
	g_free(msg);
}
void cursor_change(GtkTextBuffer *buffer, const GtkTextIter *new_location,
                   GtkTextMark *mark, gpointer data) {
	update_status_bar(buffer, GTK_STATUSBAR(data));
}
// void replace_button_clicked(GtkWidget *replace_button) {
// 	GtkTextBuffer *buffer;
// 	GtkTextIter iter;
// 	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW());//
// 	gtk_text_buffer_get_start_iter(buffer, &iter);

// }

// void replaceUtil (GtkTextView *text_view, const gchar *text,
//                   const gchar *text1, GtkTextIter *iter) {
// 	GtkTextIter mstart, mend;
// 	GtkTextBuffer *buffer;
// 	gboolean found;
// 	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW());//
// 	found = gtk_text_iter_forward_search (iter, text, 0, &mstart, &mend, NULL);
// 	if (found)
// 	{
// 		gtk_text_buffer_select_range (buffer, &mstart, &mend);
// 		gtk_text_buffer_create_mark (buffer, "last_pos", &mend, FALSE);

// 		int len = strlen(text1);
// 		gtk_text_buffer_delete(buffer, &mstart, &mend);
// 		gtk_text_buffer_insert(buffer, &mstart, text1, len);
// 	}
// }