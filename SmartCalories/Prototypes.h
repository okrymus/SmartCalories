//Function Prototypes

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// Print title and menu section

// Pre condition:  os is opened or not
// Post condition: Print a centered title for the program
//                 write the title to a file
void titleOfProgram(ostream &os = cout);

// Pre condition:  NONE
// Post condition: Print activity's options for the program
void activitiyOptions();

// Calculate section

// Pre condition:  NONE
// Post condition: retrun "bmr" Basal metabolic rate as a double number
double calcBMR(int age, string sex, int feet, int inches, double pound, int activity);

// Personal information section

// Pre condition:  nameInput must not be existed as \\nameInput.txt
// Post condition: it asks for a user's personal information
//                 create and write all information to \\nameInput.txt
//                 removes everything else from the cin
void getPersonalInformation(string &nameUser);

// Pre condition:  NONE
// Post condition: print a user's personal information from a file
//                 returns bmr to the main
double printAccountInformation(string nameUser);

// Pre condition:  os is opened or not
// Post condition: prints how many calories that a user require
//                 or write it to a file
void personalCaloriesRequire(double bmr, ostream &os = cout);

// Pre condition:  nameInput must be existed as \\nameInput.txt
// Post condition: it asks for a user's personal information that a user want to change
//                 create and write changes information to \\nameInput.txt
//                 removes everything else from the cin
void editPersonalInformation(string nameUser);

// Pre condition:  NONE
// Post condition: it prints message to a monitor
//                 it accepts input a number between 1 and 5 or "/n"
//                 returns the number "select" or 0 when a user hited enter
int getOthersOption();

// Pre condition:  os is opened
// Post condition: write a user's personal information to a file 
//                 it gets a personal BMR "bmr"
void writePersonalInformationToFile(string nameUser, int age, string sex, int feet, int inches, double pound, int activity, ostream &os);

// Calculate section

// Pre condition:  NONE
// Post condition: retrun "bmr" Basal metabolic rate as a double number
double calcBMR(int age, string sex, int feet, int inches, double pound, int activity);

// Date section

// Pre condition:  NONE
// Post condition: gets three integer numbers that can be a form of date 
//                 it does not crashes for non-numeric input
//                 removes everything else from the cin
void getDate(int &date, int &month, int &year);

// Pre condition:  NONE
// Post condition: returns true when the input date is legal date
//                 returns false when the input date is not legal date
bool checkDate(int month, int date, int year);

// Pre condition:  "year" is greater than 1999 ,but it is less than 2100
// Post condition: returns true when the year has 29 days in February or
//                 returns false when the year has 28 days in February
bool isLeap(int year);

// Pre condition:  A number of month "month" must be in range between 1 and 12
// Post condition: returns a month of year as a string
string monthOfYear(int month);

// Pre condition:  a value "value" must be greater than 1 or equal 1
//                 the value is used to find an ordinal number of the value
// Post condition: returns an ordinal letter of the value 
//                 such as "th", "rd" and "st"
string getOrdinalFor(int value);

// Pre condition:  "date" is in range between 1 and 31
//                 "monte" is in range between 1 and 12
//                 "year" is in range between 2000 and 2100
//                 in the other word all these variables is legal date
// Post condition  returns a day of week as a string
string dayOfWeek(int date, int month, int year);

// Record  section

// Pre condition:  os is opened or not
// Post condition: Print the title of a record with the date of recording
//                 or write the title to a file
void printViewRecordTitle(int month, int date, int year, ostream &os = cout);

// Pre condition:  os is opened or not
// Post condition: print the title of a writing record with the date of recording
//                 or write the title to a file
void printWriteRecordTitle(int month, int date, int year, ostream &os = cout);

// Pre condition:  (if need to write to a file, os is opened)
// Post condition: print Calories is possible that a person can maintain his weight
//                 or write it to a file 
void printCaloriesPossibleToMaintainWeight(double netTotalCalories, double bmr, ostream &os = cout);

