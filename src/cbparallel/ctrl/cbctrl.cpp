#include "cbctrl.hpp"

void cbctrl::push_task(CBTask* t, bool wait){
    _tp.push_task(t, wait);
}

void cbctrl::push_tasks(std::vector<CBTask*> v, bool wait){
    _tp.push_tasks(v, wait);
}
