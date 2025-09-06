#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;


// Class to store team member information
class TeamMember {
private:
    string name;
    string studentId;
    string tutorialGroup;

public:
    TeamMember(const string& n, const string& id, const string& group)
        : name(n), studentId(id), tutorialGroup(group) {
    }

    void displayInfo() const {
        cout << left << setw(25) << name
            << setw(15) << studentId
            << setw(10) << tutorialGroup << endl;
    }
};

// Class to represent a Subject
class Subject {
public:
    string code;
    string sname;
    int credit;
    string grade;

    Subject(string c = "", string sn = "", int cr = 0, string gr = "")
        : code(c), sname(sn), credit(cr), grade(gr) {
    }
    int getcredit() const { return credit; }
    string getSname() const { return sname; }

};

// Class to represent a Student
class Student {
public:
    string name;
    string id;
    string major;
    int year;
    double gpa;
    vector <Subject> subjects;

    Student(string n = "", string i = "", string m = "", int y = 0, double g = 0.0)
        : name(n), id(i), major(m), year(y), gpa(g) {
    }

    string getID() const { return id; }
    string getName() const { return name; }
    string getMajor() const { return major; }
    int getYear() const { return year; }
    float getGPA() const { return gpa; }

    void addSubject(const Subject& subj) {
        subjects.push_back(subj);
    }
    void removeSubject(int o) {
        if (o >= 0 && o < subjects.size())
            subjects.erase(subjects.begin() + o);
    }

};
vector<Student> students;

// Function to display credits
void displayCredits(const vector<TeamMember>& team) {
    system("cls"); // Clear screen (Windows specific, use "clear" for Linux/Mac)
    cout << "=============================================\n";
    cout << "            GROUP MEMBERS CREDITS            \n";
    cout << "=============================================\n";
    cout << left << setw(25) << "NAME"
        << setw(15) << "STUDENT ID"
        << setw(10) << "GROUP" << endl;
    cout << "---------------------------------------------\n";

    for (const auto& member : team) {
        member.displayInfo();
    }

    cout << "=============================================\n";
}

// Function to get yes/no confirmation from user
bool getConfirmation(const string& prompt) {
    char firstChoice, confirmChoice;

    while (true) {
        cout << prompt << " (Y/N): ";
        cin >> firstChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        firstChoice = toupper(firstChoice);

        if (firstChoice != 'Y' && firstChoice != 'N') {
            cout << "Invalid input! Please enter 'Y' or 'N' (case insensitive).\n";
            continue; // Skip to next loop iteration if invalid
        }

        // Second confirmation input
        cout << "Enter again to confirm (Y/N): ";
        cin >> confirmChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        confirmChoice = toupper(confirmChoice);

        if (confirmChoice != 'Y' && confirmChoice != 'N') {
            cout << "Invalid input! Please enter 'Y' or 'N' (case insensitive).\n";
        }
        else if (firstChoice != confirmChoice) {
            cout << "Confirmation does not match! Please try again.\n";
        }
        else {
            return (firstChoice == 'Y'); // Returns 'Y', 'N'
        }
    }
}

// Function for the credits and exit option
void creditsAndExit(const vector<TeamMember>& team) {
    if (getConfirmation("Are you sure you want to exit and view credits?")) {
        displayCredits(team);
        cout << "Thank you for using our system. Goodbye!\n";
        exit(0);
    }
    else {
        cout << "Returning to main menu...\n";
        // In a real program, you would return to the main menu here
    }
}

//Function of calculate gpa
double calgpa(const vector<Subject>& subject) {
    double totalpoints = 0.0;
    int totalcredits = 0;

    //grade and gpa
    const string grades[] = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F" };
    const double points[] = { 4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1.3, 1.0, 0.0 };
    const int count = sizeof(points) / sizeof(points[0]);

    for (const auto& subject : subject) {
        if (subject.grade != "--") {
            for (int i = 0; i < count; ++i) {
                if (subject.grade == grades[i]) {
                    totalpoints += points[i] * subject.credit;
                    totalcredits += subject.credit;
                    break;
                }
            }
        }
    }

    if (totalcredits > 0) {
        return totalpoints / totalcredits;
    }
    else {
        return 0;
    }
}

