//	Eloy Fernández.	Programming Course, 2019-2020 U. Prof. Harith 
// 	Carlos III Leganés
//	File of the "FDP project"

class FDPCollection{
	
	private:
		vector<FDP *>vpFDPs;
		vector<Director *> vpDirectors;
			// If two FDPs share one Director, they must be a pointer to the same,
			// (or we wouldn't be able to edit the Director, except by changing every copy of it).
			// It seemed much better to create a vector with all the pointers to Director created with "new "			
	public:	
		//only way to acces the vector with all the directors

		~FDPCollection() {
			//release the directors
			while (0 != vpDirectors.size()) {
				delete vpDirectors[0];
				vpDirectors.erase(vpDirectors.begin());
			}
			while (0 != vpFDPs.size()) {
				delete vpFDPs[0];
				vpFDPs.erase(vpFDPs.begin());
			}
		}

		Director* getPVallDirectorslast(){
			return vpDirectors.back();
		}
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
				cout<<"project number: "<<i+1<<endl;
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
					cout << "Done!"<<endl;
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
				if (!(ptracces->getLast_name().compare(lastName)) and !(ptracces->getFirst_name().compare(firstName))) {
					return vpFDPs[i];
				}
			}
			return NULL;
		}

		void showProjectsByDirector(string firstName, string lastName) {
			int count;
			cout << "Director: " << firstName << " " << lastName << endl;
			count = 0;
			for (unsigned int iProj = 0; iProj < vpFDPs.size(); iProj++) {
				if (NULL != vpFDPs[iProj]-> searchDirector(firstName, lastName)) {
					vpFDPs[iProj]->displayminiFDP();

					count++; // the director in iDir is a director of this project, count it
				}
			}
			if ( 0==count ) 
				cout << "   No projects." << endl;
			else
				cout << "   Total projects directed by "<< firstName <<" "<<lastName<<": " << count << "" << endl;
		}

		void ShowFDPByDirector(){
			int count;
			for (unsigned int iDir=0;iDir< vpDirectors.size();iDir++){
				count = 0;
				for (unsigned int iProj = 0; iProj < vpFDPs.size(); iProj++) {
					if (NULL != vpFDPs[iProj]->searchDirector(vpDirectors[iDir]->getFirst_name(), vpDirectors[iDir]->getLast_name() )) {
						count++; // the director in iDir is a director of this project, count it
					}
				}
				cout << vpDirectors[iDir]->getFirst_name() << " " << vpDirectors[iDir]->getLast_name() << ":\t" << count << " projects" << endl;
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
