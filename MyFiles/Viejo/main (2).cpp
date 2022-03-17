// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
struct Date {int day; int month; int year;};

int ReadNon0IntegerFromKeyboard() {
// returns the number entered (<>0), or 0 if just enter is pressed
	string sTmp;
	int nTmp;
		do {
			getline( cin, sTmp);
			if ( ""==sTmp) return 0;
			try {
				nTmp = stoi(sTmp);
			}
			catch (...) { nTmp = 0; }

			if (0==nTmp) { cout << "Must be a non-zero integer; try again"; }
		} while (0==nTmp); // If input is wrong, repeat
	return nTmp;
}

void ReadDateFromKeyboard( Date date ) {
// Returns day=0 if no date has been entered
	bool bOk;
	bOk=false;

	do {
		cout << "Enter day (enter to end): ";
		date.day= ReadNon0IntegerFromKeyboard();
		if (0==date.day) return;
		if (date.day >= 1 && date.day <= 31) {
			cout << "Enter month (enter to end):";
			date.month=ReadNon0IntegerFromKeyboard();
			if (0==date.month) { date.day=0; return; }
			
			if (date.month >= 1 && date.month <= 12) {
				cout << "Enter year (enter to end):";
				date.year=ReadNon0IntegerFromKeyboard();
				if (0==date.year) { date.day=0; return; }
				if (date.year >1000 && date.year <2100) bOk=true;
			}
		}
		if (!bOk) cout << "Not a date, try again";
	} while (!bOk);
	return;
}

string ReadStringFromStreamNoEof(ifstream& input) {
// Function to avoid having to test eof after reading each line of input.txt
	string sTmp;
	getline(input, sTmp);
	if (input.eof()) {
		cout << "Error reading input file" << endl;
		exit(-1);
	}
	return sTmp;
}

class Director{
	private:
		string first_name;
		string last_name;
		string department;
		string officeNumber;
	public:
	 	Director(string f, string l,string d,string o){
			setFirst_name(f);
			setLast_name(l);
			setDepartment(d);
			setofficeNumber(o);
		}
		void setFirst_name(string f){
			first_name=f;
		}
		string getFirst_name(){
			return first_name;
		}
		void setLast_name(string l){
			last_name=l;
		}
		string getLast_name(){
			return last_name;
		}		
		void setDepartment(string d){
			department=d;
		}
		string getDepartment(){
			return department;
		}		
		void setofficeNumber(string o){
			officeNumber=o;
		}
		string getofficeNumber(){
			return officeNumber;
		}		
};

class Student{
	
	private:
		string NIA, first_name, last_name;
	public:
		Student(string f, string l, string n){
			setNIA(n);
			setFirst_name(f);
			setLast_name(l);
		}
		//default constructor
		Student(){
			NIA="";
			first_name="";
			last_name="";
		}
		void setNIA(string n){
			NIA=n;
		}
		string getNIA(){
			return NIA;
		}
		void setFirst_name(string f){
			first_name =f;
		}
		string getFirst_name(){
			return first_name;
		}	
		void setLast_name(string l){
			last_name =l;
		}		
		string getLast_name(){
			return last_name;
		}
};

class FDP{
	private:
		string title, description;
		Date oDate;
		vector<Director *> list_of_directors;
		Student oStudent;
	public:
		FDP(string t, string d, Date date,vector<Director*>directors, Student student){
			setTitle(t);
			description=d;
			setPresentationDate(date);
			assignDirectors(directors);
			assignStudent(student);
		}
		
		void setTitle(string t){title=t;}
		
		string getTitle (){return title;}
		
		void assignDirectors(vector<Director*> directors){
			list_of_directors.clear();
			for (unsigned int i=0;i<directors.size();i++){
				list_of_directors.push_back(directors[i]);
			}
		}
		
		void setPresentationDate(Date date){
			oDate.day=date.day;
			oDate.month=date.month;
			oDate.year=date.year;
		}
		
