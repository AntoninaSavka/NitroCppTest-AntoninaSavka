#ifndef USING_H_
#define USING_H_

#include <set>
#include <vector>

#include "Point2D.h"
#include "Rectangle2D.h"

using RectIndexes = std::set<unsigned long>;
using Rectangle2DPtr = std::shared_ptr<Rectangle2D>;
using RectDescr = std::pair<RectIndexes, Rectangle2DPtr>;

using RectDescrList = std::vector<RectDescr>;

#endif //USING_H_
