#include <bits/stdc++.h>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;

string generatePassword()
{
    srand(time(NULL));
    int upper = 122;
    int lower = 97;
    char s[8];
    for (int i = 0; i < 8; i++)
    {
        s[i] = (rand() % (upper - lower + 1)) + lower;
    }
    return (s);
}

class admin
{
public:
    void menu();
    void add_student();
    void delete_student();
    void add_faculty();
    void delete_faculty();
    void assign_course();
    void unassign_course();
    void add_course();
    void delete_course();
    void change_password();
    void show_students();
    void show_faculty();
    void show_courses();
    void show_batch();
};

void admin::menu()
{
    cout << "\t\t\t--------------------------------" << endl;
    cout << "\t\t\t1.) SHOW ALL STUDENTS" << endl;
    cout << "\t\t\t2.) SHOW ALL FACULTIES" << endl;
    cout << "\t\t\t3.) SHOW ALL COURSES" << endl;
    cout << "\t\t\t4.) ADD STUDENT RECORD" << endl;
    cout << "\t\t\t5.) DELETE STUDENT RECORD" << endl;
    cout << "\t\t\t6.) ADD FACULTY RECORD" << endl;
    cout << "\t\t\t7.) DELETE FACULTY RECORD" << endl;
    cout << "\t\t\t8.) SHOW STUDENTS OF A COURSE" << endl;
    cout << "\t\t\t9.) ASSIGN STUDENT TO A COURSE" << endl;
    cout << "\t\t\t10.) REMOVE STUDENT FROM A COURSE" << endl;
    cout << "\t\t\t11.) ADD COURSE" << endl;
    cout << "\t\t\t12.) DELETE COURSE" << endl;
    cout << "\t\t\t13.) CHANGE PASSWORD" << endl;
    cout << "\t\t\t14.) LOGOUT" << endl;
    cout << "\t\t\tPlease Enter your Choice (1-14):" << endl;
    cout << "\t\t\t--------------------------------" << endl;
    int choice;
    cin >> choice;
    system("clear");
    switch (choice)
    {
    case 1:
        show_students();
        break;
    case 2:
        show_faculty();
        break;
    case 3:
        show_courses();
        break;
    case 4:
        add_student();
        break;
    case 5:
        delete_student();
        break;
    case 6:
        add_faculty();
        break;
    case 7:
        delete_faculty();
        break;
    case 8:
        show_batch();
        break;
    case 9:
        assign_course();
        break;
    case 10:
        unassign_course();
        break;
    case 11:
        add_course();
        break;
    case 12:
        delete_course();
        break;
    case 13:
        change_password();
        break;
    case 14:
        cout << "Bye\n";
        exit(0);
    }
}
void admin::show_students()
{
    res = stmt->executeQuery("Select * from students");
    cout << "\t\t\tAll Students of Institute" << endl;
    cout << "\t\t\t--------------------------------" << endl;
    while (res->next())
    {
        cout << "\t\t\tStudent ID : " << res->getString("studentId") << endl;
        cout << "\t\t\tStudent Name: " << res->getString("name") << endl;
        cout << "\t\t\t--------------------------------" << endl;
    }
    cout << endl;
    menu();
}
void admin::show_faculty()
{
    res = stmt->executeQuery("Select * from faculty");
    cout << "\t\t\tAll Faculties of Institute" << endl;
    cout << "\t\t\t--------------------------------" << endl;
    while (res->next())
    {
        cout << "\t\t\tFaculty ID : " << res->getString("facultyId") << endl;
        cout << "\t\t\tFaculty Name: " << res->getString("name") << endl;
        cout << "\t\t\t--------------------------------" << endl;
    }
    cout << endl;
    menu();
}
void admin::show_courses()
{
    res = stmt->executeQuery("Select * from courses");
    cout << "\t\t\tAll Courses of Institute" << endl;
    cout << "\t\t\t--------------------------------" << endl;
    while (res->next())
    {
        cout << "\t\t\tCourse Code: " << res->getString("coursecode") << endl;
        cout << "\t\t\tCourse Name: " << res->getString("name") << endl;
        cout << "\t\t\tInstructor ID: " << res->getString("facultyId") << endl;
        cout << "\t\t\tCredits: " << res->getString("credits") << endl;
        cout << "\t\t\tFloating? (Y/N): " << res->getString("isFloating") << endl;
        cout << "\t\t\t--------------------------------" << endl;
    }
    cout << endl;
    menu();
}
void admin::show_batch()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    res = stmt->executeQuery("Select * from " + code);
    cout << "\t\t\tStudents of course " << code << endl;
    cout << "\t\t\t--------------------------------" << endl;
    while (res->next())
    {
        cout << "\t\t\tStudent ID : " << res->getString("studentId") << endl;
        cout << "\t\t\tStudent Grade: " << res->getString("Grade") << endl;
        cout << "\t\t\t--------------------------------" << endl;
    }
    cout << endl;
    menu();
}
void admin::add_student()
{
    cout << "Please Enter Student Details\n";
    cout << "Enter Student ID: ";
    string id, name;
    cin >> id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);
    string password = generatePassword();
    cout << "Password generated for " << id << " is " << generatePassword() << endl;
    stmt->execute("insert into students value('" + id + "','" + name + "','" + password + "')");
    cout << "Successfully added " << name << " to institute\n";
    menu();
}
void admin::delete_student()
{
    cout << "Please Enter Student ID: ";
    string id;
    cin >> id;
    stmt->execute("delete from students where studentId = '" + id + "'");
    cout << "Successfully deleted " << id << " from institute\n";
    menu();
}
void admin::add_faculty()
{
    cout << "Please Enter Faculty Details\n";
    cout << "Enter Faculty ID: ";
    string id, name;
    cin >> id;
    cout << "Enter Faculty Name: ";
    cin.ignore();
    getline(cin, name);
    string password = generatePassword();
    cout << "Password generated for " << id << " is " << generatePassword() << endl;
    stmt->execute("insert into faculty value('" + id + "','" + name + "','" + password + "')");
    cout << "Successfully added " << name << " to institute\n";
    menu();
}
void admin::delete_faculty()
{
    cout << "Please Enter Faculty ID: ";
    string id;
    cin >> id;
    stmt->execute("delete from faculty where facultyId = '" + id + "'");
    cout << "Successfully deleted " << id << " from institute\n";
    menu();
}
void admin::assign_course()
{
    cout << "Please Enter Student ID: ";
    string id;
    cin >> id;
    res = stmt->executeQuery("SELECT * FROM students WHERE studentId = '" + id + "'");
    if (res->rowsCount())
    {
        cout << "Please Enter Course Code: ";
        string code;
        cin >> code;
        res = stmt->executeQuery("SELECT * FROM courses WHERE coursecode = '" + code + "'");
        if (res->rowsCount())
        {
            stmt->execute("insert into " + code + " values('" + id + "',NULL)");
            cout << "Successfully assigned course " << code << " to " << id << "\n";
            menu();
        }
        else
        {
            cout << "This course is not applicable.\n";
            menu();
        }
    }
    else
    {
        cout << "This ID is not defined.\n";
        menu();
    }
}
void admin::unassign_course()
{
    cout << "Please Enter Student ID: ";
    string id;
    cin >> id;
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    stmt->execute("delete from " + code + " where studentId = '" + id + "'");
    cout << "Successfully removed " << id << " from " << code << endl;
    ;
    menu();
}
void admin::add_course()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    string name;
    cout << "Please Enter Course Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Please Enter Faculty Id: ";
    string id;
    cin >> id;
    cout << "Credits: ";
    int credits;
    cin >> credits;
    string str;
    str = to_string(credits);
    cout << "Is the course floating (Y/N): ";
    char isFloating;
    cin >> isFloating;
    stmt->execute("insert into courses value('" + code + "','" + name + "','" + id + "','" + str + "','" + isFloating + "')");
    stmt->execute("create table " + code + " (studentId VARCHAR(50), Grade CHAR, PRIMARY KEY(studentId))");
    cout << "Successfully added course " << code << endl;
    menu();
}
void admin::delete_course()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    stmt->execute("delete from courses where coursecode = '" + code + "'");
    stmt->execute("drop table " + code);
    cout << "Successfully deleted course " << code << endl;
    menu();
}
void admin::change_password()
{
    cout << "Please Enter Current Password: ";
    string password;
    cin >> password;
    cout << "Please Enter New Password: ";
    string newPassword;
    cin >> newPassword;
    string adminPassword, SqlUser, SqlPassword;
    fstream userfile;
    userfile.open("userfile.txt", ios::in);
    getline(userfile, SqlUser);
    getline(userfile, SqlPassword);
    getline(userfile, adminPassword);
    userfile.close();
    if (adminPassword == password)
    {
        userfile.open("userfile.txt", ios::out);
        userfile << SqlUser << "\n"
                 << SqlPassword << "\n"
                 << newPassword;
        userfile.close();
    }
    cout << "Password changed successfully\n";
    menu();
}