		void assignStudent(Student student){
			string check=oStudent.getFirst_name();
			if(check.empty()){
				oStudent.setLast_name(student.getLast_name());
				oStudent.setNIA(student.getNIA());
				oStudent.setFirst_name(student.getFirst_name());
			}
			else
				cout<<"Sorry, this FDP already has an assigned student"<<endl;
		}
		
		void showDirectors(){
			for (unsigned int i=0;i<list_of_directors.size();i++){
				cout<<"Printing the information of the director number "<<i<<endl;
				cout<<"First name: "<<list_of_directors[i]->getFirst_name()<<endl;
				cout<<"Last name: "<<list_of_directors[i]->getLast_name()<<endl;
				cout<<"Department: "<<list_of_directors[i]->getDepartment()<<endl;
				cout<<"Office number: "<<list_of_directors[i]->getofficeNumber()<<endl;
			}
		}
		
		void displayFDP(){
			cout<<getTitle()<<":"<<endl;
			cout<<"Presentation date: "<<oDate.day<<"/"<<oDate.month<<"/"<<oDate.year<<endl;
			cout<<"Description: "<<description<<endl;
			showDirectors();
			string check=oStudent.getFirst_name();
			if (check.empty()){
				cout<<"  There is no assigned student to this FDP"<<endl;
			}
			else{
				cout<<"  First name of the student: "<<oStudent.getFirst_name()<<endl;
				cout<<"  Last name of the student: "<<oStudent.getLast_name()<<endl;
				cout<<"  NIA of the student: "<<oStudent.getNIA()<<endl;
			}
		}
		
		Director* searchDirector( string first, string last ){
			// If the first last is a director of this FPD, returns it. If not, NULL
			// This function avoids having to repeat the loop in several places (I have removed 6 loops with it)
			Director *pDirector;
			for (unsigned int i = 0; i < list_of_directors.size(); i++) {
				pDirector = list_of_directors[i];
				if ( (! first.compare( pDirector->getFirst_name() ))
						&& (! last.compare(pDirector->getLast_name() )) ) {
					// Found
					return list_of_directors[i];
				}
			}
			return NULL;
		}

		Student* getpStudent(){
			return &oStudent;
		}
		void unassignStudent(){
			oStudent.setFirst_name("");
			oStudent.setLast_name("");
			oStudent.setNIA("");
		}
		void removeDirector (string firstName,string lastName){
			bool succes=false;
			for (unsigned int i=0;i<list_of_directors.size();i++){
				if (!(firstName.compare(list_of_directors[i]->getFirst_name())) and !(lastName.compare(list_of_directors[i]->getLast_name())))
					list_of_directors.erase(list_of_directors.begin()+i);
					succes=true;
			}
			if (succes)
				cout<<"DONE";
			else
				cout<<"Sorry that is not a director of this project";	
		}
};

class FDPCollection{
	
	private:
		vector<FDP *>vpFDPs;
		vector<Director *> vpDirectors;
			// If two FDPs share one Director, they must be a pointer to the same,
			// (or we wouldn't be able to edit the Director, except by changing every copy of it).
			// It seemed much better to create a vector with all the pointers to Director created with "new "
	
	public:	

		void addDirector(string first, string last, string department, string officeNumber) {
			vpDirectors.push_back(new Director(first, last, department, officeNumber));
		}

		Director *searchDirector(string first, string last) {
			// if first+last is in the vector of directors, return it. If not, NULL
			// This function avoids having to repeat the loop in several places (I have removed 6 loops with it)
			
			for (unsigned int i = 0; i < vpDirectors.size(); i++) {
				if (first.compare(vpDirectors[i]->getFirst_name()) == 0 
					and last.compare(vpDirectors[i]->getLast_name()) == 0) {
					
					return vpDirectors[i];
				}
			}
			return NULL;
		}

