#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class FiniteAutomata {
private:
    vector<int> states;
    vector<char> input_symbols;
    int start_state;
    vector<int> accept_states;
    unordered_map<pair<int, char>, int, hash_pair> transition_table;

public:
    FiniteAutomata(const vector<int>& states, const vector<char>& input_symbols, int start_state, const vector<int>& accept_states, const unordered_map<pair<int, char>, int, hash_pair>& transition_table)
        : states(states), input_symbols(input_symbols), start_state(start_state), accept_states(accept_states), transition_table(transition_table) {}

    string validate_string(const string& input_string) {
        int current_state = start_state;

        for (char symbol : input_string) {
            if (find(input_symbols.begin(), input_symbols.end(), symbol) == input_symbols.end()) {
                return "Invalid String: Symbol not in input alphabet";
            }

            auto transition = make_pair(current_state, symbol);
            if (transition_table.find(transition) != transition_table.end()) {
                current_state = transition_table.at(transition);
            } else {
                return "Invalid String";
            }
        }

        if (find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end()) {
            return "Valid String";
        }
        return "Invalid String";
    }
};

int main() {
    int num_symbols;
    cout << "Number of input symbols: ";
    cin >> num_symbols;

    vector<char> input_symbols(num_symbols);
    cout << "Input symbols: ";
    for (int i = 0; i < num_symbols; ++i) {
        cin >> input_symbols[i];
    }

    int num_states;
    cout << "Enter number of states: ";
    cin >> num_states;

    vector<int> states(num_states);
    for (int i = 0; i < num_states; ++i) {
        states[i] = i + 1;
    }

    int start_state;
    cout << "Initial state: ";
    cin >> start_state;

    int num_accept_states;
    cout << "Number of accepting states: ";
    cin >> num_accept_states;

    vector<int> accept_states(num_accept_states);
    cout << "Accepting states: ";
    for (int i = 0; i < num_accept_states; ++i) {
        cin >> accept_states[i];
    }

    unordered_map<pair<int, char>, int, hash_pair> transition_table;
    cout << "Enter transition table (format: state_from symbol state_to). Type 'END' to stop: \n";

    cin.ignore(); // To clear the newline from the input buffer
    while (true) {
        string input;
        getline(cin, input);
        if (input == "END") {
            break;
        }

        istringstream iss(input);
        int state_from, state_to;
        char symbol;
        if (iss >> state_from >> symbol >> state_to) {
            transition_table[{state_from, symbol}] = state_to;
        } else {
            cout << "Invalid input format. Please use 'state_from symbol state_to' or 'END'.\n";
        }
    }

    string input_string;
    cout << "Input string: ";
    cin >> input_string;

    FiniteAutomata fa(states, input_symbols, start_state, accept_states, transition_table);
    cout << fa.validate_string(input_string) << endl;

    return 0;
}
