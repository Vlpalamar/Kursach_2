#pragma once
#include"list.h"

class  Question
{
public:
	string rightAnswer;
	string aText;
	int QuNumber;
};

class Subject : public Question
{
public:
	string SubjName;
	ForwardList<Question, 20> Q_list;
	string QuestionFileName=SubjName+"Q.txt";
	

};

class Section : public Subject
{
public:
	string SectName;
	ForwardList<Subject, 5>Sub_list;
};

class Program :public Section
{
protected:
	map < string, bool > map_log;
	class User
	{
	protected:
		
	public:
		string Login;
		int password=-1;
		string name;
		string sername;
		string mail;
		string number;
		string User_file = Login + ".txt";
		
		
	};
	string User_data =	"user_data.txt";
	string Subj_file =	"subj_list.txt";
	ForwardList<User, 10>		user_list;
	ForwardList<Section, 10>	sect_list;
	int ID=-1;//ID юзера в сети, функци€ log() возвращает это значение

	void startForm();
	void reg();
	int log();
	void saveUser(User u);
	void Modify();
	void resaveData();
	void print(User u);
	void addTask();
	void addSection();
	void addSubject();
	void addQuestion();
	void saveSubjectList();
	void saveQuestion(int sec,int subj);
	void loadQuestion(int sec, int subj);
	void go_test(int sec,int subj,int RightQuestion=0,int ActualAnswer=0 ); 
	void save_stat(int sec, int subj,int mark,int colAns, int perAns);
	void MyStat();
	void AdminStat();
	void AllStat();
	void TargetStat();
	void change();
	void changeLogin();
	void changePassword();
public:
	void menu();
	Program();
	
	~Program();
	
};



inline void Program::menu()
{
	
	system("cls");
	if (ID == -1)
		do
		{
			startForm();
		} while (ID == -1);

	if (ID == 0)
	{
		
		do
		{
			system("cls");
			cout << "Hello Admin\n";
			cout << "1.Reg new user\n2.Modify user\n3.Statistics\n4.change my login/password\n5.Add Section/subject/Question\n6.Log out\n";
			int ch;
			cin >> ch;
			switch (ch)
			{
			case 1:
				reg();
				break;
			case 2:
				Modify();
				break;
			case 3:
				AdminStat();
				break;
			case 4:
				change();
				break;
			case 5:
				addTask();
			case 6:
				ID = -1;
				menu();
				break;
			default:
				break;
			}


		} while (true);
	}
	else
	{
		do
		{
			system("cls");
			cout << "Hello " << user_list[ID].name << " " << user_list[ID].sername << "\n";
			cout << "1.go test\n2.check my stat\n3.Log out\n";
			int ch;
			cin >> ch;
			
			string heshFileN = user_list[ID].Login + "Cache.txt";
			ifstream ifs(heshFileN);	
				int itSect;
				int itSub;
				int RA = 0; //right answers
				int AA = 0; //Actual Answer
			switch (ch)
			{
		
			case 1:
				//если у нас есть кэш, мы его записываем
				ifs >> itSect >> itSub >> RA >> AA;
					if (AA == 0)
					{
						RA = 0;
						do
						{
							system("cls");
							cout << "choose\n";
							for (size_t i = 0; i < sect_list.getSize(); i++)
							{
								cout << i + 1 << sect_list[i].SectName << "\n";
							}
							cin >> itSect;
							itSect--;
						} while (itSect<0 or itSect> sect_list.getSize());
					
						if ((!sect_list[itSect].Sub_list.isEmpty()))
						{
							do
							{
								system("cls");
								cout << "choose\n";
								for (size_t i = 0; i < sect_list[itSect].Sub_list.getSize(); i++)
								{
									cout << i + 1 << sect_list[itSect].Sub_list[i].SubjName << "\n";
								}
								cin >> itSub;
								itSub--;
							} while (itSect<0 or itSect> sect_list[itSect].Sub_list.getSize());
						}
						else
						{
							cout << "Subject list is empty\n";
							system("pause");
							menu();
						}
					}
					ifs.close();
				go_test(itSect,itSub,RA,AA);
				break;
			case 2:
				MyStat();
				break;
			case 3:
				ID = -1;
				menu();
			default:
				break;
			}

		} while (true);
	}
	
}