		void addProject(FDP *pFdp){
			for (unsigned int i=0;i<vpFDPs.size();i++){
				if ( ! vpFDPs[i]->getTitle().compare(pFdp->getTitle()) ) {
					cout<<"Sorry that's not a possible title, it is already used"<<endl;
					return;
				}
			}
			vpFDPs.push_back(pFdp); // Title is ok, add
		}
		
		//function to print all the information of all the projects
		void PrintAllFDP(){
			for(unsigned int i=0;i<vpFDPs.size();i++){
				cout<<"project number: "<<i<<endl;
				vpFDPs[i]->displayFDP();
			}
		}
		
		FDP* searchFDP (string title){
			for (unsigned int i=0;i<vpFDPs.size();i++){
				string thistitle=vpFDPs[i]->getTitle();
				if (!(thistitle.compare(title))){
					return vpFDPs[i];
				}
			}
			return NULL;
		}
		
		void deleteFDP(string title){
			for (unsigned int i=0;i<vpFDPs.size();i++){
				string thistitle=vpFDPs[i]->getTitle();
				if (!(thistitle.compare(title))){
					vpFDPs.erase(vpFDPs.begin()+i);
					return;
				}
			}
			cout<< "Sorry, not found"<<endl;
			return;
		}
		
		void deleteAll(){
			vpFDPs.clear();
		}
		
		Student* searchStudent (string firstName, string lastName){
			FDP* pFDP = searchFdpByStudent(firstName, lastName);
			if (NULL == pFDP)
				return NULL;
			else return pFDP->getpStudent();		
		}
		
		FDP* searchFdpByStudent(string firstName, string lastName) {
			// This function is needed to find a FDP given the student
			for (unsigned int i = 0; i < vpFDPs.size(); i++) {
				Student* ptracces = vpFDPs[i]->getpStudent();
				if (!(ptracces->getLast_name().compare(firstName)) and !(ptracces->getFirst_name().compare(lastName))) {
					return vpFDPs[i];
				}
			}
			return NULL;
		}

		void showProjectsByDirector(string firstName, string lastName) {
			int count;
			Director* pDirector;
			for (unsigned int iDir = 0; iDir < vpDirectors.size(); iDir++) {
				pDirector = vpDirectors[iDir];
				cout << "Director: " << pDirector->getFirst_name() << " " << pDirector->getLast_name() << endl;
				count = 0;
				for (unsigned int iProj = 0; iProj < vpFDPs.size(); iProj++) {
					if (NULL != vpFDPs[iProj]-> searchDirector(pDirector->getFirst_name(), pDirector->getLast_name() )) {
						cout << "   " << vpFDPs[iProj]->getTitle() << endl;
						count++; // the director in iDir is a director of this project, count it
					}
				}
				if ( 0==count ) 
					cout << "   No projects." << endl;
				else
					cout << "   Total " << count << " projects" << endl;
			}
		}

		void ShowFDPByDirector(){
			int count;
			for (unsigned int iDir=0;iDir< vpDirectors.size();iDir++){
				count = 0;
				for (unsigned int iProj = 0; iProj < vpFDPs.size(); iProj++) {
					if (NULL != vpFDPs[iProj]-> 
						searchDirector(vpDirectors[iDir]->getFirst_name(), vpDirectors[iDir]->getLast_name() )) {
						
						count++; // the director in iDir is a director of this project, count it
					}
				}
				cout << vpDirectors[iDir]->getFirst_name() << " " << vpDirectors[iDir]->getLast_name() << "\t" << count << "projects" << endl;
			}			
		}
		bool assignFDPtoStudent(FDP* fdp, Student student){
			if (!searchStudent(student.getFirst_name(), student.getLast_name())){
				fdp->assignStudent(student);
				return true;
			}
			else{
				cout<<"This student has already been assigned to another project"<<endl;
				return false;
			}
		}	
};

