#include "library.h"
void library::print(vector<string> txt, int n)
{
	for (int i = 0; i < txt.size(); i += n)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(12) << txt[i + j];
		}
		cout << endl;
	}

}
void library::EnterBook()
{
	fstream out;
	string  book_name, book_author;

	out.open("book.txt", ios::app);
	if (!out)
	{
		cout << "檔案讀取失敗" << endl;
	}

	time_t book_id = time(0);

	cout << "輸入書籍名稱" << endl;
	cin >> book_name;
	cout << "輸入作者名稱" << endl;
	cin >> book_author;

	out << book_id << " " << book_name << " " << book_author << " " << "O" << "\n";
	out.close();
}
void library::ShowBook()
{
	fstream in;
	string line, temp;
	vector<string> txt;



	in.open("book.txt", ios::in);
	if (!in)
	{
		cout << "讀取檔案失敗" << endl;
	}
	while (getline(in, line))
	{

		stringstream input(line);
		while (input >> temp)
		{

			txt.push_back(temp);
		}
	}

	cout << setw(12) << "書籍編號" << " " << setw(12) << "書籍名稱" << " " << setw(12) << "書籍作者" << " " << setw(12)<<"    在館O,不在館X" << " " << endl;
	print(txt, 4);
	in.close();
}
void library::EnterMember()
{
	fstream out;
	string  member_name, member_sex;
	int sex;
	out.open("member.txt", ios::app);
	if (!out)
	{
		cout << "檔案讀取失敗" << endl;
	}
	time_t member_id = time(0);
	cout << "輸入會員名稱: " << endl;
	cin >> member_name;
	cout << "輸入會員性別 0是女 1是男" << endl;
	do
	{
		cin >> sex;
		if (sex == 0)
		{
			member_sex = "女";
			break;
		}
		else if (sex == 1)
		{
			member_sex = "男";
			break;
		}
		cout << "請輸入正確性別: "<<endl;
	} while (sex != 0 && sex != 1);
	out << member_id << " " << member_name << " " << member_sex <<"\n";
	out.close();
}
void library::ShowMember()
{
	fstream in;
	vector<string> txt;
	string line, temp;
	in.open("member.txt", ios::in);
	if(!in)
	{
		cout<<"檔案讀取失敗" << endl; 
	}
	while (getline(in,line))
	{
		stringstream input(line);
		while (input >> temp)
		{
			txt.push_back(temp);
		}
		
	}
	cout << setw(12) << "會員編號" << " " << setw(12) << "會員名稱" << " " << setw(12) << "會員性別" << " " << endl;
	print(txt, 3);
	in.close();
}
void library::BorrowBooks()
{
	fstream in;
	vector<string> txt;
	string line, temp;
	string borrowBooks, member_id;
	string books[4], member[3];
	bool bookflag = false; 
	in.open("book.txt", ios::in);
	if (!in)
	{
		cout << "'檔案讀取失敗" << endl;
	}
	cout << "請輸入要借閱的書籍ID: ";
	cin >> borrowBooks;
	while (getline(in, line))
	{

		stringstream input(line);
		lock = 0;
		while (input>>temp)
		{
			if ((borrowBooks == temp) && (lock == 0))
			{
				books[0] = temp;
				txt.push_back(temp);
				for (int i=1; i < 3; i++)
				{
					input >> temp;
					books[i] = temp;
					txt.push_back(temp);
				}
				input >> temp;
				if (temp == "O")
				{
					books[3] = "X";
					bookflag = true;
				}
				else if (temp == "X")
				{
					cout << "此書本已出借" << endl;
					return;
				}
				
			}
			lock++;
			txt.push_back(temp);
		}
	}
	in.close();

	if (!bookflag)
	{
		cout << "錯誤書籍ID" << endl;
		return;
	}

	in.open("member.txt", ios::in);

	if (!in)
	{
		cout << "讀取檔案失敗" << endl;
	}

	cout << "請輸入會員編號ID: " << endl;
	cin >> member_id;

	while (getline(in, line))
	{
		lock = 0;
		stringstream input(line);
		while (input >> temp)
		{
			if ((member_id == temp) && (lock == 0))
			{
				member[0] = temp;
				for (int i = 1; i < 3; i++)
				{
					input >> temp;
					member[i] = temp;
				}
				lock++;
			}
		}
	}
	in.close();

	fstream out;
	out.open("book.txt", ios::out);
	if (!out)
	{
		cout << "檔案讀取失敗" << endl;
	}

	for(int i=0;i<txt.size();i+=4)
		{
			if (txt[i] == borrowBooks)
			{
				txt[i + 3] = "X";
			}
			out << txt[i] << " " << txt[i + 1] << " " << txt[i + 2] << " " << txt[i + 3] << " " << endl;
		}
	out.close();

	out.open("borrowBooks.txt", ios::app);
	if (!out)
	{
		cout << "檔案讀取失敗" << endl;
	}
	out << member[0] << " " << member[1] << " " << books[1] << " "<<"已借出"<<"\n";
	out.close();



}
void library::ReturnBooks()
{
	fstream in;
	vector<string> txt;
	string line, temp, member_id;
	string ReturnBooks;
	string books[4], member[3];
	bool bookflag = false;
	in.open("book.txt", ios::in);
	if (!in)
	{
		cout << "'檔案讀取失敗" << endl;
	}
	cout << "請輸入要還的書籍ID: ";
	cin >> ReturnBooks;
	while (getline(in, line))
	{
		stringstream input(line);
		lock = 0;
		while (input >> temp)
		{
			if ((ReturnBooks == temp) && (lock == 0))
			{
				books[0] = temp;
				txt.push_back(temp);
				for (int i = 1; i < 3; i++)
				{
					input >> temp;
					books[i] = temp;
					txt.push_back(temp);
				}
				input >> temp;
				if (temp == "X")
				{
					books[3] = "O";
					bookflag = true;
				}
				else if (temp == "O")
				{
					cout << "此書本已歸還" << endl;
					return;
				}

			}
			lock++;
			txt.push_back(temp);
		}
	}
	in.close();

	if (!bookflag)
	{
		cout << "錯誤書籍ID" << endl;
		return;
	}

	in.open("member.txt", ios::in);

	if (!in)
	{
		cout << "讀取檔案失敗" << endl;
	}

	cout << "請輸入會員編號ID: " << endl;
	cin >> member_id;

	while (getline(in, line))
	{
		lock = 0;
		stringstream input(line);
		while (input >> temp)
		{
			if ((member_id == temp) && (lock == 0))
			{
				member[0] = temp;
				for (int i = 1; i < 3; i++)
				{
					input >> temp;
					member[i] = temp;
				}
				lock++;
			}
		}
	}
	in.close();

	fstream out;
	out.open("book.txt", ios::out);
	if (!out)
	{
		cout << "檔案讀取失敗" << endl;
	}

	for (int i = 0; i < txt.size(); i += 4)
	{
		if (txt[i] == ReturnBooks)
		{
			txt[i + 3] = "O";
		}
		out << txt[i] << " " << txt[i + 1] << " " << txt[i + 2] << " " << txt[i + 3] << " " << endl;
	}
	out.close();

	out.open("ReturnBooks.txt", ios::app);
	if (!out)
	{
		cout << "檔案讀取失敗" << endl;
	}
	out << member[0] << " " << member[1] << " " << books[1] << " " << "已歸還" << "\n";
	out.close();
}