class student
{
public:
    string studentId;
    void menu();
    void course_register();
    void deregister();
    void show_grades();
    void change_password();
    void show_courses();
};

void student::menu()
{
    cout << "\t\t\t-------------------------------" << endl;
    cout << "\t\t\t1.) REGISTER FOR A COURSE" << endl;
    cout << "\t\t\t2.) DEREGISTER FOR A COURSE" << endl;
    cout << "\t\t\t3.) SHOW MY GRADES" << endl;
    cout << "\t\t\t4.) CHANGE PASSWORD" << endl;
    cout << "\t\t\t5.) LOGOUT" << endl;
    cout << "\t\t\tPlease Enter your Choice (1-5): " << endl;
    cout << "\t\t\t-------------------------------" << endl;
    int choice;
    cin >> choice;
    system("clear");
    switch (choice)
    {
    case 1:
        course_register();
        break;
    case 2:
        deregister();
        break;
    case 3:
        show_grades();
        break;
    case 4:
        change_password();
        break;
    case 5:
        cout << "Bye\n";
        exit(0);
    }
}
void student::course_register()
{
    show_courses();
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    res = stmt->executeQuery("SELECT * FROM courses WHERE coursecode = '" + code + "'");
    res->next();
    if (res->getString("isFloating") == "N")
    {
        cout << "Sorry, this course can't be registered as of now.\n";
    }
    else
    {
        stmt->execute("insert into " + code + " value('" + studentId + "',NULL)");
        cout << "Succesfully registered you for course " << code << endl;
    }
    menu();
}
void student::show_courses()
{
    res = stmt->executeQuery("Select * from courses");
    cout << "\t\t\tAll Courses of Institute" << endl;
    cout << "\t\t\t--------------------------------" << endl;
    while (res->next())
    {
        cout << "\t\t\tCourse Code: " << res->getString("coursecode") << endl;
        cout << "\t\t\tCourse Name: " << res->getString("name") << endl;
        cout << "\t\t\tInstructor ID: " << res->getString("facultyId") << endl;
        cout << "\t\t\tCredits: " << res->getString("credits") << endl;
        cout << "\t\t\tFloating? (Y/N): " << res->getString("isFloating") << endl;
        cout << "\t\t\t--------------------------------" << endl;
    }
    cout << endl;
}
void student::deregister()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    res = stmt->executeQuery("SELECT * FROM " + code + " WHERE studentId = '" + studentId + "' AND Grade is NULL");
    if (res->rowsCount())
    {
        stmt->execute("delete from " + code + " where studentId = '" + studentId + "'");
        cout << "Successfully deregistered you from " << code << endl;
    }
    else
    {
        cout << "Sorry, this course can't be deregistered as it is graded.\n";
    }
    menu();
}
void student::show_grades()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    res = stmt->executeQuery("SELECT * FROM " + code + " WHERE studentId ='" + studentId + "' AND Grade is NOT NULL");
    if (res->rowsCount())
    {
        res->next();
        cout << "Your grade in course " << code << " is: ";
        cout << res->getString("Grade") << endl;
        menu();
    }
    else
    {
        cout << "Course has not been graded yet.\n";
        menu();
    }
}
void student::change_password()
{
    cout << "Please Enter Current Password: ";
    string password;
    cin >> password;
    cout << "Please Enter New Password: ";
    string newPassword;
    cin >> newPassword;
    res = stmt->executeQuery("SELECT password FROM students WHERE studentId ='" + studentId + "'");
    res->next();
    if (res->getString("password") == password)
    {
        stmt->execute("UPDATE students SET password = '" + newPassword + "' WHERE studentID ='" + studentId + "'");
    }
    cout << "Password changed successfully\n";
    menu();
}

