#pragma once
#include <string>
#include <iostream>
#include <list>
#include "players.h"
#include "point.h"
#include "screen.h"
using namespace std;

namespace nullsAndCrosses {
	static const int MAX_RECOMENDED_SIZE_OF_FIELD = 35;
	/// ����� �������������� � �������������
	class Dialog {
		static bool yn_handling() {
			string yn_in;
			bool yn_out;
			cin >> yn_in;
			if (!stringToBool(yn_in, yn_out)) {
				cout << "Wrong input. You should print y or n. Try again." << endl;
				return yn_handling();
			}
			return yn_out;
		}
		/// ���������� ������ ��������
		static bool stringToChar(const string in, char &out) {
			if (in.length() > 1)
				return false;
			out = in.at(0);
			return true;
		}
		/// ���������� ������ ��������
		static bool stringToInt(string in, int &out) {
			out = 0;
			for (int i = 0; i < in.length(); i++) {
				if (in.at(i) > '9' || in.at(i) < '0')
					return false;
				out *= 10;
				out += in.at(i) - '0';
			}
			return true;
		}
		/// ���������� ������ ��������
		static bool stringToBool(string in, bool &out) {
			if (in.length() > 1)
				return false;
			if (in.at(0) == 'y') {
				out = true;
				return true;
			}
			if (in.at(0) == 'n') {
				out = false;
				return true;
			}
			return false;
		}
		static string askPlayers_name() {
			string name;
			cout << "Print your name." << endl;
			cin >> name;
			return name;
		}
		static char askPlayers_symbol() {
			string symbol;
			char symbolC;
			cout << "Print your symbol." << endl;
			cin >> symbol;
			if (!(stringToChar(symbol, symbolC))) {
				cout << "Wrong input. You should print symbol." << endl;
				return askPlayers_symbol();
			}
			return symbolC;
		}
		static bool askPlayers_ifWantAddNew() {
			string in;
			bool out;
			cout << "Would you like to add more players?" << endl;
			return yn_handling();
		}
		static void playerWins(string name, bool noOne) {
			if (noOne) {
				cout << "Draw!" << endl;
				return;
			}
			cout << name << " wins!" << endl;
		}
	public:
		/// ������ ���������� �� �������
		static list <Player> askPlayersInfo() {
			Screen::clear();
			list <Player>(players);
			string name;
			char symbol;
			do {
				do {
					name = askPlayers_name();
				} while (OperationsWithListOfPlayers::isNameContain(players, name));
				do {
					symbol = askPlayers_symbol();
				} while (OperationsWithListOfPlayers::isSymbolContain(players, symbol));
				players.push_back(Player(name, symbol));
			} while (askPlayers_ifWantAddNew());
			return players;
		}
		/// �������� ����� �� ������ ����� ����
		static bool askStartNewOrNo() {
			cout << "Would you like to start new game? (y/n)" << endl;
			return yn_handling();
		}
		/// ���������� ���� � ��������� ���������� ������ �������
		static Point askNewSymbolCoord(string name) {
			// �� ������� �����, ����� �� ������� ����������� ����
			string x_in, y_in;
			int x_out, y_out;
			cout << name << ", where do you prefer to put symbol? (x, y)" << endl;
			cin >> x_in >> y_in;
			if (!stringToInt(x_in, x_out) || !stringToInt(y_in, y_out)) {
				cout << "Wrong input. You should print coords of new point. Try again" << endl;
				return askNewSymbolCoord(name);
			}
			x_out--; // ������������ �������� � �������, � �� � ����
			y_out--;
			return Point(x_out, y_out);
		}
		/// �������� ������ ����
		static int askFieldSize() {
			string size_in;
			int size_out;
			cout << "What size of field would you prefer?" << endl;
			cin >> size_in;
			if (!stringToInt(size_in, size_out)) {
				cout << "Wrong input. You should print number. Try again." << endl;
				return askFieldSize();
			}
			if (size_out > MAX_RECOMENDED_SIZE_OF_FIELD) {
				cout << "Are you sure? It can be too large. (y/n)" << endl;
				if (!yn_handling())
					return askFieldSize();
			}
			return size_out;
		}
		/// �������� �����, ����������� ��� ������
		static int askWinComboSize() {
			int size_out;
			string size_in;
			cout << "What size of win-combo would you like?" << endl;
			cin >> size_in;
			if (!(stringToInt(size_in, size_out))) {
				cout << "Wrong input. You should print number. Try again." << endl;
				return askWinComboSize();
			}
			return size_out;
		}
		/// �������� ������ ��� �� ������� ������
		static char askEmptyCellSymbol() {
			char out;
			string in;
			cout << "What empty cell symbol would you prefer?" << endl;
			cin >> in;
			if (!(stringToChar(in, out))) {
				cout << "Wrong input. You should print symbol. Try again." << endl;
				return askEmptyCellSymbol();
			}
			return out;
		}
		/// ��������, ����� �� ������ ��������� � ���������
		static bool askChangingInfo() {
			cout << "Would you like to change some preferences? (y/n)" << endl;
			return yn_handling();
		}
		/// ������� ���������� ����
		static void printFinalResults(Field &field, string nameWinner, bool draw) {
			Screen::draw(field);
			playerWins(nameWinner, draw);
		}
	};
}