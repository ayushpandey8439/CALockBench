cd Hierarchical-locks-Tree/src
echo Compiting binary-tree ...
rm -rf ../a.out
g++ main.cpp -std=c++20 -lpthread -o ../a.out
cd ../..

g++ NoBucket_Plotter.cpp -o NoBucket_Plotter
g++ Skewness_Plotter.cpp -o Skewness_Plotter
g++ Depth_Plotter.cpp -o Depth_Plotter
cd Hierarchical-locks-Tree

echo Stage 1 of 4: Benchmarking execution time against number of nodes locked.
echo Step:1 of 6: Executing DomLock over tree......
	./domscript_noBucket.sh
echo Step:2 of 6: Executing CALock over tree......
	./CALockScript_noBucket.sh
echo Step:3 of 6: Executing Intention Lock over tree......
  ./ILscript_noBucket.sh

echo Stage 2 of 4: Benchmarking execution time against skewness of nodes locked.
echo Step:1 of 3: Executing DomLock over tree......
	./domscript_Bucket.sh
echo Step:2 of 3: Executing CALock over tree......
	./CALockScript_Bucket.sh
echo Step:3 of 3: Executing Intention Lock over tree......
  ./ILscript_Bucket.sh


echo Stage 3 of 4: Benchmarking execution time against Depth of Hierarchy.
echo Step:1 of 3: Executing DomLock over tree......
	./domscript_Depth.sh
echo Step:2 of 3: Executing CALock over tree......
	./CALockScript_Depth.sh
echo Step:3 of 3: Executing Intention Lock over tree......
  ./ILscript_Depth.sh
cd ..

./NoBucket_Plotter
./Depth_Plotter
./Skewness_Plotter

python NodesLockedTree.py
#python NodesLockedGraph.py
python SkewnessImage.py
python DepthTree.py
