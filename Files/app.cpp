#define _CRT_SECURE_NO_WARNINGS

#include	<iostream>
#include	<stdlib.h>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<iomanip>
#include	<sstream> 
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List *, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
 int durationcalculation(Date, Date);
 int leapYearCounter(Date d);
 int duration(Date dt1, Date dt2);
 int menu();

 struct counter {
	 char course[3];
	 int count;
	 int totalbook;
	 int ttlduebook;
	 double duefine;

	 counter() {
		 strcpy(course, " ");
		 count = 0;
		 totalbook = 0;
		 ttlduebook = 0;
		 duefine = 0;
	 }
 };

 
int main() {
	List list,type1,type2;
	LibStudent stu;
	bool exit = false;
	do {
		switch (menu()) {
		case 1:
			ReadFile("student.txt", &list);
			break;
		case 2:
			char id[10];
			cout << "Please enter the id of student wanted to delete: ";
			cin >> id;
			if (DeleteRecord(&list, id)) {
				cout << "Deleted\n";
			}
			else {
				cout << "Failed to Delete record\n";
			}
			break;
		case 3:
			char id1[10];
			cout << "Please enter the id of student wanted to search for: ";
			cin >> id1;
			SearchStudent(&list, id1, stu);
			break;
		case 4:
			InsertBook("book.txt", &list);
			break;
		case 5:
			int source, detail;
			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			Display(&list, source, detail);
			break;
		case 6:
			computeAndDisplayStatistics(&list);
			break;
		case 7:
			char call[20];
			cout << "Call Id of the book: ";
			cin >> call;
			printStuWithSameBook(&list, call);
			break;
		case 8:
			displayWarnedStudent(&list, &type1, &type2);
			break;
		case 9:
			exit = true;
			break;
		default:
			cout << "\nPlease enter a valid input (1-9)\n";
			break;
		}
	} while (exit == false);
	

	cout << "\n\n Bye! Have a Nice Day!\n";
	system("pause");
	return 0;
}

bool ReadFile(string filename, List* list) {
	
	ifstream readFile;
	string input;
	int position = 0;
	int count = 0;

	readFile.open(filename);

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			LibStudent student;

			//read student id
			getline(readFile, input);
			position = input.find('=') + 2;
			input = input.substr(position);
			strcpy(student.id, input.c_str());

			//readname 
			getline(readFile, input);
			position = input.find('=') + 2;
			input = input.substr(position);
			strcpy(student.name, input.c_str());

			//read course
			getline(readFile, input);
			position = input.find('=') + 2;
			input = input.substr(position);
			strcpy(student.course, input.c_str());

			//read phone num
			getline(readFile, input);
			position = input.find('=') + 2;
			input = input.substr(position);
			strcpy(student.phone_no, input.c_str());
			
			//insert struct into list
			list->insert(count, student);
			count++;
			getline(readFile, input);
			getline(readFile, input);

		}
		readFile.close();
		cout <<"\n"<< count << " records has been successful read.\n";

		
	}
	else {
		cout << "The file cannot be open" << endl;
	}
	return true;
}

bool DeleteRecord(List* list, char* id) {
	bool j = false;
	for (int i = 1; i <= list->size(); i++) {
		if (strcmp(list->find(i)->item.id, id) == 0) {
			list->remove(i);
			i = true;
			return true;
		}
	}
	if (j == false) {
		cout << endl << "Error: ID not found"<<id<< endl;
	}
	return false;
}

