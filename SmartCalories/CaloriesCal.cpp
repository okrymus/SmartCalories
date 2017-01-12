// The program calculateas BMR and record users eating activites
// Smart Calories
// Programmer: Panupong Leenawarat
// Last modified: Dec 12, 2015

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "Prototypes.h"
using namespace std;

int main()
{
	const int SIZE_OF_RECORD = 30;
	char YesOrNo, select;
	double bmr, netTotalCalories;
	double aCaloriesOfAUnit[SIZE_OF_RECORD];
	int option, date, month, year, logicalSizeArrayOfRecord;
	int aUnitOfFood[SIZE_OF_RECORD];
	string aNameFood[SIZE_OF_RECORD];
	string nameUser, file, dateAsStr, fileName;
	ofstream newFile;
	
	system("COLOR F0");
	
	//////////////////////////////////// INTRODUCTION OF THE PROGRAM ////////////////////////////////////
	titleOfProgram();

	// Input a user's name
	cout << "  Please enter your name: ";
	getline(cin, nameUser);
	
	file = nameUser + "//" + nameUser + ".txt";

	// Use the nameUser to find \\nameUser.txt which is existed or not, if it is not, process it
	if (!(findExistedFile(file)))
	{
		// The progran cannot find nameUser.txt, then asks to create a new account
		cout
			<< "\n\t       !! The program does not have your record !!" << endl << endl
			<< "\tPlease type \"YES\" to create an account" << endl
			<< "\t    or type \"NO\" to exist the program: ";
		YesOrNo = getYorN();
		
		// The user input "YES"  to create a new file or "NO" to exit the program
		if (YesOrNo == 'y' || YesOrNo == 'Y')
		{
			system("cls");
			
			cout
				<< endl
				<< "              Create your account" << endl
				<< "              ===================" << endl;
			
			getPersonalInformation(nameUser);
		}
		else
		{
			// Close the program
			cout << endl << "Closing the program" << endl << endl;
			
			system("pause");
			exit(0);
		}
	}
	/////////////////////////////////////////// MAIN MANU ///////////////////////////////////////////
	// while a use has done any part of the main menu option, restart to the following process again
	while (true)
	{
		system("COLOR 0C");
		system("cls");
		
		titleOfProgram();
		cout << "  ========= Your information =========";
		
		// Get bmr from a \\nameUser.txt
		bmr = printAccountInformation(nameUser);

		// Print the main manu to the monitor
		cout
			<< endl
			<< "\t              ***********************************  " << endl
			<< "\t              *    1] Edit your information     *  " << endl
			<< "\t              *    2] Record or view Activity   *  " << endl
			<< "\t              *    3] View report               *  " << endl
			<< "\t              *    4] Create another account    *  " << endl
			<< "\t              *    5] Exit the program          *  " << endl
			<< "\t              ***********************************  " << endl << endl
		    << "\t                 Please choose the options: ";
		
		option = getIntInRange(1, 5);
		
		while (option > 0)
		{ 
			switch (option)
			{
			case 1:
				system("cls");
				
				titleOfProgram();
				// 1. Edit a user's information
				cout
					<< endl
					<< "\t                     Edit your information   " << endl;
				
				editPersonalInformation(nameUser);
				
				option = 0;
				break;
			case 2:
				system("cls");

				titleOfProgram();

				// 2. Record or View a user's activities
				cout
					<< "\t               ++++++++++++++++++++++++++++++++ " << endl
					<< "\t               +   Record or View Activities  + " << endl
					<< "\t               ++++++++++++++++++++++++++++++++ " << endl << endl;
					
				cout<< "  Please enter the date which you want to record or view " << endl << endl;
				getDate(date, month, year);
				
				dateAsStr = intToStr(month) + "-" + intToStr(date) + "-" + intToStr(year);
				file = nameUser + "\\" + dateAsStr + ".txt";

				// Find the file "file" is existed or not. If not, process it
				if (!(findExistedFile(file)))
				{
					system("cls");
					
					titleOfProgram();

					printWriteRecordTitle(month, date, year);
					foodCategoriesMenu();
					
					// Load a user's activities on the date
					logicalSizeArrayOfRecord = loadArrayOfActivity(aNameFood, aUnitOfFood, aCaloriesOfAUnit, SIZE_OF_RECORD);
					
					// Print a user's activities on the date
					if (logicalSizeArrayOfRecord != 0)
					{						
						system("cls");
						
						titleOfProgram();

						printViewRecordTitle(month, date, year);
						netTotalCalories = printArray(aNameFood, aUnitOfFood, aCaloriesOfAUnit, logicalSizeArrayOfRecord);
						printCaloriesPossibleToMaintainWeight(netTotalCalories, bmr);

						// Write the record to \\dateAsStr.txt
						newFile.open(file);
						
						newFile << "Net calories gained is " << netTotalCalories << " on the date" << endl << endl;
						
						printViewRecordTitle(month, date, year, newFile);
						netTotalCalories = printArray(aNameFood, aUnitOfFood, aCaloriesOfAUnit, logicalSizeArrayOfRecord, newFile);
						printCaloriesPossibleToMaintainWeight(netTotalCalories, bmr, newFile);
						
						newFile.close();
					}
				}
				else
				{
					system("cls");
					
					titleOfProgram();
					
					// Print options to monitor when tha input date file is existed
					cout
						<< "\n                       !!!You already have the record!!! " << endl 
						<< "                    ***************************************" << endl
						<< "                    *   1] Replace the record             *" << endl
						<< "                    *   2] View the record on the date    *" << endl
						<< "                    *   3] Back to menu                   *" << endl
						<< "                    ***************************************" << endl << endl
						<< "                         Please choose the options: ";
					
					option = getIntInRange(1, 3);

					// If the option is 1, a user can replace a record on the input date
					if (option == 1)
					{
						system("cls");

						titleOfProgram();

						// Get a user's activities on the input date
						printWriteRecordTitle(month, date, year);
						logicalSizeArrayOfRecord = loadArrayOfActivity(aNameFood, aUnitOfFood, aCaloriesOfAUnit, SIZE_OF_RECORD);

						if (logicalSizeArrayOfRecord != 0)
						{
							system("cls");

							titleOfProgram();

							printViewRecordTitle(month, date, year);
							netTotalCalories = printArray(aNameFood, aUnitOfFood, aCaloriesOfAUnit, logicalSizeArrayOfRecord);
							printCaloriesPossibleToMaintainWeight(netTotalCalories, bmr);

							// Write the record to dateAsStr.txt
							newFile.open(file);
							
							// Write the first line in the input date file with net calories gained
							newFile << "Net calories gained is " << netTotalCalories << " on the date" << endl << endl;
							
							printViewRecordTitle(month, date, year, newFile);
							netTotalCalories = printArray(aNameFood, aUnitOfFood, aCaloriesOfAUnit, logicalSizeArrayOfRecord, newFile);
							printCaloriesPossibleToMaintainWeight(netTotalCalories, bmr, newFile);
							
							newFile.close();
						}
					}
					else if (option == 2)
					{
						system("cls");

						titleOfProgram();
						
						// Print a user's activity record on the dateAsStr
						netTotalCalories = printWritedRecord(nameUser, dateAsStr);
					}
				}
				
				cout << "\n\t Hit ENTER to back to the main manu: ";
				cin.ignore();

				option = 0;
				break;
			case 3:
				system("cls");

				titleOfProgram();
				
				// 3. Report options which allow a user to view report via following options
				cout
					<< endl
					<< "\t                         Report options " << endl
					<< "\t                         ============== " << endl << endl;

				cout
					<< "\t                 *****************************" << endl
					<< "\t                 *     1] Daily Report       *" << endl
					<< "\t                 *     2] Monthly Report     *" << endl
					<< "\t                 *     3] Weekly Report      *" << endl
					<< "\t                 *     4] Back to menu       *" << endl 
					<< "\t                 *****************************" << endl << endl
					<< "\t                  Please choose the options: ";
				
				option = getIntInRange(1, 4);

				if (option == 1)
				{
					
					// 3.1 Daily report (open dateAsStr.txt to print on the monitor and allows to write the record to a file
					cout << endl << "  Please enter the date which you want to get a report" << endl << endl;
					getDate(date, month, year);
					
					dateAsStr = intToStr(month) + "-" + intToStr(date) + "-" + intToStr(year);
					file = nameUser + "\\" + dateAsStr + ".txt";
					
					system("cls");

					titleOfProgram();

					// The program is able to access dateAsStr.txt
					if (findExistedFile(file))
					{
						cout
							<< "\t                ******************************** " << endl
							<< "\t                *         Daily report         * " << endl
							<< "\t                ******************************** " << endl;
						
						printWritedRecord(nameUser, dateAsStr);

						// Ask to save the record 
						cout 
							<< endl
							<< "       __________________________________________________________________" << endl << endl
							<< "         Do you want to save the report? ";
						
						YesOrNo = getYorN();

						// If a user want to save the record, process it
						if (YesOrNo == 'y' || YesOrNo == 'Y')
						{
							cout << "         What file do you want to output the report? ";
							getline(cin, fileName);
							
							file = nameUser + "\\" + fileName;
							
							newFile.open(file);

							// Cheak the fileName is able to use create a file or not. While invalid name, process it
							while (!newFile)
							{
								cout
									<< "\tThe program failed to use the name file: \"" << fileName << "\". " << endl
									<< "\tPlease enter another name: ";
								
								getline(cin, fileName);
								file = nameUser + "\\" + fileName;
								
								// Open a file
								newFile.open(file);
							}

							// Write to fileName
							titleOfProgram(newFile);
							newFile 
								<< "\t                ******************************** " << endl
								<< "\t                *         Daily report         * " << endl
								<< "\t                ******************************** " << endl;

							printWritedRecord(nameUser, dateAsStr, newFile);

							newFile.close();
						}
					}
					else
						// If the input dateAsStr.txt is not existed, process it to show message
						cout
							<< "         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
							<< "         !!  Do not have any record on " << setw(9) << dayOfWeek(date, month, year) << setw(3) << date << getOrdinalFor(date) << setw(10) << monthOfYear(month) << setw(5) << year << "  !!" << endl
							<< "         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;


					cout << "\n         Hit ENTER to back to the main manu: ";
					cin.ignore();
					
					option = 0;
				}
				else if (option == 2)
				{
					// 3.2 Monthly report (open \\dateAsStr.txt in the input month of a year to print on the monitor and allows to write the record to a file
					cout << endl << "  Please enter the month and the year which you want to get a report" << endl << endl;
					
					cout << "  Month(mm): ";
					month = getIntInRange(1, 12);
					
					cout << "  Year(yyyy): ";
					year = getIntInRange(2000, 2100);
					
					system("cls");

					titleOfProgram();

					// If the program can open files in month of a year, process it
					if (printReport(month, year, nameUser, bmr))
					{
						cout
							<< endl
							<< "       __________________________________________________________________" << endl << endl
							<< "         Do you want to save the report? ";
						
						YesOrNo = getYorN();

						// If a user want to save the record, ask a fileName 
						if (YesOrNo == 'y' || YesOrNo == 'Y')
						{
							cout << "         What file do you want to output the report? ";
							getline(cin, fileName);
							file = nameUser + "\\" + fileName;
							newFile.open(file);

							// Cheak the fileName is able to use create a file or not. While invalid name, process it
							while (!newFile)
							{
								cout
									<< "\tThe program failed to use the name file: \"" << fileName << "\". " << endl
									<< "\tPlease enter another name: ";
								getline(cin, fileName);
								file = nameUser + "\\" + fileName;
								// Open a file
								newFile.open(file);
							}

							// Write to fileName
							titleOfProgram(newFile);
							printReport(month, year, nameUser,bmr, newFile);

							newFile.close();
						}
					}

					cout << "\n         Hit ENTER to back to the main manu: ";
					cin.ignore();
					
					option = 0;
				}
				else if (option == 3)
				{
					// 3.3 Weekly report (open \\dateAsStr.txt  of a week to print on the monitor and allows to write the record to a file
					cout << endl << "  Please enter the first date of a week which you want to get a report" << endl << endl;
					getDate(date, month, year);
					
					system("cls");

					titleOfProgram();

					// If the program can open files in \\dateAsStr.txt of a week, process it
					if (printReport(month, date, year, nameUser, bmr))
					{
						cout
							<< endl
							<< "       __________________________________________________________________" << endl << endl
							<< "         Do you want to save the report? ";
						
						YesOrNo = getYorN();
						
						// If a user want to save the record, ask a fileName 
						if (YesOrNo == 'y' || YesOrNo == 'Y')
						{
							cout << "         What file do you want to output the report? ";
							getline(cin, fileName);
							
							file = nameUser + "\\" + fileName;
							
							newFile.open(file);
							
							// Cheak the fileName is able to use create a file or not. While invalid name, process it
							while (!newFile)     
							{
								cout
									<< "\tThe program failed to use the name file: \"" << fileName << "\". " << endl
									<< "\tPlease enter another name: ";
								getline(cin, fileName);
								
								file = nameUser + "\\" + fileName;
								
								newFile.open(file);
							}
							
							// Write to fileName
							titleOfProgram(newFile);
							printReport(month, date, year, nameUser, bmr, newFile);

							newFile.close();
						}
					}

					cout << "\n         Hit ENTER to back to the main manu: ";
					cin.ignore();
				}

				option = 0;
				break;
			case 4:
				system("cls");
			
				titleOfProgram();
			
				// 4. Create another account
				cout
					<< "\t                     Create another account  " << endl
					<< "\t                     ====================== " << endl << endl;
				
				cout << "  Please enter your name: ";
				getline(cin, nameUser);
				
				file = nameUser + "//" + nameUser + ".txt";

				// While nameUse has already existed, the program asks for another name  
				while (findExistedFile(file))
				{
					cout << "\t  The name is existed. Please try another name: ";
					getline(cin, nameUser);
					
					file = nameUser + "//" + nameUser + ".txt";
				}
				
				getPersonalInformation(nameUser);
				
				option = 0;
				break;
			case 5:
				// 5. Exit the program. print warnning or allows a user to choose another option in the main manu
				cout
					<< endl
					<< "               ************************************************ " << endl
					<< "               *  Please hit ENTER to exit or select another  * " << endl
					<< "               ************************************************ " << endl << endl
					<< "                         Please choose the options: ";
				
				cin.get(select);

				// If a user hit enter, exit the program
				if (select == '\n')
					exit(0);

				cin.putback(select);
				option = getIntInRange(1, 5);
			}
		}
	}
}