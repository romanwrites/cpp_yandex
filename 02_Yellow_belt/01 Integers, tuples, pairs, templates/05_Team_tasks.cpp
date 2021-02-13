#include <iostream>
#include <map>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
private:
    map<string, TasksInfo> data;
public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return data.at(person);
    }

    void AddNewTask(const string& person) {
        data[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count) {
        TasksInfo updated;
        TasksInfo unchanged;

        try {
            data.at(person);
        } catch (exception &ex) {
            return make_tuple(updated, unchanged);
        }

        for (auto &i : data.at(person)) {
            while (task_count > 0 && i.second > 0) {
                if (i.first == TaskStatus::NEW) {
                    updated[TaskStatus::IN_PROGRESS]++;
                } else if (i.first == TaskStatus::IN_PROGRESS){
                    updated[TaskStatus::TESTING]++;
                } else if (i.first == TaskStatus::TESTING) {
                    updated[TaskStatus::DONE]++;
                } else {
                    break ;
                }
                i.second--;
                task_count--;
            }
            if (i.second > 0) {
                unchanged[i.first] = i.second;
            }
        }

        data[person] = MergeLogs(updated, unchanged);
        unchanged.erase(TaskStatus::DONE);

        return make_tuple(updated, unchanged);
    }

private:
    TasksInfo MergeLogs(TasksInfo const &upd, TasksInfo const &unchanged) {
        TasksInfo merged = upd;

        for (auto const &i : unchanged) {
            merged[i.first] += i.second;
        }
        return merged;
    }
};


void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
}
