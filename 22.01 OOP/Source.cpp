#include <iostream> 
#include <fstream>
using namespace std;
class  Game {
public:
	enum class Category {
		SHOOTER,
		RACE,
		SURVIVAL,
		UND
	};
private:

	static const int str_size=255;
	char name[str_size];
	int popularity;
	Category category;
public:
	
	Game(const char * name="NoName",const int& popularity=0,const Category& category=Category::UND)
		:popularity(popularity),category(category)
	{
		if ((strlen(name)+1)==0 || (strlen(name) + 1)> 255)
		{
			throw "Incorrect strlen";
		}
		strcpy_s(this->name, strlen(name) + 1, name);
		this->category = category;
	}
	void print()const{
		cout <<"NAME: "<< name << endl;
		cout <<"POPULARITY: "<< popularity << endl;
		cout << " CATEGORY : ";
		switch ((int)category)
		{
		case 0:
			cout << "Shooter" << endl;
			break;
		case 1:
			cout << "Race" << endl;
			break;
		case 2:
			cout << "Survival" << endl;
			break;
		default:
			cout << "UND" << endl;
			break;
		}
		

	}
	string getName() const {
		return name;
	}
	const int getCategory() const{
		return (int)category;
	}
};
class ReadingGame {
public:
	static void readAllGames(const string& fname)
	{
		Game value, temp;
		ifstream in(fname, ios_base::binary);// | ios_base::in);
		if (!in)
		{
			/*cerr << "Error opening for reading\n";

			return 0;*/
			throw exception("Error opening file for read");
		}
		//in.seekg(0, ios_base::end);
		//int  amount = in.tellg() / sizeof(int); // tellg() 


		//cout << "Test amount : " << amount << endl;
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			//	cout << "Needed to print" << endl;
			value.print();

			in.read(reinterpret_cast<char*>(&value), sizeof(Game));


		}

	}
	static void newGame(const Game& value, const string& fname)
	{
		ofstream out(fname, ios_base::binary | ios_base::app);
		if (!out)
		{
			cerr << "Error opening for writing\n";
			return;
		}

		//out << value << endl; // text format:  -1234554445;      binary    [.][.][.][.]  raw value
		out.write((char*)&value, sizeof(Game));
		out.close(); // not  need
	}
	static void findGame(const string& name, const string& file_path) {
		Game value, temp;
		ifstream in(file_path, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getName() == name)
			{
				cout << "You game with name " << name << " is Have in list" << endl;
				return;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
		cout << "Your game haven`t " << endl;
	}
	static void findNameOfCategory(const int category, const string& file_path) {
		if (category > 3 || category < 0)
		{
			cout << "Incorrect category" << endl;
			return;
		}
		Game value, temp;
		ifstream in(file_path, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getCategory() == category)
			{
				cout << "You game with your category have name : " << value.getName() << endl;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
		cout << "Haven`t game with your category" << endl;
	}
	static void editGameWithName(const string& name, const string& file_path) { // work only for game with first same name in list
		Game value, temp;
		int index = -1;
		ifstream in(file_path, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getName() == name)
			{
				cout << "You game with your category have name : " << value.getName() << endl;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
			++index;
		}
		cout << "Haven`t game with your category" << endl;
	}
	static void deleteFirstGameWithName(const string&name , const string& file_path) {
		Game value, temp;
		vector<string> lines;
		ifstream in(file_path, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getName() == name)
			{
				cout << "You game with name " << name << " is Have in list" << endl;
				return;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
		cout << "Your game haven`t " << endl;
	}
	}
};
int main() {
	Game game("CS:GO",200000,Game::Category::SHOOTER);
	ReadingGame::newGame(game,"game.dat");
	ReadingGame::newGame(game,"game.dat");
	ReadingGame::newGame(game,"game.dat");
	ReadingGame::readAllGames("game.dat");
	ReadingGame::findGame("CS:GO","game.dat");
	ReadingGame::findNameOfCategory(0,"game.dat");
	//game.print();
	//cout << sizeof(Game);
	return 0;
}