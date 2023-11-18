#pragma once

#include <bits/stdc++.h>

#ifdef ADIB_PC
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;


#ifdef _WIN32
#include <windows.h>    // for win32 API functions
enum Color { BLACK, GREY = 8, BLUE , GREEN, CYAN, RED, PURPLE, LIGHT_YELLOW, WHITE };
void setTextColor(Color color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#else // For Linux
enum Color { RED = 31, GREEN, BLUE = 34, WHITE = 37 };
void setTextColor(Color color)
{
    string s = "\033[0;" + to_string(color) + "m";
    cout << s;
}
#endif


struct ProcessState {
    int AT, BT, remaining, WT;
};

void print_divider(int n)
{
    cout << "+";
    for(int i = 0; i <= n; i++)
        cout << "----+";
    cout << "\n";
}
void print_top_column(int n)
{
    setTextColor(BLUE);
    cout << (char)178 + string(" ");
    setTextColor(WHITE);
    cout << "-> Waiting\n";

    setTextColor(GREEN);
    cout << (char)178 + string(" ");
    setTextColor(WHITE);
    cout << "-> Executing\n";
    
    setTextColor(RED);
    cout << (char)178 + string(" ");
    setTextColor(WHITE);
    cout << "-> Finished\n";

    print_divider(n);
    cout << "|Time|";
    for(int i = 0; i < n; i++)
        cout << setw(4) << left << " P"+to_string(i), cout << "|";
    cout << "\n";
    print_divider(n);
}

void print_current_state(vector<ProcessState> &states, int t, int indx)
{
    cout << "|";
    // setTextColor(BLUE);
    cout << setw(4) << left << " " + to_string(t);
    setTextColor(WHITE);
    cout << "|";
    // int indx = index_of_executing_process(states, t);
    for(int i = 0; i < states.size(); i++)
    {
        auto ps = states[i];
        if(ps.AT > t) cout << setw(4) << left << " "; // X
        else if(i == indx)
        {
            setTextColor(GREEN);
            cout << setw(4) << left << string(" ") + (char)178; // Executing
        }
        else if(ps.remaining)
        {
            setTextColor(BLUE);
            cout << setw(4) << left << string(" ") + (char)178; // Waiting
        }
        else
        {
            setTextColor(RED);
            cout << setw(4) << left << string(" ") + (char)178; // Finished
        }
        setTextColor(WHITE);
        cout << "|";
    }
    cout << "\n";
    // print_divider(states.size());
}


vector<ProcessState> take_input()
{
    setTextColor(Color::WHITE);
    cout << "Enter number of Processes: ";
    int n;
    cin >> n;
    vector<ProcessState> states(n);
    for(int i = 0; i < n; i++)
    {
        int in;
        cout << "AT for process " << i << ": ";
        cin >> in;
        states[i].AT = in;
        cout << "BT for process " << i << ": ";
        cin >> in;
        states[i].BT = in;
        states[i].remaining = in;
        states[i].WT = 0;
    }
    return states;
}