//Function of load data
void loadstart(vector<Student>& students) {
    students.clear(); // it is for clear

    //those student data is given
    vector<Student> givenStudents = {
        Student("CHAN Tai Man", "S243560", "Information Engineering", 1, 0.0),
        Student("CHEUNG Jacky", "S232210", "Civil Engineering", 2, 0.0),
        Student("PAN Peter", "S222343", "Global Business", 3, 0.0),
        Student("WONG Kam", "S244617", "Educational Psychology", 1, 0.0)
    };

    givenStudents[0].subjects = {
        Subject("ENG2042", "Introduction to C++", 3, "A"),
        Subject("ENG2219", "Signal Processing", 3, "A"),
        Subject("LCH1302", "Professional English Writing", 2, "A"),
        Subject("LCH1019", "Japanese I", 2, "--")
    };

    givenStudents[1].subjects = {
        Subject("ENG1113", "Structural Fundamental", 3, "B"),
        Subject("ENG2250", "Engineering Mathematics", 3, "B+"),
        Subject("ENG2041", "Applied Computing", 3, "F"),
        Subject("LCH1302", "Professional English Writing", 2, "A-"),
        Subject("LCH1019", "Japanese I", 2, "B"),
        Subject("BUS1021", "Personal Financial Planning", 3, "--"),
        Subject("ENG2042", "Introduction to C++", 3, "--")
    };

    givenStudents[2].subjects = {
        Subject("BUS1021", "Personal Financial Planning", 3, "A"),
        Subject("BUS2002", "Introduction to Economics", 3, "A+"),
        Subject("BUS3006", "Understanding Globalization", 3, "B-"),
        Subject("BUS4510", "Business Project Management", 4, "A-"),
        Subject("BUS5523", "Final Year Project", 5, "B+"),
        Subject("LCH1019", "Japanese I", 2, "C")
    };

    givenStudents[3].subjects = {
        Subject("PSY1234", "Introduction to Psychology", 2, "C"),
        Subject("PSY2233", "Sociology", 3, "B"),
        Subject("PSY2190", "Human Behavior", 3, "B+")
    };

    //add them to vectr
    for (auto& student : givenStudents) {
        student.gpa = calgpa(student.subjects);
        students.push_back(student);
    }
    cout << "Starting data loaded successfully.\n";
}

// Function to display the Main Menu
void displayMainMenu() {
    cout << "\n********* SMS Main Menu *********\n";
    cout << "[1] Load Starting Data\n";
    cout << "[2] Show Student Records\n";
    cout << "[3] Add/Delete Students\n";
    cout << "[4] Edit Students\n";
    cout << "[5] Generate Transcript\n";
    cout << "[6] Credits and Exit\n";
    cout << "*********************************\n";
    cout << "\nOption (1 - 6): ";
}

//Function to display the student record
void showStudentRecords(vector<Student>& students) {
    int sortOption;
    cout << "Sort by:\n[1] Name (Ascending)\n[2] GPA (Descending)\nOption: ";
    cin >> sortOption;
    while (sortOption < 1 || sortOption > 2) {
        cout << "Invalid option. Enter 1 or 2: ";
        cin >> sortOption;
    }

    // Sorting
    if (sortOption == 1) {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.name < b.name;
            });
    }
    else {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;
            });
    }

    // Display the needed table
    cout << "\n" << string(80, '-') << "\n";
    cout << left << setw(25) << "Student Name" << setw(12) << "ID"
        << setw(30) << "Major" << setw(6) << "Year" << "GPA\n";
    cout << string(80, '-') << "\n";

    for (const auto& s : students) {
        bool hasGrades = any_of(s.subjects.begin(), s.subjects.end(),
            [](const Subject& sub) { return sub.grade != "--"; });

        string gpaStr = "N/A";
        if (hasGrades == 1) {
            double roundedGPA = round(s.gpa * 100) / 100;
            gpaStr = to_string(roundedGPA);

            size_t dotPos = gpaStr.find('.');
            if (dotPos != string::npos) {
                if (gpaStr.length() > dotPos + 3) {
                    gpaStr = gpaStr.substr(0, dotPos + 3);
                }
                else {
                    while (gpaStr.length() < dotPos + 3) {
                        gpaStr += '0';
                    }
                }
            }
            else {
                gpaStr += ".00";
            }
        }

        cout << left << setw(25) << s.name << setw(12) << s.id
            << setw(30) << s.major << setw(6) << s.year << gpaStr << "\n";
        cout << string(80, '-') << "\n";
    }
}

