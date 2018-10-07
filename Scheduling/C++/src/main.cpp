#include<fstream>
#include<iostream>

struct node{
    int data;
    int timeReq;
    node *next;

    node(int id, int x){
        data = id;
        timeReq = x;
        next = NULL;
    }
};

struct linkedList{
    node* head;
    int size;

    linkedList(){
        head = NULL;
        size = 0;
    }

    void addNode(node *n){
        if(head == NULL) {
            head = n;
            size++;
            return;
        }
        if( (n->timeReq) <= (head->timeReq) ){
            n->next = head;
            head = n;
            size++;
            return;
        }
        node* temp = head;
        node* prev = head;
        while(temp->next!= NULL && (n->timeReq > temp->timeReq)){
            prev = temp;
            temp = temp->next;
        }
        if(n->timeReq <= temp->timeReq){
            prev->next = n;
            n->next = temp;
        }else{
            n->next = temp->next;
            temp->next = n;
        }
        size++;
    }

    node* removeHead(){
        node* temp = head;
        head = head->next;
        temp->next = NULL;
        size--;
        return temp;
    }

    bool isEmpty(){
        return size == 0;
    }

    void toString(){
        std::cout<< "Open LinkedListQueue\n";
        node* trans = head;
        while(trans!=NULL){
            std::cout << trans->data << " ";
            trans = trans->next;
        }
        std::cout << std::endl;
    }
};

class Scheduler{
    private:
    int numNode, totalJobTime, numProc, currentTime, processUsed;
    int** adjacencyMatrix, **scheduleTable;
    int* jobTime, *processTime, *processJob, *jobDone, *jobMarked, *parentCount;
    linkedList* open;

    public:
    Scheduler(int x){
        numNode = x;
        totalJobTime = currentTime = processUsed = 0;
        numProc = getProcessor();
        jobTime = new int[numNode+1];
        processJob = new int[numProc+1];
        processTime = new int[numProc+1];
        parentCount = new int[numNode+1];
        jobDone = new int[numNode+1];
        jobMarked = new int[numNode+1];
        open = new linkedList();
        adjacencyMatrix = new int*[numNode + 1];
        for(int i = 0; i < numNode+1; i++)
            adjacencyMatrix[i] = new int[numNode + 1];
        scheduleTable = new int*[numProc + 1];
    }

    ~Scheduler(){
        delete[]jobTime;
        delete[]processJob;
        delete[]processTime;
        delete[]parentCount;
        delete[]jobDone;
        delete[]jobMarked;
        delete open;
        for(int i = 0; i<=numNode; i++)
            delete[] adjacencyMatrix[i];
        for(int i = 0; i<=numProc; i++)
            delete[] scheduleTable[i];
        delete[] adjacencyMatrix;
        delete[] scheduleTable;
    }

    void loadMatrix(std::ifstream &input){
        int node, adj;
        while(input >> node){
            input >> adj;
            adjacencyMatrix[adj][node]++;
            parentCount[adj]++;
        }
    }

    void computeTotalJobTime(std::ifstream &input){
        int time, node, numNode;
        input >> numNode;
        while(input >> node){
            input >> time;
            jobTime[node] = time;
        }
        for(int i = 0; i <= numNode; i++)
            totalJobTime += jobTime[i];
        for(int i = 0; i < numProc+1; i++)
            scheduleTable[i] = new int[totalJobTime];

    }

    int getProcessor(){
        int x;
        std::cout << "Enter the number of processors:\n";
        std::cin >> x;
        if(x <= 0){
            std::cout << "Error\n";
            exit(0);
        }
        if(x > numNode) x = numNode;
        return x;
    }

