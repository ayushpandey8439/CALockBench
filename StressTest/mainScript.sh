cd Hierarchical-locks-Tree/src
echo Compiting binary-tree ...
g++ main.cpp -std=gnu++0x -lpthread -o ../a.out
cd ../../Hierarchical-locks-Graph/src
echo Compiling directed-graph
g++ main.cpp -std=gnu++0x -lpthread -o ../a.out
cd ../..
g++ NoBucket_Plotter.cpp -o NoBucket_Plotter
g++ Skewness_Plotter.cpp -o Skewness_Plotter

echo Stage 1 of 2: Benchmarking execution time against number of nodes locked.
cd Hierarchical-locks-Tree
echo Step:1 of 6: Executing DomLock over tree......
	./domscript_noBucket.sh
echo Step:2 of 6: Executing CALock over tree......
	./CALockScript_noBucket.sh
echo Step:3 of 6: Executing Intention Lock over tree......
  ./ILscript_noBucket.sh

cd ../Hierarchical-locks-Graph
echo Step:4 of 6: Executing DomLock over graph......
	./domscript_noBucket.sh
echo Step:5 of 6: Executing CALock over graph......
	./CALockScript_noBucket.sh
echo Step:6 of 6: Executing Intention Lock over graph......
	./ILscript_noBucket.sh
cd ..
./NoBucket_Plotter


echo Stage 2 of 2: Benchmarking execution time against skewness of nodes locked.
cd Hierarchical-locks-Tree
echo Step:1 of 6: Executing DomLock over tree......
	./domscript_Bucket.sh
echo Step:2 of 6: Executing CALock over tree......
	./CALockScript_Bucket.sh
echo Step:3 of 6: Executing Intention Lock over tree......
  ./ILscript_Bucket.sh
cd ..
./Skewness_Plotter

python NodesLockedTree.py
python NodesLockedGraph.py
python SkewnessImage.py
