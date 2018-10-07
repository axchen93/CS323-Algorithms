import java.util.Scanner;
import java.io.*;
class Scheduling{
    private int numNode, totalJobTime, numProc, currentTime, processUsed;
    private int adjacencyMatrix[][], scheduleTable[][];
    private int jobTime[], processTime[], processJob[], jobDone[], jobMarked[], parentCount[];
    private LinkedList open;

    public Scheduling(Scanner input1, Scanner input2){
        numNode = input1.nextInt();
        totalJobTime = currentTime = processUsed = 0;
        numProc = getProcessor();
        jobTime = new int[numNode+1];
        processJob = new int[numProc+1];
        processTime = new int[numProc+1];
        parentCount = new int[numNode+1];
        jobDone = new int[numNode+1];
        jobMarked = new int[numNode+1];
        open = new LinkedList();
        adjacencyMatrix = new int[numNode+1][numNode+1];
        loadMatrix(input1);
        computeTotalJobTime(input2);
        scheduleTable = new int[numProc+1][totalJobTime];
    }

    public void run(PrintWriter output){
        while(!isDone()){
            int orphan = getOrhpan();
            while(orphan != -1){
                jobMarked[orphan] = 1;
                Node newNode = new Node(orphan, jobTime[orphan]);
                insertOpen(newNode);
                orphan = getOrhpan();
            }
            open.to_String();
            while(!open.isEmpty() && processUsed<numProc){
                int openProc = findProcessor();
                if(openProc>0) processUsed++;
                Node newJob = open.removeHead();
                processJob[openProc] = newJob.getData();
                processTime[openProc] = newJob.getTime();
                updateTable(openProc, newJob);
            }
            if(checkCycle()){
                System.out.println("Error: Cycle Found");
                System.exit(0);
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

    private void debug(){
        System.out.println("current time: " + currentTime);
        System.out.println("process used: " + processUsed);
        System.out.println("current time: " + currentTime);
        System.out.println("Job Marked");
        for(int i=1; i<=numNode; i++){
            System.out.println(i + ": " + jobMarked[i]);
        }
        System.out.println();
        System.out.println("Job Done");
        for(int i=1; i<=numNode; i++){
            System.out.println(i + ": " + jobDone[i]);
        }
        System.out.println();
        System.out.println("Process Job");
        for(int i=1; i<=numProc; i++){
            System.out.println(i + ": " + processJob[i]);
        }
        System.out.println();
        System.out.println("Process Time");
        for(int i=1; i<=numProc; i++){
            System.out.println(i + ": " + processTime[i]);
        }
        System.out.println();
    }

    private boolean isDone(){
        for(int i = 1; i<=numNode; i++) 
            if(jobDone[i] == 0 ) return false;
        return true;
    }

    private int getOrhpan(){
        for(int i =1; i<=numNode; i++){
            if(jobMarked[i]==0 && parentCount[i]==0) return i;
        }
        return -1;
    }

    private int findProcessor(){
        for(int i = 1; i<=numProc; i++)
            if(processTime[i]<=0) return i;
        return -1;
    }

    private void insertOpen(Node n){
        open.addNode(n);
    }

    private void updateTable(int openProc, Node n){
        int node = n.getData();
        int jobTime = n.getTime();
        for(int i = currentTime; i<currentTime+jobTime; i++){
            scheduleTable[openProc][i] = node;
        }
    }

    private int getProcessor(){
        Scanner terminal = new Scanner(System.in);
        System.out.println("Enter the number of Processors:");
        int x = terminal.nextInt();
        if(x<=0){
            System.out.println("Error!");
            System.exit(0);
        }
        if(x > numNode) x = numNode;
        terminal.close();
        return x;
    }

    private void printTable(PrintWriter output){
        for(int i = 0; i<=totalJobTime; i++){
            output.print("------" + i);
        }
        output.println();
        for(int i = 1; i<=numProc; i++){
            output.print("P(" + i + ") |");
            for(int j = 0; j<totalJobTime; j++){
                output.print("    " + scheduleTable[i][j] + "  ");
                if(scheduleTable[i][j]<10) output.print(" ");
            }
            output.println();
        }
    }

    private boolean checkCycle(){
        boolean openEmpty = open.isEmpty();
        boolean graph = false, proc = true;
        for(int i=1; i<=numNode; i++)
            if(jobDone[i]==0) graph = true;
        for(int i=1; i<=numProc; i++)
            if(processTime[i]>0) graph = false;
        if(openEmpty==true && graph==true && proc==true) return true;
        return false;  
    }

    private void loadMatrix(Scanner input){
        while(input.hasNextInt()){
            int node = input.nextInt();
            int adj = input.nextInt();
            adjacencyMatrix[adj][node]++;
            parentCount[adj]++;
        }
    }

    private void computeTotalJobTime(Scanner input){
        int time, node, numNode;
        numNode = input.nextInt();
        while(input.hasNextInt()){
            node = input.nextInt();
            time = input.nextInt();
            jobTime[node] = time;
            totalJobTime += time;
        }
    }
}