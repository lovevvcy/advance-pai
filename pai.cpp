#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<ctime>

// #define DEBUG

using namespace std;

int totalNums;
int totalSubject;
int totalPosition;
int maxDeep;

class Course {
public:
    int subjectId;
    int duration;
    Course() {
    }
    Course(int _subjectId, int _duration) {
        subjectId = _subjectId;
        duration = _duration;
    }
};

vector<Course> courses;

class Subject {
public:
    string name;
    int id;
    int teaNums;
    int selectStuNums;
    int unselectStuNums;
    int selectNums;
    int unselectNums;
    vector<int> flags;
    vector<int> crs;
    Subject() {
        teaNums = 0;
    }
    Subject(int _id, int tnums, int snums, int selectnums, int unselectnums, string _name) {
        id = _id;
        teaNums = tnums;
        selectStuNums = snums;
        unselectStuNums = totalNums - snums;
        selectNums = selectnums;
        unselectNums = unselectnums;
        name = _name;
        crs.push_back(courses.size());            
        courses.push_back(Course(id, selectNums));
        crs.push_back(courses.size());
        courses.push_back(Course(id, unselectNums));
        flags.clear();
        flags.assign(tnums, 0);
    }
    void setTeaNum(int nums) {
        teaNums = nums;
        flags.clear();
        flags.assign(nums, 0);
    }
};

vector<Subject> subjects;

class Group {
public: 
    set<int> selectSubs;
    vector<int> selectCourses;
    vector<vector<int> > choices;
    int nums;
    Group() {
        nums = 0;
    }
    Group(int x, int y, int z, int _nums) {
        selectSubs.insert(x);
        selectSubs.insert(y);
        selectSubs.insert(z);
        nums = _nums;
        for (int i = 0; i < totalSubject; ++i) {
            if (selectSubs.count(i)) {
                selectCourses.push_back(subjects[i].crs[0]);
            } else {
                if (subjects[i].unselectNums > 0) { 
                    selectCourses.push_back(subjects[i].crs[1]);
                }
            }
        }
        do {
            choices.push_back(selectCourses);
        } while (next_permutation(selectCourses.begin(), selectCourses.end()));
    }
    bool operator < (const Group &g) const {
        return choices.size() < g.choices.size();
    }
    void debugPrint() {
        cout << choices.size() << endl;
        for (auto cho: choices) {
            for (auto crs: cho) {
                cout << crs << " " ;
            }
            cout << endl;
        }
    }
};

vector<Group> groups;

class Klass {
public:
    vector<int> students;
    int people;
    int subjectId;
    int position;
    Klass() {
        people = 0;
        students.clear();
    }
    Klass(int stu, int _people, int _subjectId, int _position) {
        subjectId = _subjectId;
        position = _position;
        people = _people;
        students.clear();
        students.push_back(stu);
    }
    void debugPrint() {
        cout << "include students: ";
        for (auto stu: students) {
            cout << stu << " " ;
        }
        cout << endl;
        cout << "总人数：" << people << endl;
        cout << "科目：" << subjects[subjectId].name << endl;
        cout << "Position: " << position << endl;
        cout << endl;
    }
};

class Solution {
public:
    int maxPos;
    vector<vector<int> > flags;
    vector<Klass> klasses;
    Solution() {
        flags.clear();
        klasses.clear();
        maxPos = 0;
    }
    Solution(int mPos) {
        flags.clear();
        klasses.clear();
        maxPos = mPos;
    }
    string flag2String(int flag) {
        string ret = "|";
        for (int i = 0; i < maxPos; ++i) {
            if (flag & (1 << i))
                ret += " ■■■■■ |";
            else
                ret += "       |";
        }
        return ret;
    }
    
    void debugPrint() {
        for (auto klass: klasses) {
            klass.debugPrint();
        }
        for (int i = 0; i < flags.size(); ++i) {
            auto crs = flags[i];
            for (auto flag: crs) {
                cout << subjects[i].name << ": ";
                cout << flag2String(flag) << endl;
            }
        }
        cout << endl;
    }
};

Solution answer;

int random(int a, int b) {
    return (rand() % (b - a)) + a;
}

int genFlag(int crs, int pos) {
    return ((1 << courses[crs].duration) - 1) << pos;
}

Solution applyCho(Solution a, vector<int> cho) {
    Solution ret = a;
    for (auto crs: cho) {
        auto sub = courses[crs].subjectId;
        for (auto &flag: ret.flags[sub]) {
            auto tmp = genFlag(crs, total);
            if (Flag = )
            ret.klasses.push_back(Klass(groupId, grs.nums, sub, flag));
            break;
        }
        total += courses[crs].duration;
    }
    return ret;
}

void dfs(int deep, Solution now) {
    if (deep == maxDeep) {
        now.debugPrint();
        return;
    }
    auto choices = groups[deep].choices;
    for (auto cho: choices) {
        Solution tmp = applyCho(now, cho);
        dfs(deep + 1, tmp);
    }
}

Solution initialSolution() {
    Solution ret(totalPosition);
    for (auto sub: subjects) {
        ret.flags.push_back(sub.flags);
    }
    sort(groups.begin(), groups.end());
#ifdef DEBUG
    for (auto grs: groups) {
        grs.debugPrint();
    }
#endif
    int groupId = groups.size() - 1;
    auto grs = groups.back();
    auto choices = grs.choices;
    auto cho = choices[0];
    int total = 0;
    for (auto crs: cho) {
        auto sub = courses[crs].subjectId;
        for (auto &flag: ret.flags[sub]) {
            flag |= genFlag(crs, total);
            ret.klasses.push_back(Klass(groupId, grs.nums, sub, flag));
            break;
        }
        total += courses[crs].duration;
    }
    ret.debugPrint();
    return ret;
}

void arrange() {
    Solution init = initialSolution();
    maxDeep = 10;
    //dfs(0, init);
}

int main() {
    subjects.clear();
    courses.clear();
    groups.clear();

    totalNums = 66;

    subjects.push_back(Subject(0, 2, 55, 5, 3, "物理"));
    subjects.push_back(Subject(1, 1, 52, 2, 0, "地理"));
    subjects.push_back(Subject(2, 1, 48, 2, 0, "历史"));
    subjects.push_back(Subject(3, 1, 16, 4, 2, "政治"));
    subjects.push_back(Subject(4, 1, 27, 2, 0, "生物"));

    totalSubject = subjects.size();    

    groups.push_back(Group(0, 2, 4, 3));
    groups.push_back(Group(0, 1, 4, 12));
    groups.push_back(Group(0, 3, 4, 1));
    groups.push_back(Group(0, 1, 2, 13));
    groups.push_back(Group(0, 1, 2, 13));
    groups.push_back(Group(0, 1, 3, 4));
    groups.push_back(Group(0, 2, 3, 9));
    groups.push_back(Group(1, 2, 4, 9));
    groups.push_back(Group(1, 3, 4, 1));
    groups.push_back(Group(2, 3, 4, 1));

    totalPosition = 11;

    arrange();
}