inline void Program::reg()
{	
		User u;
		cout << "Hello, pls Enter your name and sername\n";
		cin >> u.name >> u.sername;
		cout << "Enter your Phone Number\n";
		cin >> u.number;
		cout << "Enter your e-mail adress\n";
		cin >> u.mail;
		do
		{
			cout << "Enter your Login\n";
			cin >> u.Login;
			auto it = map_log.find(u.Login);
			if (it == map_log.end())
			{
				map_log.emplace(u.Login, 1);
				break;
			}
			else
				cout << "sorry,login in use already,try again pls";
		} while (true);
		do
		{
			cout << "Enter Password:\n";
			string pass1;
			string pass2;
			cin >> pass1;
			cout << "Confirm you Password:\n";
			cin >> pass2;
			if (pass1 == pass2)
			{
				hash<string> h;
				u.password = h(pass2);
				break;
			}
			else
				cout << "Wrong password";
		} while (true);
		user_list.push_back(u);
		saveUser(u);
}

inline int Program::log()
{
	system("cls");
	int iteration = -1;
	do
	{
		system("cls");
		cout << "Enter Login pls\n";
		string l;
		cin >> l;
		for (size_t i = 0; i < user_list.getSize(); i++)
		{
			if (l == user_list[i].Login)
			{
				iteration = i;
				break;
			}
		}
		cout << "\nEnter your password pls\n";
		string pass;
		cin >> pass;
		hash<string> p;
	
		if (iteration != -1)
		{
			if (user_list[iteration].Login == l and user_list[iteration].password == p(pass))
			{
				cout << "complete\n";
				Sleep(300);
				return iteration;
			}
			else
			{
				cout << "Wrong Data\n";
				system("pause");
				menu();
				
			}
			
				
		}
		else
			cout << "Wrong Data\n";
		system("pause");
		


	} while (iteration==-1);
}

inline void Program::saveUser(User u)
{
	ofstream fout(User_data, ios::app);
	if (u.Login != user_list[0].Login)
					fout<< "\n" ;
	fout  << u.Login	<< "\n"	;
	fout  << u.password << "\n"	;
	fout  << u.name		<< "\n"	;
	fout  << u.sername	<< "\n"	;
	fout  << u.mail		<< "\n"	;
	fout  << u.number			;
	fout.close();
}

inline void Program::Modify()
{
	system("cls");
	cout << "choose user u wanna modify \n";
	for (size_t i = 1; i < user_list.getSize(); i++)
	{
		cout<<i<< user_list[i].name << " " << user_list[i].sername<<"\n";
	}
	do
	{
		int it = 0;
		cin >> it;
		
		if (it<user_list.getSize())
		{	
			bool ex = true;
			do
			{
				int mi = 0;//my iteration
				system("cls");
				print(user_list[it]);
				cout<<"choose data u wanna change		\n";
				cout << "---------------------------	\n";
				cout << ++mi << "- name "			<< "\n";
				cout << ++mi << "- sername: "		<< "\n";
				cout << ++mi << "- E-mail:"			<< "\n";
				cout << ++mi << "- phone Number:"	<< "\n";
				cout << ++mi << "- Delete User" << "\n";
				cout << "6-Exit\n";
				int ch;
				cin >> ch;
				
				switch (ch)
				{
				case 1:
					cout << "old name: " << user_list[it].name << "\n";
					cout << "Enter new name\n";
					cin >> user_list[it].name;
					resaveData();
					break;
				case 2:
					cout << "old sername: " << user_list[it].sername << "\n";
					cout << "Enter new sername\n";
					cin >> user_list[it].sername;
					resaveData();
					break;
				case 3:
					cout << "old E-mail: " << user_list[it].mail << "\n";
					cout << "Enter new E-mail\n";
					cin >> user_list[it].mail;
					resaveData();
					break;
				case 4:
					cout << "old Phone number: " << user_list[it].number << "\n";
					cout << "Enter new Phone number\n";
					cin >> user_list[it].number;
					resaveData();
					break;
				case 5:
					user_list.pop_at(it);
					resaveData();
					menu();
				case 6:
					menu();
					break;
				default:
					break;
				}
			} while (ex==true);
			

		}
	} while (true);
	
}	