bool Display(List* list, int source, int detail) {
	LibStudent student;
	LibBook book;
	ofstream writeFile("LibraryRecord.txt");

	if (detail == 1) {
		if (source == 1) {
			
			int i = 1;
			writeFile << "Student and Book Information: " << endl;

			while (list->get(i, student)) {
				student.print(writeFile);
				writeFile << endl;
				writeFile << "BORROWING BOOKS:\n";
				for (int i = 0; i < student.totalbook; i++) {
					(student.book + i)->print(writeFile);
				}
				i++;
			}
	}
		else if (source == 2) {
			int i = 1;
			cout << "Student and Book Information: " << endl;

			while (list->get(i, student)) {
				student.print(cout);
				cout << endl;
				cout << "BORROWING BOOKS:\n";
				for (int i = 0; i < student.totalbook; i++) {
					(student.book + i)->print(cout);
				}

				cout << "--------------------------------BORDER-----------------------------------" << endl;
				i++;
			}


		}
		else {
			cout << "Please key in a valid selection (1: Display in file  2: Display on screen)" << source;
			bool Display(List * list, int cource, int detail);
		}
		return true;
	}
	
	if (detail == 2) {
		if (source == 1)    //display in file
		{
			int i = 1;
			writeFile << "Student Information:" << endl;
			while (list->get(i, student)) {
				student.print(writeFile);
				writeFile << endl;
				i++;
			}

		}
		else if (source == 2)    //display in screen
		{
			int i = 1;
			cout << "Student Information:" << endl;
			
			while (list->get(i, student)) {
				student.print(cout);
				cout << endl;
				i++;
			}

		}
		else
		{
			cout << "Please key in a valid selection (1: Display in file   2: Display on screen)" << source;
			bool Display(List * list, int source, int detail);
		}
		return true;
	}
	return false;
}

