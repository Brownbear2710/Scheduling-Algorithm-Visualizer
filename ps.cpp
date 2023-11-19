#include "common.cpp"

namespace ps
{
    template<typename T>
    using min_heap = priority_queue<T, vector<T>, greater<T>>;
    bool visual_output = true;
    bool show_wait_time = true;
    vector<int> get_sequence(vector<ProcessState> states)
    {
        int t = 0;
        vector<int> seq;
        min_heap<pair<int,int>> pq, proc;
        for(int i = 0; i < states.size(); i++)
            pq.emplace(states[i].AT,i);
        do
        {
            while(pq.size() and pq.top().first <= t)
                proc.emplace(states[pq.top().second].priority, pq.top().second), pq.pop();
            if(proc.size())
            {
                seq.push_back(proc.top().second);
                if(!--states[proc.top().second].remaining) proc.pop();
            }
            else seq.push_back(-1);
            t++;
        } while (pq.size() or proc.size());
        return seq;
    }

    void next_state(vector<ProcessState> &states, int t, int indx)
    {
        for(int i = 0; i < states.size(); i++)
            if(i == indx) states[i].remaining--;
            else if(t >= states[i].AT and states[i].remaining) states[i].WT++;
    }
    vector<int> simulate(vector<ProcessState> states)
    {
        auto seq = get_sequence(states);
        if(visual_output or show_wait_time)
        {
            setTextColor(RED);
            cout << "- PS (Priority Scheduling): \n";
            setTextColor(WHITE);
        }
        if(visual_output)
        {
            print_top_column(states.size());
            for(int i = 0; i < seq.size(); i++)
            {
                print_current_state(states, i, seq[i]);
                next_state(states, i, seq[i]);
            }
            print_divider(states.size());
        }
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