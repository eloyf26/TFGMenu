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
			nTmp=stoi(sTmp);
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





class Director{
	private:
		string first_name;
		string last_name;
		string department;
		string office_number;
	public:
	 	Director(string f, string l,string d,string o){
			setFirst_name(f);
			setLast_name(l);
			setDepartment(d);
			setOffice_number(o);
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
		void setOffice_number(string o){
			office_number=o;
		}
		string getOffice_number(){
			return office_number;
		}		
};
class Student{
	
	private:
		string NIA, first_name, last_name;
	public:
		Student(string n, string f, string l){
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
			NIA=f;
		}
		string getFirst_name(){
			return first_name;
		}	
		void setLast_name(string l){
			NIA=l;
		}		
		string getLast_name(){
			return last_name;
		}
};
class FDP{
	private:
		string title, description;
		Date oDate;
		vector<Director*>list_of_directors;
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
				cout<<"Office number: "<<list_of_directors[i]->getOffice_number()<<endl;
			}
		}
		void displayFDP(){
			cout<<getTitle()<<":"<<endl;
			cout<<"Presentation date: "<<oDate.day<<"/"<<oDate.month<<"/"<<oDate.year<<endl;
			cout<<"Description: "<<description<<endl;
			showDirectors();
			string check=oStudent.getFirst_name();
			if (check.empty()){
				cout<<"There is no assigned students to this FDP"<<endl;
			}
			else{
				cout<<"First name of the student: "<<oStudent.getFirst_name()<<endl;
				cout<<"Last name of the student: "<<oStudent.getLast_name()<<endl;
				cout<<"NIA of the student: "<<oStudent.getNIA()<<endl;
			}
		}
		//a way to acces the vector of directors, since it's private
		Director* getVectDirect(){
			return list_of_directors[0];
		}
		//easy way to now the number of directors
		unsigned int getSizeDirectors(){
			return list_of_directors.size();
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
		vector<FDP>vFDP;
	public:
		void addProject(FDP fdp){
			int add=0;
			if(vFDP.empty()){
				vFDP.push_back(fdp);	
			}
			else{
				for (unsigned int i;i<vFDP.size();i++){
					string thistitle=vFDP[i].getTitle();
					if (!(thistitle.compare(fdp.getTitle()))){
						cout<<"Sorry that's not a possible title, it is already used"<<endl;
						add=1;
					}
				}
			}
			if (!add)
				vFDP.push_back(fdp);	
		}
		//function to print all the information of all the proyects
		void PrintAllFDP(){
			for(unsigned int i=0;i<vFDP.size();i++){
				cout<<"project number: "<<i<<endl;
				vFDP[i].displayFDP();
			}
		}
		FDP* searchFDP (string title){
			for (unsigned int i;i<vFDP.size();i++){
				string thistitle=vFDP[i].getTitle();
				if (!(thistitle.compare(title))){
					return &vFDP[i];
				}
			}
			return NULL;
		}
		void deleteFDP(string title){
			for (unsigned int i;i<vFDP.size();i++){
				string thistitle=vFDP[i].getTitle();
				if (!(thistitle.compare(title))){
					vFDP.erase(vFDP.begin()+i);
					return;
				}
			}
			cout<< "Sorry, not found"<<endl;
			return;
		}
		void deleteAll(){
			vFDP.clear();
		}
		Student* searchStudent (string firstName, string lastName){
			for (unsigned int i;i<vFDP.size();i++){
				Student* ptracces=vFDP[i].getpStudent();
				string thislastname=ptracces->getLast_name();
				string thisfirstname=ptracces->getFirst_name();
				if (!(thisfirstname.compare(firstName)) and !(thislastname.compare(lastName))){
					return ptracces;
				}
			}
			return NULL;
		}
		void showProjectsByDirector(string firstName, string lastName){
//			check every project through a pointer			
			for (unsigned int i=0;i<vFDP.size();i++){									
				Director* ptrdirectors=vFDP[i].getVectDirect();
				int sizedirectors=vFDP[i].getSizeDirectors();
//				check every director through another pointer
				for (int k=0;k<sizedirectors;k++){
					string thisfirstname=ptrdirectors->getFirst_name();
					string thislastname=ptrdirectors->getLast_name();
//					print the information
					if(!(thisfirstname.compare(firstName)) and !(thislastname.compare(lastName))){
						cout<<"Director found: "<<endl; 
						cout<<"Title of the project: "<<vFDP[i].getTitle()<<endl;
//						print the info of every director of the project
						for (int x=0;x<sizedirectors;x++){
							cout<<"The name of the "<<(x+1)<<" director is: "<<endl;
							cout<<ptrdirectors->getFirst_name()<<" ";
							cout<<ptrdirectors->getLast_name()<<endl;
							cout<<"And he belongs to the department number "<<ptrdirectors->getDepartment()<<endl;
						}
						
					}
					ptrdirectors=ptrdirectors+1;
				}
		    }
		}	
		void ShowFDPByDirector(){
////			create a vector with all the directors
			vector<Director*>AllDirectorsVect;
			int repeat=0;
//		add an object so the vector is not empty 			
			AllDirectorsVect.push_back(vFDP[0].getVectDirect());
//		adding the rest of the directors
//			choosing the vector of directors of each FDP			
			for (unsigned int i=0;i<vFDP.size();i++){
				Director* ptrdirector=vFDP[i].getVectDirect();
//  			choosing each director of the vector to compare it with the vector with all the directors				
				for (unsigned int j=0;j<vFDP[i].getSizeDirectors();j++){
//				Comparing it to the rest of directors on the vector so it doesnt repeat	 
					for(unsigned int k=0;k<AllDirectorsVect.size();k++){
						if (ptrdirector==AllDirectorsVect[k]){
							repeat=1;
						}
					}
					//adding it to the vector with all the directors
					if (repeat==0)
						AllDirectorsVect.push_back(ptrdirector);
					ptrdirector=ptrdirector+1;	
					repeat=0;
				}
			}
//			the vector with all the directors has already been created 
			int count=0;
			for (unsigned int iDir=0;iDir<AllDirectorsVect.size();iDir++){
				
				for (unsigned int iProy=0; iProy<vFDP.size();iProy++){
					Director* ptrdirector=vFDP[iProy].getVectDirect();
// 		 			choosing each director of the vector to compare it with the vector with all the directors				
					for (unsigned int j=0;j<vFDP[iProy].getSizeDirectors();j++){
						if(ptrdirector==AllDirectorsVect[iDir])
							count=count+1;
						ptrdirector=ptrdirector+1;
					}
				}
				cout<<AllDirectorsVect[iDir]->getFirst_name()<<" "<<AllDirectorsVect[iDir]->getLast_name()<<"\t"<<count<<"projects"<<endl;
				count=0;
			}			
		}
		bool assignFDPtoStudent(FDP* fdp, Student* student){
			if (!searchStudent(student->getFirst_name(), student->getLast_name())){
				fdp->assignStudent(*student);
				return true;
			}
			else{
				cout<<"This student has already been assigned to another project"<<endl;
				return false;
			}
		}	
};
int main( /* int argc, char** argv */ ){
	FDPCollection oFDPCollection;
	vector<Director>vAllDirectors;
	int intselection;
	string selection;
	string sTmp;
	string title, description,stufirstname,stulastname,stuNIA,dirfirstname,dirlastname;
	Date date;
	Student* pStudent;
	vector<Director*>list_of_directors;
	int count=0;
	
	//read the data from the file input.txt
	cout<<"hello";
	ifstream input;
	input.open("input.txt");
	if (input.fail()){
		cout<<"error opening input"<<endl;
		return -1;	
	}
	//I first create a vector with all the directors from the file input.txt
	string end;
	do{
		
		string firstname,lastname,department;
		string office_number;
		getline(input,firstname);
		end=firstname;
		if (firstname.compare("ENDDIRS") !=0){
			getline(input,lastname);
			getline(input,department);
			getline(input,office_number);
			Director* pDirector=new Director(firstname,lastname,department,office_number);
			vAllDirectors.push_back( *pDirector);
		}
	}
	while(end.compare("ENDDIRS")!=0);
	//create the vector with all the project 
	do{
		count=0;
		getline(input,title);
		if (input.eof())
			break; //if I test at the end of the while loop, EOF has not been read yet
		getline(input,description);		
		getline(input,stufirstname);
		if (stufirstname.compare("-")!=0){
			getline(input,stulastname);
			getline(input,stuNIA);
			pStudent=new Student(stufirstname,stulastname,stuNIA);
		}
		else if (stufirstname.compare("-")==0){
			pStudent=new Student();
		}
		// Read the date
			getline(input,sTmp); date.day=stoi(sTmp);
			getline(input,sTmp); date.month=stoi(sTmp);
			getline(input,sTmp); date.year=stoi(sTmp);
		// Read the 1st director's name, or endproy if none
		getline(input,dirfirstname);
		while(dirfirstname.compare("ENDPROY")!=0){
			if (count==0){
				getline(input,dirlastname);
				for(unsigned int i=0;i<vAllDirectors.size();i++){
					if (dirfirstname.compare(vAllDirectors[i].getFirst_name())==0 and dirlastname.compare(vAllDirectors[i].getLast_name())==0){
						list_of_directors.push_back(&vAllDirectors[i]);
						count=1;
					}
				}
			}
			else{
				getline(input,dirfirstname);
				if(dirfirstname.compare("ENDPROY")!=0){
					getline(input,dirlastname);
					for(unsigned int i=0;i<vAllDirectors.size();i++){
						if (dirfirstname.compare(vAllDirectors[i].getFirst_name())==0 and dirlastname.compare(vAllDirectors[i].getLast_name())==0){
							list_of_directors.push_back(&vAllDirectors[i]);
						}
					}
				}
			}	
		}
		
		FDP* oFDP= new FDP(title,description,date,list_of_directors,*pStudent);
		oFDPCollection.addProject(*oFDP);
	}
	while(true);


	bool bFin=false;
	do{
		//creating the menu for the user divided in 3 types of actions: actions with fdp, directors or students
		cout<<"\nChoose one of the next options (select the number written before the name):\n";
		cout<<"FDP actions:\n"<<"\t(11) Display the information of all the FDP's\n"<<"\t(12) Add new FDP\n"<<"\t(13) Display project data by title\n";
		cout<<"\t(14) Delete by title\n"<<"\t(15) Delete all the FDP's\n"<<"\t(16) Search FDP by student's first and last name\n";
		cout<<"Director actions:\n"<<"\t(21) List FDP's directed by the same professor\n"<<"\t(22) List all directors with the number of FDP's directed\n"<<"\t(23) Edit director data\n"<<"\t(24) Remove a director from a specified FDP\n";
		cout<<"Student actions:\n"<<"\t(31) Search FDP by student's first and last name\n"<<"\t(32) Assingn student to project\n"<<"\t(33) Unassign student from an FDP\n"<<"\t(34) Edit student data\n";
		//check if the selection is valid with the while and the boolean variable
		string cont;
		getline(cin,selection);
				intselection= stoi(selection);
		bool succes;
		string officenum,newOfficenum;
		int choice;
		string title,description,firstname,lastname,NIA,department,thisfirstname,thislastname,newfirstname,newlastname,newdepartment,newNIA; 
		Date oDate;
		FDP* p2FDP;
		
		vector<Director*>list_of_directors;
		string answer;
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

				//create the object student
				cout<<"Would you like to add a student to the project?(Y/N)\n";
				getline(cin,answer) ;
					if ("Y"==answer){
						cout<<"Introduce the firstname:\n"; getline(cin,firstname); cout<<"Now the lastname: \n"; getline(cin,lastname);
						cout<<"Introduce the NIA of the student: "; getline(cin,NIA);
											}
					//empty student case
					else if(answer=="N"){
						lastname="";
						firstname="";	
						NIA="";
					}
				pStudent= new Student(firstname,lastname,NIA);
				//create the vector of directors
				do{
					cout<<"Introduce the first name of the director: ";getline(cin,firstname); 
					cout<<"Now introduce the last name: "; getline(cin,lastname) ;
					cout<<"Next, introduce the director's department:"; getline(cin,department);
					cout<<"Last, introduce his office number: "; getline(cin,officenum);
										
					Director* pDirector= new Director(firstname,lastname,department,officenum);
					list_of_directors.push_back(pDirector);
					vAllDirectors.push_back(*pDirector);
					cout<<"Do you want to add another director to this project? (Y/N)";
				    string answer; 
					getline(cin,answer);
				}
				while(answer=="Y");
				//create the project and add it
				p2FDP = new FDP(title,description,oDate,list_of_directors,*pStudent);
				oFDPCollection.addProject(*p2FDP);
			
			break;
			case 13:
				cout<<"Introduce the title of the project you are looking for: "; getline(cin,title);
				p2FDP=oFDPCollection.searchFDP(title);
				p2FDP->displayFDP();
			break;
			case 14:
				cout<<"Introduce the title of the project you are looking for: "; getline(cin,title);
				oFDPCollection.deleteFDP(title);
			break;
			case 15:
				cout<<"Do you want to delete all the saved proyects? (Y/N)";
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
				
				cout<<"What would you like to edit?\n 1- First name\n 2-Last name\n 3-Department\n 4-Office number\n0 o Enter-Cancel\n";
				choice=ReadNon0IntegerFromKeyboard();
				
				switch (choice){
					case 0:
					break;
						
					case 1:
						for (unsigned int i=0;i<vAllDirectors.size();i++){
							thisfirstname=vAllDirectors[i].getFirst_name();
							thislastname=vAllDirectors[i].getLast_name();
							if (firstname.compare(thisfirstname) and lastname.compare(thislastname)){
								cout<<"Please introduce the new first name of the director: "; getline(cin,newfirstname);		
							}	
						}
						cout<<"Done!";
					break;
					case 2:
						for (unsigned int i=0;i<vAllDirectors.size();i++){
							thisfirstname=vAllDirectors[i].getFirst_name();
							thislastname=vAllDirectors[i].getLast_name();
							if (firstname.compare(thisfirstname) and lastname.compare(thislastname)){
								cout<<"Please introduce the new last name of the director: "; getline(cin,newlastname);		
							}	
						}
						cout<<"Done!";
					break;
					case 3:
						for (unsigned int i=0;i<vAllDirectors.size();i++){
							thisfirstname=vAllDirectors[i].getFirst_name();
							thislastname=vAllDirectors[i].getLast_name();
							if (firstname.compare(thisfirstname) and lastname.compare(thislastname)){
								cout<<"Please introduce the new department of the director: "; getline(cin,newdepartment);		
							}	
						}
						cout<<"Done!";
					break;
					case 4:
						for (unsigned int i=0;i<vAllDirectors.size();i++){
							thisfirstname=vAllDirectors[i].getFirst_name();
							thislastname=vAllDirectors[i].getLast_name();
							if (firstname.compare(thisfirstname) and lastname.compare(thislastname)){
								cout<<"Please introduce the new office number of the director: "; getline(cin,newOfficenum);		
							}	
						}
						cout<<"Done!";
					break;
				}
			break;
			case 24:
				cout<<"Introduce the title of the project from which the director must be removed"; getline(cin,title);
				cout<<"Introduce the name of the director: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				p2FDP=oFDPCollection.searchFDP(title);
				p2FDP->removeDirector(firstname, lastname);
			break;
			case 31:
				cout<<"Please introduce the first name of the student: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pStudent=oFDPCollection.searchStudent(firstname, lastname);
				if (pStudent){
					cout<<pStudent->getNIA();
					cout<<" "<<firstname<<" "<<lastname;
				}
				else
					cout<<"Sorry student not found";	
			break;
			case 32:
				//create the student that its supposed to be added
				cout<<"Please introduce the first name of the student: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				cout<<"Last, introduce his NIA"; getline(cin,NIA);
				pStudent= new Student(firstname, lastname, NIA);
				//get the pointer of the project in which the student is going to be added
				cout<<"Please introduce the titlte of the FDP: "; getline(cin,title);
				succes=oFDPCollection.assignFDPtoStudent(oFDPCollection.searchFDP(title), pStudent);
				if (succes)
					cout<<"Completed!";
				else
					cout<<"Sorry the student was already assigned to another project or the project title was wrong ";	
			break;
			case 33:
				cout<<"Introduce the title of the project from which the student must be unassigned"; getline(cin,title);
				p2FDP=oFDPCollection.searchFDP(title);
				p2FDP->unassignStudent();
			break;
			case 34:
				cout<<"Please introduce the first name of the student: "; getline(cin,firstname);
				cout<<"Now introduce the last name: "; getline(cin,lastname);
				pStudent=oFDPCollection.searchStudent(firstname, lastname);
				cout<<"What would you like to edit?\n 1- First name\n 2-Last name\n 3-NIA";
				choice=ReadNon0IntegerFromKeyboard();
				switch (choice){
					case 1:
						cout<<"Please introduce the new first name of the Student: "; getline(cin,newfirstname);
						pStudent->setFirst_name(newfirstname);
						cout<<"Done!"<<endl;
					break;
					case 2:
						cout<<"Please introduce the new first name of the Student: "; getline(cin,newlastname);
						pStudent->setLast_name(newlastname);
						cout<<"Done!"<<endl;
					break; 
					case 3:
						cout<<"Please introduce the new first name of the Student: "; getline(cin,newNIA);
						pStudent->setNIA(newNIA);
						cout<<"Done!"<<endl;
					break;
				}
			break;		
			default: 
				cout<<"\nSorry, non existant option selected. Please select a correct number: ";
				getline(cin,selection);
				intselection= stoi(selection);
				bFin=true;
			break;	
		}
		cout<<"Press Y to choose another option."<<endl;
		getline(cin,cont);
		if (cont=="Y" or cont=="y"){
			bFin=true;
		}
	}
	while (bFin==true);
	return 0;

}


