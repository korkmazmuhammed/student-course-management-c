#include <stdio.h>
char choice;

void role_to_dep(char initial);
int instructor_cl(int given_ID);
int course_print(int given_ID);
void same_class(int given_class);
float grade_student(int midterm, int final, double midterm_avg, double final_avg);
void match_first_initial(FILE *id_fp, char first_initial);
void get_ID();
int average_grade(FILE *id_fp, int id);
int get_id_fi(FILE *id_fp, char first_initial);

int main()
{
    FILE *id_fp;
    char first_initial;
    int id;
    int menu_flag = 1;
    char comma;
    int controller;

    while (menu_flag)
    {
        printf("\n p: PRINT ALL THE USERS PASS OR FAIL\n");
        printf(" n: PRINT ONLY THE USER WITH A SPECIFIC FIRST INITIAL\n");
        printf(" g: CALCULATE THE GPA OF A GIVEN STUDENT \n");
        printf(" c: PRINT WHETHER EACH USER PASSED OR FAILED THE SAME CLASS\n");
        printf(" t: PRINT THE NUMBER OF CLASSES FOR THE INSTRUCTOR\n");
        printf(" d: PRINT THE DEPARTMENT OF ALL PERSONS ACCORDING TO THE ROLE\n");
        printf(" l: PRINT THE COURSE_ID OF A GIVEN STUDENT\n");
        printf(" e: QUIT THE PROGRAM\n");
        printf("ENTER A CHOICE: ");
        scanf(" %c", &choice);
        printf("\n");
        switch (choice)
        {
        case 'p':
            get_ID();
            break;

        case 'n':
            id_fp = fopen("second.txt", "r");
            printf("\nEnter a first initial: ");
            scanf(" %c", &first_initial);
            match_first_initial(id_fp, first_initial);
            fclose(id_fp);

            break;

        case 'g':
            printf("\nEnter an ID : ");
            scanf(" %d", &id);
            controller = course_print(id);
            if (controller == -1)
                printf("NOT A STUDENT\n");
            else
            {
                id_fp = fopen("first.txt", "r");
                average_grade(id_fp, id);
                fclose(id_fp);
            }
            break;

        case 'c':
            int classID;
            printf("\nEnter an course ID : ");
            scanf(" %d", &classID);
            same_class(classID);
            break;

        case 't':
            int instructor_ID;
            int number_of_class;
            int is_instructor = 0;
            printf("\nEnter an Instructor ID : ");
            scanf(" %d", &instructor_ID);
            is_instructor = course_print(instructor_ID);
            if (is_instructor == -1)
            {
                number_of_class = instructor_cl(instructor_ID);
                if (number_of_class != -1)
                    printf("\nThis instructor has %d classes\n", number_of_class);
                else
                    printf("ERROR ID NOT FOUND");
            }
            else
            {
                printf("\nThe instructor not fount or wrong ID\n");
            }
            break;

        case 'd':
            printf("\nEnter a role first initial s for student i for instructor :");
            char role;
            scanf(" %c", &role);
            if (role != 's' && role != 'i')
                printf("INVALID CHOICE\n");
            role_to_dep(role);
            break;

        case 'l':
            printf("\nEnter an ID : ");
            scanf(" %d", &id);
            controller = course_print(id);
            if (controller == -1)
                printf("NOT A STUDENT\n");
            else
                printf("ID OF STUDENT : %d  CLASS OF STUDENT :%d\n", id, controller);
            break;

        case 'e':
            menu_flag = 0;
            break;

        default:
            printf("INVALID CHOICE\n");

            break;
        }
    }
}

int get_id_fi(FILE *id_fp, char first_initial)
{

    int id_finder = 0;
    char name_letter;
    char comma;
    int flag = 1;
    while (flag)
    {
        fscanf(id_fp, "%d", &id_finder);
        fscanf(id_fp, "%c", &comma);
        fscanf(id_fp, "%c", &name_letter);
        if (name_letter == first_initial)
        {
            flag = 0;
        }
        else
        {
            while (name_letter != '\n')
            {
                fscanf(id_fp, "%c", &name_letter);
            }
        }
    }
    return id_finder;
}

