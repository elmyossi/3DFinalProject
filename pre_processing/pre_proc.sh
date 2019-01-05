#!/bin/bash

FIGURE_FILE_WITHOUT_EXTENSION=../pre_processing/$1
if [ ! -f $FIGURE_FILE_WITHOUT_EXTENSION.obj ]; then
    python ../pre_processing/stl2obj.py  -o $FIGURE_FILE_WITHOUT_EXTENSION.obj $FIGURE_FILE_WITHOUT_EXTENSION.stl
fi
if [ ! -f ../pre_processing/points.txt ]; then
	xz $FIGURE_FILE_WITHOUT_EXTENSION.stl
	echo "Calculating Winding numbers..."
	date
	xzcat $FIGURE_FILE_WITHOUT_EXTENSION.stl.xz | python ../pre_processing/demo-turbo.py > ../pre_processing/points.txt
	wait
	date
	echo "Done"
fi
