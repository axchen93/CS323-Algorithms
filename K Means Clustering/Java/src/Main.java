import java.util.Scanner;
import java.io.*;

class Main{
    public static void main(String args[]){
        try{
        Scanner terminal = new Scanner(System.in);
        Scanner input = new Scanner(new FileReader(args[0]));
        PrintWriter output = new PrintWriter(args[1]);
        PrintWriter output2 = new PrintWriter(args[2]);
        
        int numRows, numCols, kCluster, numPoints;
        System.out.println("Enter number of K:");
        kCluster = terminal.nextInt();
        numRows = input.nextInt();
        numCols = input.nextInt();
        numPoints = input.nextInt();

        K_Mean kMean = new K_Mean(kCluster, numRows, numCols, numPoints);
        
        kMean.loadPtList(input);
        
        int i = 0;
        while(kMean.getNumLabelChange()>0 && i<2*kCluster){
            kMean.mapPointToImg();
            kMean.printPt(output);
            kMean.printImage(output2);
            kMean.computeCentroid();
            kMean.clusterCheck();
            i++;
        }
       
        input.close();
        output.close();
        output2.close();
        }catch(Exception e){}
    }
}

    