float grade_student(int midterm, int final, double midterm_avg, double final_avg)
{
    float GPA = 0;
    if (midterm >= 90)
        GPA = 4;
    else if (midterm > 40 && midterm > midterm_avg)
        GPA = 3.5;
    else if (midterm > 40 && midterm < midterm_avg)
        GPA = 3;
    else if (midterm > 40 && midterm < midterm_avg)
        GPA = 2.5;
    else if (midterm < 40 && midterm < midterm_avg && final < 40)
        GPA = 1;

    if (final >= 90)
        GPA = (4 + GPA) / 2;
    else if (90 > final && final > final_avg)
        GPA = (3.5 + GPA) / 2;
    else if (final > 40 && final > final_avg)
        GPA = (3 + GPA) / 2;
    else if (final > 40 && final < final_avg)
        GPA = (2.5 + GPA) / 2;
    else if (final < 40 && final < final_avg)
        GPA = (1 + GPA) / 2;

    return GPA;
}

void match_first_initial(FILE *id_fp, char first_initial)
{
    FILE *id_fp_to_control;
    int id_finder = 0;
    char name_letter;
    char comma;
    int flag = 1;
    int counter = 0;
    int is_student = 0;
    while (flag)
    {
        fscanf(id_fp, "%d", &id_finder);
        fscanf(id_fp, "%c", &comma);
        fscanf(id_fp, "%c", &name_letter);
        if (name_letter == first_initial)
        {
            counter++;
            if (choice == 'n')
            {
                is_student = course_print(id_finder);
                if (is_student != -1)
                {
                    id_fp_to_control = fopen("first.txt", "r");
                    average_grade(id_fp_to_control, id_finder);
                    fclose(id_fp_to_control);

                    printf("\n");
                }
            }
        }
        else
        {
            while (name_letter != '\n')
            {
                if (fscanf(id_fp, "%c", &name_letter) != 1)
                {
                    name_letter = '\n';
                    flag = 0;
                }
            }
        }
    }
    if (counter == 0)
        printf("THERE IS NO MATCHING\n");
}

void get_ID()
{
    int student_id;
    char comma;
    int class;
    FILE *id_fp;
    FILE *id_fp_to_pass;
    id_fp = fopen("first.txt", "r");
    id_fp_to_pass = fopen("first.txt", "r");

    while (fscanf(id_fp, "%d", &student_id) != EOF)
    {
        average_grade(id_fp_to_pass, student_id);

        while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
        {
            fscanf(id_fp, "%d", &class);
        }
    }
    fclose(id_fp);
    fclose(id_fp_to_pass);
}

void same_class(int given_class)
{
    char comma;
    int class;
    int id;
    FILE *id_fp;
    FILE *id_fp_to_average;
    int comma_count = 0;
    int counter = 0;
    id_fp = fopen("first.txt", "r");
    while (fscanf(id_fp, "%d", &id) != EOF)
    {

        while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
        {
            if (comma == ';')
                comma_count++;
            fscanf(id_fp, "%d", &class);
        }

        if (class == given_class && (comma_count == 4 || comma_count == 3))
        {
            counter++;
            id_fp_to_average = fopen("first.txt", "r");
            average_grade(id_fp_to_average, id);
            fclose(id_fp_to_average);
        }

        comma_count = 0;
    }
    if (counter == 0)
        printf("WARNING WRONG CLASS ID\n");
    fclose(id_fp);
}

int course_print(int given_ID)
{
    char comma;
    int class;
    int id;
    FILE *id_fp;
    int flag = 0;
    int comma_count = 0;
    id_fp = fopen("first.txt", "r");
    while (fscanf(id_fp, "%d", &id) != EOF)
    {
        if (id == given_ID)
        {
            while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
            {
                if (comma == ';')
                    comma_count++;
                fscanf(id_fp, "%d", &class);
            }
            if (comma_count >= 3)
            {
                fclose(id_fp);

                return class;
            }
            else
            {
                fclose(id_fp);
                return -1;
            }
        }
        while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
        {
            fscanf(id_fp, "%d", &class);
        }
    }
}

int instructor_cl(int given_ID)
{
    char comma;
    int class;
    int id;
    FILE *id_fp;
    int flag = 0;
    id_fp = fopen("first.txt", "r");
    while (fscanf(id_fp, "%d", &id) != EOF)
    {
        if (id == given_ID)
        {
            flag = 1;
            fscanf(id_fp, ";%d", &class);
            fclose(id_fp);
            return class;
        }
        while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
        {
            fscanf(id_fp, "%d", &class);
        }
    }
    if (flag == 0)
    {
        fclose(id_fp);
        return -1;
    }
}

