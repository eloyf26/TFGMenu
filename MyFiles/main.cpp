//	Eloy Fernández.	Programming Course, 2019-2020 U. Prof. Harith 
// 	Carlos III Leganés
//	File of the "FDP project"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
struct Date {int day; int month; int year;};

#include "Student.cpp"
#include "Director.cpp"
#include "FDP.cpp"
#include "FDPcollection.cpp"
#include "functions.cpp"

int main( /* int argc, char** argv */ ){
	// Where FDP objects and director objects are stored
		FDPCollection oFDPCollection;

	string selection; 
	int intselection;
	string cont;
	bool succes;
	string officenum, newOfficenum;
	int choice;
	string title, description, firstname, lastname, NIA, department, thisfirstname, thislastname, newfirstname, newlastname, newdepartment, newNIA;
	Date oDate;
	FDP* pFDP;
	Student oStudent, *pStudent;
	vector<Director*>list_of_directors;
	Director* pDirector;
	string answer, sTmp;
	
	oDate.day = 1;
	oDate.month = 1;
	oDate.year = 2020;

	//read the data from the file input.txt
	cout << "Reading input.txt\n";
	if (-1 == ReadInputFile("input.txt", oFDPCollection)) return -1;
		// if the file has directory, the \ must be \\ or it does not open the file
	
	bool bFin;
		
	do{
		bFin = false;
		//creating the menu for the user divided in 3 types of actions: actions with fdp, directors or students
		
		cout<<"FDP actions:\n"<<"\t(11) Display the information of all the FDP's\n"<<"\t(12) Add new FDP\n"<<"\t(13) Display project data by title\n";
		cout<<"\t(14) Delete by title\n"<<"\t(15) Delete all the FDP's\n"<<"\t(16) Search FDP by student's first and last name\n";
		cout<<"Director actions:\n"<<"\t(21) List FDP's directed by the same professor\n"<<"\t(22) List all directors with the number of FDP's directed\n"<<"\t(23) Edit director data\n"<<"\t(24) Remove a director from a specified FDP\n";
		cout<<"Student actions:\n"<<"\t(31) Search FDP by student's first and last name\n"<<"\t(32) Assingn student to project\n"<<"\t(33) Unassign student from an FDP\n"<<"\t(34) Edit student data\n";
		cout << "\nChoose one of the next options (select the number written before the name) or press enter to end:\n";
		//check if the selection is valid with the while and the boolean variable
		getline(cin, selection);
		try {
			intselection = stoi(selection);
		}
		catch (...) { return 0; }

		switch (intselection){
			//FDP options
			case 11:
				oFDPCollection.PrintAllFDP();
			break;
			case 12:
				//introduce the information of the new project that is going to be added to the collection
				cout<<"Introduce the title: "; getline(cin,title);
				
				if (!title.empty()) {
					cout << "Introduce the description: "; getline(cin, description);
					ReadDateFromKeyboard(oDate);

					//read data of the student
					oStudent.setFirst_name("");
					oStudent.setLast_name("");
					oStudent.setNIA("");
					cout << "Would you like to add a student to the project?(Y/N)\n";
					getline(cin, answer);
					if ("Y" == answer || "y" == answer) {
						cout << "Introduce the firstname:\n";
						getline(cin, sTmp);
						oStudent.setFirst_name(sTmp);
						cout << "Now the lastname: \n";
						getline(cin, sTmp);
						oStudent.setLast_name(sTmp);
						cout << "Introduce the NIA of the student: ";
						getline(cin, sTmp);
						oStudent.setNIA(sTmp);
					}
					//create the vector of directors
					do {
						cout << "Introduce the first name of the director: "; getline(cin, firstname);
						cout << "Now introduce the last name: "; getline(cin, lastname);
						pDirector = oFDPCollection.searchDirector(firstname, lastname);
						if (!pDirector) {
							cout << "Next, introduce the director's department:"; getline(cin, department);
							cout << "Last, introduce his office number: "; getline(cin, officenum);
							oFDPCollection.addDirector(firstname, lastname, department, officenum);
							pDirector = oFDPCollection.getPVallDirectorslast();
							list_of_directors.push_back(pDirector);
						}
						else
						{
							list_of_directors.push_back(pDirector);
						}



						cout << "Do you want to add another director to this project? (Y/N)";
						getline(cin, answer);
					} while (answer == "Y");
					//create the project and add it
					oFDPCollection.addProject(new FDP(title, description, oDate, list_of_directors, oStudent));
					list_of_directors.clear();
				}
				else{
					cout << "Invalid title";
				}
			break;
			case 13:
				cout<<"Introduce the title of the project you are looking for: "; getline(cin,title);
				pFDP=oFDPCollection.searchFDP(title);
				pFDP->displayFDP();
			break;
			case 14:
				cout<<"Introduce the title of the project you are looking for: "; getline(cin,title);
				oFDPCollection.deleteFDP(title);
			break;
			case 15:
				cout<<"Do you want to delete all the saved projects? (Y/N)";
				getline(cin,answer);
				if (answer=="Y" || answer=="y"){
					oFDPCollection.deleteAll();	
					cout << "Done!" << endl;
				}
				
			break;
			//Director options
			case 21:
				cout<<"Please introduce the firstname of the director: "; getline(cin,firstname);
				cout<<"Now introduce the lastname: "; getline(cin,lastname);
				oFDPCollection.showProjectsByDirector(firstname,lastname);
			break;
			case 22:
				oFDPCollection.ShowFDPByDirector();
			break;
			case 23:
				cout<<"Please introduce the first name of the director: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pDirector = oFDPCollection.searchDirector(firstname, lastname);
				if (NULL == pDirector) {
					cout << "Does not exist." << endl;
					break;
				}
				cout<<"What would you like to edit?\n 1- First name\n 2-Last name\n 3-Department\n 4-Office number\n0 o Enter-Cancel\n";
				choice=ReadNon0IntegerFromKeyboard();
				switch (choice){
					case 1:
						cout << "Please introduce the new first name of the director: ";
						getline(cin, sTmp);
						pDirector->setFirst_name(sTmp);
						break;
					case 2:
						cout << "Please introduce the new last name of the director: ";
						getline(cin, sTmp);
						pDirector->setLast_name(sTmp);
						break;
					case 3:
						cout << "Please introduce the new department of the director: ";
						getline(cin, sTmp);
						pDirector->setDepartment(sTmp);
						break;
					case 4:
						cout << "Please introduce the new office number of the director: ";
						getline(cin, sTmp);
						pDirector->setofficeNumber(sTmp);
						break;
				}
				cout << "Done!";

			break;
			case 24:
				cout<<"Introduce the title of the project from which the director must be removed:\n"; getline(cin,title);
				cout<<"Introduce the name of the director: \n"; getline(cin,firstname);
				cout<<"Now introduce the last name: \n"; getline(cin,lastname);
				pFDP=oFDPCollection.searchFDP(title);
				pFDP->removeDirector(firstname, lastname);
			break;
			case 31:
			case 16:
				cout<<"Please introduce the first name of the student: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pFDP=oFDPCollection.searchFdpByStudent(firstname, lastname);
				if (NULL != pFDP)
					pFDP->displayFDP();
				else
					cout<<"Sorry student not found\n";	
			break;
			case 32:
				//set the student data that its supposed to be added
				cout<<"Please introduce the first name of the student: \n"; getline(cin,sTmp);
				oStudent.setFirst_name(sTmp);
				cout<<"Now introduce the last name: \n"; getline(cin,sTmp);
				oStudent.setLast_name(sTmp);
				cout<<"Last, introduce his NIA: \n"; getline(cin, sTmp);
				oStudent.setNIA(sTmp);
				//get the pointer of the project in which the student is going to be added
				cout<<"Please introduce the titlte of the FDP: \n"; getline(cin,title);
				succes=oFDPCollection.assignFDPtoStudent( oFDPCollection.searchFDP(title), oStudent);
				if (succes)
					cout<<"Completed!\n";
				else
					cout<<"Sorry the student was already assigned to another project or the project title was wrong \n";	
			break;
			case 33:
				cout<<"Introduce the title of the project from which the student must be unassigned: \n"; getline(cin,title);
				pFDP=oFDPCollection.searchFDP(title);
				pFDP->unassignStudent();
			break;
			case 34:
				cout<<"Please introduce the first name of the student: \n"; getline(cin,firstname);
				cout<<"Now introduce the last name: \n"; getline(cin,lastname);
				pStudent=oFDPCollection.searchStudent(firstname, lastname);
				do {
					cout << "What would you like to edit?\n 1- First name\n 2-Last name\n 3-NIA\n";
					choice = ReadNon0IntegerFromKeyboard();
					switch (choice) {
					case 1:
						cout << "Please introduce the new first name of the Student: \n"; getline(cin, sTmp);
						pStudent->setFirst_name(sTmp);
						break;
					case 2:
						cout << "Please introduce the new last name of the Student: \n"; getline(cin, sTmp);
						pStudent->setLast_name(sTmp);
						break;
					case 3:
						cout << "Please introduce the new NIA of the Student: \n"; getline(cin, sTmp);
						pStudent->setNIA(sTmp);
						break;
					}
					cout << "Done!" << endl;
					cout << "Press enter to keep editing and anything else to exit.\n";
					getline(cin, sTmp);
				}
				
				while (sTmp == "");

			break;		
			default: 
				cout<<"\nSorry, non existant option selected, please select a correct number.\n";
				bFin=true;
			break;	
		}
		if (bFin == false) {
			cout << "\nPress enter to choose another option of the main menu, any other input to exit." << endl;
			getline(cin, cont);
			if (cont == "") {
				bFin = true;
			}
		}
		
	}
	while (bFin==true);
	return 0;

}
