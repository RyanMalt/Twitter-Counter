#!/bin/bash

cd PythonModules

cd setuptools-15.2
python setup.py build
sudo python setup.py install

cd ../httplib2-master
python setup.py build
sudo python setup.py install

cd ../simplejson-3.6.5
python setup.py build
sudo python setup.py install

cd ../python-oath2-master
python setup.py build
sudo python setup.py install

cd ../python-twitter-1.1
python setup.py build
sudo python setup.py install

cd ../Source_Code
g++ main.cpp HashTable.cpp Location.cpp Pair.cpp WordParser.cpp TrieTree.cpp -o Tweetalyzer.out
mv Tweetalyzer.out ../Tweetalyzer.out

cd ..
