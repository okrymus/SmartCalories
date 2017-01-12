#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "Prototypes.h"
using namespace std;


// Print title and menu section

void titleOfProgram(ostream &os)
{
	os
		<< endl
		<< "\t                   Smart Calories Calculator              " << endl
		<< "\t                        By Lee. Panupong                  " << endl << endl;
}

void activitiyOptions()
{
	cout
		<< endl
		<< "   ***************************************************" << endl
		<< "   *    1] Little or no exersice                     *" << endl
		<< "   *    2] exercise or play sports 1-3 times/week    *" << endl
		<< "   *    3] exercise or play sports 3-5 times/week    *" << endl
		<< "   *    4] exercise or play sports 6-7 times/week    *" << endl
		<< "   *    5] exercise or play sport very hard          *" << endl
		<< "   ***************************************************" << endl;
}

// Personal information section

void getPersonalInformation(string &nameUser)
{
	string file, sex;
	ofstream newFile;
	char YesOrNo;
	int age, feet, inches, activity;
	double pound;
	
	file = nameUser + "//" + nameUser + ".txt";

	// Prit a user name
	cout << "\n  You name is " << nameUser << endl;
	
	// Ask the correct nameUser
	cout << "\tIs it your correct name? ";
	YesOrNo = getYorN();
	
	if (YesOrNo == 'N' || YesOrNo == 'n')
	{
		cout << "  Please enter your name: ";
		getline(cin, nameUser);
		
		file = nameUser + "//" + nameUser + ".txt";

		// It prohibits control characters in filenames and checks nameuser.txt is existed or not
		while (findExistedFile(file))
		{
			cout
				<< "\n\tThe program failed to use the name: : \"" << nameUser << "\" as a file." << endl
				<< "\tPlease enter another name: ";
			getline(cin, nameUser);

			file = nameUser + "//" + nameUser + ".txt";
		}
	}

	cout << "\n  Please enter the following questions" << endl << endl;

	// 1. Get a user's age "age" is a integer 1-120
	cout << "  1.Your age: ";
	age = getIntInRange(1, 120);

	// 2. Get a user's gender
	cout << "  2.Genger(male/female): ";
	cin >> sex;  	 cin.ignore(80, '\n');

	while (!(sex == "male" || sex == "female"))
	{
		cout << "\tPlease enter only \"male\" or \"female\": ";
		cin >> sex;  	cin.ignore(80, '\n');
	}

	// 3. Get a user's height "feet" and "inches"
	cout << "  3.Height in feet and inches on the next line" << endl;
		
	// in feet unit
	cout<< "    feet: ";
	feet = getIntPosNum();

	// in inches unit

	cout << "    inches: ";
	inches = getIntInRange(0, 12);

	// 4. Get a user's weight
	cout << "  4.Weight: ";
	pound = getPosNum();

	// 5. Get a user's activitiy
	activitiyOptions();
	
	cout << endl << "  5.Please choose the activity: ";
	activity = getIntInRange(1, 5);

	// Create a new directory by using nameInput as name of a folder
	string quote = "\"";
	string commandString = "mkdir " + quote + nameUser + "\"";
	system(commandString.c_str());
	
	// Write a personal information to nameUser.txt
	newFile.open(file);

	writePersonalInformationToFile(nameUser, age, sex, feet, inches, pound, activity, newFile);

	newFile.close();
}

void writePersonalInformationToFile(string nameUser, int age, string sex, int feet, int inches, double pound, int activity, ostream &os)
{
	// Get bmr from calcBMR function
	double bmr = calcBMR(age, sex, feet, inches, pound, activity);

	titleOfProgram(os);
	os
		<< "  Name    : " << nameUser << endl
		<< "  Age     : " << age << endl
		<< "  Gender  : " << sex << endl
		<< "  Height  : " << feet << "\" " << inches << "\'" << endl
		<< "  Weight  : " << pound << endl
		<< "  Activity: ";

	switch (activity)
	{
	case 1: os << "Little or no exersice";                      break;
	case 2: os << "exercise or play sports 1-3 times/week";     break;
	case 3: os << "exercise or play sports 3-5 times/week";     break;
	case 4: os << "exercise or play sports 6-7 times/week";     break;
	case 5: os << "exercise or play sport very hard";
	}
	os << endl;

	personalCaloriesRequire(bmr, os);
}

