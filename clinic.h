
#ifndef CLINIC_H
#define CLINIC_H
// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10

#include <string.h>

#define NO_INDICATOR 0
#define YES_INDICATOR 1
#define OPERATION_START_HOUR 10
#define OPERATION_END_HOUR 14
#define OPERATION_MINUTE_INTERVAL 30
//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
// ToDo:
struct Phone
{
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};

// Data type: Patient 
// ToDo:
struct Patient
{
    int patientNumber;
    char name[NAME_LEN + 1];
    struct Phone phone;
};

// Data type: Time
// ToDo:
struct Time
{
    int hour;
    int min;
};


// Data type: Date
// ToDo:
struct Date
{
    int year;
    int month;
    int day;
};

// Data type: Appointment
// ToDo:
struct Appointment
{
    int patientNumber;
    struct Date date;
    struct Time time;
};


// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,const struct Appointment* appoint,int includeDateField);

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data);

// View appointment schedule for the user input date

void viewAppointmentSchedule(struct ClinicData* data);

// Add an appointment record to the appointment array

void addAppointment(struct Appointment* appointments, int maxAppts, struct Patient* patients, int maxPatients);


// Remove an appointment record from the appointment array

void removeAppointment(struct Appointment* appointments, int maxAppts, struct Patient* patients, int maxPatients);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

// Prompt user for the date (year, month, day) of the appointment
struct Date getApptDate(void);

// Prompt user for the time (hour, minute) of the appointment
struct Time getApptTime(void);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* file, struct Patient patients[],int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* file, struct Appointment appoints[], int max);

#endif // !CLINIC_H