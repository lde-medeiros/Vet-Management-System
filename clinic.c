

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
// include the user library "core" so we can use those functions
#include "core.h"

// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max,FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// Find the patient array index with the earliest date and time
int LowestAppData(const struct Appointment appointment[], int max)
{
    int i, index = 0;
    int lowestYear = 9999;
    int lowestMonth = 12;
    int lowestDay = 31;
    int lowestHour = 24;
    int lowestMin = 60;

    // Find and save the appointment with the earliest year
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year < lowestYear)
        {
            lowestYear = appointment[i].date.year;
        }
    }
    // Find and save the appointment with the earliest month, in the earliest year
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear && appointment[i].date.month < lowestMonth)
        {
            lowestMonth = appointment[i].date.month;
        }
    }
    // Find and save the appointment with the earliest day, in the earliest year, and month
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear && appointment[i].date.month == lowestMonth && appointment[i].date.day < lowestDay)
        {
            lowestDay = appointment[i].date.day;
        }
    }
    // Find and save the appointment with the earliest hour, in the earliest year, month, and day
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear && appointment[i].date.month == lowestMonth && appointment[i].date.day == lowestDay && appointment[i].time.hour < lowestHour)
        {
            lowestHour = appointment[i].time.hour;
        }
    }
    // Find and save the appointment with the earliest minute, in the the earliest year, month, day, and hour
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear && appointment[i].date.month == lowestMonth && appointment[i].date.day == lowestDay && appointment[i].time.hour == lowestHour && appointment[i].time.min < lowestMin)
        {
            lowestMin = appointment[i].time.min;
            index = i;
        }
    }
    // Return the index of the appointment with the earliest date and time
    return index;
}


// Sorts the appointment data in ascending order by date and time
void SortAppTdata(struct Appointment appointment[], int max)
{
    int i, index;
    struct Appointment sortedAppts[50] = { {0} };

    for (i = 0; i < max; i++)
    {
        index = LowestAppData(appointment, max);

        sortedAppts[i].patientNumber = appointment[index].patientNumber;
        sortedAppts[i].date.year = appointment[index].date.year;
        sortedAppts[i].date.month = appointment[index].date.month;
        sortedAppts[i].date.day = appointment[index].date.day;
        sortedAppts[i].time.hour = appointment[index].time.hour;
        sortedAppts[i].time.min = appointment[index].time.min;
    
        // Remove from original array
        appointment[index].patientNumber = 0;
    }

    for (i = 0; i < max; i++)
    {
        // Save the values of the new array to the original array
        appointment[i].patientNumber = sortedAppts[i].patientNumber;
        appointment[i].date.year = sortedAppts[i].date.year;
        appointment[i].date.month = sortedAppts[i].date.month;
        appointment[i].date.day = sortedAppts[i].date.day;
        appointment[i].time.hour = sortedAppts[i].time.hour;
        appointment[i].time.min = sortedAppts[i].time.min;        
    }

    return;
}
  
// Prompt user for the date (year, month, day) of the appointment
struct Date ApptDate(void)
{
    struct Date date = { 0 };

    // Prompt user and save the valid year input
    printf("Year        : ");
    date.year = inputIntPositive();

    // Prompt user and save the valid month input
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    // Prompt user and save the valid day input for odd months
    if (date.month % 2 != 0)
    {
        printf("Day (1-31)  : ");
        date.day = inputIntRange(1, 31);
    }
    // Prompt user and save the valid day input for even months
    else if (date.month % 2 == 0)
    {
        // Check for leap year if month is February
        if (date.month == 2)
        {
            if (date.year % 4 == 0)
            {
                printf("Day (1-29)  : ");
                date.day = inputIntRange(1, 29);
            }
            else
            {
                printf("Day (1-28)  : ");
                date.day = inputIntRange(1, 28);
            }
        }
        else
        {
            printf("Day (1-30)  : ");
            date.day = inputIntRange(1, 30);
        }
    }

    // Return the date (year, month, day)
    return date;
}

// Prompt user for the time (hour, minute) of the appointment
struct Time ApptTime(void)
{
   
    struct Time time = { 0 };
     int flag = 0;
    // Repeat prompting for the hour and minute, until valid input is entered
    do
    {
        // Prompt user for the hour
        printf("Hour (0-23)  : ");
        time.hour = inputIntRange(0, 23);

        // Prompt user for the minute
        printf("Minute (0-59): ");
        time.min = inputIntRange(0, 59);

        // Check if entered time is within business hours, and make sure time is at valid minute intervals
        if ((time.hour == OPERATION_END_HOUR && time.min != 0) ||
            (time.hour < OPERATION_START_HOUR || time.hour > OPERATION_END_HOUR) ||
            ((time.hour >= OPERATION_START_HOUR && time.hour <= OPERATION_END_HOUR) && (time.min % OPERATION_MINUTE_INTERVAL != 0)))
        {
            printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
        }
        else
        {
            flag = 1;
        }
    } while (flag == 0);


    return time;
}

// Display's all patient data in the FMT_FORM | FMT_TABLE format

