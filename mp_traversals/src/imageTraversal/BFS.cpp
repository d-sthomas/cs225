#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  startPoint = start;
  max_tol = tolerance;
  image = png;
  add(startPoint);

  visited.resize(png.width());
  for (unsigned i = 0; i < visited.size(); i++) {
    visited[i].resize(png.height());
    for (unsigned j = 0; j < visited[i].size(); j++) {
      visited[i][j] = false;
    }
  }
  visited[startPoint.x][startPoint.y] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, startPoint, image);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(image);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  to_visit.push(point);
  
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  Point p = to_visit.front();
  to_visit.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  return empty() ? Point() : to_visit.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return to_visit.empty();
}

double BFS::getTolerance() const { return max_tol; }

void BFS::setVisit(Point p) { visited[p.x][p.y] = true; }

bool BFS::getVisit(Point p) { return visited[p.x][p.y]; }
