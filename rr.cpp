#include "common.cpp"

namespace rr
{
    template<typename T>
    using min_heap = priority_queue<T, vector<T>, greater<T>>;
    int round_size = 3;
    bool show_wait_time = true;
    bool visual_output = true;
    vector<int> get_sequence(vector<ProcessState> states)
    {
        vector<int> seq;
        min_heap<pair<int,int>> pq; // <at, i>
        queue<int> q;
        for(int i = 0; i < states.size(); i++)
            pq.emplace(states[i].AT, i);
        while(pq.size() and pq.top().first == 0)
            q.push(pq.top().second), pq.pop();
        int t = 0;
        do
        {
            if(q.size())
            {
                for(int i = 0; i < round_size and states[q.front()].remaining; i++)
                {
                    seq.push_back(q.front());
                    states[q.front()].remaining--, t++;
                }
            }
            else
            {
                t++;
                seq.push_back(-1);
            }
            while( pq.size() and pq.top().first <= t)
                q.push(pq.top().second), pq.pop();
            if(q.size() and states[q.front()].remaining)  q.push(q.front());
            if(q.size()) q.pop();
        } while (q.size() or pq.size());
        seq.push_back(-1);
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
            cout << "- RR (Round Robin): \n";
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