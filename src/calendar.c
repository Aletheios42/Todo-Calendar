#include "calendar.h"
#include "tasks.h"
#include <gtk/gtk.h>

static GtkWidget *task_entry;
static GtkWidget *task_list_box;

// Callback para manejar la selección de fecha en el calendario
static void on_date_selected(GtkCalendar *calendar, gpointer data) {
    guint year, month, day;
    gtk_calendar_get_date(calendar, &year, &month, &day);

    // Limpiar la lista de tareas anterior
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(task_list_box));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    // Obtener las tareas para la fecha seleccionada
    GList *tasks_for_date = get_tasks_for_date(year, month + 1, day);

    // Añadir cada tarea a la lista de la UI
    for (GList *l = tasks_for_date; l != NULL; l = l->next) {
        Task *task = (Task *)l->data;
        GtkWidget *label = gtk_label_new(task->description);
        gtk_list_box_insert(GTK_LIST_BOX(task_list_box), label, -1);
    }

    gtk_widget_show_all(task_list_box);
    free_task_list(tasks_for_date);  // Liberar memoria temporal de la lista de tareas para la fecha
}

// Callback para añadir una tarea a la fecha seleccionada
static void on_add_task_clicked(GtkWidget *button, GtkCalendar *calendar) {
    const char *description = gtk_entry_get_text(GTK_ENTRY(task_entry));
    if (description == NULL || strlen(description) == 0) return;

    guint year, month, day;
    gtk_calendar_get_date(calendar, &year, &month, &day);

    add_task(year, month + 1, day, description);  // Añadir tarea
    gtk_entry_set_text(GTK_ENTRY(task_entry), "");  // Limpiar el campo de entrada
}

void display_calendar(GtkWidget *parent_window) {
    GtkWidget *calendar_window;
    GtkWidget *calendar;
    GtkWidget *vbox;
    GtkWidget *add_task_button;

    calendar_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(calendar_window), "Calendar");
    gtk_window_set_default_size(GTK_WINDOW(calendar_window), 400, 400);
    gtk_container_set_border_width(GTK_CONTAINER(calendar_window), 10);

    g_signal_connect(calendar_window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(calendar_window), vbox);

    calendar = gtk_calendar_new();
    gtk_box_pack_start(GTK_BOX(vbox), calendar, FALSE, FALSE, 0);

    // Entrada para la tarea
    task_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), task_entry, FALSE, FALSE, 0);

    // Botón para añadir la tarea
    add_task_button = gtk_button_new_with_label("Add Task");
    g_signal_connect(add_task_button, "clicked", G_CALLBACK(on_add_task_clicked), calendar);
    gtk_box_pack_start(GTK_BOX(vbox), add_task_button, FALSE, FALSE, 0);

    // Lista para mostrar las tareas
    task_list_box = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(vbox), task_list_box, TRUE, TRUE, 0);

    // Conectar la selección de fecha
    g_signal_connect(calendar, "day-selected", G_CALLBACK(on_date_selected), NULL);

    gtk_widget_show_all(calendar_window);
}

