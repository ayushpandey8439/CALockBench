cd Hierarchical-locks-Tree/src
echo Compiting binary-tree ...
g++ main.cpp -std=gnu++0x -lpthread -o ../a.out
cd ../../Hierarchical-locks-Graph/src
echo Compiling directed-graph
g++ main.cpp -std=gnu++0x -lpthread -o ../a.out
cd ../..
g++ Plotter.cpp -o Plotter

cd Hierarchical-locks-Tree
echo Step:1 of 6: Executing DomLock over tree......
	./domscript.sh
echo Step:2 of 6: Executing Intention Lock over tree......
  ./ILscript.sh
echo Step:3 of 6: Executing CALock over tree......
	./CALockScript.sh

cd ../Hierarchical-locks-Graph
echo Step:4 of 6: Executing DomLock over graph......
	./domscript.sh
echo Step:5 of 6: Executing Intention Lock over graph......
	./ILscript.sh
echo Step:6 of 6: Executing CALock over graph......
	./CALockScript.sh
cd ..
./Plotter
