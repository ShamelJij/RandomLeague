#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <iomanip>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;
//
//bool fncomp(char lhs, char rhs) { return lhs < rhs; }
//
//struct classcomp {
//	bool operator() (const char& lhs, const char& rhs) const
//	{
//		return lhs < rhs;
//	}
//};
//
//int main()
//{
//	std::map<char, int> first;
//
//	first['a'] = 10;
//	first['b'] = 30;
//	first['c'] = 50;
//	first['d'] = 70;
//
//	std::map<char, int> second(first.begin(), first.end());
//
//	std::map<char, int> third(second);
//
//	std::map<char, int, classcomp> fourth;                 // class as Compare
//
//	bool(*fn_pt)(char, char) = fncomp;
//	std::map<char, int, bool(*)(char, char)> fifth(fn_pt); // function pointer as Compare
//
//	std::cout << third << endl;
//
//	return 0;
//}

//std::vector<int> make_vector(int a, int b) {
//    std::vector<int> result;
//    result.push_back(a);
//    result.push_back(b);
//    return result;
//}
//
//int main()
//
//{
//
//    map <int, vector<int> > mymap;
//
//    mymap.insert(make_pair(10, make_vector(1, 2)));
//    // Or, alternatively:
//    //   mymap[10] = make_vector(1,2);
//
//    assert(mymap[10][0] == 1);
//    assert(mymap[10][1] == 2);
//
//    cout << map << endl;
//
//    return 0;
//}

class Player {
    public:
		string _firstName;
		string _lastName;
		int _skills;
		int _price;
        int _index;
        int _scoringChance;

        // _B am ende..

        void assignNumber(int number) {
            _number = number;
        }

		void display() {
            cout << "Team member no: " << _index << " First name: " 
                 << _firstName << " Last name: " << _lastName ;
		}

        string name() {
            return _firstName + " " + _lastName;
        }

private:
    int _number;

};

class Game {
public :
    Player _team1[12];
    Player _team2[12];
    void play() {
        int team1Score = 0;
        int team2Score = 0;
        for (int i = 0; i < 12; i++) {
            team1Score = team1Score + _team1[i]._scoringChance;
            team2Score = team2Score + _team2[i]._scoringChance;
        }

        team1Score = team1Score / 2;
        team2Score = team2Score / 2;

        if (team1Score > team2Score) {
            cout << "\n\n!!!! Team 1 Won !!!!\n\n" << endl;
            cout << "Team 1: " << team1Score << "\nTeam 2: " << team2Score << "\n\n"<< endl;
        } else if (team1Score < team2Score) {
            cout << "\n\n!!!! Team 2 Won !!!!\n\n" << endl;
            cout << "Team 1: " << team1Score << "\nTeam 2: " << team2Score << "\n\n" << endl;
        } else {
            cout << "\n\n!!!! Draw !!!!\n\n" << endl;
            cout << "Team 1: " << team1Score << "\nTeam 2: " << team2Score << "\n\n" << endl;
        }
    }

    void displayTeams() {
        cout << left << setw(40) << setfill(' ') << "Team 1";
        cout << left << setw(40) << setfill(' ') << "Team 2\n\n";
        cout << endl;
        for (int i = 0; i < 12; i++) {
            cout << left << setw(40) << setfill(' ') << _team1[i].name();
            cout << left << setw(40) << setfill(' ') << _team2[i].name();
            cout << endl;
        }
    }
};

class Randomizer {
public:
    int generateRandomNamber() {
        return _min + rand()%(_max - _min + 1);
        
    };

    Randomizer(int min, int max) {
        _min = min;
        _max = max;
    };
private :
    int _min;
    int _max;
};

static void displayHeader() {
    cout << "****************************************" << endl;
    cout << "* ((:  Welcome to Random League   :))  *" << endl;
    cout << "****************************************\n\n" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    string inputFileName;
    string outputFileName;
    ifstream fileIn;
    ofstream fileOut;

    map<int, Player> _players;

    displayHeader();
    cout << "enter players file name: ";
    string fileName;
    cin >> fileName;
    fileIn.open(fileName);

    string line;
    while (std::getline(fileIn, line)) {
        stringstream ss(line);
        Player player;
        //int index;
        ss >> player._index;
        ss >> player._firstName;
        ss >> player._lastName;

        player._skills = 100;
        player.assignNumber(12);
        _players[player._index] = player;
    }
    fileIn.close();


    int choice = 0;
    while (choice != 9) {
        system("CLS");
        displayHeader();
        cout << "1. play game\n" << endl;
        cout << "2. enter players file name\n" << endl; //exception werfen
        cout << "9. exit\n" << endl;
        cout << "Please choose: ";
        cin >> choice;

        if (choice == 1) {
            Game game;
            Randomizer _randomizer(1, _players.size());
            Randomizer _scoreRand(0, 1);

            for (int i = 0; i < 12; i++) {
                game._team1[i] = _players[_randomizer.generateRandomNamber()];
                game._team2[i] = _players[_randomizer.generateRandomNamber()];
                game._team1[i]._scoringChance = _scoreRand.generateRandomNamber();
                game._team2[i]._scoringChance = _scoreRand.generateRandomNamber();
            }
            game.displayTeams();
            game.play();
            system("pause");
        }
        else if (choice == 9) {
            exit(0);
        }
        else if (choice == 2) {
            system("CLS");
            displayHeader();
            cout << "enter players file name: ";
            string fileName;
            cin >> fileName;
            fileIn.open(fileName);

            _players.clear();

            string line;
            while (std::getline(fileIn, line)) {
                stringstream ss(line);
                Player player;
                //int index;
                ss >> player._index;
                ss >> player._firstName;
                ss >> player._lastName;

                player._skills = 100;
                player.assignNumber(12);
                _players[player._index] = player;
            }
            fileIn.close();
        }
    }
}