double printAccountInformation(string nameUser)
{
	string readerLine[20];
	string aWordString1, aWordString2;
	ifstream accountFile;
	int i = 0;
	double bmr;
	string file = nameUser + "//" + nameUser + ".txt";
	
	accountFile.open(file);
	
	// Read from nameUser.txt and get "bmr" from file
	for (; i < 16; i++) {
		getline(accountFile, readerLine[i + 1]);
		if (i == 9)
			accountFile >> aWordString1 >> aWordString2 >> bmr;
	}
	accountFile.close();
	
	// Print information from ReaderLine[i]
	for (i = 4; i < 16; i++) {	
		if (i == 6)
			cout << readerLine[i] << " years old" << endl;
		else if (i == 8)
			cout << readerLine[i] << " Feet\"inches\'" << endl;
		else if (i == 9)
			cout << readerLine[i] << " pound" << endl;
		else if (i == 11)
			cout << endl << "  " << aWordString1 << " " << aWordString2 << " " << bmr <<  readerLine[i] << endl;
		else
			cout << readerLine[i] << endl;
	}
	return bmr;
}

void personalCaloriesRequire(double bmr, ostream &os)
{
	os
		<< endl << "  You need " << bmr << " Calories / day to maintain your weight." << endl
		<< "  You need " << bmr - 500 << " Calories / day to lose 1 lb per week." << endl
		<< "  You need " << bmr - 1000 << " Calories / day to lose 2 lb per week." << endl
		<< "  You need " << bmr + 500 << " Calories / day to gain 1 lb per week." << endl
		<< "  You need " << bmr + 1000 << " Calories / day to gain 2 lb per week." << endl;
}

int getOthersOption()
{
	char select;

	cout
		<< endl
		<< "          ************************************************************* " << endl
		<< "          *  Please hit ENTER to back to main menu or select another  * " << endl
		<< "          ************************************************************* " << endl << endl
		<< "                            Please choose the options: ";
	
	cin.get(select);

	// If a user hit enter, back to the main 
	if (select == '\n')
		return 0;
	
	cin.putback(select);
	select = getIntInRange(1, 5);

	return select;
}

void editPersonalInformation(string nameUser)
{
	string line, sex, aWordString;
	string readerLine[20];
	ofstream newFile;
	ifstream readFile;
	int age, feet, inches, select, activity;
	double pound;
	int i = 0;
	bool askForOnce = true;
	string file = nameUser + "//" + nameUser + ".txt";

	cout
		<< "\t              ==================================" << endl
		<< "\t              =     1] Age                     =" << endl
		<< "\t              =     2] Gender                  =" << endl
		<< "\t              =     3] Height                  =" << endl
		<< "\t              =     4] Weight                  =" << endl
		<< "\t              =     0] Back to the main menu   =" << endl
		<< "\t              ==================================" << endl;
	
	cout << "\t           Which information do you want to edit? ";
	
	select = getIntInRange(0, 4);

	if (select == 0)
		return;
	
	// Read from nameUser.txt
	readFile.open(file);

	for (; i < 8; i++) {
		getline(readFile, readerLine[i + 1]);
		if (i == 4)
			readFile >> aWordString >> aWordString >> age;
		else if (i == 5)
			readFile >> aWordString >> aWordString >> sex;
		else if (i == 6)
			readFile >> aWordString >> aWordString >> feet >> aWordString >> inches;
		else if (i == 7)
			readFile >> aWordString >> aWordString >> pound;
	}
	
	readFile.close();

	// while a user still want to select another editing option
	while (select > 0)
	{
		cout << endl;

		switch (select)
		{
		case 1:
			// Get age
			cout << "  1.Your age: ";
			age = getIntInRange(1, 120);

			break;
		case 2:
			// Get gender
			cout << "  3.Genger(male/female): ";
			cin >> sex;  	 cin.ignore(80, '\n');

			while (!(sex == "male" || sex == "female"))
			{
				cout << "\tPlease enter only \"male\" or \"female\": ";
				cin >> sex;  	cin.ignore(80, '\n');
			}

			break;
		case 3:
			// Get height
			cout<< "  3.Height in feet and inches on the next line" << endl;
			
			cout << "    feet: ";
			feet = getIntPosNum();

			cout << "    inches: ";
			inches = getIntInRange(0, 12);

			break;
		case 4:
			// Get weight
			cout << "  4.Weight: ";
			pound = getPosNum();		
		}
			
		if (askForOnce)
		{
			activitiyOptions();
			
			cout << endl << " Please choose the activity once again: ";
			activity = getIntInRange(1, 5);
			
			askForOnce = false;
		}

		select = getOthersOption();
	}

	// Write a personal information to nameUser.txt
	newFile.open(file);

	writePersonalInformationToFile(nameUser, age, sex, feet, inches, pound, activity, newFile);

	newFile.close();
}

