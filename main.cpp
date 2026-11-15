#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <ctime>
#include <limits>
#include <cctype>

using namespace std;

string toLowerCase(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c)
              {
                  return static_cast<char>(tolower(c));
              });
    return s;
}

long long dateKey(const string &date)
{
    int day, month, year;
    char slash1, slash2;
    stringstream ss(date);
    if (!(ss >> day >> slash1 >> month >> slash2 >> year)) return -1;
    if (slash1 != '/' || slash2 != '/' || year < 1 || month < 1 || month > 12) return -1;
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (leap) daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1]) return -1;
    return (long long)year * 10000 + month * 100 + day;
}

long long daysBetween(const string &from, const string &to)
{
    long long a = dateKey(from), b = dateKey(to);
    if (a == -1 || b == -1) return -1;
    int d1 = a % 100, m1 = (a / 100) % 100, y1 = a / 10000;
    int d2 = b % 100, m2 = (b / 100) % 100, y2 = b / 10000;
    tm t1 = {}, t2 = {};
    t1.tm_mday = d1; t1.tm_mon = m1 - 1; t1.tm_year = y1 - 1900; t1.tm_hour = 12;
    t2.tm_mday = d2; t2.tm_mon = m2 - 1; t2.tm_year = y2 - 1900; t2.tm_hour = 12;
    time_t time1 = mktime(&t1), time2 = mktime(&t2);
    if (time1 == (time_t)-1 || time2 == (time_t)-1) return -1;
    return (long long)difftime(time2, time1) / 86400;
}

string todayDate()
{
    time_t now = time(nullptr);
    tm *local = localtime(&now);
    if (local == nullptr) return "";
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", local);
    return string(buffer);
}