class faculty
{
public:
    string facultyId;
    void menu();
    void show_students();
    void submit_grades();
    void change_password();
};
void faculty::menu()
{
    cout << "\t\t\t--------------------------------" << endl;
    cout << "\t\t\t1.) SHOW MY STUDENTS" << endl;
    cout << "\t\t\t2.) SUBMIT GRADES" << endl;
    cout << "\t\t\t3.) CHANGE PASSWORD" << endl;
    cout << "\t\t\t4.) LOGOUT" << endl;
    cout << "\t\t\tPlease Enter your Choice (1-4):" << endl;
    cout << "\t\t\t--------------------------------" << endl;
    int choice;
    cin >> choice;
    system("clear");
    switch (choice)
    {
    case 1:
        show_students();
        break;
    case 2:
        submit_grades();
        break;
    case 3:
        change_password();
        break;
    case 4:
        cout << "Bye\n";
        exit(0);
    }
}
void faculty::show_students()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    res = stmt->executeQuery("Select * from " + code);
    cout << "\t\t\tStudents of course " << code << endl;
    cout << "\t\t\t--------------------------------" << endl;
    while (res->next())
    {
        cout << "\t\t\tStudent ID : " << res->getString("studentId") << endl;
        cout << "\t\t\tStudent Grade: " << res->getString("Grade") << endl;
        cout << "\t\t\t--------------------------------" << endl;
    }
    cout << endl;
    menu();
}
void faculty::submit_grades()
{
    cout << "Please Enter Course Code: ";
    string code;
    cin >> code;
    cout << "Please Enter Student ID: ";
    string studentId;
    cin >> studentId;
    cout << "Please Enter Grade: ";
    char Grade;
    cin >> Grade;
    stmt->execute("update " + code + " set Grade = '" + Grade + "' where studentId = '" + studentId + "'");
    cout << "Grade submitted succesfully\n";
    menu();
}
void faculty::change_password()
{
    cout << "Please Enter Current Password: ";
    string password;
    cin >> password;
    cout << "Please Enter New Password: ";
    string newPassword;
    cin >> newPassword;
    res = stmt->executeQuery("SELECT password FROM faculty WHERE facultyId ='" + facultyId + "'");
    res->next();
    if (res->getString("password") == password)
    {
        stmt->execute("UPDATE faculty SET password = '" + newPassword + "' WHERE facultyID ='" + facultyId + "'");
    }
    cout << "Password changed successfully\n";
    menu();
}	
void database(){
    stmt->execute("insert into students value('ai21btech11007','CHERUKUPALLI SAI MALINI MOUKTIKA','password')");
    stmt->execute("insert into students value('ai21btech11016','JYOTHI BLESSY ANVITHA','password')");
    stmt->execute("insert into students value('ai21btech11017','VELMA DHATRI REDDY','password')");
    stmt->execute("insert into students value('ai21btech11020','JANGA TUSHITA SHARVA','password')");
    stmt->execute("insert into students value('ai21btech11026','CHEEDELLA LAXMI SRAVANI','password')");
    stmt->execute("insert into students value('ai21btech11030','HARSH GOYAL','password')");
    stmt->execute("insert into students value('cs21btech11012','RISHIT D','password')");
    stmt->execute("insert into students value('cs21btech11060','VARUN GUPTA','password')");
    stmt->execute("insert into students value('cs21btech11022','LAKSHYA MUKHIJA','password')");
    stmt->execute("insert into students value('cs21btech11025','PUSHPENDRA BAIRWA','password')");
    stmt->execute("insert into students value('cs21btech11027','HARSHIT KHANDELWAL','password')");
    stmt->execute("insert into students value('cs21btech11008','PRABHAV JAIN','password')");
    stmt->execute("insert into students value('cs21btech11052','SALAPU SRI CHARVI','password')");
    stmt->execute("insert into students value('cs21btech11053','RAHUL RAMACHANDRAN','password')");
    stmt->execute("insert into students value('cs21btech11011','SURISETTY RISHITHA','password')");
    stmt->execute("insert into students value('cs21btech11019','VEDANT BHANDARE','password')");
    stmt->execute("insert into students value('cs21btech11020','MAHARSHI KADEVAL','password')");
    stmt->execute("insert into students value('cs21btech11061','YASHVARDHAN SAINI','password')");
    stmt->execute("insert into students value('cs21btech11062','ABHAY SHANKAR','password')");
    stmt->execute("insert into students value('cs21btech11063','ENNA GUPTA','password')");
    stmt->execute("insert into faculty value('mvpraoiith','M V Panduranga Rao','password')");
    stmt->execute("insert into faculty value('rakeshiith','Rakesh Venkat','password')");
    stmt->execute("insert into faculty value('gvviith','Dr GVV Sharma','password')");
    stmt->execute("insert into faculty value('ramaiith','Ramakrishna Upadrasta','password')");
    stmt->execute("insert into faculty value('atuliith','Atul Agrawal','password')");
    stmt->execute("insert into courses value('AI1110','Probability and Random Variables','gvviith',3,'Y')");
    stmt->execute("create table AI1110 (studentId VARCHAR(50), Grade CHAR, PRIMARY KEY(studentId))");
    stmt->execute("insert into courses value('CS1023','Software Development Fundamentals','mvpraoiith',3,'Y')");
    stmt->execute("create table CS1023 (studentId VARCHAR(50), Grade CHAR, PRIMARY KEY(studentId))");
    stmt->execute("insert into courses value('CS1010','Discrete Mathematics','rakeshiith',2,'N')");
    stmt->execute("create table CS1010 (studentId VARCHAR(50), Grade CHAR, PRIMARY KEY(studentId))");
    stmt->execute("insert into courses value('ID1050','Introduction to Programming','ramaiith',2,'N')");
    stmt->execute("create table ID1050 (studentId VARCHAR(50), Grade CHAR, PRIMARY KEY(studentId))");
    stmt->execute("insert into courses value('MA1050','Calculus','atuliith',3,'Y')");
    stmt->execute("create table MA1050 (studentId VARCHAR(50), Grade CHAR, PRIMARY KEY(studentId))");
    return;
}

