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

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(MapPrx& mprx);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);

	int addImage(const image &img);
	data getData(const int id);

public slots:
	void compute();

private:
	struct listImg
	{
		unsigned int id, id_first;
		QMutex mlist;
		std::map<int, image> map_imgs;
		void listImg()
		{
			id = 0;
			id_first = 0;
		}
		unsigned int push(image img)
		{
				QMutexLocker locker(mlist);
				map_imgs[id] = img;
				id++;
				return id-1;
		};

		image pop()
		{
			QMutexLocker locker(mlist);
			image img = map_imgs.at(id_first);
			mlist.erase(id_first);
			id_first++;
			return img;
		};
		image get(unsigned int id)
		{
			QMutexLocker locker(mlist);
			return map_imgs.at(id);
		};

		bool emty()
		{
			QMutexLocker locker(mlist);
			return map_imgs.size()==0;
		};

		unsigned int size()
		{
			QMutexLocker locker(mlist);
			return map_imgs.size();
		};
	};

	struct listBoxs
	{
		QMutex mlist;
		std::map<unsigned int, listBox> map_Box;

		void push(listBox lBox, unsigned int id)
		{
				QMutexLocker locker(mlist);
				map_Box[id] = lBox;
		};

		listBox get(unsigned int id)
		{
			QMutexLocker locker(mlist);
			return map_Box.at(id);
		};

		void erase(unsigned int id)
		{
			QMutexLocker locker(mlist);
			map_Box.erase(id);
		};
		bool emty()
		{
			QMutexLocker locker(mlist);
			return map_Box.size()==0;
		};

		unsigned int size()
		{
			QMutexLocker locker(mlist);
			return map_Box.size();
		};
		bool find(unsigned int id)
		{
			QMutexLocker locker(mlist);
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

	listBoxs lBoxs;
	listImg lImgs;
	InnerModel *innerModel;

};

#endif
