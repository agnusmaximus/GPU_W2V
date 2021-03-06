#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <deque>

using namespace std;

#define WINDOW 20
#define LIMIT -1

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    map<int, map<int, int> > graph;
    map<string, int> word_to_id;
    deque<int> window;
    string cur_word;
    int id_count = 1;
    int iteration = 0;
    int n_edges = 0;
    while (in >> cur_word) {
	if (LIMIT >= 0 && iteration >= LIMIT) break;
	iteration++;
	if (word_to_id.find(cur_word) == word_to_id.end()) {
	    word_to_id[cur_word] = id_count++;
	}
	int id = word_to_id[cur_word];
	if (window.size() >= WINDOW) {
	    window.pop_front();
	}
	for (int i = 0; i < window.size(); i++) {
	    if (id != window[i]) {
		graph[id][window[i]]++;
		graph[window[i]][id]++;
	    }
	}
	window.push_back(id);
    }
    ofstream out_map("word_id_map");
    for (auto const &x : word_to_id) {
	out_map << x.first << " " << x.second << endl;
    }
    out_map.close();
    in.close();
    ofstream out(argv[2]);
    string output = "";
    for (int i = 1; i < id_count; i++) {
	for (auto const &x : graph[i]) {
	    output += to_string(x.first) + " " + to_string(x.second) + " ";
	    n_edges++;
	}
	output += "\n";
    }
    cout << n_edges << endl;
    out << id_count-1 << " " << n_edges/2 << " " << "001" << endl;
    out << output << endl;
    out.close();
}
