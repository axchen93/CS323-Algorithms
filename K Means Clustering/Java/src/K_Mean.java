import java.io.PrintWriter;
import java.util.Scanner;

class K_Mean{
    private int K;
    private int numRows;
    private int numCols;
    private int numPoints;
    private Points[] ptList;
    private int[][] imageArray;
    private xyCoord[] centroidList;
    private int numLabelChange;
    private static int iteration = 0;

    K_Mean(int k, int nr, int nc, int np){
        K = k;
        numRows = nr;
        numCols = nc;
        numPoints = np;
        ptList = new Points[numPoints];
        imageArray = new int[numRows][numCols];
        centroidList = new xyCoord[K+1];
        numLabelChange = 1;
    }

    public int getNumLabelChange(){
        return numLabelChange;
    }
    
    public void loadPtList(Scanner input){
        int newRow, newCol, i = 0, label = 1;
        while(input.hasNext()){
            newRow = input.nextInt();
            newCol = input.nextInt();
            ptList[i] =  new Points(newRow, newCol, label);
            if(label == K) label = 1;
            else label++;
            i++;
        }
    }

    public void printImage(PrintWriter output){
        
        output.println("Groups after " + iteration + " iterations:");
        for(int i = 0; i<numRows; i++){
            for(int j = 0; j<numCols; j++){
                if(imageArray[i][j]>0) output.print(imageArray[i][j]);
                else output.print(" ");
            }
            output.println();
        }
        iteration++;
    }

    public void printPt(PrintWriter output){
        output.println("Labels after " + iteration + " iterations:");
        for(int i = 0; i < numPoints; i++){
            Points temp = ptList[i];
            output.println(temp.getX() + " " + temp.getY() + " " + temp.getLabel());
        }
    }

    public void mapPointToImg(){
        for(int i = 0; i < numPoints; i++){
            Points temp = ptList[i];
            imageArray[temp.getX()][temp.getY()] = temp.getLabel();
        }
    }

    public void computeCentroid(){
        int sumX[] = new int[K+1];
        int sumY[] = new int[K+1];
        int count[] = new int[K+1];
        for(int i = 0 ; i < numPoints; i++){
            Points temp = ptList[i];
            int x = temp.getX();
            int y = temp.getY();
            int label = temp.getLabel();
            count[label]++;
            sumX[label] += x;
            sumY[label] += y; 
        }
        for(int i = 1 ; i<=K ; i++){
            int xCoord = sumX[i]/count[i];
            int yCoord = sumY[i]/count[i];
            centroidList[i] = new xyCoord(xCoord, yCoord, i);
        }
    }

    public void clusterCheck(){
        numLabelChange = 0;
        double dist[] = new double[K+1];
        for(int i = 0; i< numPoints; i++){
            Points tempPt = ptList[i];
            for(int j = 1; j<=K; j++){
                dist[j] = computeDist(tempPt, centroidList[j]);
            }
            int currentLabel = tempPt.getLabel();
            double currentDistance  = dist[currentLabel];
            for(int j = 1; j<=K; j++){
                if(dist[j] < currentDistance){
                    currentDistance = dist[j];
                    currentLabel = j;
                }
            }
            if(currentLabel!=tempPt.getLabel()){
                tempPt.setLabel(currentLabel);
                numLabelChange++;
            }
        }
    }

    private double computeDist(Points p, xyCoord x){
        double ptX = p.getX();
        double ptY = p.getY();
        int ptL = p.getLabel();
        double centX = x.getX();
        double centY = x.getY();
        int centL = x.getLabel();
        double sqX = (ptX - centX) * (ptX - centX);
        double sqY = (ptY - centY) * (ptY - centY);
        return  Math.sqrt(sqX + sqY);
    }
}