// Calculate section

double calcBMR(int age, string sex, int feet, int inches, double pound, int activity)
{
	double bmr, activityFactor;

	switch (activity)
	{
	case 1: activityFactor = 1.2;       break;
	case 2: activityFactor = 1.375;     break;
	case 3: activityFactor = 1.55;      break;
	case 4: activityFactor = 1.725;     break;
	case 5: activityFactor = 1.9;
	}

	if (sex == "male")
		bmr = (66 + (6.23 * pound) + ((12.7 * ((feet * 12) + inches))) - (6.8 * age))*activityFactor;
	else if (sex == "female")
		bmr = (655 + (4.35 * pound) + ((4.7 * ((feet * 12) + inches))) - (4.7 * age))*activityFactor;

	return bmr;
}

// Date section

void getDate(int &date, int &month, int &year)
{
	cout << "  Month(mm) : ";
	month = getIntInRange(1, 12);
	
	cout << "  Date(dd)  : ";
	date = getIntInRange(1, 31);
	
	cout << "  Year(yyyy): ";
	year = getInteger();   

	while (!(checkDate(month, date, year)))
	{
		cout << endl << "\tInvalid date! Please try again" << endl << endl;
		
		cout << "  Month(mm) : ";
		month = getIntInRange(1, 12);
		
		cout << "  Date(dd)  : ";
		date = getIntInRange(1, 31);
		
		cout << "  Year(yyyy): ";
		year = getInteger();   
	}
}

bool checkDate(int month, int date, int year)
{
	bool result = true;
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (year<2000 || year>2100)
		result = false;
	if (isLeap(year))
		daysInMonths[1] = 29;
	if (date < 1 || date > daysInMonths[month - 1])
		result = false;

	return result;
}

bool isLeap(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return true;
	else
		return false;
}

string getOrdinalFor(int value)
{
	int hundredRemainder = value % 100;
	int tenRemainder = value % 10;

	if (hundredRemainder - tenRemainder == 10)
		return "th";
	else
		switch (tenRemainder)
	{
		case 1:
			return "st";      break;
		case 2:
			return "nd";      break;
		case 3:
			return "rd";      break;
		default:
			return "th";
	}
}

string monthOfYear(int month)
{
	switch (month)
	{
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	default: return "Undefined month";
	}
}

