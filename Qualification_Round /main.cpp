#include "global.h"

static int n_contribuitors = 0, n_projects = 0;
static fstream file;
static string line;
static vector<project> final;

// ./main input/a_an_example.in.txt > A.txt && ./main input/b_better_start_small.in.txt > B.txt && ./main input/c_collaboration.in.txt > C.txt  && ./main input/d_dense_schedule.in.txt > D.txt && ./main input/e_exceptional_skills.in.txt > E.txt && ./main input/f_find_great_mentors.in.txt > F.txt 

void read_contrib()
{
    for (int j = 0; j < n_contribuitors; j++)
    {
        getline(file, line);
        istringstream linestream(line);
        char name[21];
        int n_skills, level;

        linestream >> name >> n_skills;
        // cout << "Name: " << name << " Skills: " << n_skills<<endl;
        contributor new_contributor;
        strcpy(new_contributor.name, name);
        new_contributor.available = true;
        new_contributor.skills = vector<skill>(n_skills);
        // cout << "Name: " << new_contributor.name << " Skills: " << new_contributor.skills.size()<<endl;

        for (size_t i = 0; i < n_skills; i++)
        {
            getline(file, line);
            istringstream linestream(line);
            linestream >> name >> level;
            strcpy(new_contributor.skills[i].name, name);
            new_contributor.skills[i].level = level;
        }
        contr_list.push_back(new_contributor);
    }
}

void read_projs()
{
    for (int j = 0; j < n_projects; j++)
    {
        getline(file, line);
        istringstream linestream(line);
        char name[21];
        int days, score, best_before, roles, level;

        linestream >> name >> days >> score >> best_before >> roles;
        project new_project;
        strcpy(new_project.name, name);
        new_project.days = days;
        new_project.score = score;
        new_project.best_before = best_before;
        new_project.role_number = roles;
        new_project.roles_list = vector<role>(roles);

        for (size_t i = 0; i < roles; i++)
        {
            getline(file, line);
            istringstream linestream(line);
            linestream >> name >> level;
            strcpy(new_project.roles_list[i].name, name);
            new_project.roles_list[i].level = level;
        }
        projects_list.push_back(new_project);
    }
}

bool comp_proj_bf(project a, project b)
{
    bool ret = a.best_before == b.best_before;
    if (ret)
        ret = a.score < a.score;
    else
        ret = a.best_before < b.best_before;
    return ret;
}

bool search_contr(role r, contributor* c)
{
    vector<contributor> eligible;
    for (contributor c : contr_list)
    {
        if (c.available)
            for (skill s : c.skills)
            {
                // cout << s.name << "==" << r.name << endl;
                if (!strcmp(s.name, r.name))
                {
                    //cout << s.name << "==" << r.name << endl;
                    if (s.level == r.level)
                        eligible.push_back(c);
                }
            }
    }

    if (eligible.size() == 0)
        return false;



    contributor ret = eligible[0];
    int max_sum = skill_sum(ret);
    // Implement search by project
    for (contributor contr : eligible)
    {
        int current_sum = skill_sum(contr);
        if (current_sum > max_sum)
        {
            ret = contr;
            max_sum = current_sum;
        }
    }
    *c = ret;
    return true;
}

void supersecretalg()
{
    sort(projects_list.begin(), projects_list.end(), comp_proj_bf);
    for (project proj : projects_list)
    {
        for (role r : proj.roles_list)
        {
            contributor cur_contr;
            if (!search_contr(r, &cur_contr))
            {
                // fill dumb people
                continue;
            }
            if (add_contributor(cur_contr, &proj) < 0)
                break;
        }
        if (project_is_full(&proj))
        {
            //cout << "PAOOOOOO; " << endl;
            final.push_back(proj);
        }
    }
}


void output()
{
    cout << final.size() << endl;
    for (project p : final)
    {
        cout << p.name << endl;
        for (contributor c : p.assigned)
        {
            cout << c.name << " ";
        }
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    file.open(argv[1], ios::in);

    getline(file, line);

    istringstream linestream(line);
    linestream >> n_contribuitors >> n_projects;

    //cout << "Contri.: " << n_contribuitors << " Proj.: " << n_projects << endl;

    read_contrib();
    read_projs();

    supersecretalg();
    output();

    return 0;
}