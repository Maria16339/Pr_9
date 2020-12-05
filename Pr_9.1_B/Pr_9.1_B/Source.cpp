// B
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>

using namespace std;

#pragma pack(push, 1)

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "Інформатика ",
                            "Радіоелектроніка", "Комп'ютерні науки",
                            "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_pedagogy;
    union
    {
        int grade_programming;
        int grade_numerical_methods;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
double kilkist(Students* S, const int N);
double Percentage(Students* S, const int N);
void Print(Students* S, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    Print(S, N);
    cout << "Процент студентів, які мають 5  з фізики: " << setprecision(2) << Percentage(S, N) << "%" << endl;
    cout << "Кількість студентів, які вчаться на “відмінно”:" << setprecision(2) << kilkist(S, N) << endl;
    return 0;
}
void Create(Students* S, const int N)
{
    int speciality;
    for (int i = 0; i < N; i++)
    {
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "Курс: "; cin >> S[i].course; cout << endl;
        cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки,";
        cout << "\n3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
        cin >> speciality;
        cout << "Оцінка з фізики: "; cin >> S[i].grade_physics;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math;
        S[i].speciality = (Speciality)speciality;

        switch (S[i].speciality)
        {
        case KN:
            cout << "Оцінка з програмування: "; cin >> S[i].grade_programming;
            break;
        case ITIS:
            cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_numerical_methods;
            break;
        default:
            cout << "Оцінка з педагогіки: "; cin >> S[i].grade_pedagogy;
        }
        cout << endl;
    }
}
void Print(Students* S, const int N)
{
    cout << "==============================================================================================================================" << endl;
    cout << "|  №  |  Прізвище  |  Курс  |  Спеціальність  |  Фізика  |  Математика  |  Програмування  |";
    cout << "  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(3) << S[i].surname << setw(3);
        cout << "|" << setw(4) << S[i].course << setw(4);
        cout << "|" << setw(3) << speciality_str[S[i].speciality] << setw(3);
        cout << "|" << setw(5) << S[i].grade_physics << setw(5);
        cout << "|" << setw(7) << S[i].grade_math << setw(7);
        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(7) << S[i].grade_programming << setw(7);
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(7) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(8) << S[i].grade_numerical_methods << setw(8);
            cout << "|" << setw(8) << "-" << setw(8) << "|";
            break;
        default:
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(7) << S[i].grade_pedagogy << setw(7) << "|";
        }
        cout << endl;
    }
    cout << "=============================================================================================================================" << endl;
}
double kilkist(Students* S, const int N)
{
    int m = 0;
    for (int i = 0; i < N; i++)
       switch (S[i].speciality)
      { 
        case KN:
            return (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_programming * 1.) / 3.==5;
        case ITIS:
            return (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_numerical_methods * 1.) / 3.==5;
        default:
            return (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_pedagogy * 1.) / 3.==5;
        }
            m++;
    return m;
}
double Percentage(Students* S, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (S[i].grade_physics == 5)
            k++;
    return k / (N * 1.0) * 100;
}