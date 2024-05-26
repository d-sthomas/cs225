/* Your code here! */
#include "maze.h"
#include <map>
#include <queue>
#include <stack>

using namespace std;
using namespace cs225;
/*
    No-parameter constructor.
    Creates an empty maze.
*/
SquareMaze::SquareMaze() {}

/*
    Makes a new SquareMaze of the given height and width.

    If this object already represents a maze it will clear all the existing data before doing so. 
    You will start with a square grid (like graph paper) with the specified height and width. 
    You will select random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.

    Hints: You only need to store 2 bits per square: the "down" and "right" walls. The finished maze is always a tree of corridors.)

    Parameters
    width: width of the SquareMaze (number of cells)
    height: height of the SquareMaze (number of cells)

*/
void SquareMaze::makeMaze(int width, int height) { 
    w = width;
    h = height;
    int size = w*h;
    maze.addelements(size); // 1d vector to represent 2d vector
    for (int i = 0; i < size; i++) {
        walls.push_back(pair<bool, bool> (true, true)); // makes all edges exists (graph with squares)
    }
    
    int j = 0;
    while( j < size-1) {
        int x = rand() % w;
        int y = rand() % h;
        bool wall = rand() % 2; // picks which size (left/down) to check

        if(!wall) {
            if(walls[x + y * w].second && (y < h - 1) && (maze.find(x + y * w) !=  maze.find(x + (y+1) * width))) { // checks down
                walls[x + y * w].second = false; // deletes bottom wall
                maze.setunion(maze.find(x + y * w), maze.find(x + (y+1)* w));
                j++;
            }
        } else {
            if(walls[x + y * w].first && (x < w - 1) && (maze.find(x + y * w) != maze.find(x + y * w + 1))) { // checks left
                walls[x + y * w].first = false; // deletes left wall
                maze.setunion(maze.find(x + y * w), maze.find(x + y * w + 1));
                j++;
            }
        }
    }
}

/*
    This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y). 
    For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).

    dir = 0 represents a rightward step (+1 to the x coordinate)
    dir = 1 represents a downward step (+1 to the y coordinate)
    dir = 2 represents a leftward step (-1 to the x coordinate)
    dir = 3 represents an upward step (-1 to the y coordinate)
    You can not step off of the maze or through a wall.

    This function will be very helpful in solving the maze. It will also be used by the 
    grading program to verify that your maze is a tree that occupies the whole grid, and 
    to verify your maze solution. So make sure that this function works!

    Parameters
    x: x coordinate of the current cell
    y: y coordinate of the current cell
    dir: desired direction to move from the current cell
    Returns whether you can travel in the specified direction    
*/
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {
        if (x >= w - 1) return false;
        return !walls[x + y * w].first;
    }
    if (dir == 1) {
        if (y >= h - 1) return false;
        return !walls[x + y * w].second;
    }
    if (dir == 2) {
        if (x < 1) return false;
        return !walls[(x - 1) + y * w].first;
    }
    if (dir == 3) {
        if (y < 1) return false;
        return !walls[x + (y - 1) * w].second;
    }
    return false;
}

/*
    Sets whether or not the specified wall exists.

    This function should be fast (constant time). 
    You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. 
    setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. 
    Our tests will call setWall to copy a specific maze into your implementation.

    Parameters
    x: x coordinate of the current cell
    y: y coordinate of the current cell
    dir: Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). You only need to support setting the bottom and right walls of every square in the grid.
    exists: true if setting the wall to exist, false otherwise
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if(dir == 0) {
        walls[x + y * w].first = exists;
    } else if(dir == 1) {
        walls[x + y * w].second = exists;
    }
}

/*
    Solves this SquareMaze.

    For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.

    Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
    solveMaze() returns the winning path from the origin to the destination as a vector of integers, where each integer represents the direction of a step, using the same encoding as in canTravel().

    If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.

    Hint: this function should run in time linear in the number of cells in the maze.

    Returns a vector of directions taken to solve the maze
*/
std::vector<int> SquareMaze::solveMaze() {
    vector<int> path;

    std::vector<int> bottom_edge;
    map<int, int> iter;
    vector<bool> visited;

    for(int i = 0; i < w * h; i++) visited.push_back(false);
    
    queue<int> traversal;
    traversal.push(0);
    visited[0] = true;

    while(!traversal.empty()) {
        int curr = traversal.front();
        traversal.pop();
        int x = curr % w;
        int y = curr / w;
        if(y == h -1) bottom_edge.push_back(curr);

        if(canTravel(x,y, 3) && visited[curr - w]== false) {
            iter.insert(pair<int, int>(curr - w, curr));
            visited[curr - w]= true;
            traversal.push(curr - w);
        }

        if(canTravel(x,y, 2) && visited[curr - 1]== false) {
            iter.insert(pair<int, int>(curr - 1, curr));
            visited[curr-1]= true;
            traversal.push(curr-1);
        }

        if(canTravel(x,y, 1) && visited[curr + w]== false) {
            iter.insert(pair<int, int>(curr + w, curr));
            visited[curr + w]= true;
            traversal.push(curr + w);
        }
        if(canTravel(x,y, 0) && visited[curr + 1]== false) {
            iter.insert(pair<int, int>(curr + 1, curr));
            visited[curr + 1]= true;
            traversal.push(curr + 1);
        }
    }
    
    stack<int> stack;
    int last = w - 1;
    while(bottom_edge[last] == bottom_edge[last-1]) last=-1;
  
    int start = bottom_edge[last];
    while(start !=0) {
        int prev = iter[start];
        if (start == prev - w) stack.push(3);
        else if (start == prev - 1) stack.push(2);
        else if (start == prev + w) stack.push(1);
        else if (start == prev + 1) stack.push(0);
        start = prev;
  }

    int size= stack.size();
    for(int i=0; i<size; i++ ) {
        path.push_back(stack.top());
        stack.pop();
    }
  return path;
}