int main()
{
    fstream userfile;
    string SqlUser, SqlPassword, adminPassword;
    userfile.open("userfile.txt", ios::in);
    getline(userfile, SqlUser);
    getline(userfile, SqlPassword);
    getline(userfile, adminPassword);
    userfile.close();
    
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", SqlUser, SqlPassword);
    stmt = con->createStatement();
    stmt->execute("create database if not exists AIMS");
    stmt->execute("use AIMS");
    stmt->execute("create table if not exists students(studentId VARCHAR(50), name VARCHAR(50), password VARCHAR(50), PRIMARY KEY(studentId))");
    stmt->execute("create table if not exists faculty(facultyId VARCHAR(50), name VARCHAR(50), password VARCHAR(50), PRIMARY KEY(facultyId))");
    stmt->execute("create table if not exists courses(coursecode VARCHAR(50), name VARCHAR(50), facultyId VARCHAR(50), credits INT, isFloating CHAR, PRIMARY KEY(coursecode), FOREIGN KEY(facultyId) REFERENCES faculty(facultyId))");
    
    if (adminPassword == "password")
    {
        cout << "Please enter new ADMIN Password: ";
        cin >> adminPassword;
        userfile.open("userfile.txt", ios::out);
        userfile << SqlUser << "\n"
                 << SqlPassword << "\n"
                 << adminPassword;
        userfile.close();
        cout << "Do you want to insert default database in AIMS (Y/N): ";
        char c; cin >> c;
        if (c == 'Y' || c == 'y')
        {
            database();
        }
        else if (c == 'N' || c == 'n');
        else
        {
            cout << "Please enter your choice again: ";
            cin >> c;
            if (c == 'Y' || c == 'y')
            {
                database();
            }
        }
    }
    cout << "Enter Login ID: ";
    string loginId;
    cin >> loginId;
    cout << "Enter Password: ";
    string password;
    cin >> password;
    if (loginId == "admin" && password == adminPassword)
    {
        cout << "Welcome ADMIN\n";
        admin admin;
        admin.menu();
    }
    else if (loginId == "admin" && password != adminPassword)
    {
        cout << "ADMIN, you have entered incorrect password" << endl;
    }
    else
    {
        res = stmt->executeQuery("SELECT * FROM students WHERE studentId ='" + loginId + "'");
        if (res->rowsCount())
        {
            res->next();
            if (res->getString("password") == password)
            {
                cout << "Welcome ";
                cout << res->getString("name") << endl;
                student student;
                student.studentId = loginId;
                student.menu();
            }
            else
            {
                cout << "You have entered incorrect password.\n";
                exit(0);
            }
        }
        else
        {
            res = stmt->executeQuery("SELECT * FROM faculty WHERE facultyId ='" + loginId + "'");
            if (res->rowsCount())
            {
                res->next();
                if (res->getString("password") == password)
                {
                    cout << "Welcome ";
                    cout << res->getString("name") << endl;
                    faculty faculty;
                    faculty.facultyId = loginId;
                    faculty.menu();
                }
                else
                {
                    cout << "You have entered incorrect password\n";
                    exit(0);
                }
            }
            else
            {
                cout << "You have entered incorrect Login ID\n";
                exit(0);
            }
        }
    }
    delete res;
    delete stmt;
    delete con;
    return EXIT_SUCCESS;
}
