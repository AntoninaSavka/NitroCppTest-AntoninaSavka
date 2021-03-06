#ifndef USING_H_
#define USING_H_

#include <vector>
#include <memory>

#include "Point2D.h"
#include "Rectangle2D.h"

using Rectangle2DPtr = std::shared_ptr<Nitro::Rectangle2D>;
using RectDescrList = std::vector<Rectangle2DPtr>;

#endif //USING_H_