Program::Program()
{
	ofstream fout(User_data, ios::app);
	ifstream fin(User_data);
	if (fin.is_open())
	{
		string a;
		long long i;
		while (!fin.eof())
		{
			User u;
			fin >> a;
			u.Login		= a;
			map_log.emplace(u.Login, 1);
			fin >> i;
			u.password	= i;
			fin >> a;
			u.name		= a;
			fin >> a;
			u.sername	= a;
			fin >> a;
			u.mail		= a;
			fin >> a;
			u.number	= a;
			user_list.push_back(u);
			
		}
		fin.close();
	}
	if (user_list[0].name!="Aname")		//костыль, так как если файл будет пустой оно что то добавит в список 
			user_list.clear();
	if (fout.is_open())
	{
		if (user_list.isEmpty())
		{
			User Admin;
			cout << "Hello, Admin\nEnter login:\n";
			cin >>Admin.Login;
			cout << "Enter Password:\n";
			string password;
			cin >> password;
			hash<string> h;
			Admin.password = h(password);
			Admin.name= "Aname";// админу не нужно вводить свое им€,эта и слудущее 3 строчки что бы удобнее было хранить и вычитывать из данные из файла
			Admin.sername= "Asername";
			Admin.mail = "Amail";
			Admin.number = "88000000000";
			user_list.push_back(Admin);
			saveUser(Admin);
			
		}
		
	}
		ifstream f(Subj_file);
	if (f.is_open())
	{
		
		int i=-1;
		
		string subj;
		do
		{
			string check;
			f >> check;
			if (check =="1")
			{
				Section s;
				f >> s.SectName;
				s.SectName.erase(0,0);
				sect_list.push_back(s);
				i++;
			}
			else if (check == "2")
			{
				Subject sub;
				getline(f, sub.SubjName);
				sub.SubjName.erase(0, 1);
				sect_list[i].Sub_list.push_back(sub);
			}
			else
			{
				break;
			}
		} while (!f.eof());
	}
	for (size_t i = 0; i < sect_list.getSize(); i++)
	{
		for (size_t j = 0; j < sect_list[i].Sub_list.getSize(); j++)
		{
			loadQuestion(i, j);
		}
		
	}
	fout.close();
	f.close();
}

inline void Program::startForm()
{
	system("cls");	
	int ch1;
	cout << "1.Log in\n2.Reg\n3.Exit\n";
	cin >> ch1;
	//number of user in a system
	switch (ch1)
	{
	case 1:
		ID = log();
		break;
	case 2:
		reg();
		break;
	case 3:
		exit(0);
	default:
		break;
	}
}

Program::~Program()
{
	user_list.clear();
	for (size_t i = sect_list.getSize()-1; i <=0 ; i++)
	{
		for (size_t j = 0; j < sect_list[i].Sub_list.getSize(); j++)
		{
			sect_list[i].Sub_list[j].Q_list.clear();
		}
		sect_list[i].Sub_list.clear();
	}
	sect_list.clear();
}

inline void Program::resaveData()
{
	ofstream fout(User_data);
	for (size_t i = 0; i < user_list.getSize(); i++)
	{
		fout.clear();
		saveUser(user_list[i]);
		fout.close();
	}
}

inline void Program::print(User u)
{
	cout << "Login:" << u.Login << "\n";
	cout<<"name: "		<< u.name << " "<< u.sername << "\n";
	cout <<"E-mail: "	<< u.mail << "\n";
	cout <<"number: "	<< u.number<<"\n";
}

inline void Program::addTask()
{
	system("cls");
	cout << "1.Section\n2.Subject\n3.Question\n4.menu\n";
	int ch;
	cin >> ch;
	int itSect = -1;
	int itSub = -1;
	switch (ch)
	{
	case 1:
		addSection();
		break;
	case 2:

		addSubject();
		break;
	case 3:
		
		addQuestion();
		break;
	case 4:
		menu();
	default:
		break;
	}
}

