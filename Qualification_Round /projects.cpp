#include "global.h"

using namespace std;

bool project_is_full(project *p)
{
    //cout << p.role_counter << " " << p.role_number << endl;
    return p->role_number == p->role_counter;
}

int add_contributor(contributor c, project *p)
{
    if (!project_is_full(p))
    {
        p->assigned.push_back(c);
        p->role_counter++;
        //cout << p.name << " QUEIJO: " << c.name << " " << p.role_counter << endl;
        return 0;
    }
    return -1;
}

bool check_mentor(project p, role r)
{
    for (contributor c : p.assigned)
    {
        for (skill s : c.skills)
        {
            if (s.name == r.name)
            {
                if (r.level <= s.level)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int finish_project(project p)
{
    for (contributor c : p.assigned)
    {
        role r = c.roles_queue.front();
        for (skill s : c.skills)
        {
            if (s.name == r.name)
            {
                if (r.level >= s.level)
                {
                    learn_skill(c, s);
                }
                else
                {
                    end_project(c);
                }
            }
        }
    }
    return get_score(p);
}

int get_score(project p)
{
    int ret_value = 0;

    if (current_date >= p.best_before)
    {
        return ret_value;
    }
    else
    {
        return p.score - (current_date - p.best_before);
    }
}
