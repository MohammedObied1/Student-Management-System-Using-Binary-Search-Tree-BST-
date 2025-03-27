#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node1* student;
struct Node1 {
    int studentId;
    char name[100];
    char adrees[100];
    int class;
    char enrollment[100];
    struct Node1* Right;
    struct Node1* Left;
};
student Find ( int X, student T ) {
    if (T == NULL)
        return NULL;
    else if (X < T->studentId)
    {
        return Find(X, T->Left);
    }
    else if (X > T->studentId) {
        return Find(X, T->Right);
    }
    else
        return T;
}

student Insert(int X, student T, char name[100], char adrees[100], int class, char enrollment[100]) {
    if (T == NULL) {
        T = (student)malloc(sizeof(struct Node1));
        if (T == NULL)
            printf("Out of space");
        else {
            T->studentId = X;
            strcpy(T->name, name);

            strcpy(T->adrees, adrees);
            T->class = class;

            strcpy(T->enrollment, enrollment);
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->studentId)
        T->Left = Insert(X, T->Left, name, adrees, class, enrollment);
    else if (X > T->studentId)
        T->Right = Insert(X, T->Right, name, adrees, class, enrollment);

    return T;
}
void Print(student T) {
    if (T != NULL) {
        Print(T->Left);
        printf("Student ID: %d\n", T->studentId);
        printf("Name: %s\n", T->name);
        printf("Address: %s\n", T->adrees);
        printf("Class: %d\n", T->class);
        printf("Enrollment: %s\n", T->enrollment);
        printf("--------------------\n");
        Print(T->Right);
    }
}

student FindMin(student T) {
    if (T == NULL) {
        return NULL;
    } else if (T->Left == NULL) {
        return T;
    } else {
        return FindMin(T->Left);
    }
}

student Delete(int key, student T) {
    if (T == NULL) {
        printf("Node not found\n");
        return T;
    }

    if (key < T->studentId) {
        T->Left = Delete(key, T->Left);
    } else if (key > T->studentId) {
        T->Right = Delete(key, T->Right);
    } else {

        if (T->Left == NULL && T->Right == NULL) {

            free(T);
            T = NULL;
        } else if (T->Left == NULL) {

            student temp = T;
            T = T->Right;
            free(temp);
        } else if (T->Right == NULL) {

            student temp = T;
            T = T->Left;
            free(temp);
        } else {

            student minRight = FindMin(T->Right);


            T->studentId = minRight->studentId;
            strcpy(T->name, minRight->name);

            strcpy(T->adrees, minRight->adrees);
            T->class = minRight->class;

            strcpy(T->enrollment, minRight->enrollment);


            T->Right = Delete(minRight->studentId, T->Right);
        }
    }

    return T;
}

void PrintCity(student T, const char city[]) {
    if (T != NULL) {
        PrintCity(T->Left, city);


        if (strstr(T->adrees, city) != NULL) {
            printf("Student ID: %d\n", T->studentId);
            printf("Name: %s\n", T->name);
            printf("Address: %s\n", T->adrees);
            printf("Class: %d\n", T->class);
            printf("Enrollment: %s\n", T->enrollment);
            printf("--------------------\n");
        }

        PrintCity(T->Right, city);
    }
}


void PrintClass(student T, int class) {
    if (T != NULL) {
        PrintClass(T->Left, class);

        if (T->class == class) {
            printf("Student ID: %d\n", T->studentId);
            printf("Name: %s\n", T->name);
            printf("Address: %s\n", T->adrees);
            printf("Class: %d\n", T->class);
            printf("Enrollment: %s\n", T->enrollment);
            printf("--------------------\n");
        }

        PrintClass(T->Right, class);
    }
}

student InsertNode(student root,int x ,  const char name[], const char address[], int  class, const char enrollment[]) {
    if (root == NULL) {
        root = (student)malloc(sizeof(struct Node1));
        if (root == NULL)
            printf("Out of space");
        else {
            root->studentId = x;
            strcpy(root->name, name);
            strcpy(root->adrees, address);
            root->class=class;

            strcpy(root->enrollment, enrollment);
            root->Left = root->Right = NULL;
        }

    } else {
        int compareResult = strcmp(name, root->name);
        if (compareResult < 0)
            root->Left = InsertNode(root->Left, x, name, address, class, enrollment);
        else if (compareResult > 0)
            root->Right = InsertNode(root->Right, x, name, address, class, enrollment);


    }

    return root;
}


void PrintFile(student T, FILE* file) {
    if (T != NULL) {
        PrintFile(T->Left, file);

        fprintf(file, "Student ID: %d\n", T->studentId);
        fprintf(file, "Name: %s\n", T->name);
        fprintf(file, "Address: %s\n", T->adrees);
        fprintf(file, "Class: %d\n", T->class);
        fprintf(file, "Enrollment: %s\n", T->enrollment);
        fprintf(file, "--------------------\n");

        PrintFile(T->Right, file);
    }



}
int  studentintree(student root, int studentId) {
    if (root == NULL) {
        return 0;
    }

    if (root->studentId == studentId) {
        return 1;
    } else if (studentId < root->studentId) {
        return studentintree(root->Left, studentId);
    } else {
        return studentintree(root->Right, studentId);
    }
}




int InClass(student root, int classID) {
    if (root == NULL) {
        return 0;
    }

    if (root->class == classID) {
        return 1;
    }


    int hasLeft = InClass(root->Left, classID);
    int hasRight = InClass(root->Right, classID);

    if (hasLeft || hasRight) {
        return 1;
    } else {
        return 0;
    }
}
int count(student root) {
    if (root == NULL) {
        return 0;
    }

    int c = 1;

    c += count(root->Left);
    c += count(root->Right);
    return c;
}


int main() {
    int x;
    student A = NULL;
    student B = NULL;


    FILE* f;
    char line[100];

    f = fopen("students.data", "r");



    while (fgets(line, sizeof(line), f) != NULL) {
        int studentID;
        char name[50];
        char addres[100];
        int className;
        char enrollment[50];

        sscanf(line, "Student ID: %d", &studentID);
        fgets(line, sizeof(line), f);
        sscanf(line, "Name: %s", name);
        fgets(line, sizeof(line), f);
        sscanf(line, "Address: %s", addres);
        fgets(line, sizeof(line), f);
        sscanf(line, "Class: %d",  &className);
        fgets(line, sizeof(line), f);
        sscanf(line, "Enrollment: %s", enrollment);
        fgets(line, sizeof(line), f);

        A = Insert(studentID, A, name, addres, className, enrollment);
        B = InsertNode(B, studentID, name, addres, className, enrollment);
    }

    fclose(f);

    while (1) {
        printf("**  Welcome in  my school  **\n");
        printf("1 -  new student\n");
        printf("2 - Find student  and update\n");
        printf("3 - print all student  \n ");
        printf("4 - search for city \n ");
        printf("5 -search for class  \n");
        printf("6 - Delete a student\n");
        printf("7 - Save all students to file\n");
        printf("8 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &x);
        printf("---------------------------------------------------------------------------\n");

        if (x == 1) {


            printf("Enter student ID: ");
            int student;
            scanf("%d", &student);

            if (studentintree(B,student)==1){
                printf("this id is in tree \n");


            } else {

                printf("Enter name ues - betwen name    : ");
                char name[100];
                scanf("%s", name);


                printf("Enter address  : ");
                char a[100];
                scanf("%s", a);

                printf("Enter class ID  : ");
                int b;
                scanf("%d",&b);

                printf("Enter date of enrollment : ");
                char e[100];
                scanf("%s", e);
                A = Insert(student, A, name, a, b, e);
                B = InsertNode(B, student, name, a, b, e);




            }
        } else if (x == 3) {

            Print(B);





        } else if (x == 2) {

            int Id;
            printf("Enter student ID to find and update: ");
            scanf("%d", &Id);

            student find = Find(Id, B);

            printf(" student ID :  %d\n",find->studentId);
            printf("name   : %s\n",find->name);
            printf("adrees :  %s\n",find->adrees);
            printf("class  : %d\n",find->class);
            printf("enrollment  : %s\n",find->enrollment);


            int p ;

            printf("if you need to updata enter 1 \n");
            scanf("%d",&p);

            if (p==1){
                Delete(Id,A);
                Delete(Id,B);

                printf("Enter student ID: ");
                int student;
                scanf("%d", &student);


                printf("Enter name without spase  : ");
                char name [100];
                scanf("%s", name);


                printf("Enter address: ");
                char a [100];
                scanf("%s",a);

                printf("Enter class ID: ");
                int b ;
                scanf("%d", &b);

                printf("Enter date of enrollment: ");
                char e [100];
                scanf("%s", e);
                A = Insert(student, A, name, a, b, e);

                B = InsertNode(B,student,  name, a, b, e);





            }


        } else if (x == 4) {
            char city[100];

            printf("enter name of city    :     ");

            scanf("%s", city);

            PrintCity(B, city);

        } else if (x == 5) {

            int size = count(B);

            int i = 0 ;

            while (i < size*100) {

                if (InClass(B, i) == 0) {

                    i++;

                    continue;
                }
                printf(" in  Class ID: %d\n", i);

                PrintClass(B, i);


                i++;
            }
        } else if (x == 6) {
            int a;

            printf("Enter the numper of  delete ");

            scanf("%d", &a);

            B = Delete(a, B);

            A= Delete(a,A);

            printf("DONE\n");

            FILE *file = fopen("students.data", "w");

            PrintFile(A, file);

            fclose(file);

        } else if (x == 7) {

            FILE *file = fopen("students.data", "w");


            PrintFile(A, file);

            fclose(file);

            printf("DONE \n");

        } else   if ( x==8){

            printf("end\n");

            break;

        } else{
            printf("this numper invaild\n");
        }
    }
    return 0;
}
