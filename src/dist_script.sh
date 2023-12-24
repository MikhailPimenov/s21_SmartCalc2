#!/bin/sh

mkdir -p SmartCalc_dist SmartCalc_dist/model SmartCalc_dist/model/calculator SmartCalc_dist/model/credit SmartCalc_dist/model/deposit SmartCalc_dist/model/graph SmartCalc_dist/model/parcer SmartCalc_dist/model/rpn SmartCalc_dist/view SmartCalc_dist/controller SmartCalc_dist/protocol SmartCalc_dist/tests 

cd SmartCalc_dist
cp ../*.cc . 2>/dev/null
cp ../*.h . 2>/dev/null
cp ../*.sh . 2>/dev/null
cp ../readme.html . 2>/dev/null
cp ../Makefile . 2>/dev/null
cp ../test_valgrind_ubuntu_docker . 2>/dev/null
cp ../CMakeLists.txt . 2>/dev/null
cp ../../.gitignore . 2>/dev/null
cp ../../Dockerfile_ubuntu . 2>/dev/null
cp ../../test_valgrind_ubuntu_docker.sh . 2>/dev/null
cp ../../CHANGELOG . 2>/dev/null
cp ../../LICENSE . 2>/dev/null
cp ../../README.md . 2>/dev/null
cp ../../README_RUS.md . 2>/dev/null



cp ../model/calculator/*.h model/calculator 2>/dev/null
cp ../model/calculator/*.cc model/calculator 2>/dev/null
cp ../model/calculator/CMakeLists.txt model/calculator 2>/dev/null

cp ../model/credit/*.h model/credit 2>/dev/null
cp ../model/credit/*.cc model/credit 2>/dev/null
cp ../model/credit/CMakeLists.txt model/credit 2>/dev/null

cp ../model/deposit/*.h model/deposit 2>/dev/null
cp ../model/deposit/*.cc model/deposit 2>/dev/null
cp ../model/deposit/CMakeLists.txt model/deposit 2>/dev/null

cp ../model/graph/*.h model/graph 2>/dev/null
cp ../model/graph/*.cc model/graph 2>/dev/null
cp ../model/graph/CMakeLists.txt model/graph 2>/dev/null

cp ../model/parcer/*.h model/parcer 2>/dev/null
cp ../model/parcer/*.cc model/parcer 2>/dev/null
cp ../model/parcer/CMakeLists.txt model/parcer 2>/dev/null

cp ../model/rpn/*.h model/rpn 2>/dev/null
cp ../model/rpn/*.cc model/rpn 2>/dev/null
cp ../model/rpn/CMakeLists.txt model/rpn 2>/dev/null

cp ../model/CMakeLists.txt model 2>/dev/null


cp ../controller/*.h controller 2>/dev/null
cp ../controller/*.cc controller 2>/dev/null
cp ../controller/CMakeLists.txt controller 2>/dev/null

cp ../view/*.h view 2>/dev/null
cp ../view/*.cc view 2>/dev/null
cp ../view/*.ui view 2>/dev/null
cp ../view/CMakeLists.txt view 2>/dev/null

cp ../protocol/*.h protocol 2>/dev/null

cp ../tests/*.h tests 2>/dev/null
cp ../tests/*.cc tests 2>/dev/null

cd ..

tar -czf SmartCalc_mac.tar.gz SmartCalc_dist/
