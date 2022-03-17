class FDP {
private:
	string title, description;
	Date oDate;
	vector<Director*> list_of_directors;
	Student oStudent;
public:
	FDP(string t, string d, Date date, vector<Director*>directors, Student student) {
		setTitle(t);
		description = d;
		setPresentationDate(date);
		assignDirectors(directors);
		assignStudent(student);
	}

	void setTitle(string t) { title = t; }

	string getTitle() { return title; }

	void assignDirectors(vector<Director*> directors) {
		list_of_directors.clear();
		for (unsigned int i = 0; i < directors.size(); i++) {
			list_of_directors.push_back(directors[i]);
		}
	}

	void setPresentationDate(Date date) {
		oDate.day = date.day;
		oDate.month = date.month;
		oDate.year = date.year;
	}

	void assignStudent(Student student) {
		string check = oStudent.getFirst_name();
		if (check.empty()) {
			oStudent.setLast_name(student.getLast_name());
			oStudent.setNIA(student.getNIA());
			oStudent.setFirst_name(student.getFirst_name());
		}
		else
			cout << "Sorry, this FDP already has an assigned student" << endl;
	}

	void showDirectors() {
		for (unsigned int i = 0; i < list_of_directors.size(); i++) {
			cout << "\tPrinting the information of the director number " << i + 1 << endl;
			cout << "\t\tFirst name: " << list_of_directors[i]->getFirst_name() << endl;
			cout << "\t\tLast name: " << list_of_directors[i]->getLast_name() << endl;
			cout << "\t\tDepartment: " << list_of_directors[i]->getDepartment() << endl;
			cout << "\t\tOffice number: " << list_of_directors[i]->getofficeNumber() << endl;
		}
	}
	//function used to print just the fullname and department
	void showDirectorsmini() {
		for (unsigned int i = 0; i < list_of_directors.size(); i++) {
			cout << "\tPrinting the information of the director number " << i + 1 << endl;
			cout << "\t\tFirst name: " << list_of_directors[i]->getFirst_name() << endl;
			cout << "\t\tLast name: " << list_of_directors[i]->getLast_name() << endl;
			cout << "\t\tDepartment: " << list_of_directors[i]->getDepartment() << endl;
		}
	}

	void displayFDP() {
		cout << getTitle() << ":" << endl;
		cout << "\tPresentation date: " << oDate.day << "/" << oDate.month << "/" << oDate.year << endl;
		cout << "\tDescription: " << description << endl;
		showDirectors();
		string check = oStudent.getFirst_name();
		if (check.empty()) {
			cout << "\tThere is no assigned student to this FDP" << endl;
		}
		else {
			cout << "\n\tStudent:\n";
			cout << "\t\tFirst name of the student: " << oStudent.getFirst_name() << endl;
			cout << "\t\tLast name of the student: " << oStudent.getLast_name() << endl;
			cout << "\t\tNIA of the student: " << oStudent.getNIA() << endl;
		}
	}
	//function used to display only the title and directors of a project
	void displayminiFDP() {
		cout << getTitle() << ":" << endl;
		showDirectorsmini();
	}
	Director* searchDirector(string first, string last) {
		// If the first last is a director of this FPD, returns it. If not, NULL
		// This function avoids having to repeat the loop in several places (I have removed 6 loops with it)
		Director* pDirector;
		for (unsigned int i = 0; i < list_of_directors.size(); i++) {
			pDirector = list_of_directors[i];
			if ((!first.compare(pDirector->getFirst_name()))
				&& (!last.compare(pDirector->getLast_name()))) {
				// Found
				return list_of_directors[i];
			}
		}
		return NULL;
	}

	Student* getpStudent() {
		return &oStudent;
	}
	void unassignStudent() {
		oStudent.setFirst_name("");
		oStudent.setLast_name("");
		oStudent.setNIA("");
	}
	void removeDirector(string firstName, string lastName) {
		bool succes = false;
		for (unsigned int i = 0; i < list_of_directors.size(); i++) {
			if (!(firstName.compare(list_of_directors[i]->getFirst_name())) and !(lastName.compare(list_of_directors[i]->getLast_name())))
				list_of_directors.erase(list_of_directors.begin() + i);
			succes = true;
		}
		if (succes)
			cout << "DONE";
		else
			cout << "Sorry that is not a director of this project";
	}

};