inline void Program::addSection()
{
	system("cls");
	
	for (size_t i = 0; i < sect_list.getSize(); i++)
	{
		cout << sect_list[i].SectName<<"\n";
	}
	Section S;
	cin >> S.SectName;
	sect_list.push_back(S);
	saveSubjectList();
	cout << "\n1.Add one more Section\n2.Add Subject\n3.Exit\n";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		addSection();
		break;
	case 2:
		addSubject();
	case 3:
		addTask();
	default:
		break;
	}
}

inline void Program::addSubject()
{
	system("cls");
	int it;
	cout << "choose\n";
	do
	{
		for (size_t i = 0; i < sect_list.getSize(); i++)
		{
			cout << i + 1 << sect_list[i].SectName << "\n";
		}
	cin >> it;
	it--;
	} while (it<0 or it>sect_list.getSize());
	for (size_t i = 0; i < sect_list[it].Sub_list.getSize(); i++)
	{
		cout << sect_list[it].Sub_list[i].SubjName << "\n";
	}
	cout << "Enter name of subject\n";
	Subject sub;
	cin.ignore();
	getline(cin, sub.SubjName);
	sect_list[it].Sub_list.push_back(sub);
	saveSubjectList();
	cout << "\n1.Add one more Subject\n2.add other Section\n3.AddQuestion\n4.Exit";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		addSubject();
		break;
	case 2:
		addSection();
	case 3:
		addQuestion();
	case 4:
		addTask();
	default:
		break;
	}
}

inline void Program::addQuestion()
{
	system("cls");
	cout << "choose\n";
	for (size_t i = 0; i < sect_list.getSize(); i++)
	{
		cout << i + 1 << sect_list[i].SectName << "\n";
	}
	int itSect;
	cin >> itSect;
	itSect--;
	if (!sect_list[itSect].Sub_list.isEmpty())
	{
		for (size_t i = 0; i < sect_list[itSect].Sub_list.getSize(); i++)
		{
			cout << i + 1 << sect_list[itSect].Sub_list[i].SubjName << "\n";
		}
		int itSub;
		cin >> itSub;
		itSub--;
		cout << "Enter Question \n";
		Question Q;
		cin.ignore();
		getline(cin, Q.aText);

		cout << "Enter Answer options\n";
		string Ao;
		getline(cin, Ao);
		Q.aText = Q.aText + "|" + Ao;
		cout << "Enter right Answer\n";
		cin >> Q.rightAnswer;
		sect_list[itSect].Sub_list[itSub].Q_list.push_back(Q);
		saveQuestion(itSect, itSub);
	}
	else
		cout << "Subject list is empty\n";
	
	

	cout << "\n1.Add one more Question\n2.Exit";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		addQuestion();
	case 2:
		addTask();
	case 3:
		
	default:
		break;
	}
}

inline void Program::saveSubjectList()
{
	ofstream fout(Subj_file);
	if (fout.is_open())
	{
		for (size_t i = 0; i < sect_list.getSize(); i++)
		{
			if (i != 0)
				fout << "\n";
			fout << "1 ";
			fout <<sect_list[i].SectName;
			for (size_t j = 0; j <sect_list[i].Sub_list.getSize() ; j++)
			{
				fout << "\n";
				fout << "2 ";
				fout << sect_list[i].Sub_list[j].SubjName;
			}
		}
	}
	fout.close();
}

inline void Program::saveQuestion(int sec, int subj)
{
	QuestionFileName =sect_list[sec].Sub_list[subj].SubjName + "_Q.txt";
	ofstream ofs(QuestionFileName);
	if (ofs.is_open())
	{
		for (size_t i = 0; i < sect_list[sec].Sub_list[subj].Q_list.getSize(); i++)
		{
			if (i != 0)
				ofs << "\n";
			ofs << sect_list[sec].Sub_list[subj].Q_list[i].aText << " $ " << sect_list[sec].Sub_list[subj].Q_list[i].rightAnswer;
		}
		
	}

	ofs.close();

}

