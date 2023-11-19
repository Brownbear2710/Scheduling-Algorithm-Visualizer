#include "srtf.cpp"

namespace sjf
{
    bool show_wait_time = true;
    bool visual_output = true;
    vector<int> simulate(vector<ProcessState> states)
    {
        for(int i = 0; i < states.size(); i++)
            states[i].AT = 0;
        bool tmp_visual_output = srtf::visual_output;
        bool tmp_show_wait_time = srtf::show_wait_time;
        srtf::visual_output = visual_output;
        srtf::show_wait_time = show_wait_time;
        auto ret = srtf::simulate(states, "- SJF (Shortest Job First) [All processes arrive at 0]:");
        srtf::visual_output = tmp_visual_output;
        srtf::show_wait_time = tmp_show_wait_time;
        return ret;
    }
}