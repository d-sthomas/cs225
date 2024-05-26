/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>


Graph::Graph(const V2D& corrected) {
    // resizes matrix to classses x classes
    adj_matrix.resize(corrected.size(), std::vector<bool> (corrected.size())); 
    // goes through entire matrix twice to check for edges
    for (unsigned r = 0; r < corrected.size(); r++) {
        for (unsigned c = 1; c < corrected[r].size(); c++) {
            for (unsigned i = r+1; i < corrected.size(); i++) {
                for (unsigned j = 1; j < corrected[i].size(); j++) {
                    if (corrected[r][c] == corrected[i][j]) {
                        adj_matrix[r][i] = 1;
                        adj_matrix[i][r] = 1;
                    }
                }
            }
        }
    }
}

std::vector<std::vector<bool>> Graph::get_matrix() { return adj_matrix; }


/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    std::string file = file_to_string(filename);
    V2D to_return;
    std::stringstream ss(file);
    while(ss.good()) {
        std::string substr;
        while(getline(ss, substr)) {
            std::vector<std::string> line;
            std::stringstream split(substr);
            std::string value;
            while (getline(split, value, ',')) {
                line.push_back(Trim(value));
            }
            to_return.push_back(line);
        }
    }
    return to_return;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D cleaned;
    for (std::vector<std::string> course : cv) {
        std::vector<std::string> correct_class;
        correct_class.push_back(course[0]);
        for (unsigned i = 1; i < course.size(); i++) {
            bool in_class = false;
            for (std::vector<std::string> child : student) {
                if (child[0] == course[i]) {
                    for (unsigned j = 1; j < child.size(); j++) {
                    if (child[j] == course[0]) in_class = true;
                    }
                }
            }
            
            if (in_class) {
                correct_class.push_back(course[i]);
            }
            
        }
        if (correct_class.size() > 1) cleaned.push_back(correct_class);
    }
    return cleaned;
}


bool safeColor(std::vector<std::vector<bool>> adj, int v, int c, std::vector<int> &slots) {
    for (unsigned i = 0; i < slots.size(); i++) {
        if(adj[v][i] && (c == slots[i]))
            return false;      
    }
    return true;  
}


bool graphColoring(std::vector<std::vector<bool>> adj, int m, unsigned v, std::vector<int> &slots)
{
    if (v == slots.size()) return true;

    for (int i = 1; i <= m; i++) {
        if (safeColor(adj, v, i, slots))
        {
            slots[v] = i;
            if (graphColoring(adj, m, v+1, slots))
                return true;
            slots[v] = 0;
        }
    }
    return false;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    Graph g(courses);
    V2D exam_schedule;
    std::vector<std::vector<bool>> adj_matrix = g.get_matrix();
    
    int times = timeslots.size();
    std::vector<int> exams;
    exams.resize(adj_matrix.size());
    if (graphColoring(adj_matrix, times, 0, exams)) {
        for (int i = 0; i < times; i++) {
            std::vector<std::string> classes;
            classes.push_back(timeslots[i]);
            for (unsigned j = 0; j < exams.size(); j++) {
                if (exams[j] == i+1) {
                    classes.push_back(courses[j][0]);
                }
            }
            exam_schedule.push_back(classes);
        }
    } else {
        std::vector<std::string> invalid;
        invalid.push_back("-1");
        exam_schedule.push_back(invalid);
    }
    return exam_schedule;
}