inline void Program::loadQuestion(int sec, int subj)
{
	QuestionFileName = sect_list[sec].Sub_list[subj].SubjName + "_Q.txt";
	ifstream ifQ(QuestionFileName);
	int i = 0;
	if (ifQ.is_open())
	{
		do
		{
			i++;
			Question Q;
			string B;
			string a;
			string d;
			do
			{
				a = a + B + " ";
				ifQ >> B;
			} while (B != "$");
			ifQ >> d;
			a.pop_back();
			a.erase(0, 1);
			Q.aText = a;
			Q.rightAnswer = d;
			Q.QuNumber = i;
			sect_list[sec].Sub_list[subj].Q_list.push_back(Q);
		} while (!ifQ.eof());
		
	}
	ifQ.close();
}

inline void Program::go_test(int itSect,int itSub,int RightQ,int ActAnsw)
{
	
	int RA=0;
	RA = RightQ;
	if (!sect_list[itSect].Sub_list[itSub].Q_list.isEmpty())
	{
		for (size_t i = ActAnsw; i < sect_list[itSect].Sub_list[itSub].Q_list.getSize(); i++)
		{
			system("cls");
			cout << "Enter ""EXIT"" if you want to exit\n\n";
			cout << "\t\tQuestion " << i + 1 << "\n";
			cout << sect_list[itSect].Sub_list[itSub].Q_list[i].aText << "\n";
			cout << "Your Answer: ";
			string Myanswer;
			cin >> Myanswer;
			if (Myanswer == "EXIT")
				menu();
			for (size_t j = 0; j < Myanswer.size(); j++)
			{
				if (Myanswer[j] > 64 and Myanswer[j] < 91)
					Myanswer[j] = Myanswer[j] + 32;
				//если в ответе есть буквы в верхнем регистре они будут изменены на буквы в нижнем
			}
			for (size_t j = 0; j < sect_list[itSect].Sub_list[itSub].Q_list[i].rightAnswer.size(); j++)
			{
				if (sect_list[itSect].Sub_list[itSub].Q_list[i].rightAnswer[j] > 64 and sect_list[itSect].Sub_list[itSub].Q_list[i].rightAnswer[j] < 91)
					sect_list[itSect].Sub_list[itSub].Q_list[i].rightAnswer[j] = sect_list[itSect].Sub_list[itSub].Q_list[i].rightAnswer[j] + 32;
				//если в правильном ответе есть буквы в верхнем регистре они на нижний мен€ютс€
			}
			if (Myanswer == sect_list[itSect].Sub_list[itSub].Q_list[i].rightAnswer)
			{
				cout << "Right\n";
				RA++;
			}
			else
			{
				cout << "wrong\n";
			}
			string CacheFilename = user_list[ID].Login + "Cache.txt";
			ofstream fout(CacheFilename);
			fout << itSect << " " << itSub << " " << RA << " ";
			if (i != sect_list[itSect].Sub_list[itSub].Q_list.getSize() - 1)
				fout << i + 1;
			else
				fout << 0;
			fout.close();
			Sleep(500);
		}
		int mark;
		mark = (12 / sect_list[itSect].Sub_list[itSub].Q_list.getSize()) * RA;
		if (mark == 0)
			mark = 1;
		int markInPec;
		markInPec = 100 / sect_list[itSect].Sub_list[itSub].Q_list.getSize() * RA;
		save_stat(itSect, itSub, mark, RA, markInPec);
		cout << "DONE your mark is: " << mark << "\n";
	
	}
	else
	{
		cout << "Question list is empty\n";
		system("pause");
		menu();
	}

	system("pause");
}

