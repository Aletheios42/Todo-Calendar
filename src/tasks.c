#include "tasks.h"
#include <stdlib.h>
#include <string.h>

static GList *task_list = NULL; // Lista de todas las tareas

// Crear una nueva tarea y agregarla a la lista
void add_task(int year, int month, int day, const char *description) {
  Task *new_task = malloc(sizeof(Task));
  new_task->year = year;
  new_task->month = month;
  new_task->day = day;
  new_task->description = strdup(description);

  task_list = g_list_append(task_list, new_task);
}

// Obtener las tareas asociadas a una fecha específica
GList *get_tasks_for_date(int year, int month, int day) {
  GList *tasks_for_date = NULL;

  for (GList *l = task_list; l != NULL; l = l->next) {
    Task *task = (Task *)l->data;
    if (task->year == year && task->month == month && task->day == day) {
      tasks_for_date = g_list_append(tasks_for_date, task);
    }
  }
  return tasks_for_date;
}

// Eliminar una tarea
void remove_task(Task *task) {
  task_list = g_list_remove(task_list, task);
  free(task->description);
  free(task);
}

// Liberar memoria de la lista de tareas
void free_task_list(GList *task_list) {
  g_list_free_full(task_list, (GDestroyNotify)remove_task);
}

