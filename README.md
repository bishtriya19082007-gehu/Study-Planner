🎓 Smart Study Planner
A C++ Application Using Data Structures and Object-Oriented Programming

Smart Study Planner is a student-focused academic management application developed using C++. It helps students organize their subjects, manage daily study tasks, schedule examinations, track task completion, and monitor their academic progress in one place.

The application allows students to create study tasks with deadlines, priorities, and estimated study times. It also provides percentage-based progress tracking and urgency-based task sorting to help students manage their study schedules more effectively.

The project demonstrates the practical implementation of Object-Oriented Programming (OOP), Data Structures and Algorithms (DSA), File Handling, Searching, Sorting, and Modular Programming.

✨ Features

📚 Subject Management
Add and manage subjects.
Store subject name, subject code, teacher name, and total topics.
View all added subjects.

📝 Study Task Management
Add study tasks for different subjects.
Assign unique task IDs.
Set task deadlines.
Set task priorities: High, Medium, or Low.
Add estimated study time.
View and delete study tasks.

📊 Study Progress Tracking
Update task progress from 0% to 100%.
Track Pending, In Progress, and Completed tasks.
View overall study progress.
Monitor task completion.

🔍 Task Searching
Search for tasks using available task information.
Find relevant tasks quickly.

📅 Daily and Upcoming Schedule
View today's study tasks.
Add examination details.
View upcoming examinations.
Validate dates in DD/MM/YYYY format.

⚡ Task Sorting and Priority Management
Sort tasks by deadlines.
Arrange tasks according to priority.
Use urgency-based sorting to identify important unfinished tasks.

↩️ Undo Completion
Use a Stack to manage recently completed tasks.
Undo the last completion operation.

📥 Pending Task Management
Use a Queue to maintain pending tasks.
View the next pending task.

💾 File Handling
Save subject information.
Save study task information.
Save examination details.
Load previously saved data when the application starts.
🛠️ Technologies Used
Backend
C++
Object-Oriented Programming (OOP)
Data Structures and Algorithms
File Handling
Searching and Sorting Algorithms
Date and Time Handling
Data Structures
Vector
Stack
Queue
Libraries
iostream
vector
stack
queue
fstream
sstream
algorithm
iomanip
string
ctime
limits
cctype
Tools
Visual Studio Code
G++ Compiler
Git
GitHub
Frontend

The project is currently being developed as a web application using:

HTML
CSS
JavaScript

The frontend is a planned/in-progress component and will be documented here as it is integrated with the C++ application.

📂 Project Structure

Current C++ console application structure:

text
Smart-Study-Planner/
│
├── main.cpp
│
├── subjects.txt
├── tasks.txt
├── exams.txt
│
└── README.md


File Description:

File	Description
main.cpp	Contains the main C++ application, classes, functions, and menu-driven operations.
subjects.txt	Stores subject information.
tasks.txt	Stores study task information and progress.
exams.txt	Stores examination details.
README.md	Contains project documentation and instructions.

Note: The text files are used for data storage and may be created automatically when the application runs.

🧩 Project Modules
1. 📚 Subject Management
This module manages the academic subjects entered by the student.
It stores:
Subject Name
Subject Code
Teacher Name
Total Number of Topics

2. 📝 Task Management
This module allows students to create and manage study tasks.
Each task contains:
Task ID
Subject Name
Topic
Deadline
Priority
Estimated Study Time
Task Status
Progress Percentage
Students can add, view, search, update, and delete tasks.

3. 📊 Progress Tracking
This module helps students monitor their study progress.
Tasks can have three statuses:
Pending – 0% progress
In Progress – 1% to 99% progress
Completed – 100% progress
Students can update their progress and monitor their work.

4. 📅 Examination Management
This module allows students to:
Add examination details.
Store examination dates.
View upcoming examinations.
Keep track of examination schedules.

