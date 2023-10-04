#!/bin/sh

mkdir -p SmartCalc_dist SmartCalc_dist/model SmartCalc_dist/view SmartCalc_dist/controller SmartCalc_dist/tests

cd SmartCalc_dist
cp ../*.cc . 2>/dev/null
cp ../*.h . 2>/dev/null
cp ../*.sh . 2>/dev/null
cp ../readme.html . 2>/dev/null
cp ../Makefile . 2>/dev/null
cp ../CMakeLists.txt . 2>/dev/null
cp ../../.gitignore . 2>/dev/null
cp ../../CHANGELOG . 2>/dev/null
cp ../../LICENSE . 2>/dev/null
cp ../../README.md . 2>/dev/null
cp ../../README_RUS.md . 2>/dev/null

cp ../model/*.h model 2>/dev/null
cp ../model/*.cc model 2>/dev/null
cp ../model/CMakeLists.txt model 2>/dev/null

cp ../controller/*.h controller 2>/dev/null
cp ../controller/*.cc controller 2>/dev/null
cp ../controller/CMakeLists.txt controller 2>/dev/null

cp ../view/*.h view 2>/dev/null
cp ../view/*.cc view 2>/dev/null
cp ../view/*.ui view 2>/dev/null
cp ../view/CMakeLists.txt view 2>/dev/null

cp ../tests/*.h tests 2>/dev/null
cp ../tests/*.cc tests 2>/dev/null

cd ..

tar -czf SmartCalc_mac.tar.gz SmartCalc_dist/