void role_to_dep(char initial)
{
    FILE *id_fp;
    int comma_count = 0;
    char comma;
    char comma2;
    int flag = 1;
    int department;
    int id;
    id_fp = fopen("second.txt", "r");
    while (fscanf(id_fp, "%d", &id) != EOF)
    {
        while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
        {
            if (comma == ';')
                comma_count++;
            if (comma_count == 3)
            {
                fscanf(id_fp, "%c", &comma);
                comma_count = 0;
                if (comma == initial)
                {
                    while (comma != ';')
                    {
                        fscanf(id_fp, "%c", &comma);
                        if (comma == ';')
                        {
                            if (initial == 's')
                                printf("STUDENT ");
                            else
                                printf("INSTRUCTOR ");

                            fscanf(id_fp, "%d", &department);
                            printf("%d ", id);
                            printf("%d\n", department);
                        }
                    }
                }
            }
        }
        comma_count = 0;
    }
    fclose(id_fp);
}

int average_grade(FILE *id_fp, int id)
{
    int id_finder;
    char comma;
    int mid1;
    int mid2;
    int final;
    float class_mid_avg, class_final_avg;
    int student_count = 0;
    float sum_mid = 0;
    float final_sum = 0;
    int stored_class;
    int student_mid, student_final;
    int class;
    int comma_count = 0;

    rewind(id_fp);
    /*DETERMINE THE CLASS*/
    while (fscanf(id_fp, "%d", &id_finder) != EOF)
    {
        if (id_finder == id)
        {
            while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
            {
                if (comma == ';')
                    comma_count++;
                fscanf(id_fp, "%d", &class);
            }
        }
        while ((fscanf(id_fp, "%c", &comma) != EOF) && (comma != '\n'))
            ;
    }

    rewind(id_fp);
    stored_class = class;

    if (comma_count == 4)
    {
        while (fscanf(id_fp, "%d;%d;%d;%d;%d ", &id_finder, &mid1, &mid2, &final, &class) != EOF)
        {

            if (class == stored_class)
            {
                if (id == id_finder)
                {
                    printf("ID: %2d MIDTERM 1: %2d MIDTERM 2: %2d FINAL: %2d CLASS: %2d", id, mid1, mid2, final, class);

                    student_mid = (mid1 + mid2) / 2;
                    student_final = final;
                }
                sum_mid += (mid1 + mid2) / 2;
                final_sum += final;
                student_count++;
            }
            else
            {
                class = 0;
                continue;
            }
            class = 0;
        }

        class_mid_avg = sum_mid / student_count;
        class_final_avg = final_sum / student_count;
    }
    else if (comma_count == 3)
    {

        while (fscanf(id_fp, "%d;%d;%d;%d%c ", &id_finder, &mid1, &final, &class, &comma) != EOF)
        {
            if (class == stored_class)
            {
                if (id == id_finder)
                {
                    printf("ID: %2d MIDTERM 1: %2d FINAL: %2d CLASS: %2d", id, mid1, final, class);

                    student_mid = mid1;
                    student_final = final;
                }
                sum_mid += (mid1);
                final_sum += final;
                student_count++;
            }
            else
            {
                class = 0;
                continue;
            }
            class = 0;
        }
        class_mid_avg = sum_mid / student_count;
        class_final_avg = final_sum / student_count;
    }
    float GPA;
    if (comma_count == 4)
    {
        GPA = grade_student(student_mid, student_final, class_mid_avg, class_final_avg);
    }
    else if (comma_count == 3)
        GPA = grade_student(student_mid, student_final, class_mid_avg, class_final_avg);

    if ((choice == 'c' || choice == 'p') && (comma_count == 4 || comma_count == 3))
    {
        if (GPA == 1)
            printf("   *FAIL* \n");
        else
            printf("   -PASS- \n");
        return 2 * GPA;
    }
    if (choice == 'g' || choice == 'n')
    {
        if (GPA > 0)
        {
            if (GPA == 1)
                printf("   *FAIL* ");
            else
                printf("  -PASS- ");

            printf(" GPA : %.2lf ", GPA);
        }
        else
            printf("NOT A STUDENT\n");
    }
}