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

/**
       \brief
       @author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>


extern "C" {
    void test_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh, float hier_thresh);
    void init_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh, float hier_thresh);
//    void cuda_set_device(int n);
    //#include "cuda.h"
}

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(MapPrx& mprx);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);

	int addImage(const Image &img);
	Labels getData(const int id);

public slots:
	void compute();

private:
	struct ListImg
	{
		unsigned int id, id_first;
		QMutex mlist;
		std::map<int, Image> map_imgs;
		void listImg()
		{
			id = 0;
			id_first = 0;
		}
		unsigned int push(Image img)
		{
				QMutexLocker locker(&mlist);
				map_imgs[id] = img;
				id++;
				return id-1;
		};

		Image pop()
		{
			QMutexLocker locker(&mlist);
			Image img = map_imgs.at(id_first);
			map_imgs.erase(id_first);
			id_first++;
			return img;
		};
		Image get(unsigned int id)
		{
			QMutexLocker locker(&mlist);
			return map_imgs.at(id);
		};

		bool empty()
		{
			QMutexLocker locker(&mlist);
			return map_imgs.size()==0;
		};

		unsigned int size()
		{
			QMutexLocker locker(&mlist);
			return map_imgs.size();
		};
	};

	struct ListBoxs
	{
		QMutex mlist;
		std::map<unsigned int, ListBox> map_Box;

		void push(ListBox lBox, unsigned int id)
		{
			QMutexLocker locker(&mlist);
			map_Box[id] = lBox;
		};

		ListBox get(unsigned int id)
		{
			QMutexLocker locker(&mlist);
			return map_Box.at(id);
		};

		void erase(unsigned int id)
		{
			QMutexLocker locker(&mlist);
			map_Box.erase(id);
		};
		bool emty()
		{
			QMutexLocker locker(&mlist);
			return map_Box.size()==0;
		};

		unsigned int size()
		{
			QMutexLocker locker(&mlist);
			return map_Box.size();
		};
		bool find(unsigned int id)
		{
			QMutexLocker locker(&mlist);
			try
			{
				map_Box.at(id);
				return true;
			}
			catch(...)
			{
				return false;
			}
		};
	};

	ListBoxs lBoxs;
	ListImg lImgs;
	InnerModel *innerModel;

};

#endif
