
// function prototypes
// Clear the standard input buffer
void clearInputBuffer(void);
// Wait for user to input the "enter" key to continue
void suspend(void);
// Gets int input
int inputInt(void);
// Gets positive int input
int inputIntPositive(void);
// Gets integer input within a range
int inputIntRange(int lowerBound, int upperBound);
// Get a character input matching any of the characters in a given string
char inputCharOption(char *validChars);
// Gets string within range of length of string
void inputCString(char *cString,int minNumChars, int maxNumChars);
// Formats and display phone number(10 digit)
void displayFormattedPhone(const char*);