inline void Program::save_stat(int sec, int subj, int mark, int col,int pec)
{
	string StatisticFilename = user_list[ID].Login + "_Stat.txt";
	ofstream fout(StatisticFilename,ios::app);
	fout << __DATE__ << "\t" << __TIME__
		<< "\n" << "===============================\n"
		<< "!!" << sect_list[sec].SectName << "\n"
		<< "->" << sect_list[sec].Sub_list[subj].SubjName << "\n"
		<< "-------------------------------\n"
		<< "\tMark: " << mark << "\n"
		<< "amount of right answers: " << col << " | " << pec << "%\n"
		<< "_______________________________\n"
		<< "-------------------------------\n\n\n";
	fout.close();

}

inline void Program::MyStat()
{
	string StatisticFilename = user_list[ID].Login + "_Stat.txt";
	ifstream fin(StatisticFilename);
	cout << "\n";
	do
	{
		string a;
		getline(fin, a);
		cout << a<<"\n"	;
	} while (!fin.eof());
	fin.close();
	cout << "\nEnter any button to comebeck\n";
	system("pause");
}

inline void Program::AdminStat()
{
	cout << "\n1.All stat\n2.Stat of target user\n3.Exit";
	int ch=0;
	do
	{
		cin >> ch;
		switch (ch)
		{
		case 1:
			AllStat();
			break;
		case 2:
			TargetStat();
			break;
		case 3:
			menu();
		default:
			break;
		}

	} while (true);

}

inline void Program::AllStat()
{
	system("cls");
	string FullStat;

	for (size_t i = 1; i < user_list.getSize(); i++)
	{
		string StatisticFilename = user_list[i].Login + "_Stat.txt";
		ifstream fin(StatisticFilename);
		if (fin.is_open())
		{
			cout << "\n";
			string a= "======================================\n\t" + user_list[i].Login+ "\n" + user_list[i].name + "\t" + user_list[i].sername+"\n======================================\n";
			do
			{
				FullStat = FullStat + a+"\n";
				getline(fin, a);
				
			} while (!fin.eof());
			fin.close();
		}

	}
	cout << FullStat;
	cout << "\n1.Save in file\n2.Exit";
	int ch=0;
	string FullStat_Filename= "FullStat_Filename.txt";
	ofstream fout(FullStat_Filename);
	do
	{
		cin >> ch;
		switch (ch)
		{
		case 1:
			fout << FullStat;
			fout.close();
			AdminStat();
		case 2:
			AdminStat();
		default:
			break;
		}
	} while (true);
}

inline void Program::TargetStat()
{
	system("cls");	
	for (size_t i = 1; i < user_list.getSize(); i++)
	{
		cout << i<<" "<<user_list[i].Login<<"\n";
	}
	int ch;
	string Stat;
	do
	{
		cin >> ch;
		if (ch>=1 and ch<user_list.getSize())
		{
			string StatisticFilename = user_list[ch].Login + "_Stat.txt";
			ifstream fin(StatisticFilename);
			string a;

			if (fin.is_open())
			{
				do
				{
					Stat = Stat + a + "\n";
					getline(fin, a);

				} while (!fin.eof());
				fin.close();
				break;

			}
			else
			{
				cout << "this User hasn't pass any exams\n";
				break;
			}

		}
	
	} while (true);
	
	cout << Stat;
	
	system("pause");
	AdminStat();
}

inline void Program::change()
{
	system("cls");
	cout << "\What do whant to change?\n1.Login\n2.Password\n3.exit\n";
	int ch;
	do
	{
		cin >> ch;
		switch (ch)
		{
		case 1:
			changeLogin();
			break;
		case 2:
			changePassword();
			break;
		case 3:
			menu();
		default:
			break;
		}
		resaveData();
	} while (true);
}

inline void Program::changeLogin()
{
	system("cls");
	cout << "\nEnter new login\n";
	cin >> user_list[ID].Login;
	system("pause");
	
}

inline void Program::changePassword()
{
	system("cls");
	
	string newpass1;
	string newpass2;
	do
	{
		cout << "\nEnter new password\n";
		cin >> newpass1;
		cout << "Confirm your password\n";
		cin >> newpass2;
		if (newpass1!= newpass2)
		{
			cout << "passwords are different\n";
		}
		else
		{
			break;
		}
	} while (true);
	hash<string> h;
	user_list[ID].password = h(newpass1);
	system("pause");
}