// Pre condition:  0 < "ls" logical size <= physical size of aNameFood[], aUnitOfFood[] and aCaloriesOfAUnit[] 
// Post condition: loads the first "ls" element of aNameFood[] with input "nameFood",
//                      aUnitOfFood[] with input "foodUnit" >= 1, but it <= 20, 
//                      and aCaloriesOfAUnit[] with input "foodCalories" is a number
//                 stops loading when input "nameFood" is "stop" or reached the "ls" cell
//                 return "logical" logical size of aNameFood[]
int loadArrayOfActivity(string aNameFood[], int aUnitOfFood[], double aCaloriesOfAUnit[], int ls);

// Pre condition:  0 < "ls" logical size <= physical size of aNameFood[], aUnitOfFood[] and aCaloriesOfAUnit[] 
//                                          os is opened and "ls" logical size is greater than 0
// Post condition: print the first cell thorough "ls" to os
double printArray(string aNameFood[], int aUnitOfFood[], double aCaloriesOfAUnit[], int ls, ostream &os = cout);

// Pre condition:  nameUser// "date" date.txt is existed
//                                   os is open or not
// Post condition: prints a record on date "date" to the monitor and get netTotalCalories from \\date.txt
//                 returns "netTotalCalories" to the main
double printWritedRecord(string nameUser, string date, ostream &os = cout);

// Pre condition:  NONE
// Post condition: Print the food categories and the direction
void foodCategoriesMenu();

// Pre condition:  categoriesSelect must be greater than 0 and less than 6
// Post condition: Print the food lists of the selected category "categoriesSelect"
//                 when the food lists do not have what a user want, let the user to type by own
//                 Retrun nameFood that a user chose
string printFoodList(string categoriesSelect);

// Report section

// Pre condition:  os is opened
// Post condition: returns false when the program cannot found any record during time period
//                 returns true when the program found the records during time period
//                 it prints the whole file which is existed during the specific time period
//                 which is weekly report
bool printReport(int month, int date, int year, string nameUser, double bmr, ostream &os = cout);

// Pre condition:  os is opened
// Post condition: returns false when the program cannot found any record during time period
//                 returns true when the program found the records during time period
//                 it prints the whole file which is existed during the specific time period
//                 which is monthly report
bool printReport(int month, int year, string nameUser, double bmr, ostream &os = cout);

// Pre condition:  0 < "ls" logical size <= physical size of dateFile[],aNetTotalCalories[] 
//                                  os is opened or not
// Post condition: prints stats(maximum value, minimum value, average) of the first ls cells of a[] to os
void printStatisticInReport(string dateFile[], double aNetTotalCalories[], int ls, double bmr, ostream &os = cout);

// Statistic section

// Pre condition:  0 < "ls" logical size <= physical size of a[]
// Post condition: returns ("sum" divide by "ls") the average of calories which "sum" is forn a[]
double getAverage(double a[], int ls);

// Pre condition:  0 < "ls" logical size <= physical size of a[]
// Post condition: returns "max" the index of maximum value which stored in a[]
int findIndexMax(double a[], int ls);

// Pre condition:   0 < "ls" logical size <= physical size of a[]
// Post condition: returns "min" the index of minimum value which stored in a[]
int findIndexMin(double a[], int ls);

// Get numbers and letter section 

// Pre condition:  endPoint > startPoint
// Post condition: Return a integer number which is in the range
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
int getIntInRange(double startPoint, double endPoint);

// Pre condition:  NONE
// Post condition: Return a valid integer value  
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
int getInteger();

// Pre condition:  NONE
// Post condition: Return a valid double number
//                 it does not crashes for non-numeric input   
//                 removes everything else from the cin
double getNum();

// Pre condition:  NONE
// Post condition: Return a valid positive integer
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
int getIntPosNum();

// Pre condition:  NONE
// Post condition: Return a valid positive double
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
double getPosNum();

// Pre condition:  NONE
// Post condition: Return a letter: "n", "N", "y", or "Y"
//                 removes everything else from the cin
char getYorN();

// others section

// Pre condition:  number has to be an integer
// Post condition: Returns number as a string
string intToStr(int number);

// Pre condition:  The nameinput doesn't have control characters in filenames
// Post condition: Return TRUE when the nameInput.file is existed
//                 return FALSE when the nameInput.file is not existed
bool findExistedFile(string fileName);





