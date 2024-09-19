#include <gtk/gtk.h>
#include "ui.h"
#include "calendar.h"

// Declaración de la función de callback para el botón de calendario
static void on_calendar_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *parent_window = GTK_WIDGET(data);
    display_calendar(parent_window);
}

void create_main_window(void) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *add_task_button;
    GtkWidget *calendar_button;
    GtkWidget *task_list;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Todo App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    add_task_button = gtk_button_new_with_label("Add Task");
    gtk_box_pack_start(GTK_BOX(vbox), add_task_button, FALSE, FALSE, 0);

    task_list = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(vbox), task_list, TRUE, TRUE, 0);

    // Crear el botón de calendario y conectarlo a la función de callback
    calendar_button = gtk_button_new_with_label("Show Calendar");
    g_signal_connect(calendar_button, "clicked", G_CALLBACK(on_calendar_button_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), calendar_button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
}