5. 🔍 Searching and Sorting
This module helps students find and organize their study tasks.
It includes:
Linear searching.
Sorting tasks by date.
Sorting tasks by priority.
Urgency-based sorting.

6. ↩️ Stack-Based Undo Operation
A Stack is used to maintain recently completed task IDs.
It supports the undo completion operation, allowing the student to reverse the last completion action.

7. 📥 Queue-Based Pending Task Management
A Queue is used to maintain pending tasks.
It follows the FIFO (First In, First Out) principle to manage the next pending task.

8. 💾 File Handling
File handling is used to save and retrieve application data.
The application uses:
subjects.txt
tasks.txt
exams.txt
This helps preserve information even after the application is closed.

🧠 Concepts Used
Object-Oriented Programming (OOP)
Classes and Objects
Encapsulation
Data Members and Member Functions
Constructors
Modular Programming
Data Structures and Algorithms (DSA)
Data Structure / Algorithm	Application
Vector	Stores subjects, tasks, and examinations.
Stack	Manages recently completed tasks and undo operations.
Queue	Maintains pending tasks.
Linear Search	Searches for tasks and relevant information.
Sorting	Organizes tasks by date, priority, and urgency.
Other C++ Concepts
File Handling
String Manipulation
Input Validation
Date and Time Functions
Standard Template Library (STL)


🚀 How the System Works
The application starts and loads previously saved information from files.
The student selects an operation from the main menu.
The student can add subjects and create study tasks.
Each task can be assigned a deadline, priority, and estimated study time.
The student can view today's tasks and search for specific tasks.
The student can update task progress using percentages.
The application updates the task status according to its progress.
Students can sort tasks by date, priority, and urgency.
Examination details can be added and viewed.
Stack and Queue operations help manage completed and pending tasks.
Updated information is saved using file handling.


💻 How to Compile and Run
Prerequisites
Make sure you have:
A C++ compiler such as G++ or MinGW.
Visual Studio Code or another C++ IDE.
Git installed (for cloning the repository).
Step 1: Clone the Repository
(https://github.com/bishtriya19082007-gehu/Study-Planner/tree/main)
Step 2: Open the Project Folder
cd Smart-Study-Planner
Step 3: Compile the Program
g++ -std=c++17 main.cpp -o StudyPlanner
Step 4: Run the Program
Windows:
.\StudyPlanner.exe
Linux/macOS:
./StudyPlanner

👥 Team Contributions

Aarohi:	Project planning, main program structure, OOP implementation,Vector and integration.
Ananya:	Data Structures implementation using Queue, also STL and lambda functions.
Shreya: Task management, searching, sorting, time handling and input validation and progress tracking.
Riya: File handling, examination management, date validation, Stack implementation and testing.

🎯 Project Objectives
To develop an application that helps students organize their academic activities.
To manage subjects, study tasks, and examination schedules.
To implement Object-Oriented Programming concepts using C++.
To demonstrate practical applications of Data Structures.
To use Stack and Queue for task management.
To implement searching and sorting algorithms.
To maintain study progress using percentage-based tracking.
To implement file handling for permanent data storage.
To improve time management and study organization.


🔮 Future Improvements
🌐 Develop a complete web-based frontend using HTML, CSS, and JavaScript.
🔗 Integrate the C++ backend with the web frontend.
🔐 Add student login and authentication.
📱 Improve the application with a responsive user interface.
📊 Add graphical study progress charts and dashboards.
🔔 Add reminders for upcoming deadlines and examinations.
📈 Add detailed subject-wise progress reports.
☁️ Explore cloud-based data storage.
📅 Add a calendar-based study schedule.
🎓 Project Purpose

Smart Study Planner was developed as a college project to demonstrate the practical implementation of:

C++ Programming
Object-Oriented Programming
Data Structures and Algorithms
File Handling
Searching and Sorting
Standard Template Library (STL)

The project applies these concepts to solve a real-world student problem: organizing study activities, managing deadlines, scheduling examinations, and tracking academic progress.