int leapYearCounter(Date d)
{
	int years = d.year;

	if (d.month <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}

int duration(Date dt1, Date dt2)
{
	int monthDays[12] = { 31, 28, 31, 30, 31, 30,
						  31, 31, 30, 31, 30, 31 };

	long int n1 = dt1.year * 365 + dt1.day;

	for (int i = 0; i < dt1.month - 1; i++)
		n1 += monthDays[i];

	n1 += leapYearCounter(dt1);

	long int n2 = dt2.year * 365 + dt2.day;
	for (int i = 0; i < dt2.month - 1; i++)
		n2 += monthDays[i];
	n2 += leapYearCounter(dt2);

	return (n2 - n1);
}

bool InsertBook(string bookfile, List* list) {
	ifstream readfile;
	string input,author,delimiter,token;
	
	readfile.open(bookfile);
	if (list->count == 0) {
		cout << "\nThe list is empty, please select (1. Read File) first\n";
	}
	else {
		if (readfile.is_open()) {
			while (readfile >> input) {
				LibBook booklist;
				LibBook* bookary;
				char id[10];
				size_t pos = 0;
				int position = 0;


				//read student id who borrow the book
				strcpy(id, input.c_str());
				for (int i = 1; i <= list->size(); i++) {
					if (strcmp(list->find(i)->item.id, id) == 0) {
						position = i;

					}
				}

				cout << id << endl;

				//read book author
				readfile >> input;
				string delimiter = "/";

				int i = 0;
				if (input.find(delimiter) == std::string::npos) {
					booklist.author[i] = new char[50];
					strcpy(booklist.author[i], input.c_str());
				}
				else {
					while (input.find(delimiter) != std::string::npos) {
						pos = input.find(delimiter);
						token = input.substr(0, pos);
						booklist.author[i] = new char[50];
						strcpy(booklist.author[i], token.c_str());
						input.erase(0, pos + delimiter.length());
						i++;
					}
					booklist.author[i] = new char[50];
					strcpy(booklist.author[i], input.c_str());
				}


				//read book title
				readfile >> input;
				strcpy(booklist.title, input.c_str());

				//read publisher
				readfile >> input;
				strcpy(booklist.publisher, input.c_str());

				//read ISBN
				readfile >> input;
				strcpy(booklist.ISBN, input.c_str());

				//read year published
				int year;

				readfile >> year;
				booklist.yearPublished = year;

				//read call num
				readfile >> input;
				strcpy(booklist.callNum, input.c_str());

				//read date borrow
				readfile >> input;

				int conday = 0, conmon = 0, conyear = 0;
				//insert day
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				stringstream day(token);
				day >> conday;
				booklist.borrow.day = conday;
				input.erase(0, pos + delimiter.length());

				//insert month
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				stringstream mon(token);
				mon >> conmon;
				booklist.borrow.month = conmon;
				input.erase(0, pos + delimiter.length());

				//insert year
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				stringstream yearcon(token);
				yearcon >> conyear;
				booklist.borrow.year = conyear;


				// read date due{same method as borrow, just change location}
				readfile >> input;
				//insert day
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				stringstream dday(token);
				dday >> conday;
				booklist.due.day = conday;
				input.erase(0, pos + delimiter.length());

				//insert month
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				stringstream dmon(token);
				dmon >> conmon;
				booklist.due.month = conmon;
				input.erase(0, pos + delimiter.length());

				//insert year
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				stringstream dyearcon(token);
				dyearcon >> conyear;
				booklist.due.year = conyear;

				//trieve due date
				Date due;
				due.day = conday;
				due.month = conmon;
				due.year = conyear;

				//preset the current date
				Date curDate;
				curDate.day = 29;
				curDate.month = 3;
				curDate.year = 2020;

				//calculate fine for that book inserted
				if (duration(curDate, due) < 0) {
					double fine = duration(curDate, due) * 0.50;
					booklist.fine = -fine;
				}


				//insert the booklist into the list
				if (list->find(position)->item.totalbook == 0) {
					list->find(position)->item.book[0] = booklist;
					list->find(position)->item.totalbook++;
				}
				else {
					list->find(position)->item.book[list->find(position)->item.totalbook] = booklist;
					list->find(position)->item.totalbook++;
				}

				list->find(position)->item.calculateTotalFine();
				
			}
			cout << "\nBooks inserted successfully to student list.\n";
			return true;
		}
		else {
			cout << "The file cannot be open!" << endl;
			return false;
		}
	}
}

bool SearchStudent(List* list, char* id, LibStudent& stu)
{

	for (int i = 1; i <= list->size(); i++)
	{
		if (strcmp(list->find(i)->item.id, id) == 0)
		{
			stu = list->find(i)->item;
			cout << "Student found\n";
			stu.print(cout);
			return true;
			break;
		}
			
	}
	cout << "Student ID:" << id << " not Found\n";
	return false;
};

bool computeAndDisplayStatistics(List* list) {
	counter counter[10],tmp;
	Node* cur = list->head;

	cout << setw(10) <<"\nSTATISTICS\n---------------------------------------------------------------------------------------------------------------"<<
		"\n|  Course  |" << setw(22) << right << "Number of Students  |"
		<< setw(25) << right << "Total Books Borrowed  |"<<setw(25)<<right<<"Total Overdue Books  |"
		<<setw(28)<<"Total Overdue Fine(RM)  |\n";
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;

	//first element into counter array
	strcpy(tmp.course, cur->item.course);
	tmp.count = 1;
	tmp.totalbook = cur->item.totalbook;
	tmp.duefine = cur->item.total_fine;
	for (int l = 0; l < cur->item.totalbook; l++) {
		if (cur->item.book[l].fine != 0) {
			tmp.ttlduebook++;
		}
	}
	counter[0] = tmp;
	cur = cur->next;


	while (cur) {
		int i = 0;
		bool exist = false;
		while (counter[i].count != 0) {
			//if found same course name
			if (!strcmp(counter[i].course, cur->item.course)) { 
				counter[i].count++;
				//total books borrowed
				counter[i].totalbook += cur->item.totalbook;
				//dueamount
				counter[i].duefine += cur->item.total_fine;
				//check book overdue amount
				for (int l = 0; l < cur->item.totalbook; l++) {
					if (cur->item.book[l].fine != 0.00) {
						counter[i].ttlduebook++;

					}
				}
				exist = true;
				break;
			}
			i++;
		}
		//not course not found, add new element
		tmp.ttlduebook = 0;
		if (exist == false) {
			//loop to the last element
			int j = 0;
			while (counter[j].count != 0) {
				j++;
			}
			strcpy(tmp.course, cur->item.course);
			tmp.count = 1;
			tmp.totalbook = cur->item.totalbook;
			tmp.duefine = cur->item.total_fine;
			for (int l = 0; l < cur->item.totalbook; l++) {
				if (cur->item.book[l].fine != 0.00) {
					tmp.ttlduebook++;
				}
			}
			counter[j] = tmp;
		}
		
		cur = cur->next;
	}

	int k = 0;
	while (counter[k].count != 0) {
		cout <<"|"<< setw(6) <<counter[k].course  <<"    |" << setw(10) << right <<counter[k].count <<"           |"
			<< setw(22) << right << counter[k].totalbook<<"  |" << setw(21) << right << counter[k].ttlduebook <<"   |"
			<< setw(24) << counter[k].duefine <<"  |\n";
		cout << "---------------------------------------------------------------------------------------------------------------" << endl;
		k++;
	}


	return true;
}

bool printStuWithSameBook(List* list, char* id) {
	LibStudent student,tmpstu;
	List tmp;
	int count = 0;

	for (int i = 1; i <= list->size(); i++) {
		
		//find out the student first
		list->get(i, student); 

		//loop through the book of student
		for (int b = 0; b < student.totalbook; b++) {
			
			//check if the call Num is same?
			if (strcmp(student.book[b].callNum, id) == 0) {
				student.book[0] = student.book[b];
				tmp.insert(student);
				count++;
			}
		}
	}
	if (count != 0) {
		cout << "There are " << count << " students that borrow the book with call number "
			<< id << " as shown below:\n" << endl;

		for (int i = 1; i <= tmp.size(); i++) {
			tmp.get(i, tmpstu);
			cout << "Student Id =  " << tmpstu.id << endl;
			cout << "Name = " << tmpstu.name << endl;
			cout << "Course = " << tmpstu.course << endl;
			cout << "Phone Number = " << tmpstu.phone_no << endl;
			cout << "Borrow Date = ";
			tmpstu.book[0].due.print(cout); cout << endl;
			cout << "Due Date = ";
			tmpstu.book[0].borrow.print(cout); cout << endl;
			cout << "\n";
		}

		return true;
	}
	else {
		cout << "\nCall ID not found\n";
		return false;
	}
	
}

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	LibStudent student;
	Date current;
	current.day = 22;
	current.month = 3;
	current.year = 2020;

	for (int i = 1; i <= list->size(); i++) {
		int count = 0;
		bool alloverdue = true, fine = false;
		list->get(i, student);
		for (int k = 0; k < student.totalbook; k++) {
			//2 or more than 2 book overdue >= 10 days 
			if (duration(current, student.book[k].due) <= -10) {
				count++;
			}
			//totalfine> 50
			if(student.total_fine > 50){
				fine = true;
			}
			//check overdue
			if (duration(current, student.book[k].due) > 0) {
				alloverdue = false;
			}
		}

		if (count >= 2) {
			
			type1->insert(student);
			return true;
		}

		if (fine == true && alloverdue == true) {
			
			type2->insert(student);
			return true;
		}
	}
	if (type1->size() >= 1 || type2->size() >= 1) {
		if (type1->size() != 0) {
			cout << "Student has more than 2 books that are overdue for >= 10 day\n";
			Display(type1, 2, 1);
		}
		else {
			cout << "There is no student has more than 2 books that are overdue for >= 10 day" << endl;
		}
		if (type2->size() != 0) {
			cout << "Student who total fine is more than RM50.00 and every book is overdue\n";
			Display(type2, 2, 1);
		}
		else {
			cout << "There is no student who total fine is more than RM50.00 and every book is overdue\n";
		}
		
	}
	else {
		cout << "No result found\n";
		return false;
	}
	
	
	
}

int menu() {
	int x;

		cout << "\nMenu\n\n1.Read file\n2.Delete record\n3.Search student\n4.Insert book\n5.Display output\n6.Compute and Display Statistics\n7.Student with Same Book\n8.Display Warned Student\n9.Exit\n";
		do {
			cout << "\nPlease enter your selection(1-9): ";
			cin >> x;
		} while (x < 0 || x > 9);

	return x;
}