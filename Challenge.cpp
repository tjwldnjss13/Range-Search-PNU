#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <unordered_map>
#include "RangeSearch.h"
using namespace std;

void print_time(double sec) {
	if (sec < 60)		cout << sec << "s" << endl;
	else if (sec < 60 * 60) {
		time_t min = 0;

		while (sec >= 60) {
			sec -= 60;
			min++;
		}

		cout << min << "m " << sec << "s" << endl;
	}
	else {
		time_t hour = 0, min = 0;

		while (sec >= 60 * 60) {
			sec -= 60 * 60;
			hour++;
		}

		while (sec >= 60) {
			sec -= 60;
			min++;
		}

		cout << hour << "h " << min << "m " << sec << "s" << endl;
	}
}


int main() {

	string fn = "pin_1.txt";
	ifstream in(fn);

	if (!in.is_open()) {
		cout << "파일을 읽을 수 없습니다 :(" << endl;

		return 0;
	}

	unordered_map<int, Point> table;
	RedBlackTreePnt range_tree_x(0);
	vector<string> tokens;
	pair<int, int> query_result;

	//time_t start, end;
	chrono::system_clock::time_point start, end;

	stringstream ss;
	string line;
	string token;
	Point pnt;
	int line_cnt = 0;
	int N_insert = 0;
	int N_delete = 0;
	int N_query = 0;
	int N_search_success = 0;
	int N_actual_delete = 0;
	int radius;
	int index;

	int iter = 0;

	start = chrono::system_clock::now();
	while (in.is_open() && !in.eof() && iter++ < 40) {
		cout << "[" << ++line_cnt << "]" << endl;

		tokens.clear();
		getline(in, line);

		//cout << line << endl;
		ss.clear();
		ss.str(line);

		while (ss >> token)		tokens.push_back(token);



		if (tokens[0] == "+") {
			N_insert++;
			index = stoi(tokens[1]);
			pnt.x = stoi(tokens[2]);
			pnt.y = stoi(tokens[3]);

			table.insert(unordered_map<int, Point>::value_type(index, pnt));

			range_tree_x.rb_insert_x(index, pnt);

			//range_tree_x.print_tree();
			//cout << "------------------------------------------------------------------------" << endl;

			if (range_tree_x.rb_search_x(pnt) != NULL)
				N_search_success++;
		}
		else if (tokens[0] == "-") {
			N_delete++;
			// 보류
		}
		else if (tokens[0] == "?") {

			//cout << "-----------------------------------------------------------------------------" << endl;
			//range_tree_x.print_tree();


			N_query++;
			pnt.x = stoi(tokens[1]);
			pnt.y = stoi(tokens[2]);
			radius = stoi(tokens[3]);

			range_tree_x.print_points();

			query_result = range_search(range_tree_x, pnt, radius);
			cout << query_result.first;
			if (query_result.first > 0)		cout << " " << query_result.second << endl;
			cout << endl;
		}

	}

	in.close();

	end = chrono::system_clock::now();

	chrono::duration<double> sec = end - start;

	print_time(sec.count());

}

