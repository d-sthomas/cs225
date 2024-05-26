/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  double getTolerance() const;
  void setVisit(Point p);
  bool getVisit(Point p);

private:
	/** @todo [Part 1] */
	/** add private members here*/
  std::stack<Point> to_visit;
  Point startPoint;
  double max_tol = 0;
  cs225::PNG image;
  std::vector<std::vector<bool>> visited;
};
