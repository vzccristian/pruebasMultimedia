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
//       THE FOLLOWING IS JUST AN EXAMPLE
//
//	try
//	{
//		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
//		innermodel_path = par.value;
//		innermodel = new InnerModel(innermodel_path);
//	}
//	catch(std::exception e) { qFatal("Error reading config params"); }




	timer.start(Period);


	return true;
}

void SpecificWorker::compute()
{
	QMutexLocker locker(mutex);
}


int SpecificWorker::addImage(const image &img)
{
	image im;
	for(int k = 0; k < 3; ++k){
      for( int j = 0; j < img.h; ++j){
          for( int i = 0; i < img.w; ++i)
					{
              int dst_index = i + w*j + w*h*k;
              int src_index = k + c*i + c*w*j;
              im.data[dst_index] = (float)data[src_index]/255.;
          }
      }
  }
	return lImgs.push(im);
}

data SpecificWorker::getData(const int id)
{
	data d;
	d.isReady = lBoxs.find(id);
	if(d.isReady==true)
	{
		d.lBox = lBoxs.get(id)
		lBoxs.erase(id)
	}
	retunr d;
}
