#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <map>
#include "RangeSearch.h"
using namespace std;

map<int, Point> TABLE;

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

	string in_fn = "pin_1.txt";
	string out_fn = "out_1.txt";
	ifstream in(in_fn);
	ofstream out(out_fn);


	if (!in.is_open()) {
		cout << "파일을 읽을 수 없습니다 :(" << endl;

		return 0;
	}

	RedBlackTreePnt range_tree_x(0);
	vector<string> tokens;
	pair<int, int> query_result;

	//time_t start, end;
	chrono::system_clock::time_point start, end;
	chrono::duration<double> sec;

	stringstream ss;
	string line;
	string out_line;
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
	int n = 144444;

	start = chrono::system_clock::now();
	while (in.is_open() && !in.eof() && iter++ < n) {
		//if (iter > 0 && iter % 1000 == 0)		cout << ".";

		cout << "[" << ++line_cnt << "]" << endl;

		tokens.clear();
		getline(in, line);

		//cout << line << endl;
		ss.clear();
		ss.str(line);

		while (ss >> token)		tokens.push_back(token);

		if (iter == 56350)
			cout << "Break point" << endl;
		

		if (tokens[0] == "+") {
			N_insert++;
			index = stoi(tokens[1]);
			pnt.x = stoi(tokens[2]);
			pnt.y = stoi(tokens[3]);

			//if (index == 93223)
				//cout << "Break point" << endl;

			TABLE.insert(make_pair(index, pnt));
			range_tree_x.rb_insert_x(index, pnt);

			//range_tree_x.print_tree();
			//cout << "------------------------------------------------------------------------" << endl;

			if (range_tree_x.rb_search_x(pnt) != NULL)
				N_search_success++;
		}
		else if (tokens[0] == "-") {
			N_delete++;
			index = stoi(tokens[1]);

			if (TABLE.find(index) != TABLE.end()) {
				N_actual_delete++;
				range_tree_x.rb_delete(TABLE.find(index)->second);
				TABLE.erase(index);
			}
		}
		else if (tokens[0] == "?") {
			N_query++;
			pnt.x = stoi(tokens[1]);
			pnt.y = stoi(tokens[2]);
			radius = stoi(tokens[3]);

			query_result = range_search(range_tree_x, pnt, radius);

			out_line = to_string(query_result.first);
			if (query_result.first > 0)
				out_line += " " + to_string(query_result.second);
			out_line += "\n";

			out << out_line;

			//cout << "[" << N_query << "] " << out_line;
		}

	}

	in.close();
	out.close();

	end = chrono::system_clock::now();
	sec = end - start;
	print_time(sec.count());

	range_tree_x.delete_tree();

	string opt_fn = "pout_1.txt";
	
	ifstream opt(opt_fn);
	ifstream my(out_fn);

	if (!opt.is_open()) {
		cout << "정답 파일을 읽을 수 없습니다 :(" << endl;

		return 0;
	}
	if (!my.is_open()) {
		cout << "내 결과 파일을 읽을 수 없습니다 :(" << endl;

		return 0;
	}

	int N_correct = 0;
	int N = 0;

	while ((opt.is_open() && !opt.eof()) && (my.is_open() && !my.eof())) {
		string opt_line, my_line;

		getline(opt, opt_line);
		getline(my, my_line);

		if (!opt_line.compare(my_line))
			N_correct++;
		N++;
	}

	opt.close();
	my.close();

	cout << "Correct answer : " << N_correct << " / " << N << endl;
	cout << "Accuracy : " << (float)N_correct / N << endl;;
}

