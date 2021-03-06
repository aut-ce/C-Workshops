#include <stdlib.h>
#include <string.h>

#include "courses.h"

struct course *course_create(const char *name, const char *professor, int number_of_sessions) {
  struct course *crs = malloc(sizeof(struct course));

  size_t nlen = sizeof(crs->name) / sizeof(char);
  strncpy(crs->name, name, nlen - 1);
  crs->name[nlen - 1] = '\0';

  size_t plen = sizeof(crs->professor) / sizeof(char);
  strncpy(crs->professor, professor, plen - 1);
  crs->professor[plen - 1] = '\0';

  crs->students = students_new();

  crs->number_of_sessions = number_of_sessions;
  crs->attendance = malloc(sizeof(struct students *) * number_of_sessions);
  for (int i = 0; i < number_of_sessions; i++) {
    crs->attendance[i] = students_new();
  }

  return crs;
}

void course_register(struct course *course, struct student *student) {
  students_push_back(course->students, student);
}

void course_attend(struct course *course, struct student *student, int session) {
  // check the student existence in the list
  if (students_search_id(course->students, student->id) != -1) {
    students_push_back(course->attendance[session], student);
  }
}

int course_student_attend_count(struct course *course, const char *id) {
  int count = 0;

  for (int i = 0; i < course->number_of_sessions; i++) {
    if (students_search_id(course->attendance[i], id) != -1) {
      count++;
    }
  }

  return count;
}


void course_delete(struct course *course) {
  students_delete(course->students);

  for (int i = 0; i < course->number_of_sessions; i++) {
    students_delete(course->attendance[i]);
  }
  free(course->attendance);

  free(course);
}
