#ifndef STUDENT_H
#define STUDENT_H

struct student {
    int number;
    char* name;
    char** lecture;
    int lCount;
};

void addStudent(student** body, int number, int* stCount);
bool searchStudent(student** body, int value, int* stCount);
void deleteStudent(student** body, int number, int* stCount);

#endif
