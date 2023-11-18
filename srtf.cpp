#pragma once
#include "common.cpp"

namespace srtf {
    bool visual_output = true;
    bool show_wait_time = true;
    int index_of_executing_process(vector<ProcessState> &states, int t)
    {
        int indx = -1;
        for(int i = 0; i < states.size(); i++)
            if(states[i].remaining and states[i].AT <= t and (indx == -1 or states[i].remaining < states[indx].remaining)) indx = i;
        return indx;
    }
    bool next_state(vector<ProcessState> &states, int &t)
    {
        bool f = false;
        for(int i = 0; i < states.size(); i++)
            if(states[i].remaining != 0) f = true;
        if(!f) return false;

        int indx = index_of_executing_process(states, t);
        
        for(int i = 0; i < states.size(); i++)
            if(i == indx) states[i].remaining--;
            else if(states[i].AT <= t and states[i].remaining) states[i].WT++;
        t++;
        return true;
    }
    vector<int> simulate(vector<ProcessState> states)
    {
        vector<int> seq;
        if(visual_output)
        {
            setTextColor(RED);
            cout << "- SRTF (Shortest Remaining Time First):\n";
            setTextColor(WHITE);
            print_top_column(states.size());
        }
        int t = 0;
        do
        {
            seq.push_back(index_of_executing_process(states, t));
            if(visual_output) print_current_state(states, t, index_of_executing_process(states, t));
        } while (next_state(states, t));
        if(visual_output) print_divider(states.size());
        if(show_wait_time)
        {
            double WT = 0;
            for(int i = 0; i < states.size(); i++)
            {
                cout << "WT" << i << ": " << states[i].WT << "\n";
                WT = (int) WT + states[i].WT;
            }
            cout << "Avg. WT: " << WT/states.size() << "\n";
        }
        return seq;
    }
}