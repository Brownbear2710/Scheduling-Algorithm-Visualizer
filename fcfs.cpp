/*
    So, which of the favours
    of your Lord would you deny?
*/

#include "common.cpp"

namespace fcfs{
    bool visual_output = true;
    bool show_wait_time = true;
    int index_of_executing_process(vector<ProcessState> &states, int t)
    {
        int indx = -1;
        for(int i = 0; i < states.size(); i++)
            if(states[i].remaining and states[i].AT <= t and
                (indx == -1 or states[i].AT < states[indx].AT)) indx = i;
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
    vector<int> simulate(vector<ProcessState> &states)
    {
        if(visual_output) print_top_column(states.size());
        vector<int> seq;
        int t = 0;
        do
        {
            seq.push_back(index_of_executing_process(states, t));
            if(visual_output) print_current_state(states, t, index_of_executing_process(states, t));
        } while (next_state(states, t));
        if(visual_output) print_divider(states.size());
        double WT = 0;
        if(show_wait_time)
        {
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
