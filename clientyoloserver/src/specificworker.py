#
# Copyright (C) 2017 by YOUR NAME HERE
#
#    This file is part of RoboComp
#
#    RoboComp is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    RoboComp is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
#

import sys, os, traceback, time

from PySide import *
from genericworker import *
import cv2


class SpecificWorker(GenericWorker):
	def __init__(self, proxy_map):
		super(SpecificWorker, self).__init__(proxy_map)
		self.timer.timeout.connect(self.compute)
		self.Period = 2000
		self.timer.start(self.Period)

	def setParams(self, params):
		#try:
		#	self.innermodel = InnerModel(params["InnerModelPath"])
		#except:
		#	traceback.print_exc()
		#	print "Error reading config params"
		return True

	@QtCore.Slot()
	def compute(self):
		try:
			print 'SpecificWorker.compute...'
			img = cv2.imread('/home/ivan/robocomp/components/multimedia/pruebasMultimedia/yoloserver/src/yololib/dehesa_humano.jpg',cv2.IMREAD_COLOR)
			im = Image()
			height, width, channels = img.shape
			print height, width
			b,g,r = cv2.split(img)
			im.w=width
			im.h=height
			
			print 56
			id = self.yoloserver_proxy.addImage(im)
			print "el id es: ", id
			while self.yoloserver_proxy.getData(id):
				print "esperando"
		except Exception as e:
			print "error", e
