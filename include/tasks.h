#ifndef TASKS_H
#define TASKS_H

#include <gtk/gtk.h>

// Estructura para representar una tarea
typedef struct {
  int year;
  int month;
  int day;
  char *description;
} Task;

// Función para crear una nueva tarea
void add_task(int year, int month, int day, const char *description);

// Función para obtener las tareas asociadas a una fecha
GList *get_tasks_for_date(int year, int month, int day);

// Función para eliminar una tarea
void remove_task(Task *task);

// Función para liberar memoria de la lista de tareas
void free_task_list(GList *task_list);

#endif // TASKS_H