int ReadInputFile( string sFileName, FDPCollection &oFDPCollection) {
	ifstream input;
	string sTmp, title, description, stuNIA;
	string firstName, lastName, officeNumber, department;
	Date date;
	Student student;
	vector<Director*>list_of_directors;
	Director* pDirector;
	int count;

	input.open(sFileName);
	if (input.fail()) {	cout << "error opening input" << endl;	exit(-1);}
	//I first create a vector with all the directors from the file input.txt
		do {
			firstName = ReadStringFromStreamNoEof( input);
			if (0 == firstName.compare("ENDDIRS")) break;
			lastName = ReadStringFromStreamNoEof(input);
			department = ReadStringFromStreamNoEof(input);
			officeNumber = ReadStringFromStreamNoEof(input);
			oFDPCollection.addDirector(firstName, lastName, department, officeNumber);
		} while ( !input.eof() );

	//create the vector with all the projects
	count = 0;
	do {
		getline(input, title);
		if (input.eof()) break; //if this test goes at the end of the while loop, EOF has not been read yet
		description= ReadStringFromStreamNoEof(input);
		// Student. If first name empty, no lastname and no nia
			sTmp = ReadStringFromStreamNoEof(input); 
			if ( 0 != sTmp.compare("-") != 0) {
				student.setFirst_name(sTmp);
				sTmp = ReadStringFromStreamNoEof(input);
				student.setLast_name(sTmp);
				sTmp = ReadStringFromStreamNoEof(input);
				student.setNIA(sTmp);
			}
			else {
				student.setFirst_name("");
				student.setLast_name("");
				student.setNIA("");
			}
		// Read the date
			sTmp = ReadStringFromStreamNoEof(input); date.day = stoi(sTmp);
			sTmp = ReadStringFromStreamNoEof(input); date.month = stoi(sTmp);
			sTmp = ReadStringFromStreamNoEof(input); date.year = stoi(sTmp);
		
		// Read the 1st director's name, if none it is end of project
		firstName = ReadStringFromStreamNoEof(input);
		while (firstName.compare("ENDPROJ") != 0) {
			lastName = ReadStringFromStreamNoEof(input); date.day = stoi(sTmp);
			pDirector= oFDPCollection.searchDirector(firstName, lastName);
			if ( NULL == pDirector ) { // Error: must be earlier in the file
				cout << "Director of FDP was not in the list of directors" << lastName << endl;
				exit(-1);
			}
			list_of_directors.push_back(pDirector);

			firstName = ReadStringFromStreamNoEof(input); 
		}

		oFDPCollection.addProject(new FDP(title, description, date, list_of_directors, student));

	} while (true);
}

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
	cout << "Reading input.txt";
	if (-1 == ReadInputFile("c:\\tmp\\input.txt", oFDPCollection)) return -1;
		// you have to repeat the \ or it does not open the file
	
	bool bFin=false;
		
	do{
		//creating the menu for the user divided in 3 types of actions: actions with fdp, directors or students
		cout<<"\nChoose one of the next options (select the number written before the name):\n";
		cout<<"FDP actions:\n"<<"\t(11) Display the information of all the FDP's\n"<<"\t(12) Add new FDP\n"<<"\t(13) Display project data by title\n";
		cout<<"\t(14) Delete by title\n"<<"\t(15) Delete all the FDP's\n"<<"\t(16) Search FDP by student's first and last name\n";
		cout<<"Director actions:\n"<<"\t(21) List FDP's directed by the same professor\n"<<"\t(22) List all directors with the number of FDP's directed\n"<<"\t(23) Edit director data\n"<<"\t(24) Remove a director from a specified FDP\n";
		cout<<"Student actions:\n"<<"\t(31) Search FDP by student's first and last name\n"<<"\t(32) Assingn student to project\n"<<"\t(33) Unassign student from an FDP\n"<<"\t(34) Edit student data\n";
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
				cout<<"Introduce the description: "; getline(cin,description);

				ReadDateFromKeyboard( oDate );

				//read data of the student
				oStudent.setFirst_name("");
				oStudent.setLast_name("");
				oStudent.setNIA("");
				cout<<"Would you like to add a student to the project?(Y/N)\n";
				getline(cin,answer) ;
				if ("Y"==answer){
					cout<<"Introduce the firstname:\n";
					getline(cin,sTmp);
					oStudent.setFirst_name(sTmp);
					cout<<"Now the lastname: \n";
					getline(cin, sTmp);
					oStudent.setLast_name(sTmp);
					cout<<"Introduce the NIA of the student: ";
					getline(cin, sTmp);
					oStudent.setNIA(sTmp);
				}
				//create the vector of directors
				do{
					cout<<"Introduce the first name of the director: "; getline(cin,firstname); 
					cout<<"Now introduce the last name: "; getline(cin,lastname) ;
					cout<<"Next, introduce the director's department:"; getline(cin,department);
					cout<<"Last, introduce his office number: "; getline(cin,officenum);
										
					oFDPCollection.addDirector(firstname, lastname, department, officenum);
					
					cout<<"Do you want to add another director to this project? (Y/N)";
				    string answer; 
					getline(cin,answer);
				}
				while(answer=="Y");
				//create the project and add it
				oFDPCollection.addProject(new FDP(title, description, oDate, list_of_directors, oStudent));

			
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
				if (answer=="Y")
				oFDPCollection.deleteAll();	
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
				cout<<"Introduce the title of the project from which the director must be removed"; getline(cin,title);
				cout<<"Introduce the name of the director: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pFDP=oFDPCollection.searchFDP(title);
				pFDP->removeDirector(firstname, lastname);
			break;
			case 31:
				cout<<"Please introduce the first name of the student: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pFDP=oFDPCollection.searchFdpByStudent(firstname, lastname);
				if (NULL != pFDP)
					pFDP->displayFDP();
				else
					cout<<"Sorry student not found";	
			break;
			case 32:
				//set the student data that its supposed to be added
				cout<<"Please introduce the first name of the student: "; getline(cin,sTmp);
				oStudent.setFirst_name(sTmp);
				cout<<"Now introduce the last name: "; getline(cin,sTmp);
				oStudent.setLast_name(sTmp);
				cout<<"Last, introduce his NIA"; getline(cin, sTmp);
				oStudent.setNIA(sTmp);
				//get the pointer of the project in which the student is going to be added
				cout<<"Please introduce the titlte of the FDP: "; getline(cin,title);
				succes=oFDPCollection.assignFDPtoStudent( oFDPCollection.searchFDP(title), oStudent);
				if (succes)
					cout<<"Completed!";
				else
					cout<<"Sorry the student was already assigned to another project or the project title was wrong ";	
			break;
			case 33:
				cout<<"Introduce the title of the project from which the student must be unassigned"; getline(cin,title);
				pFDP=oFDPCollection.searchFDP(title);
				pFDP->unassignStudent();
			break;
			case 34:
				cout<<"Please introduce the first name of the student: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pStudent=oFDPCollection.searchStudent(firstname, lastname);
				cout<<"What would you like to edit?\n 1- First name\n 2-Last name\n 3-NIA\n";
				choice=ReadNon0IntegerFromKeyboard();
				switch (choice){
					case 1:
						cout<<"Please introduce the new first name of the Student: "; getline(cin,sTmp);
						pStudent->setFirst_name(sTmp);
					break;
					case 2:
						cout<<"Please introduce the new first name of the Student: "; getline(cin, sTmp);
						pStudent->setLast_name(sTmp);
					break; 
					case 3:
						cout<<"Please introduce the new first name of the Student: "; getline(cin, sTmp);
						pStudent->setNIA(sTmp);
					break;
				}
				cout << "Done!" << endl;
			break;		
			default: 
				cout<<"\nSorry, non existant option selected. Please select a correct number: ";
				getline(cin,selection);
				intselection= stoi(selection);
				bFin=true;
			break;	
		}
		cout<<"Press enter to choose another option, any other input to exit."<<endl;
		getline(cin,cont);
		if (cont=="" ){
			bFin=true;
		}
	}
	while (bFin==true);
	return 0;

}


