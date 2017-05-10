/*
 *    Copyright (C) 2017 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{

}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{

}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{    
        init_detector("src/yololib/cfg/coco.data", "src/yololib/yolo.cfg", "src/yololib/yolo.weights", "src/yololib/dehesa_humano.jpg", .24, .5);
        
  	timer.start(0);
	return true;
}

void SpecificWorker::compute()
{
    qDebug() << "hola";
    test_detector("src/yololib/cfg/coco.data", "src/yololib/yolo.cfg", "src/yololib/yolo.weights", "src/yololib/dehesa_humano.jpg", .24, .5);
}

int SpecificWorker::addImage(const Image &img)
{
	Image im;
	for(int k = 0; k < 3; ++k)
	{
      		for( int j = 0; j < img.h; ++j)
		{
          		for( int i = 0; i < img.w; ++i)
			{
              			int dst_index = i + img.w*j + img.h*k;
              			int src_index = k + i + img.w*j;
              			im.lpixel[dst_index] = (img.lpixel[src_index]); // /255;
          		}
      		}
  	}
	return lImgs.push(im);
}

Labels SpecificWorker::getData(const int id)
{
	Labels d;
	d.isReady = lBoxs.find(id);
	if(d.isReady==true)
	{
		d.lBox = lBoxs.get(id);
		lBoxs.erase(id);
	}
	return d;
}


