class Subject
{
public:
    string name, code, teacher;
    int totalTopics;
    Subject() { totalTopics = 0; }
    void input()
    {
        cout << "Enter subject name: "; getline(cin, name);
        cout << "Enter subject code: "; getline(cin, code);
        cout << "Enter teacher name: "; getline(cin, teacher);
        cout << "Enter total topics: "; cin >> totalTopics;
        while (cin.fail() || totalTopics < 0)
        {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a valid non-negative number: "; cin >> totalTopics;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    void display() const
    {
        cout << "\nSubject: " << name << "\nCode: " << code << "\nTeacher: " << teacher << "\nTotal Topics: " << totalTopics << "\n";
    }
};

class Task
{
public:
    int id;
    string subject, topic, date, priority, status;
    int estimatedMinutes;
    int progress;
    Task() { id = 0; estimatedMinutes = 0; progress = 0; status = "Pending"; }
    void input(int taskID)
    {
        id = taskID;
        cout << "Enter subject name: "; getline(cin, subject);
        cout << "Enter topic/task name: "; getline(cin, topic);
        do { cout << "Enter date (DD/MM/YYYY): "; getline(cin, date); if (dateKey(date) == -1) cout << "Invalid date. Try again.\n"; } while (dateKey(date) == -1);
        do
        {
            cout << "Enter priority (High/Medium/Low): "; getline(cin, priority); priority = toLowerCase(priority);
            if (priority != "high" && priority != "medium" && priority != "low") cout << "Enter High, Medium or Low.\n";
        } while (priority != "high" && priority != "medium" && priority != "low");
        priority[0] = toupper(static_cast<unsigned char>(priority[0]));
        cout << "Enter estimated study time in minutes: "; cin >> estimatedMinutes;
        while (cin.fail() || estimatedMinutes < 0)
        {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a valid non-negative number: "; cin >> estimatedMinutes;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); status = "Pending"; progress = 0;
    }
    void display() const
    {
        cout << left << setw(5) << id << setw(20) << subject << setw(22) << topic << setw(13) << date << setw(10) << priority << setw(13) << status << setw(8) << (to_string(progress) + "%") << estimatedMinutes << " min\n";
    }
};

class Exam
{
public:
    string subject, date;
    void input()
    {
        cout << "Enter exam subject: "; getline(cin, subject);
        do { cout << "Enter exam date (DD/MM/YYYY): "; getline(cin, date); if (dateKey(date) == -1) cout << "Invalid date. Try again.\n"; } while (dateKey(date) == -1);
    }
    void display() const
    {
        cout << left << setw(25) << subject << setw(15) << date;
        long long remaining = daysBetween(todayDate(), date);
        if (remaining >= 0) cout << remaining << " days left"; else cout << "Date unavailable";
        cout << '\n';
    }
};

class StudyPlanner
{
private:
    vector<Subject> subjects;
    vector<Task> tasks;
    vector<Exam> exams;
    stack<int> completedStack;
    queue<int> pendingQueue;
    int nextID = 1;
    int findTaskIndex(int id)
    {
        for (int i = 0; i < (int)tasks.size(); i++) if (tasks[i].id == id) return i;
        return -1;
    }
    void rebuildPendingQueue()
    {
        queue<int> emptyQueue; pendingQueue.swap(emptyQueue);
        for (const Task &t : tasks) if (t.status != "Completed") pendingQueue.push(t.id);
    }
    void saveSubjects()
    {
        ofstream file("subjects.txt");
        for (const Subject &s : subjects) file << quoted(s.name) << ' ' << quoted(s.code) << ' ' << quoted(s.teacher) << ' ' << s.totalTopics << '\n';
    }
    void saveTasks()
    {
        ofstream file("tasks.txt");
        for (const Task &t : tasks) file << t.id << ' ' << quoted(t.subject) << ' ' << quoted(t.topic) << ' ' << quoted(t.date) << ' ' << quoted(t.priority) << ' ' << t.estimatedMinutes << ' ' << quoted(t.status) << ' ' << t.progress << '\n';
    }
    void saveExams()
    {
        ofstream file("exams.txt");
        for (const Exam &e : exams) file << quoted(e.subject) << ' ' << quoted(e.date) << '\n';
    }
    void saveAll() { saveSubjects(); saveTasks(); saveExams(); }
    void loadData()
    {
        ifstream sf("subjects.txt"); Subject s;
        while (sf >> quoted(s.name) >> quoted(s.code) >> quoted(s.teacher) >> s.totalTopics) subjects.push_back(s);
        ifstream tf("tasks.txt");
        string line;
        while (getline(tf, line))
        {
            if (line.empty()) continue;
            istringstream row(line);
            Task t;
            if (!(row >> t.id >> quoted(t.subject) >> quoted(t.topic) >> quoted(t.date)
                      >> quoted(t.priority) >> t.estimatedMinutes >> quoted(t.status))) continue;
            if (!(row >> t.progress)) t.progress = (t.status == "Completed" ? 100 : 0);
            t.progress = max(0, min(100, t.progress));
            if (t.progress == 100) t.status = "Completed";
            else if (t.status == "Completed") t.status = "Pending";
            tasks.push_back(t);
            if (t.status == "Completed") completedStack.push(t.id);
            if (t.id >= nextID) nextID = t.id + 1;
        }
        ifstream ef("exams.txt"); Exam e;
        while (ef >> quoted(e.subject) >> quoted(e.date)) exams.push_back(e);
        rebuildPendingQueue();
    }
    int priorityRank(const string &priority)
    {
        if (priority == "High") return 3;
        if (priority == "Medium") return 2;
        return 1;
    }
public:
    StudyPlanner() { loadData(); }
    void addSubject()
    {
        Subject s; s.input(); subjects.push_back(s); saveSubjects(); cout << "\nSubject added successfully!\n";
    }
    void addTask()
    {
        Task t; t.input(nextID++); tasks.push_back(t); pendingQueue.push(t.id); saveTasks();
        cout << "\nTask added successfully! Task ID: " << t.id << '\n';
    }
    void viewTasks()
    {
        if (tasks.empty()) { cout << "\nNo tasks available.\n"; return; }
        cout << "\n================ ALL TASKS ================\n";
        cout << left << setw(5) << "ID" << setw(20) << "Subject" << setw(22) << "Topic" << setw(13) << "Date" << setw(10) << "Priority" << setw(13) << "Status" << setw(8) << "Progress" << "Time\n";
        cout << string(100, '-') << '\n';
        for (const Task &t : tasks) t.display();
    }
    void markCompleted()
    {
        int id; cout << "Enter task ID: "; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int index = findTaskIndex(id);
        if (index == -1) { cout << "Task not found.\n"; return; }
        if (tasks[index].status == "Completed") { cout << "Task is already completed.\n"; return; }
        tasks[index].status = "Completed"; tasks[index].progress = 100; completedStack.push(id); rebuildPendingQueue(); saveTasks();
        cout << "\nTask marked as completed!\nGreat job!\n";
    }
    void searchTasks()
    {
        string query; cout << "Search by subject, topic, priority or status: "; getline(cin, query); query = toLowerCase(query); bool found = false;
        for (const Task &t : tasks)
        {
            if (toLowerCase(t.subject).find(query) != string::npos || toLowerCase(t.topic).find(query) != string::npos || toLowerCase(t.priority).find(query) != string::npos || toLowerCase(t.status).find(query) != string::npos)
            { if (!found) { cout << "\nSearch Results:\n"; found = true; } t.display(); }
        }
        if (!found) cout << "No matching tasks found.\n";
    }
    void todaysTasks()
    {
        string today = todayDate(); cout << "\nToday's date: " << today << '\n' << "========== TODAY'S TASKS ==========\n"; bool found = false;
        for (const Task &t : tasks) if (t.date == today && t.status != "Completed")
        {
            cout << "\nTask ID: " << t.id << "\nSubject: " << t.subject << "\nTopic: " << t.topic << "\nPriority: " << t.priority << "\nStudy time: " << t.estimatedMinutes << " minutes\n"; found = true;
        }
        if (!found) cout << "No pending tasks for today.\n";
    }
    void addExam()
    {
        Exam e; e.input(); exams.push_back(e); saveExams(); cout << "Exam added successfully!\n";
    }
    void upcomingExams()
    {
        vector<Exam> upcoming;
        for (const Exam &e : exams) { long long remaining = daysBetween(todayDate(), e.date); if (remaining >= 0) upcoming.push_back(e); }
        sort(upcoming.begin(), upcoming.end(), [](const Exam &a, const Exam &b) { return dateKey(a.date) < dateKey(b.date); });
        cout << "\n========== UPCOMING EXAMS ==========\n";
        if (upcoming.empty()) { cout << "No upcoming exams.\n"; return; }
        for (const Exam &e : upcoming) e.display();
    }
    void studyProgress()
    {
        int completed = 0; double progressSum = 0;
        for (const Task &t : tasks) { if (t.progress == 100) completed++; progressSum += t.progress; }
        int total = (int)tasks.size(), pending = total - completed;
        double percentage = total == 0 ? 0 : progressSum / total;
        cout << "\n========== STUDY PROGRESS ==========\n" << "Total Tasks: " << total << '\n' << "Completed: " << completed << '\n' << "Pending/In Progress: " << pending << '\n';
        cout << fixed << setprecision(1) << "Overall Progress: " << percentage << "%\n" << "Progress Bar: [";
        int bars = (int)(percentage / 5); for (int i = 0; i < 20; i++) { if (i < bars) cout << '#'; else cout << '-'; }
        cout << "]\n\n========== SUBJECT-WISE PROGRESS ==========\n";
        for (const Subject &s : subjects)
        {
            int subjectTotal = 0, subjectCompleted = 0; double subjectProgress = 0;
            for (const Task &t : tasks) if (toLowerCase(t.subject) == toLowerCase(s.name)) { subjectTotal++; subjectProgress += t.progress; if (t.progress == 100) subjectCompleted++; }
            double p = subjectTotal == 0 ? 0 : subjectProgress / subjectTotal;
            cout << s.name << ": " << p << "% (" << subjectCompleted << "/" << subjectTotal << " tasks completed)\n";
        }
    }
    void deleteTask()
    {
        int id; cout << "Enter task ID to delete: "; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int index = findTaskIndex(id); if (index == -1) { cout << "Task not found.\n"; return; }
        tasks.erase(tasks.begin() + index); rebuildPendingQueue(); saveTasks(); cout << "Task deleted successfully.\n";
    }
    void sortTasks()
    {
        int choice; cout << "\n1. Sort by Date\n2. Sort by Priority\n3. Sort by Urgency\nEnter choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
        {
            sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) { long long da = dateKey(a.date), db = dateKey(b.date); if (da == db) return a.id < b.id; return da < db; });
            cout << "Tasks sorted by date.\n";
        }
        else if (choice == 2)
        {
            sort(tasks.begin(), tasks.end(), [this](const Task &a, const Task &b) { int pa = priorityRank(a.priority), pb = priorityRank(b.priority); if (pa == pb) return dateKey(a.date) < dateKey(b.date); return pa > pb; });
            cout << "Tasks sorted by priority.\n";
        }
        else if (choice == 3)
        {
            sort(tasks.begin(), tasks.end(), [this](const Task &a, const Task &b)
            {
                long long da = daysBetween(todayDate(), a.date);
                long long db = daysBetween(todayDate(), b.date);
                if (a.status == "Completed" && b.status != "Completed") return false;
                if (a.status != "Completed" && b.status == "Completed") return true;
                if (da != db) return da < db;
                int pa = priorityRank(a.priority), pb = priorityRank(b.priority);
                if (pa != pb) return pa > pb;
                return a.progress < b.progress;
            });
            cout << "Tasks sorted by urgency (unfinished, nearest due date, then priority).\n";
        }
        else { cout << "Invalid choice.\n"; return; }
        saveTasks(); viewTasks();
    }
    void updateProgress()
    {
        int id, value;
        cout << "Enter task ID: ";
        if (!(cin >> id)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid task ID.\n"; return; }
        int index = findTaskIndex(id);
        if (index == -1) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Task not found.\n"; return; }
        cout << "Enter completion percentage (0-100): ";
        if (!(cin >> value) || value < 0 || value > 100) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Enter a percentage from 0 to 100.\n"; return; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tasks[index].progress = value;
        tasks[index].status = (value == 100 ? "Completed" : (value == 0 ? "Pending" : "In Progress"));
        if (value == 100) completedStack.push(id);
        rebuildPendingQueue(); saveTasks();
        cout << "Task progress updated to " << value << "%.\n";
    }
    void nextPendingTask()
    {
        rebuildPendingQueue(); if (pendingQueue.empty()) { cout << "No pending tasks!\n"; return; }
        int id = pendingQueue.front(), index = findTaskIndex(id); if (index != -1) { cout << "\nNext pending task:\n"; tasks[index].display(); }
    }
    void undoCompletion()
    {
        if (completedStack.empty()) { cout << "No completed task available to undo.\n"; return; }
        int id = completedStack.top(); completedStack.pop(); int index = findTaskIndex(id);
        if (index == -1) { cout << "Task no longer exists.\n"; return; }
        tasks[index].status = "Pending"; tasks[index].progress = 0; rebuildPendingQueue(); saveTasks(); cout << "Last completion undone for task ID " << id << ".\n";
    }
    void viewSubjects()
    {
        if (subjects.empty()) { cout << "No subjects available.\n"; return; }
        cout << "\n========== SUBJECTS ==========\n"; for (const Subject &s : subjects) s.display();
    }
    void menu()
    {
        int choice;
        do
        {
            cout << "\n====================================\n           STUDY PLANNER\n====================================\n";
            cout << "1.  Add Subject\n2.  Add Study Task\n3.  View All Tasks\n4.  Mark Task as Completed\n5.  Search Tasks\n6.  View Today's Tasks\n7.  Add Exam\n8.  View Upcoming Exams\n9.  Study Progress\n10. Delete Task\n11. Sort Tasks\n12. View Next Pending Task\n13. Undo Last Completion\n14. View Subjects\n15. Update Task Progress (%)\n16. Exit\n\nEnter your choice: ";
            if (!(cin >> choice)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Please enter a valid number.\n"; continue; }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice)
            {
                case 1: addSubject(); break; case 2: addTask(); break; case 3: viewTasks(); break; case 4: markCompleted(); break;
                case 5: searchTasks(); break; case 6: todaysTasks(); break; case 7: addExam(); break; case 8: upcomingExams(); break;
                case 9: studyProgress(); break; case 10: deleteTask(); break; case 11: sortTasks(); break; case 12: nextPendingTask(); break;
                case 13: undoCompletion(); break; case 14: viewSubjects(); break;
                case 15: updateProgress(); break;
                case 16: saveAll(); cout << "Data saved. Goodbye!\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 16);
    }
};

int main()
{
    StudyPlanner planner;
    cout << "Welcome to the Study Planner!\n";
    planner.menu();
    return 0;
}
