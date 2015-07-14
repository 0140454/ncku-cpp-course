#ifndef STAIRS_H
#define STAIRS_H

#include "Stair.h"
#include "StairNormal.h"
#include "StairLeft.h"
#include "StairRight.h"
#include "StairSpiked.h"
#include "StairSpring.h"
#include "StairOnetime.h"

Stair *GenStair(int pos_y, QWidget *parent);

#endif // STAIRS_H
