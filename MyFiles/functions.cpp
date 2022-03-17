//	Eloy Fernández.	Programming Course, 2019-2020 U. Prof. Harith 
// 	Carlos III Leganés
//	File of the "FDP project"

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

void ReadDateFromKeyboard( Date &date ) {
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

int ReadInputFile( string sFileName, FDPCollection &oFDPCollection) {
	ifstream input;
	string sTmp, title, description, stuNIA;
	string firstName, lastName, officeNumber, department;
	Date date;
	Student student;
	
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
		vector<Director*>list_of_directors; //declaration must be here to be empty on the beginning of each project
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
			lastName = ReadStringFromStreamNoEof(input); 
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
	return(0);
}
