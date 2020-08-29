#include <iostream>
#include <iomanip>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <conio.h>

using namespace std;

class student
{
   int rollno;
   char name[20],fname[20],mname[20],clas[5];
   char grade;
   float pm,cm,mm,em,csm;
   float total;
   float per;
public:
   void enter();            
   void calc();                 
   void display();             
   void write_in_file();        
   int getrollno();            
   void add_data();            
   void display_all_record();  
   void delete_data();          
   void modify_data();        
} s;       

void student::calc()
{
   total=pm+cm+csm+mm+em;
   per=(total*100)/500;
   if(per>=90)
	 grade='A';
   else if(per>=75)
	 grade='B';
   else if(per>=50)
	 grade='C';
   else if(per>=33)
	 grade='E';
   else
	 grade='F';
}
void student::enter()
{
   cout<<"Hi! Please enter the information as given below:";
   cout<<"\nEnter the Roll number of Student:";
   cin>>rollno;
   cout<<"\nEnter the Class of Student:";
   gets(clas);
   cout<<"\nEnter the Name of Student:";
   gets(name);
   cout<<"\nEnter the name of Father:"<<"Mr.";
   gets(fname);
   cout<<"\nEnter the name of Mother:"<<"Mrs.";
   gets(mname);
   cout<<"\nEnter Marks in Chemistry out of 100:";
   cin>>cm;
   cout<<"\nEnter Marks in Physics out of 100:";
   cin>>pm;
   cout<<"\nEnter Marks in  Mathematics out of 100:";
   cin>>mm;
   cout<<"\nEnter Marks in English out of 100:";
   cin>>em;
   cout<<"\nEnter Marks in Computer Science out of 100:";
   cin>>csm;
   calc();                  
}
void student::display()
{
   cout<<"\nRoll number of Student :"<<rollno;
   cout<<"\nName of Student :"<<name;
   cout<<"\nClass of Student:" <<clas;
   cout<<"\nName of father : "<<"Mr."<<fname;
   cout<<"\nName of mother : "<<"Mrs."<<mname;
   cout<<"\nMarks in Chemistry : "<<cm;
   cout<<"\nMarks in Physics : "<<pm;
   cout<<"\nMarks in Mathematics : "<<mm;
   cout<<"\nMarks in English : "<<em;
   cout<<"\nMarks in Computer Science : "<<csm;
   cout<<"\nPercentage of Student : "<<setprecision(4)<<per<<"%";
   cout<<"\nGrade of Student : "<<grade;
}
int student::getrollno()
{
    return rollno;
}
void student::write_in_file()
{
   ofstream outfile;
   outfile.open("std.data",ios::binary|ios::app);
   s.enter();                          //function calling.
   outfile.write((char*)&s,sizeof(student));
   outfile.close();                       //file is closed.
   cout<<"\n\n\nStudent Record has been created !! ";
   getch();
}

void student::display_all_record()
{
    ifstream infile;
    infile.open("std.data",ios::binary);
    if(!infile)
    {
	 cout<<"File not found !!!! Press any key....";
	 getch();
	 return;
    }
    cout<<"\n\n\n\n\t\tDisplay all Record !!!!\n\n\n\n";
    while(infile.read((char*)&s,sizeof(s)))
    {
	 s.display();                    //function calling.
    }
    infile.close();                     //file is closed.
    getch();
}
void student::delete_data()
{
     ifstream fin("std.data",ios::in);
     ofstream file("temp.data",ios::out);
     int rnoo;
     char fd='f';
     char confirm='n';
     cout<<"\n\n\t\tEnter Roll Number of Student whose Record is to be Deleted:\n\n\t";
     cin>>rnoo;
     while(!fin.eof())
     {
	      fin.read((char*)&s,sizeof(s));
	      if(s.getrollno()==rnoo)         //function calling
	      {
			s.display();        //function calling.
			fd='t';
			cout<<"\n\n\t\tAre you sure , you want to delete this record?(y/n):\n\n\n";
			cin>>confirm;
			if(confirm=='n')
			file.write((char*)&s,sizeof(s));
	      }
	      else
			file.write((char*)&s,sizeof(s));
       }
       if(fd=='f')
	     {
	     cout<<"\n\n\t\tRecord not found!!!\n\n";
	     system("pause");
	     }
       fin.close();          /* both the files are closed*/
       file.close();
       remove("std.data");
       rename("temp.data","stud.data");
       fin.open("std.data",ios::in);           //file is reopened.
       cout<<"\n\n\t\tNow the file contains:";
       while(!fin.eof())
       {
		fin.read((char*)&s,sizeof(s));
		if(fin.eof())
			break;
		s.display();
       }
       fin.close();           //file is closed.
       getch();
}
void student::modify_data()
{
     int fn=0,rono;
     fstream io;
     io.open("std.data",ios::in|ios::out|ios::binary);
     cout<<"\n\n\t\tEnter the Roll Number which is to be modified:";
     cin>>rono;
     if(!io)
     {
	  cout<<"\n\n\t\tFile could not be opened!!!!Press any key....";
	  getch();
     }
     while(io.read((char*)&s,sizeof(s))&&fn==0)
     {
	   if(s.getrollno()==rono)      //function calling.
	   {
		       s.display();               //function calling.
		       cout<<"\n\n\t\tPlease enter the new details of the Student:";
		       s.enter();                 //function calling.
		       int pos=(-1)*sizeof(s);
		       io.seekp(pos,ios::cur);
		       io.write((char*)&s,sizeof(student));
		       cout<<"\n\n\t\tRecord has been Updated...";
		       fn=1;
	     }
     }
     io.close();       //file is closed.
     if(fn==0)
	   cout<<"\n\n\tRecord not found!!!";
	   getch();
}
void student::add_data()
{
    ofstream fout("std.data",ios::app);
    char ans='y';
    while(ans=='y')
    {
	    s.enter();            //function calling.
	    fout.write((char*)&s,sizeof(s));
	    cout<<"\n\n\tRecord is Added to File.......\n\n\n";
	    cout<<"Want to Enter more Records?)(y/n)\n\n";
	    cin>>ans;
    }
    fout.close();             //file is closed.
    getch();
}

int main()
{
   system("CLS");
   char c;
   do{
	system("CLS");
	cout<<"\n\n\n\t\tMain Menu:-";
	cout<<"\n\n\t\t1. Add Data";
	cout<<"\n\n\t\t2. Delete Data";
	cout<<"\n\n\t\t3. Modify Data";
	cout<<"\n\n\t\t4. Display Data";
	cout<<"\n\n\t\tPlease select one option(1-4)";
	cin>>c;
	system("CLS");
	switch(c)
	{
		 case '1': s.add_data();  break;
		 case '2': s.delete_data();  break;
		 case '3': s.modify_data();  break;
		 case '4': s.display_all_record();  break;
		 default: cout<<"\a";
	}
    }while(c!=4);

return 0;
}
