#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class Student{
// here the data of the Student should be privated 
    private:
    string name;
    int rollNo;
    string branch;
// and here the functions which are used should be privated
public:
    void input(){
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter roll number: ";
        cin>>rollNo;
        cout<<"Enter branch"<<endl;
        cin>>branch;
    }
    void display() const{
        cout<<"Name: "<<name
            << ", Roll No: "<<rollNo
            << ", Branch: "<<branch<<endl;
    }
    // here the file as been created and the data read into the file
    void saveToFile(ofstream&outFile) const{
        outFile<<name<<" " <<rollNo<<" "<<branch <<endl;
        outFile.close();
    }
    // it is a helper function in this class 
    // It assigns values to the student's name, rollNo, and branch from the data read from a
    void loadFrom(string n,int r,string b){
        name = n;
        rollNo = r;
        branch = b;
    }
    void updateInfo(){
        cout<<"Enter new name: "<<endl;
        cin>>name;
        cout<<"Enter new branch: "<<endl;
        cin>>branch;
    }
    int getRollNo()const{
        return rollNo;
    }
    string getName()const{
        return name;
    }
};
    class StudentDB{
    private:
    vector<Student>students;
        public:
        
        void loadAllFrom(){
            ifstream inFile("student.txt");
            string name,branch;
            int rollNo;
            students.clear();
            while(inFile >> name >> rollNo >> branch){
                Student s;
                s.loadFrom(name,rollNo,branch);
                // here we are storing in vector
                students.push_back(s);
            }
         // the file must be closed after use 
         // if not the data may be corrupted   
            inFile.close();
        }
        void saveAllToFile(){
            ofstream outFile("student.txt");
            for(const Student&s : students){
                s.saveToFile(outFile);
            }
         // here also the outfile shuld be closed   
            outFile.close();
        }
        void addStudent(){
            Student s;
            s.input();
            students.push_back(s);
        // save entire list after adding
            saveAllToFile();
            cout<<"Student record added!"<<endl;
        }
        void viewAllStudents(){
           cout<<" All Student Records"<<endl;
           if(students.empty()){
            cout<<"No records found."<<endl;
            return;
           }
           for(const Student&s:students){
            s.display();
           }
        }
        void searchByRoll(){
            int roll;
            cout<<"Enter roll number to search: ";
            cin>>roll;

            bool found = false;
            for(const Student&s:students){
                if(s.getRollNo() == roll){
                    cout<<"Record found:"<<endl;
                    s.display();
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<" ❌ No record found with Roll No: "<<roll<<endl;
            }
        }
        void updateStudent(){
            int roll;
            cout<<"Enter roll number to update: ";
            cin>>roll;

            bool found;
            for(Student&s:students){
                if(s.getRollNo() == roll){
                    cout<<"Record found. Enter new details:"<<endl;
                    s.updateInfo();
                    saveAllToFile();
                    cout<<"✅ Record updated successfully"<<endl;
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"❌ No record found with Roll No: "<<roll<<endl;
            }
        }
// delete function
        void deleteStudent(){
            int roll;
            cout<<"Enter roll number to delete: ";
            cin>>roll;
            bool found = false;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getRollNo() == roll) {
                students.erase(it);
                saveAllToFile();
                cout << "✅ Student deleted successfully!\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "❌ No student found with Roll No: " << roll << "\n";
        }
        }
    void menu(){
        loadAllFrom();

        int choice;
        while(true){
            cout << "\n=== Student DBMS Menu ===\n";
            cout << "1. Add Student (Create)\n";
            cout << "2. View All Students (Read)\n";
            cout << "3. Search Student by Roll Number\n";
            cout << "4. Update Student\n";
            cout << "5. Delete Student\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addStudent(); break;
                case 2: viewAllStudents(); break;
                case 3: searchByRoll(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: cout << "👋 Exiting...\n"; return;
                default: cout << "⚠️ Invalid choice. Try again.\n";
            }
        }

    }
};
int main(){
   StudentDB db;
   db.menu();
   return 0;
}
