class Director {
private:
	string first_name;
	string last_name;
	string department;
	string officeNumber;
public:
	Director(string f, string l, string d, string o) {
		setFirst_name(f);
		setLast_name(l);
		setDepartment(d);
		setofficeNumber(o);
	}
	void setFirst_name(string f) {
		first_name = f;
	}
	string getFirst_name() {
		return first_name;
	}
	void setLast_name(string l) {
		last_name = l;
	}
	string getLast_name() {
		return last_name;
	}
	void setDepartment(string d) {
		department = d;
	}
	string getDepartment() {
		return department;
	}
	void setofficeNumber(string o) {
		officeNumber = o;
	}
	string getofficeNumber() {
		return officeNumber;
	}
};