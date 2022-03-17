class Student {

private:
	string NIA, first_name, last_name;
public:
	Student(string f, string l, string n) {
		setNIA(n);
		setFirst_name(f);
		setLast_name(l);
	}
	//default constructor
	Student() {
		NIA = "";
		first_name = "";
		last_name = "";
	}
	void setNIA(string n) {
		NIA = n;
	}
	string getNIA() {
		return NIA;
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
};