/*
    Draws the maze without the solution.

    First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1), where height and width were the arguments to makeMaze.
    Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). 
    For each square in the maze, call its maze coordinates (x,y). 
    If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. 
    If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

    The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.

    Returns a PNG of the unsolved SquareMaze
*/
cs225::PNG* SquareMaze::drawMaze() const {
    PNG* image = new PNG(w * 10 + 1, h * 10 + 1);
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            if(j == 0) {
                for(unsigned k = 0; k < 10; k++){
                    if((i * 10 + k < 1)||(i * 10 + k > 9)){
                        HSLAPixel & cur_pixel = image->getPixel(i * 10 + k, 0);
                        cur_pixel.l = 0;
                    }
                }
            }
            if(i == 0) {
                for(unsigned k = 0; k < 10; k++){
                    HSLAPixel & cur_pixel = image->getPixel(0, j * 10 + k);
                    cur_pixel.l = 0;
                }
            }
            if(!canTravel(i, j, 0)) {
                for(unsigned k = 0; k <= 10; k++){
                    HSLAPixel & cur_pixel = image->getPixel((i + 1) * 10, j * 10 + k);
                    cur_pixel.l = 0;
                }
            }
            if(!canTravel(i, j, 1)) {
                for(unsigned k = 0; k <= 10; k++){
                    HSLAPixel & cur_pixel = image->getPixel(i * 10 + k, (j + 1) * 10);
                    cur_pixel.l = 0;
                }
            }
        }
    }
  return image;
}

/*
    This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

    Start at pixel (5,5). 
    Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. 
    If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). 
    Then if the second step is right, color pixels (5,15) through (15,15) red. 
    Then if the third step is up, color pixels (15,15) through (15,5) red. 
    Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.

    Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
*/
cs225::PNG* SquareMaze::drawMazeWithSolution() {
    PNG* image = drawMaze();
    std::vector<int> solution = solveMaze();
    int x = 5;
    int y = 5;

    for(unsigned i = 0; i < solution.size(); i++){
        if (solution[i] == 3) {
            for(int i = 0; i < 10; i++){
                HSLAPixel & cur_pixel = image->getPixel(x,y);
                cur_pixel.l = 0.5;
                cur_pixel.h = 0;
                cur_pixel.s =1;
                y--;
            }
        }
        if(solution[i] == 2){
            for(int i =0; i<10; i++){
                HSLAPixel & cur_pixel = image->getPixel(x,y);
                cur_pixel.l = 0.5;
                cur_pixel.h = 0;
                cur_pixel.s =1;
                x--;
            }
        }
        if(solution[i] == 1){
            for(int i =0; i<10; i++){
                HSLAPixel & cur_pixel = image->getPixel(x,y);
                cur_pixel.l = 0.5;
                cur_pixel.h = 0;
                cur_pixel.s =1;
                y++;
            }
        }
        if(solution[i] == 0){
            for(int i =0; i<10; i++){
                HSLAPixel & cur_pixel = image->getPixel(x,y);
                cur_pixel.l = 0.5;
                cur_pixel.h = 0;
                cur_pixel.s =1;
                x++;
            }
        }
    }
    HSLAPixel & wall = image->getPixel(x,y);
    wall.l = 0.5;
    wall.h = 0;
    wall.s = 1;
    wall.a = 1;
    x-=4;
    y+=5;

    for(int i =0; i<9; i++){
      HSLAPixel & cur_pixel = image->getPixel(x,y);
      cur_pixel.l = 1;
      cur_pixel.a =1;
      x++;
    }
    return image;
}