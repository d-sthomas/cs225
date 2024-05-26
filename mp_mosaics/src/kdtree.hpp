/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    else if (second[curDim] < first[curDim]) return false;
    else return first < second;
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& first, const Point<Dim>& second) const {
  int dist = 0;
  for (int i = 0; i < Dim; ++i) {
      dist += pow(first[i] - second[i], 2);
  }
  return dist;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currDist = distance(target, currentBest);
    double potDist = distance(target, potential);
    
    if (potDist != currDist) return potDist < currDist;
    if (potDist < currDist) return true;
    else if (currDist < potDist) return false;
    else return potential < currentBest;
}
template <int Dim>
unsigned KDTree<Dim>::partition(unsigned left, unsigned right, unsigned dim, unsigned pivotidx) {
    Point<Dim> pivotval = points[pivotidx]; 
    std::swap(points[pivotidx], points[right]);
    unsigned storeidx = left;
    for (unsigned i = left; i <= right-1; i++) {
      if (smallerDimVal(points[i], pivotval, dim)) {
        std::swap(points[i], points[storeidx]);
        storeidx++;
      }
    }
    std::swap(points[right], points[storeidx]);
    return storeidx;
}
template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(unsigned left, unsigned right, unsigned mid, unsigned dim) {
    if (left == right) return points[left];
    unsigned pivotidx = floor((left+right)/2);
    pivotidx = partition(left, right, dim, pivotidx);
    
    if (mid == pivotidx) return points[mid];
    else if (mid > pivotidx) return quickselect(pivotidx + 1, right, mid, dim);
    else return quickselect(left, pivotidx - 1, mid, dim);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build(unsigned left, unsigned right, unsigned dim) {
    //base case
    if (left < 0 || left > size || left > right || right < 0 || right > size) return NULL;
    unsigned median = floor((left+right)/2); 
    Point<Dim> subroot = quickselect(left, right, median, dim);
    KDTreeNode* curr = new KDTreeNode(subroot);
    curr->left = build(left, median-1, (dim+1)%Dim);
    curr->right = build(median+1, right, (dim+1)%Dim);
    return curr; 
}
    

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    
    size = newPoints.size();
    points = newPoints;
    int dim = 0;
    if (!newPoints.empty()) {
      root = build(0, size-1, 0);
    } else root = NULL;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(KDTreeNode * subroot) {
    if (subroot != NULL) {
      KDTreeNode* curr = new KDTreeNode(subroot -> point);
      curr->left = _copy(subroot->left);
      curr->right = _copy(subroot->right);
      return curr;
    }
    else return NULL;
}

template <int Dim>
void KDTree<Dim>::_delete(KDTreeNode * subroot) {
    if (subroot != NULL) {
      _delete(subroot->left);
      _delete(subroot->right);
      delete subroot;
    }
    else return;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  points = other.points;
  root = _copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (rhs == this) return *this;
  else {
    _delete(root);
    size = rhs.size;
    points = rhs.points;
    root = _copy(rhs.root);
  }
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _delete(root);
}
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_find(unsigned dim, const Point<Dim>& query, KDTreeNode* subroot, KDTreeNode* currentBest) const {
  if ((subroot->left == NULL && subroot->right == NULL ) || subroot->point == query) return subroot; // leaf node or actually found
  else if (smallerDimVal(query, subroot->point, dim)) {
    if (subroot->left != NULL) currentBest = _find((dim+1)%Dim, query, subroot->left, currentBest);
    else currentBest = subroot;

    if (shouldReplace(query, currentBest->point, subroot->point)) currentBest = subroot;

    double currDist = distance(query, currentBest->point);
    if (subroot->right != NULL && pow(query[dim] - subroot->point[dim], 2) <= currDist) {
      KDTreeNode* otherSide = _find((dim+1)%Dim, query, subroot->right, currentBest);
      Point<Dim> other = otherSide->point;
      if (shouldReplace(query, currentBest->point, other))
        currentBest = otherSide;
    }
  } else {
    if (subroot->right != NULL) currentBest = _find((dim+1)%Dim, query, subroot->right, currentBest);
    else currentBest = subroot;

    if (shouldReplace(query, currentBest->point, subroot->point)) currentBest = subroot;
    double currDist = distance(query, currentBest->point);
    if (subroot->left != NULL && pow(query[dim] - subroot->point[dim], 2) <= currDist) {
      KDTreeNode* otherSide = _find((dim+1)%Dim, query, subroot->left, currentBest);
      Point<Dim> other = otherSide->point;
      if (shouldReplace(query, currentBest->point, other))
        currentBest = otherSide;
    }
  }
  return currentBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return _find(0, query, root, NULL)->point;
}