// Function to validate yes/no input
bool getYesNoConfirmation(string prompt) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        if (choice == 'Y' || choice == 'y') return true;
        if (choice == 'N' || choice == 'n') return false;
        cout << "Invalid input. Please enter 'Y' or 'N': ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

// Function to generate Student ID based on cohort and random number
string generateStudentID(int cohort, int randomNum) {
    int sum = cohort / 10 + cohort % 10 + randomNum / 100 + (randomNum / 10) % 10 + randomNum % 10;
    char checkDigit = (sum % 10) + '0';
    return "S" + to_string(cohort) + to_string(randomNum) + checkDigit;
}

// Function to add a new student
bool addStudent(vector<Student>& students) {
    string name, major;
    int cohort, attempts = 0;
    const int MAX_ATTEMPTS = 3;

    // Input validation with retries
    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter Student Name (Surname GivenName, max 30 chars): ";
        cin.ignore();
        getline(cin, name);
        if (name.length() > 30) {
            cout << "Error: Name exceeds 30 characters.\n";
            attempts++;
            if (attempts == MAX_ATTEMPTS) return false;
            continue;
        }
        cout << "Enter Cohort Year (e.g., 23 for 2023): ";
        if (!(cin >> cohort) || cohort < 0 || cohort > 24) {
            cout << "Error: Invalid cohort year (0-24).\n";
            cin.clear();
            cin.ignore(1000, '\n');
            attempts++;
            if (attempts == MAX_ATTEMPTS) return false;
            continue;
        }
        cin.ignore();
        cout << "Enter Major (max 30 chars): ";
        getline(cin, major);
        if (major.length() > 30) {
            cout << "Error: Major exceeds 30 characters.\n";
            attempts++;
            if (attempts == MAX_ATTEMPTS) return false;
            continue;
        }
        break;
    }

    if (attempts == MAX_ATTEMPTS) {
        cout << "Too many invalid inputs. No student added.\n";
        return false;
    }

    int randomNum = rand() % 900 + 100; // 100-999
    string id = generateStudentID(cohort, randomNum);
    int year = 2025 - (2000 + cohort) + 1;

    // Add student
    Student newStudent(name, id, major, year, 0.0); // GPA set to 0.0 initially
    students.push_back(newStudent);
    cout << "Student " << name << " (ID: " << id << ") added successfully.\n";
    return true;
}

// Function to delete a student
bool deleteStudent(vector<Student>& students) {
    string id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    auto it = find_if(students.begin(), students.end(),
        [&id](const Student& s) { return s.id == id; });
    if (it == students.end()) {
        cout << "Error: Student ID " << id << " not found.\n";
        return false;
    }

    // Display student info for confirmation
    cout << "\nStudent to delete:\n";
    cout << "Name: " << it->name << "\n";
    cout << "ID: " << it->id << "\n";
    cout << "Major: " << it->major << "\n";
    cout << "Year: " << it->year << "\n";
    cout << "GPA: " << fixed << setprecision(2) << it->gpa << "\n";

    if (getYesNoConfirmation("Confirm deletion? (Y/N): ")) {
        students.erase(it);
        cout << "Student " << id << " deleted successfully.\n";
    }
    else {
        cout << "Deletion cancelled.\n";
    }
    return true;
}

//check is the student ID exsited which typed by user
int* locat;
int Isexist(vector<Student>& students)
{
    string sid;
    cout << "Enter a student ID that you want to print: ";
    cin >> sid;
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == sid)
        {
            int temp = i;
            locat = &temp;
            return 1;
        }
    }
    return -1;
}