string dayOfWeek(int date, int month, int year)
{
	int day;
	int t[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	
	year -= month < 3;
	day = (year + year / 4 - year / 100 + year / 400 + t[month - 1] + date) % 7;

	switch (day)
	{
	case 0: return "Sunday";
	case 1: return "Monday";
	case 2: return "Thuesday";
	case 3: return "Wednesday";
	case 4: return "Tuesday";
	case 5: return "Friday";
	case 6: return "Saturday";
	default: return "Blank";
	}
}

// Record  section

void printViewRecordTitle(int month, int date, int year, ostream &os)
{
	os
		<< "              Showing the rocord on " << setw(9) << dayOfWeek(date, month, year) << setw(3) << date << getOrdinalFor(date) << setw(10) << monthOfYear(month) << setw(5) << year << endl;
	
	os
		<< "       ==================================================================" << endl
		<< "       =    List of foods    Unit   Calories/unit   Total calories      =" << endl
		<< "       ==================================================================" << endl;
}

void printWriteRecordTitle(int month, int date, int year, ostream &os)
{
	os
		<< "          <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl
		<< "          <   Writing the rocord on " << setw(9) << dayOfWeek(date, month, year) << setw(3) << date << getOrdinalFor(date) << setw(10) << monthOfYear(month) << setw(5) << year << "   <" << endl
		<< "          <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl; 
}

void printCaloriesPossibleToMaintainWeight(double netTotalCalories, double bmr, ostream &os)
{
	if (netTotalCalories > bmr)
		os << "\n\t You need to reduce " << netTotalCalories - bmr << " calories to maintain your weight." << endl;
	else if (netTotalCalories < bmr)
		os << "\n\t You need more " << bmr - netTotalCalories << " calories to maintain your weight." << endl;
}

int loadArrayOfActivity(string aNameFood[], int aUnitOfFood[], double aCaloriesOfAUnit[], int ls)
{
	string foodName;
	int foodUnit;
	double foodCalories;
	int logical = 0;

	for (; logical < ls; logical++)
	{
		cout 
			<< "\n   *Please tpye \"stop\" when finnish the record or 1-5 to view food lists" << endl
			<< setw(4) << (logical + 1) << ". Enter name of food: ";
		
		getline(cin, foodName);
		
		if (foodName == "stop")
			return logical;
		else if (foodName == "1" || foodName == "2" || foodName == "3" || foodName == "4" || foodName == "5" )
			foodName = printFoodList(foodName);

		aNameFood[logical] = foodName;
		
		cout << "      Enter unit of " << foodName << ", you consumed: ";
		foodUnit = getIntInRange(1, 20);
		
		aUnitOfFood[logical] = foodUnit;

		cout << "      Enter how many calories of " << foodName << " per each: ";
		foodCalories = getNum();
		
		aCaloriesOfAUnit[logical] = foodCalories;
	}
	cout << "Loading is FULL! Cannot accept more activities\n\n";
	
	return logical;
}

double printArray(string aNameFood[], int aUnitOfFood[], double aCaloriesOfAUnit[], int ls, ostream &os)         
{
	double netTotalCalories = 0,
		totalCaloriesPerFood;

	for (int i = 0; i < ls; i++)
	{
		totalCaloriesPerFood = aUnitOfFood[i] * aCaloriesOfAUnit[i];
		
		os << "       " << right << setw(3) << i + 1 << ". " << left << setw(16) << aNameFood[i] << right << setw(5) << aUnitOfFood[i] << setw(16) << aCaloriesOfAUnit[i] << setw(17) << totalCaloriesPerFood << endl;
		
		netTotalCalories += totalCaloriesPerFood;
	}
	
	os << setw(56) << "Net Total" << setw(10) << netTotalCalories << endl;

	return netTotalCalories;
}

double printWritedRecord(string nameUser, string date, ostream &os)
{
	string line, aStringWord;
	string readerLine[50];
	int count = 0;
	ifstream readFile;
	double netTotalCalories;
	string file = nameUser + "//" + date + ".txt";
	
	// Open a file, read it and store in an array,and also gets netTotalCalories 
	readFile.open(file);

	readFile >> aStringWord >> aStringWord >> aStringWord >> aStringWord >> netTotalCalories;

	while (getline(readFile, line))
	{
		readerLine[count] = line;
		count++;
	}

	readFile.close();

	// Print from readerLine array
	for (int i = 0; i < count; i++)	{
		if (i != 0)
			os << readerLine[i] << endl;
	}
	return netTotalCalories;
}

void foodCategoriesMenu()
{
	cout
		<< endl
		<< "\t               ======= Food Categories =======" << endl
		<< "\t               =        1] Fruit             =" << endl
		<< "\t               =        2] Vegetable         =" << endl
		<< "\t               =        3] Meat              =" << endl
		<< "\t               =        4] Dairy             =" << endl
		<< "\t               =        5] Beverage          =" << endl 
		<< "\t               ===============================" << endl
		<< "\t     ** You can type a number 1 - 5 in the name of food" << endl
		<< "\t                     to view food lists       " << endl;
}

string printFoodList(string categoriesSelect)
{
	int select;
	string nameFood;

	// Fruit category
	if (categoriesSelect == "1")
	{
		cout
			<< endl
			<< "\t   Food name       Unit              Calories" << endl
			<< "\t   ==========================================" << endl
			<< "\t1] Apple           1 small(4 oz.)    80" << endl
			<< "\t2] Banana          1 medium(6 oz.)   101" << endl
			<< "\t3] Grape           each              2" << endl
			<< "\t4] Mango           1 (8 oz.)         135" << endl
			<< "\t5] Orange          1 (4 oz.)         71" << endl
			<< "\t6] Pear            1 (5 oz.)         100" << endl
			<< "\t7] Peach           1 (6 oz.)         38" << endl
			<< "\t8] Pineapple       1 cup             80" << endl
			<< "\t9] Strawberry      1 cup             53" << endl
			<< "\t10] Watermelon     1 cup             45" << endl
			<< "\t0] Not in the lists" << endl
			<< endl
			<< "      Please selcet the food: ";
		
		select = getIntInRange(0, 11);

		switch (select)
		{
		case 1: return "Apple";
		case 2: return "Banana";
		case 3: return "Grape";
		case 4: return "Mango";
		case 5: return "Orange";
		case 6: return "Pear";
		case 7: return "Peach";
		case 8: return "Pineapple";
		case 9: return "Strawberry";
		case 10: return "Watermelon";
		}
	}
	else if (categoriesSelect == "2")
	{
		// Vegetable category
		cout
			<< endl
			<< "\t   Food name       Unit             Calories" << endl
			<< "\t   =========================================" << endl
			<< "\t1] Asparagus      1 cup, boiled     36" << endl
			<< "\t2] Bean curd      4 oz.             81" << endl
			<< "\t3] Broccoli       1 cup             40" << endl
			<< "\t4] Carrots        1 cup             45" << endl
			<< "\t5] Cucumber       each              30" << endl
			<< "\t6] Eggplant       1 cup, boiled     38" << endl
			<< "\t7] Lettuce        1 cup             7" << endl
			<< "\t8] Tomato         1 cup             29" << endl
			<< "\t0] Not in the lists" << endl
			<< endl
			<< "      Please selcet the food: ";
		
		select = getIntInRange(0, 9);

		switch (select)
		{
		case 1: return "Asparagus";
		case 2: return "Bean curd";
		case 3: return "Broccoli";
		case 4: return "Carrots";
		case 5: return "Cucumber";
		case 6: return "Eggplant";
		case 7: return "Lettuce";
		case 8: return "Tomato";
		}
	}
	else if (categoriesSelect == "3")
	{
		// Meat category
		cout
			<< endl
			<< "\t   Food name                Unit              Calories" << endl
			<< "\t   ===================================================" << endl
			<< "\t1] Beef, regular, cooked    1 slice(2 oz.)    120" << endl
			<< "\t2] Chicken, cooked          1 slice(2 oz.)    95" << endl
			<< "\t3] Egg large                                  79" << endl
			<< "\t4] Fish, Catfish, cooked    2 oz.             80" << endl
			<< "\t5] Pork, cooked             1 slice(2 oz.)    130" << endl
			<< "\t6] Shrimp, cooked           2 oz.             70 " << endl
			<< "\t0] Not in the lists" << endl
			<< endl
			<< "      Please selcet the food: ";
		
		select = getIntInRange(0, 7);

		switch (select)
		{
		case 1: return "Beef";
		case 2: return "Chicken";
		case 3: return "Egg";
		case 4: return "Fish";
		case 5: return "Pork";
		case 6: return "Shrimp";
		}
	}
	else if (categoriesSelect == "4")
	{
		// Dairy category
		cout
			<< endl
			<< "\t   Food name         Unit                   Calories" << endl
			<< "\t   =================================================" << endl
			<< "\t1] Bread, regular    1 slice(1 oz.)         75" << endl
			<< "\t2] Butter            1 table spoon          102" << endl
			<< "\t3] Caesar salad      1 serving(3 cups)      360" << endl
			<< "\t4] Cheeseburger      1 (McDonald Medium)    360" << endl
			<< "\t5] Chocolate         1 oz.                  150" << endl
			<< "\t6] Corn              1 cup, cooked          140" << endl
			<< "\t7] Hamburger         1 (McDonald Medium)    280" << endl
			<< "\t8] Pizza             1 slice                180" << endl
			<< "\t9] Potato(uncooked)  1 (6 oz.)              120" << endl
			<< "\t10] Rice, cooked     1 cup                  225" << endl
			<< "\t11] Sandwich         1                      310" << endl
			<< "\t0] Not in the lists" << endl
			<< endl
			<< "      Please selcet the food: ";
		
		select = getIntInRange(0, 12);

		switch (select)
		{
		case 1: return "Bread";
		case 2: return "Butter";
		case 3: return "Caesar salad";
		case 4: return "Cheeseburger";
		case 5: return "Chocolate";
		case 6: return "Corn";
		case 7: return "Hamburger";
		case 8: return "Pizza";
		case 9: return "Potato";
		case 10: return "Rice";
		case 11: return "Sandwich";
		}
	}
	else if (categoriesSelect == "5")
	{
		// Beverage category
		cout
			<< endl
			<< "\t   Food name              Unit                 Calories" << endl
			<< "\t   =====================================================" << endl
			<< "\t1] Beer, regular          1 can or bottle      150" << endl
			<< "\t2] Coca-Cola Classic      1 cup                97" << endl
			<< "\t3] Diet Coke              1 cup                3" << endl
			<< "\t4] Milk, low-fat(1 %)     1 cup                104" << endl
			<< "\t5] Milk, low-fat(2 %)     1 cup                121" << endl
			<< "\t6] Milk, whole            1 cup                150" << endl
			<< "\t7] Orange Juice/Apple Cider 1 cup              115" << endl
			<< "\t8] Yogurt, low-fat        1 cup                200" << endl
			<< "\t9] Yogurt, non-fat        1 cup                150" << endl
			<< "\t0] Not in the lists" << endl
			<< endl
			<< "      Please selcet the food: ";
		
		select = getIntInRange(0, 10);

		switch (select)
		{
		case 1: return "Beer";
		case 2: return "Coca-Cola Classic";
		case 3: return "Diet Coke";
		case 4: return "Milk, low-fat(1 %)";
		case 5: return "Milk, low-fat(2 %)";
		case 6: return "Milk, whole";
		case 7: return "Juice";
		case 8: return "Yogurt, low-fat";
		case 9: return "Yogurt, non-fat";
		}
	}
	
	// if a user cannot found the nameFood what he/she want, process it
	cout << "      Please type the food name: ";
	getline(cin, nameFood);

	return nameFood;
}

// Report section

bool printReport(int month, int year, string nameUser,double bmr, ostream &os)
{
	const int SIZE_OF_ARRAYS = 30;
	string dateAsStr, file;
	string dateFile[SIZE_OF_ARRAYS];
	double aNetTotalCalories[SIZE_OF_ARRAYS];
	int count = 0;
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	if (isLeap(year))
		daysInMonths[1] = 29;

	for (int date = 1; date <= daysInMonths[month - 1]; date++) {
		dateAsStr = intToStr(month) + "-" + intToStr(date) + "-" + intToStr(year);
		file = nameUser + "\\" + dateAsStr + ".txt";
		
		if (findExistedFile(file)) {
			dateFile[count] = dateAsStr;
			count++;
		}
	}
	
	if (count == 0)
	{
		os 
			<< "             !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
			<< "             !!  Do not have any record during " << setw(10) << monthOfYear(month) << setw(5) << year << "." << "  !!" << endl
			<< "             !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

		return false;
	}

	os
		<< "\t                ******************************* " << endl
		<< "\t                *        Monthly report       * " << endl
		<< "\t                ******************************* " << endl 
		<< "\t               The program found " << setw(2) << count << (count == 1 ? " day " : " days ") << "record." << endl
		<< "\t                       in" << setw(10) << monthOfYear(month) << setw(5) << year << endl << endl;
	
	for (int i = 0; i <= count; i++)
		aNetTotalCalories[i] = printWritedRecord(nameUser, dateFile[i], os);

	// Print statistic in the report
	printStatisticInReport(dateFile, aNetTotalCalories, count, bmr, os);

	return true;
}

bool printReport(int month, int date, int year, string nameUser,double bmr, ostream &os)
{
	const int SIZE_OF_ARRAYS = 30;
	string dateAsStr, file;
	string dateFile[SIZE_OF_ARRAYS];
	double aNetTotalCalories[SIZE_OF_ARRAYS];
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int count = 0,
		sDate = date;

	if (isLeap(year))
		daysInMonths[1] = 29;

	for (date ; date <= daysInMonths[month - 1] && date <= sDate + 7; date++) {
		dateAsStr = intToStr(month) + "-" + intToStr(date) + "-" + intToStr(year);
		file = nameUser + "\\" + dateAsStr + ".txt";

		if (findExistedFile(file)) {
			dateFile[count] = dateAsStr;
			count++;
		}
	}

	// if no any \\dateAsStr.txt exsited, print the message 
	if (count == 0)
	{
		os
			<< "        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
			<< "        !!  Do not have any record during" << setw(3) << sDate << getOrdinalFor(sDate) << " - " << setw(2) << (sDate + 7 > daysInMonths[month - 1] ? daysInMonths[month - 1] : sDate + 6) << getOrdinalFor((sDate + 7 > daysInMonths[month - 1] ? daysInMonths[month - 1] : sDate + 6)) << setw(10) << monthOfYear(month) << setw(5) << year << "  !!" << endl
			<< "        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

		return false;
	}
	
	os
		<< "\t                ******************************* " << endl
		<< "\t                *        Weekly report        * " << endl
		<< "\t                ******************************* " << endl
		<< "\t               The program found " << setw(2) << count << (count == 1 ? " day " : " days ") << "record." << endl
		<< "\t              between" << setw(3) << sDate << getOrdinalFor(sDate) << " - " << setw(2) << (sDate + 7 > daysInMonths[month - 1] ? daysInMonths[month - 1] : sDate + 6) << getOrdinalFor((sDate + 7 > daysInMonths[month - 1] ? daysInMonths[month - 1] : sDate + 6)) << setw(10) << monthOfYear(month) << setw(5) << year << endl;
	// Print printWritedRecord by begin with dateFile
	for (int i = 0; i <= count; i++)
		aNetTotalCalories[i] = printWritedRecord(nameUser, dateFile[i], os);

	// Print statistic in the report
	printStatisticInReport(dateFile, aNetTotalCalories, count, bmr, os);

	return true;
}

void printStatisticInReport(string dateFile[], double aNetTotalCalories[], int ls, double bmr, ostream &os)
{
	double average = getAverage(aNetTotalCalories, ls);

	// Print statistic 
	os
		<< endl << endl
		<< "\t*** You gained the LOWEST   calories on: " << dateFile[findIndexMin(aNetTotalCalories, ls)] << endl
		<< "\t*** You gained the HIGHTEST calories on: " << dateFile[findIndexMax(aNetTotalCalories, ls)] << endl
		<< "\t*** The average calories: " << average << endl << endl
		<< "\tHow many calories(average) need to maintain your weight is ";

	printCaloriesPossibleToMaintainWeight(average, bmr, os);
}

// Statistic section

double getAverage(double a[], int ls)
{
	double sum = a[0];
	
	for (int i = 1; i < ls; ++i) {
		sum += a[i];
	}	
	return sum / ls;
}

int findIndexMax(double a[], int ls)
{
	int max = 0;

	for (int i = 0; i < ls; i++){
		if (a[max] <= a[i])
			max = i;
	}
	return max;
}

int findIndexMin(double a[], int ls)
{
	int min = 0;

	for (int i = 0; i < ls; i++){
		if (a[min] >= a[i])
			min = i;
	}
	return min;
}

// Get numbers section

int getIntInRange(double startPoint, double endPoint)
{
	int number = getInteger();

	while (number < startPoint || number > endPoint)
	{
		cout << "\t" << "Your number must be ";
		if (number < startPoint)
			cout << "greater than or equal " << startPoint;
		else
			cout << "less than or equal " << endPoint;

		cout << ". Try again: ";
		number = getInteger();
	}
	return (int)number;
}

int getInteger()
{
	double number = getNum();

	while (number != (int)number)
	{
		cout << "\t" << number << " is NOT an integer. Try again: ";
		number = getNum();
	}
	return int(number);
}

double getNum()
{
	double number;

	while (!(cin >> number))
	{
		cout << "\tNo letters please. Try again: ";
		cin.clear();
		cin.ignore(80, '\n');
	}
	cin.ignore(80, '\n');
	return number;
}

int getIntPosNum()
{
	int number = getInteger();

	while (number <= 0)
	{
		cout << "\t" << number << " is NOT an positive. Try again: ";
		number = getInteger();
	}
	return number;
}

double getPosNum()
{
	double number = getNum();

	while (number <= 0)
	{
		cout << "\t" << number << " is NOT an positive. Try again: ";
		number = getNum();
	}
	return number;
}

char getYorN()
{
	char select;
	
	cin >> select;  cin.ignore(80, '\n');
	
	// while a input character is not looking for characters, it is still asks for a right one
	while (!(select == 'y' || select == 'n' || select == 'Y' || select == 'N'))
	{
		cout << "\tPlease type only Yes or No :";
		cin >> select;  cin.ignore(80, '\n');
	}
	return select;
}

// others section

bool findExistedFile(string fileName)
{
	ifstream nameFile;
	// Open the file.
	nameFile.open(fileName);
	// If the file successfully opened, process it.
	if (nameFile.fail())
		return false;
	else
		return true;
	
	nameFile.close();
}

string intToStr(int number)
{
	string numAsStr;
	stringstream out;
	
	out << number;
	
	return  out.str();
}

