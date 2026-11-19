
#include <stdio.h>
#include <string.h>

struct Date {
    int day, month, year;
};

struct BloodPressure {
    int systolic, diastolic;
};

struct Patient {
    char name[50];
    int age;
    char phone[11];
    struct BloodPressure bp;
    struct Date visitDate;
};

void addPatient(struct Patient *p, const char n[],
                int a, const char ph[],
                int s, int d, struct Date date) {
    strcpy(p->name, n);
    p->age = a;
    strcpy(p->phone, ph);
    p->bp.systolic = s;
    p->bp.diastolic = d;
    p->visitDate = date;
}

int main(void) {
    struct Patient p;

    struct Date date = {19, 11, 2026};

    addPatient(&p, "Kishore", 17, "9876543210",
               120, 80, date);

    printf("Patient Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Phone: %s\n", p.phone);
    printf("Blood Pressure: %d/%d\n",
           p.bp.systolic, p.bp.diastolic);
    printf("Visit Date: %02d/%02d/%04d\n",
           p.visitDate.day,
           p.visitDate.month,
           p.visitDate.year);

    return 0;
}