//show printed student info
void showinfo(vector<Student>& students, int locat)
{
    cout << "Name" << setw(8) << ": " << students[locat].name << endl;
    cout << "Student ID" << setw(2) << ": " << students[locat].id << endl;
    cout << "Major" << setw(7) << ": " << students[locat].major << endl;
    cout << "Year" << setw(8) << ": " << students[locat].year << endl;
    cout << "\nCourse records:" << endl;
    cout << left << setw(10) << "Code" << setw(30) << "Subject Name"
        << setw(8) << "Credits" << "Grade" << endl;
    cout << string(53, '-') << endl;
    //copy data to temp
    vector<Subject> tempsubjects = students[locat].subjects;
    //sorting
    sort(tempsubjects.begin(), tempsubjects.end(),
        [](const Subject& a, const Subject& b) { return a.code < b.code; });
    //print related student subject datas
    for (int i = 0; i < students[locat].subjects.size(); ++i)
    {
        cout << left << setw(10) << tempsubjects[i].code << setw(30) << tempsubjects[i].sname << right << setw(6) << tempsubjects[i].credit << "    " << left << tempsubjects[i].grade << endl;
    }
    cout << string(53, '-') << endl;

    int credit = 0;
    const string grades[] = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F" };
    const double gradePoints[] = { 4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1.3, 1.0, 0.0 };
    const int gradeCount = sizeof(gradePoints) / sizeof(gradePoints[0]);
    //calculate credit
    for (const auto& subject : tempsubjects)
    {
        for (int i = 0; i < gradeCount; ++i)
        {
            if (subject.grade == grades[i] && subject.grade[0] < 'F')
            {
                credit += subject.credit;
                break;
            }
        }
    }
    if (credit == 0)
    {
        cout << "Credits attained: " << credit << endl;
        cout << setprecision(2) << fixed << "GPA :" << "N/A" << endl;
    }

    else
    {
        cout << "Credits attained: " << credit << endl;
        cout << setprecision(2) << fixed << "GPA :" << students[locat].gpa << endl;
    }

}
// this is for checking surname, name is not cap get
bool Checksurname(const string& S, int s) {

    bool YES = false;
    for (int i = 0; i < s; i++) {
        if (isalpha(S[i])) {
            YES = true;
            if (!isupper(S[i])) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return YES;
}

bool CheckSubjectcode(const string& code) {
    if (code.length() != 7) return false;
    for (int i = 0; i < 3; i++) {
        if (!isupper(code[i])) return false;
    }
    for (int i = 3; i < 7; i++) {
        if (!isdigit(code[i])) return false;
    }
    return true;
}



//EDIT
void editStudent(vector<Student>& students) {

    string sid;
    cout << "Enter Student ID: ";
    cin >> sid;
    auto it = find_if(students.begin(), students.end(), [&sid](const Student& s) {
        return s.getID() == sid;
        });

    if (it == students.end()) {
        cout << "Student not found.\n";
        return;
    }

    int option;
    do {
        cout << "\nAction for Student ID:" << sid << endl;
        cout << "******** Edit Student Menu ********\n";
        cout << "[1] Edit Student Name\n[2] Edit Major\n[3] Edit Subject List\n[4] Return to Main Menu\n";
        cout << "***********************************\n";
        cout << "\nOption (1 - 4): ";

        cin >> option;
        //added the cin.fail() for check input is integer or not, previos version input string will inf loop
        if (cin.fail() || option < 1 || option > 4) {
            cout << "\nInvalid option. Please enter 1-4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (option) {
        case 1: {
            string oldname = it->name;
            string newname;
            cout << "\nCurrent name: " << oldname << "\nEnter new name: ";
            cin.ignore();
            getline(cin, newname);

            if (newname.length() > 30) {
                cout << "Error: Name exceeds 30 characters.\n";
                break;
            }

            size_t space = newname.find(' ');

            string surname = newname.substr(0, space);
            if (!Checksurname(surname, surname.length())) {
                cout << "Error: Surname must be in uppercase.\n";
                break;
            }
            //confirmation
            if (getYesNoConfirmation("Confirm change from '" + oldname + "' to '" + newname + "'? (Y/N): ")) {
                it->name = newname;
                cout << "Name updated from '" + oldname + "' to '" + newname << "'\n";
            }
            else {
                cout << "Change canceled.\n";
            }
            break;
        }
        case 2: {
            string oldmajor = it->major;
            string newmajor;

            cout << "\nCurrent major: " << oldmajor << "\nEnter new major (max 30 chars): ";
            cin.ignore();

            getline(cin, newmajor);
            if (newmajor.length() > 30) {
                cout << "Error: Major exceeds 30 characters.\n";
                break;
            }
            //confirmation
            if (getYesNoConfirmation("Confirm change from '" + oldmajor + "' to '" + newmajor + "'? (Y/N): ")) {
                it->major = newmajor;
                cout << "Major updated from '" + oldmajor + "' to '" + newmajor << "'\n";
            }
            else {
                cout << "Change canceled.\n";
            }
            break;
        }
        case 3: {
            string scode;
            int retries = 0;
            bool checkcode = false;
            while (retries < 3 && !checkcode) {
                cout << "\nEnter subject code: ";
                cin >> scode;
                if (CheckSubjectcode(scode)) {
                    checkcode = true;
                }
                else {
                    cout << "Invalid subject code.\n";
                    retries++;
                    if (retries < 3) cout << "Please try again.\n";
                }
            }
            if (!checkcode) {
                cout << "Too many invalid attempts.\n";
                break;
            }
            auto subjectIt = find_if(it->subjects.begin(), it->subjects.end(),
                [&scode](const Subject& s) {
                    return s.code == scode; });
            auto Checkgrade = [](const string& grade) {
                vector<string> Checkgrade = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F", "--" };
                return find(Checkgrade.begin(), Checkgrade.end(), grade) != Checkgrade.end();
                };
            if (subjectIt != it->subjects.end()) {
                string oldgrade = subjectIt->grade;
                cout << "\nCurrent grade for " << scode << ": " << oldgrade << "\n";
                string newgrade;
                retries = 0;
                bool validgrade = false;
                while (retries < 3 && !validgrade) {
                    if (oldgrade != "--") {
                        cout << "Enter new grade (cannot be '--'): ";
                    }
                    else {
                        cout << "Enter new grade (can be '--'): ";
                    }
                    cin >> newgrade;
                    if (Checkgrade(newgrade)) {
                        if (oldgrade != "--") {
                            if (newgrade != "--") {
                                validgrade = true;
                                break;
                            }
                        }
                        else {
                            validgrade = true;
                            break;
                        }
                    }

                    if (oldgrade != "--" && newgrade == "--") {
                        cout << "Invalid grade ('--' not allowed).\n";
                    }
                    else {
                        cout << "Invalid grade.\n";
                    }
                    retries++;
                    if (retries < 3) {
                        cout << "Please try again.\n";
                    }


                }
                if (validgrade) {
                    int whois = static_cast<int>(distance(it->subjects.begin(), subjectIt));
                    subjectIt->grade = newgrade;
                    it->gpa = calgpa(it->subjects);
                    int credit = subjectIt->getcredit();
                    string sname = subjectIt->getSname();
                    it->removeSubject(whois);
                    it->addSubject(Subject(scode, sname, credit, newgrade));
                    cout << "Grade for " << scode << " changed from '" << oldgrade << "' to '" << newgrade << "'\n";
                }
                else {
                    cout << "Too many invalid attempts.\n";
                }
            }
            else {
                bool founded = false;
                string sname;
                int credit = 0;
                for (const auto& student : students) {
                    auto nit = find_if(student.subjects.begin(), student.subjects.end(),
                        [&scode](const Subject& s) {
                            return s.code == scode;
                        });
                    if (nit != student.subjects.end()) {
                        founded = true;
                        sname = nit->sname;
                        credit = nit->credit;
                        cout << "\n" << sid << "\tdont have this subject \nSubject found in the system subject list\nSuject " << nit->sname << " will add to " << sid << " suject list " << "\n" << endl;
                        break;
                    }
                }
                if (founded) {
                    string grade;
                    retries = 0;
                    bool validgrade = false;
                    while (retries < 3 && !validgrade) {
                        cout << "Enter grade (can be '--'): ";
                        cin >> grade;
                        if (Checkgrade(grade)) {
                            validgrade = true;
                        }
                        else {
                            cout << "Invalid grade.\n";
                            retries++;
                            if (retries < 3) cout << "Please try again.\n";
                        }
                    }
                    if (validgrade) {

                        it->addSubject(Subject(scode, sname, credit, grade));
                        it->gpa = calgpa(it->subjects);
                        cout << "Subject " << scode << " added with grade '" << grade << "'\n";
                    }
                    else {
                        cout << "Too many invalid attempts.\n";
                    }

                }
                else {
                    string subjname;
                    int credit;
                    cout << "\nSubject not found in the system subject list. Adding new subject.\n";
                    cout << "Enter subject name (max 35 chars): ";
                    cin.ignore();
                    getline(cin, subjname);
                    if (subjname.length() > 35) {
                        cout << "Error: Sujectname exceeds 35 characters.\n";
                        break;
                    }
                    retries = 0;
                    bool validcredit = false;
                    while (retries < 3 && !validcredit) {
                        cout << "Enter credit (2-5): ";
                        cin >> credit;
                        if (cin.fail() || credit < 2 || credit > 5) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid credit. Must be between 2 and 5.\n";
                            retries++;
                            if (retries < 3) cout << "Please try again.\n";
                        }
                        else {
                            validcredit = true;
                        }
                    }

                    if (!validcredit) {
                        cout << "Too many invalid attempts.\n";
                        break;
                    }
                    string grade;
                    retries = 0;
                    bool validgrade = false;
                    while (retries < 3 && !validgrade) {
                        cout << "Enter grade (can be '--'): ";
                        cin >> grade;
                        if (Checkgrade(grade)) {
                            validgrade = true;
                        }
                        else {
                            cout << "Invalid grade.\n";
                            retries++;
                            if (retries < 3) cout << "Please try again.\n";
                        }
                    }
                    if (validgrade) {
                        it->addSubject(Subject(scode, subjname, credit, grade));
                        it->gpa = calgpa(it->subjects);
                        cout << "New subject " << scode << " added with grade '" << grade << "'\n";

                    }
                    else {
                        cout << "Too many invalid attempts.\n";
                    }

                }

            }

            break;
        }
        case 4:
            cout << "Returning to Main Menu.\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    } while (option != 4);
}
// Main function
int main() {
    srand(time(0)); // Seed for random number generation
    cout << "Welcome to Student Management System - Designed by Group 07\n"; // Custom welcome message
    bool dataLoaded = false;

    while (true) {
        displayMainMenu();
        int choice;
        if (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "Error: Invalid option. Please enter 1-6.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            if (dataLoaded && !getYesNoConfirmation("Data already loaded. Reload? (New data will be delete) (Y/N): ")) {
                cout << "Load cancelled.\n";
            }
            else {
                loadstart(students);
                dataLoaded = true;
            }
            break;
        case 2:
            if (!dataLoaded) {
                cout << "Error: Load data first (Option 1).\n";
            }
            else {
                showStudentRecords(students);
            }
            break;

        case 3:
            if (!dataLoaded) {
                cout << "Error: Please load starting data first (Option 1).\n";
            }
            else {
                string id;
                cout << "Enter Student ID to add/delete: ";
                cin >> id;
                auto it = find_if(students.begin(), students.end(),
                    [&id](const Student& s) { return s.id == id; });
                if (it == students.end()) {
                    cout << "Student ID " << id << " not found. Adding new student...\n";
                    addStudent(students);
                }
                else {
                    cout << "Student ID " << id << " found. Deleting student...\n";
                    deleteStudent(students);
                }
            }
            break;
        case 4:
            if (!dataLoaded) {
                cout << "Error: Please load starting data first (Option 1).\n";
            }
            else {
                editStudent(students);
            }
            break;
        case 5:
            if (!dataLoaded)
            {
                cout << "Error: Please load starting data first (Option 1).\n";
            }
            else
            {
                if (Isexist(students) != -1)
                {
                    int temp = *locat;
                    showinfo(students, temp);
                }
                else
                    cout << "Student ID do not exist, sending back to mainmenu." << endl;
            }
            break;
        case 6:
            vector<TeamMember> team = {
            TeamMember("Chow Chun San Anthony", "24032606A", "B03B"),
            TeamMember("Lin Rui Peng", "24168294A", "B03A"),
            TeamMember("Lu Chun Hei", "24191330A", "B03A"),
            TeamMember("Yip Chun Ting Justin", "24112526A", "B03A"),
            TeamMember("Lui Hoi To", "24047318A", "B03A"),
            TeamMember("Ng Cheuk Hin Hinson", "24155759A", "B03B"),
            };

            creditsAndExit(team);

            break;
        }
    }
    return 0;
}