void displayAllPatients(const struct Patient patient[], int max, int fmt){
int i ;
if (patient == NULL) {
        printf("*** No records found ***");
    } else {
        displayPatientTableHeader();
    }
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number

void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);

        switch (selection) {

            case 1:
                printf("\n");
                searchPatientByPatientNumber(patient,max);
                printf("\n");

                suspend();
                break;
            case 2:
                printf("\n");
                searchPatientByPhoneNumber(patient,max);
                printf("\n");
                suspend();
                break;

            default:
            printf("\n");
        }
    } while (selection != 0);
    
    return;
}
// Add a new patient record to the patient array

void addPatient(struct Patient patient[], int max)
{
   int i, index, available = 0;

    for (i = 0; i < max && available == 0; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i;
            available = 1;
        }
    }

    if (available == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        // Find the next available patient number
        int nextNum = 1;
        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber >= nextNum)
            {
                nextNum = patient[i].patientNumber + 1;
            }
        }

        patient[index].patientNumber = nextNum;

        inputPatient(&patient[index]);

        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array

void editPatient(struct Patient patient[], int max)
{
    int num, i;
    printf("Enter the patient number: ");
    num = inputInt();
    putchar('\n');
    i = findPatientIndexByPatientNum(num, patient, max);
    if (i == -1) {
        printf("ERROR: Patient record not found!\n");
    } else {
        menuPatientEdit(&patient[i]);
    }
}
// Remove a patient record from the patient array

void removePatient(struct Patient patient[], int max)
{
    int num, index;
    char j;
    char yORn[3] = "yn";
    printf("Enter the patient number: ");
    num = inputIntPositive();
    printf("\n");
    index = findPatientIndexByPatientNum(num, patient, max);
    if (index > 0)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");
        j = inputCharOption(yORn);

        if (j == 'y')
        {
            strcpy(patient[index].name, "\0");

            patient[index].patientNumber = 0;

            strcpy(patient[index].phone.description, "\0");

            strcpy(patient[index].phone.number, "\0");

            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
    printf("\n");
}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int index, i = 0;

    displayScheduleTableHeader(&data->appointments[i].date, YES_INDICATOR);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if(data->appointments[i].patientNumber != 0)
        {
            index = findPatientIndexByPatientNum (data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &data->appointments[i], YES_INDICATOR);
        }
    }

    printf("\n");

    return;
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    struct Date tempDate = { 0 };
    int index, i;
    
    // Call function to get the appointment date and save it
    tempDate = ApptDate();

    printf("\n");

    displayScheduleTableHeader(&tempDate, NO_INDICATOR);

    for (i = 0; i < data->maxAppointments; i++)
    {
        // If there is/are appointment(s) on the entered date, display appointment information
        if (data->appointments[i].patientNumber != 0 &&
            data->appointments[i].date.year == tempDate.year &&
            data->appointments[i].date.month == tempDate.month &&
            data->appointments[i].date.day == tempDate.day)
        {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &data->appointments[i], NO_INDICATOR);
        }
    }

    printf("\n");

    return;
}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppts, struct Patient* patients, int maxPatients)
{
    int i, emptyIndex, patientIndex = -1;
    int tempPatientNumber;
    int apptAvailable = 1;
    int emptyAppt = 0;
    struct Date tempDate = { 0 };
    struct Time tempTime = { 0 };
    
    // Check if there is an available element in the appointments array for a new appointment to be added
    for (i = 0; i < maxAppts && emptyAppt == 0; i++)
    {
        if (appointments[i].patientNumber == 0)
        {
            emptyIndex = i;
            emptyAppt = 1;
        }
    }

    // Continue with the appointment setup process, if there is an available appointment timeslot
    if (emptyAppt == 1)
    {
        // Prompt user for the patient number
        printf("Patient Number: ");
        tempPatientNumber = inputIntPositive();

        // Call function to find and save the patient index using the entered patient number
        patientIndex = findPatientIndexByPatientNum(tempPatientNumber, patients, maxPatients);

        // Repeat prompting user for the desired appointment date (until input is valid), or display message
        do
        {
            apptAvailable = 1;
            // Continue if patient with the entered patient number exists
            if (patientIndex >= 0)
            {
                // Call functions to get the date and time information of the appointment to add
                tempDate = ApptDate();
                tempTime = ApptTime();

                printf("\n");

                // Display message if there is an appointment with the same date and time already
                for (i = 0; i < maxAppts && apptAvailable == 1; i++)
                {
                    if (appointments[i].patientNumber != 0 &&
                        appointments[i].date.year == tempDate.year &&
                        appointments[i].date.month == tempDate.month &&
                        appointments[i].date.day == tempDate.day &&
                        appointments[i].time.hour == tempTime.hour &&
                        appointments[i].time.min == tempTime.min)
                    {
                        printf("ERROR: Appointment timeslot is not available!\n\n");
                        apptAvailable = 0;
                    }
                }
            }
            // Display message if there are no patients with the entered patient number
            else
            {
                printf("ERROR: Patient record not found!\n");
            }
        } while (apptAvailable == 0);
    }
    // Display message if there are no available appointment timeslots
    else
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
    }

    // Save the new appointment information if input is valid and appointment timeslot is available
    if (patientIndex >= 0 && apptAvailable == 1)
    {
        appointments[emptyIndex].patientNumber = patients[patientIndex].patientNumber;
        appointments[emptyIndex].date.year = tempDate.year;
        appointments[emptyIndex].date.month = tempDate.month;
        appointments[emptyIndex].date.day = tempDate.day;
        appointments[emptyIndex].time.hour = tempTime.hour;
        appointments[emptyIndex].time.min = tempTime.min;

        printf("*** Appointment scheduled! ***\n\n");
    }

    // Call function to sort the appointments by date in ascending order
    SortAppTdata(appointments, maxAppts);

    return;
}
// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointments, int maxAppts, struct Patient* patients, int maxPatients)
{
    int index, i, flag = 0;
    int tempPatientNumber, patientIndex;
    char yesOrNo = ' ';
    struct Date tempDate = { 0 };

    // Prompt user for the patient number
    printf("Patient Number: ");
    tempPatientNumber = inputIntPositive();

    // Call function to find and save the patient index using the entered patient number
    patientIndex = findPatientIndexByPatientNum(tempPatientNumber, patients, maxPatients);


    // Continue if the patient with the patient number exists
    if (patientIndex >0)
    {
        // Call function to find and save the appointment date to remove
        tempDate = ApptDate();
        
        printf("\n");

        displayPatientData(&patients[patientIndex], FMT_FORM);

        // Check if there exists an appointment with the entered appointment date
        for (i = 0; i < maxAppts && flag == 0; i++)
        {
            if (appointments[i].patientNumber == patients[patientIndex].patientNumber &&
                appointments[i].date.year == tempDate.year &&
                appointments[i].date.month == tempDate.month &&
                appointments[i].date.day == tempDate.day)
            {
                index = i;
                flag = 1;
            }
        }

        // Confirm with user if they want to remove the appointment
        if (flag == 1)
        {
            printf("Are you sure you want to remove this appointment (y,n): ");
            yesOrNo = inputCharOption("yn");

            if (yesOrNo == 'y')
            {
                appointments[index].patientNumber = 0;
                appointments[index].date.year = 0;
                appointments[index].date.month = 0;
                appointments[index].date.day = 0;

                printf("\n");
                printf("Appointment record has been removed!\n");
            }

        }
    }

    // Display message if there are no patients with the entered patient number
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
    
    printf("\n");

    return;
}
//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
   int num, i;
    
    printf("Search by patient number: ");
    num = inputIntPositive();

    // Check if there is a record with a matching phone number
    i = findPatientIndexByPatientNum(num, patient, max);
    
    printf("\n");
    if (i > 0)
    {
        displayPatientData(&patient[i], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    //printf("\n");// 
}   


// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    
    int i, flag = 0;
    char phone_Num[PHONE_LEN + 1];
    printf("Search by phone number: ");
    inputCString(phone_Num, PHONE_LEN, PHONE_LEN);
    printf ("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(phone_Num, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("\n*** No records found ***\n");
    }
}


// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int largest_Num, i;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > largest_Num) {
            largest_Num = patient[i].patientNumber;
        }
    }
    return largest_Num + 1;
}
// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int j = 0, flag = 0;
    for (j = 0; j < max; j++) {

        if (patient[j].patientNumber == patientNumber) {
            flag = j;
        }
    }
    
    return flag;
    return j;
}
//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record

void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------");
    printf("\nNumber: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}
// Get user input for phone contact information

void inputPhoneData(struct Phone* phone)
{
    int option;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    option = inputIntRange(1, 4);
    printf("\n");

    switch (option)
    {
    case 1:
            
            strcpy((*phone).description, "CELL");
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            printf("\n");//added
            break;
    case 2:
            strcpy((*phone).description, "HOME");
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            printf("\n");
            break;

    case 3: 
            strcpy((*phone).description, "WORK");
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            printf("\n");//added
            break;

    case 4:
            strcpy((*phone).description,"TBD");
            strcpy((*phone).number, "\0");


    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char *file, struct Patient patients[], int max)
{
     int rc, i = 0;
    FILE *fp = NULL;
    fp = fopen(file, "r");
    if (fp != NULL)
    {
        do
        {
            rc = fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[i].patientNumber,patients[i].name,patients[i].phone.description,patients[i].phone.number);
            if (rc > 0)
            {
                i= i + 1;
            }
        } while (rc > 0 && i < max);

        fclose(fp);
    }
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* file, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;
    int i = 0;

    fp = fopen(file,"r");
    
    if (fp != NULL) {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber, &appoints[i].date.year,&appoints[i].date.month, &appoints[i].date.day,&appoints[i].time.hour, &appoints[i].time.min) == 6 && i < max) {
            i = i +1;
        }
        fclose(fp);
    }
    SortAppTdata( appoints, i);
    return i;
}

