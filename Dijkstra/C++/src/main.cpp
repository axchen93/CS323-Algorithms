#include<fstream>
#include<iostream>
class DijkstraSSS{
    int numNode, sourceNode, minNode, currentNode, newCost;
    int** costMatrix;
    int* fatherAry, *markedAry, *bestCostArry;


    public:
    DijkstraSSS(int x){
        numNode = x;
        sourceNode = 1;
        fatherAry = new int[numNode];
        markedAry = new int[numNode];
        bestCostArry = new int[numNode];
        costMatrix = new int*[numNode];
        for(int i = 0; i<numNode; i++)
            costMatrix[i] = new int[numNode];
        for(int i = 0; i<numNode; i++){
            for(int j = 0; j<numNode; j++){
                if(i==j) costMatrix[i][j] = 0;
                else costMatrix[i][j] = 99999;
            }
            fatherAry[i] = i;
            bestCostArry[i] = 99999;
            markedAry[i] = 0;
        }
    }

    ~DijkstraSSS(){
        delete []fatherAry;
        delete []markedAry;
        delete []bestCostArry;
        for(int i = 0; i<numNode; i++)
            delete []costMatrix[i];
        delete []costMatrix;
    }

    void loadCostMatrix(std::ifstream& input){
        int v1, v2, cost;
        while(input>>v1>>v2>>cost){
            costMatrix[v1-1][v2-1] = cost;
        }
    }

    void run(std::ofstream& out1, std::ofstream& out2){
        while(sourceNode<=numNode){
            setBestCostAry();
            setFatherArry();
            setMarkedArry();
            while(!allMarked()){
                minNode = findMindNode();
                markMinNode(minNode-1);
                debug(out2);
                currentNode = 1;
                while(currentNode <= numNode){
                    if(markedAry[currentNode-1]==0){
                        newCost = computeCost(minNode-1, currentNode-1);
                        if(newCost < bestCostArry[currentNode-1]){
                            changeCost(currentNode-1, newCost);
                            changeFather(currentNode-1, minNode);
                            debug(out2);
                        }
                    }
                    currentNode++;
                }
            }
            out1 << "Source Node = " << sourceNode << std::endl;
            out1 << "The shortest path from the source node " << sourceNode << " are:" << std::endl;
            currentNode=1;
            while(currentNode<=numNode){
                printShortestPath(out1);
                currentNode++;
            }
            sourceNode++;
            out1 << std::endl << "=========================================================" << std::endl;
        }
    }

    void setBestCostAry(){
        for(int i = 0; i<numNode; i++)
            bestCostArry[i] = costMatrix[sourceNode-1][i];
    }

    void setFatherArry(){
        for(int i = 0; i<numNode; i++)
            fatherAry[i] = sourceNode;
    }

    void setMarkedArry(){
        for(int i = 0; i<numNode; i++)
            if(i == sourceNode-1) markedAry[i] = 1;
            else markedAry[i] = 0;
    }

    void changeFather(int node, int min){
        fatherAry[node] = min;
    }

    int computeCost(int x, int y){
        return bestCostArry[x] + costMatrix[x][y];
    }

    void changeCost(int node, int cost){
        bestCostArry[node] = cost;
    }

    bool allMarked(){
        for(int i = 0; i<numNode; i++)
            if(markedAry[i]==0) return false;
        return true;
    }

    int findMindNode(){
        int min = 0, minCost=100000;
        for(int i = 0; i<numNode; i++){
            if(bestCostArry[i]<minCost && markedAry[i]==0){
                min = i;
                minCost = bestCostArry[i];
            }
        }
        return min+1;
    }

    void markMinNode(int s){
        markedAry[s] = 1;
    }

    void printShortestPath(std::ofstream& output){
        int vert1 = fatherAry[currentNode-1], vert2=currentNode; 
        output << "The path from " << sourceNode << " to " << currentNode << " : " << vert2;
        while(vert1!=sourceNode){
            output << " <- " << vert1;
            vert2 = vert1;
            vert1 = fatherAry[vert2-1];
        }
        output << " <- " << sourceNode << ": cost = " << bestCostArry[currentNode-1] << std::endl;
    }

    void debug(std::ofstream& output){
        output << "The source node is " << sourceNode << std::endl;
        output << "Min-node " << minNode << std::endl;
        output << "The fatherArray is: " << std::endl;
        for(int i = 0; i<numNode; i++)
            output << fatherAry[i] << " ";
        output << std::endl;
        output << "The bestCostArray is: " << std::endl;
        for(int i = 0; i<numNode; i++)
            output << bestCostArry[i] << " ";
        output << std::endl;
        output << "The markedArray is: " << std::endl;
        for(int i = 0; i<numNode; i++)
            output << markedAry[i] << " ";
        output << std::endl << std::endl;
    }
};

int main(int argc, char** argv){
    std::ifstream input;
    std::ofstream output1, output2;
    input.open(argv[1]);
    output1.open(argv[2]);
    output2.open(argv[3]);

    int numNode;
    input >> numNode;
    output1 << "==============================\n" << "There are " << numNode << " nodes in this graph\n";
    output1 << "==============================\n";
    DijkstraSSS ss = DijkstraSSS(numNode);
    ss.loadCostMatrix(input);
    ss.run(output1, output2);
    output1.close();
    output2.close();
    input.close();
}
