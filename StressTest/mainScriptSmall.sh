cd Hierarchical-locks-Tree/src
echo Compiting binary-tree ...
g++ main.cpp -std=gnu++0x -lpthread -o ../a.out
cd ../../Hierarchical-locks-Graph/src
echo Compiling directed-graph
g++ main.cpp -std=gnu++0x -lpthread -o ../a.out
cd ../..
g++ Plotter.cpp -o Plotter

cd ./Hierarchical-locks-Tree
echo Step:1 of 6: Executing DomLock over tree......
	./domscript_small.sh
echo Step:2 of 6: Executing Intention Lock over tree......
	./ILscript_small.sh

echo Step:3 of 6: Executing CA Lock over tree......
	./CALockScript_small.sh

cd ../Hierarchical-locks-Graph
echo Step:4 of 6: Executing DomLock over graph......
	./domscript_small.sh
echo Step:5 of 6: Executing Intention Lock over graph......
	./ILscript_small.sh
echo Step:6 of 6: Executing CA Lock over graph......
	./CALockScript_small.sh
cd ..
./Plotter
