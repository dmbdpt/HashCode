#ifndef _GLOBAL_
#define _GLOBAL_

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

static int current_date = 0;

// Roles
typedef struct ROLES
{
    char name[21];
    int level;
} role;

// Skill
typedef struct SKILL
{
    char name[21];
    int level;
} skill;

struct CONTRIBUTOR;
typedef struct CONTRIBUTOR contributor;

// Projects
typedef struct PROJECT
{
    char name[21];
    int days;
    int score;
    int best_before;
    int role_number;
    int role_counter = 0;
    vector<role> roles_list;
    vector<contributor> assigned;
} project;

// Contributors
typedef struct CONTRIBUTOR
{
    char name[21];
    bool available;
    vector<skill> skills;
    queue<role> roles_queue;
    queue<project> project_queue;
} contributor;

static vector<project> projects_list;

static vector<contributor> contr_list;

void learn_skill(contributor c, skill s);
void end_project(contributor c);

int get_score(project p);
int finish_project(project p);
bool check_mentor(project p, role r);
int add_contributor(contributor c, project*);
bool project_is_full(project*);
int skill_sum(contributor); 

#endif