    void run(std::ofstream &output){
        while(!isDone()){
            int orphan = getOrhpan();
            while(orphan != -1){
                jobMarked[orphan] = 1;
                node* newNode = new node(orphan, jobTime[orphan]);
                insertOpen(newNode);
                orphan = getOrhpan();
                open->toString();
            }
            open->toString();
            while(!open->isEmpty() && processUsed<numProc){
                int openProc = findProcessor();
                if(openProc>0) processUsed++;
                node* newJob = open->removeHead();
                processJob[openProc] = newJob->data;
                processTime[openProc] = newJob->timeReq;
                updateTable(openProc, newJob);
                delete newJob;
            }
            if(checkCycle()){
                std::cout << "Error: Cycle Found" << std::endl;
                output << "Error: Cycle Found";
                exit(1);
            }
            printTable(output);
            currentTime++;

            for(int i=1; i<=numProc; i++)
                if(processTime[i]>0)
                    processTime[i]--;
                

            for(int i=1; i <=numProc; i++){
                if(processJob[i]!=0 && processTime[i]==0){
                    int job = processJob[i];
                    processJob[i] = 0;
                    jobDone[job] = 1;
                    processUsed--;
                    for(int j=1; j<=numNode; j++)
                        if(adjacencyMatrix[j][job]>0) parentCount[j]--;
                }
            }
            debug();
        }
    }

    void debug(){
        std::cout << "current time: " << currentTime << std::endl;
        std::cout << "process used: " << processUsed << std::endl;
        std::cout << "current time: " << currentTime << std::endl;
        std::cout << "Job Marked" << std::endl;
        for(int i=1; i<=numNode; i++){
            std::cout << i << ": " << jobMarked[i] << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Job Done" << std::endl;
        for(int i=1; i<=numNode; i++){
            std::cout << i << ": " << jobDone[i] << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Process Job" << std::endl;
        for(int i=1; i<=numProc; i++){
            std::cout << i << ": " << processJob[i] << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Process Time" << std::endl;
        for(int i=1; i<=numProc; i++){
            std::cout << i << ": " << processTime[i] << std::endl;
        }
        std::cout << std::endl;
    }

    void updateTable(int openProc, node* n){
        int node = n->data;
        int jobTime = n->timeReq;
        for(int i = currentTime; i<currentTime+jobTime; i++){
            scheduleTable[openProc][i] = node;
        }
    }

    bool isDone(){
        for(int i = 1; i<=numNode; i++) 
            if(jobDone[i] == 0 ) return false;
        return true;
    }

    int getOrhpan(){
        for(int i =1; i<=numNode; i++){
            if(jobMarked[i]==0 && parentCount[i]==0) return i;
        }
        return -1;
    }

    void insertOpen(node* newNode){
        open->addNode(newNode);
    }

    int findProcessor(){
        for(int i = 1; i<=numProc; i++)
            if(processTime[i]<=0) return i;
        return -1;
    }

    void printTable(std::ofstream &output){
        for(int i = 0; i<=totalJobTime; i++){
            output << "-----" << i;
        }
        output << std::endl;
        for(int i = 1; i<=numProc; i++){
            output << "P(" << i << ") |";
            for(int j = 0; j<totalJobTime; j++){
                output << "    " << scheduleTable[i][j] << "  ";
                if(scheduleTable[i][j]<10) output << " ";
            }
            output << std::endl;
        }
    }

    bool checkCycle(){
        bool openEmpty = open->isEmpty();
        bool graph = false, proc = true;
        for(int i=1; i<=numNode; i++)
            if(jobDone[i]==0) graph = true;
        for(int i=1; i<=numProc; i++)
            if(processTime[i]>0) graph = false;
        if(openEmpty==true && graph==true && proc==true) return true;
        return false;  
    }
    
};


int main(int argc, char** argv){
    std::ifstream input1, input2;
    std::ofstream output;

    input1.open(argv[1]);
    input2.open(argv[2]);
    output.open(argv[3]);

    int numNode;
    input1 >> numNode;
    Scheduler schedule = Scheduler(numNode);
    schedule.loadMatrix(input1);
    schedule.computeTotalJobTime(input2);
    schedule.run(output);
    
    input1.close();
    input2.close();
    output.close();
    return 0;
}

