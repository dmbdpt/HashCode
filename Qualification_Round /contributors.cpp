#include "global.h"

void learn_skill (contributor c, skill s){
    for (skill sk : c.skills)  {
        if (sk.name == s.name) {
            sk.level++;
            end_project(c);
        }
    }
}

void end_project(contributor c){
    c.roles_queue.pop();
    c.project_queue.pop();
}

int skill_sum(contributor c) {
    int sum = 0;
    for (skill s : c.skills) {
        sum += s.level;
    }
    return sum;
}

