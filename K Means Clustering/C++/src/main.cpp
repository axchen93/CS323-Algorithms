#include<fstream>
#include<iostream>
#include<cmath>

//Struct for the centroids
struct xyCoord{
    int x;
    int y;
    int label;
    xyCoord(){}
    xyCoord(int x, int y, int label){
        this->x = x;
        this->y = y;
        this->label = label;
    }
};
 //Class for the points in the input file.
class Points{
    private:
        int xCoord;
        int yCoord;
        int label;
        
    public:
        Points(){}
        Points(int x, int y, int l){
            xCoord=x;
            yCoord=y;
            label=l;
        }
        int getX(){
            return xCoord;
        }
        int getY(){
            return yCoord;
        }
        int getLabel(){
            return label;
        }
        void setLabel(int l){
            label = l;
        }
};
//Class K_means is the class from which this program will do most of the work
class K_Mean{
    private:
        int K; 
        int numRows;
        int numCols;
        int numPoints;
        Points* ptList;
        int** imageArray;
        int labelChange;
        xyCoord* centroidList;

    public:
        //Constructor
        K_Mean(int k, int nr, int nc, int np){
            K = k;
            numRows = nr;
            numCols = nc;
            numPoints = np;
            //dynamic 1D array of all the Points
            ptList= new Points[numPoints];
            //dynamic 2D array of int to represent the points in a grid
            imageArray = new int*[nr];
            for(int i =0; i<nr; i++)
                imageArray[i] = new int[nc];
            //labelChange is set to 1 because this will alow us to start the loop in the main function
            labelChange = 1;
            //dynamic 1D array of the centroids
            centroidList = new xyCoord[K+1];
        }

        /*
        * Destructor 
        * Clear the memory of the various dynamic arrays in this program
        */
        ~K_Mean(){
            delete []ptList;
            delete []centroidList;
            for(int i = 0; i < numRows; i++) delete []imageArray[i];
            delete []imageArray;
        }
        
        int getLabelChange(){
            return labelChange;
        } 

        //Function loads all the points from the input file
        void loadPtList(std::ifstream& input){
            int x, y, label, i = 0;
            //Loop runs for as long as there still number to read in or until we read in all the points
            while(!input.eof() && i<numPoints){
                input >> x;
                input >> y;
                label = assignLabel();
                ptList[i] = Points(x,y,label);
                i++;
            }
        }

        //Function has a static int that assign 1 - 4 to each point. 
        int assignLabel(){
            static int label = 0;
            if(label==K) label = 0;
            return ++label;
        }

        //Function computes the K number of Centroids
        void computeCentoid(){
            /*
            * Dyanmically create 3 arrays initized with 0
            * Each array is of K+1 length. This only for simplier access of array and labels
            * Purpose is to keep track of the X values, Y values, and number of Points for each label
            */
            int* sumX = new int[K+1];
            int* sumY = new int[K+1];
            int* count = new int[K+1];
            for(int i =0; i<K+1; i++){
                sumX[i] = 0;
                sumY[i] = 0;
                count[i] = 0;
            }
            /*
            * Loop through all the points
            * Fint the label, x, and y values for each point
            * Continously adds all the values of x and y 
            * Keep track off how many points per label
            */
            for(int i = 0; i<numPoints; i++){
                int label = ptList[i].getLabel();
                int x = ptList[i].getX();
                int y = ptList[i].getY();
                count[label]++;
                sumX[label] += x;
                sumY[label] += y;
            }
            /*
            * Centroid coordinates are calculated and added to the list of centroids
            */
            for(int i = 1; i<=K; i++){
                centroidList[i].x = sumX[i]/count[i];
                centroidList[i].y = sumY[i]/count[i];
                centroidList[i].label = i;
            }
            //free the memory from the dynamic arrays
            delete[] sumX;
            delete[] sumY;
            delete[] count;
        }

        /*
        * The distance is caluated using the distance formula with the point and the centroid
        */
        double computeDist(Points &pt, xyCoord &cent){
            double ptX = pt.getX();
            double ptY = pt.getY();
            double centX = cent.x;
            double centY = cent.y;
            double sqX = (ptX - centX) * (ptX - centX);
            double sqY = (ptY - centY) * (ptY - centY);
            return sqrt(sqX + sqY);
        }

        
        //Function checks for the min distance between the point and the centroids
        void clusterCheck(){
            //labelChange is set to 0 and will keep track if labels are changed
        	labelChange = 0;
            //dynamic array to store the distance to each centroid
            double *dist = new double[K+1];
            //Loop through the entire array and compute the distance for each point
            for(int i = 0; i<numPoints; i++){
                //Loop computes and stores the distances into the array
                for(int j =1 ;j<=K ; j++) dist[j] = computeDist(ptList[i], centroidList[j]);
                //Get the current label for the point
                int currentLabel = ptList[i].getLabel();
                //Get the current distance between that point and its centroid
                double currentDistance = dist[currentLabel];
                /*
                * This loop find the lowest of the distances
                * If it finds a smaller distance, save the new low distance
                * and save the label of that new low distance centroid
                */
                for(int j = 1; j<=K; j++){
                    if(dist[j]<currentDistance){
                        currentDistance = dist[j];
                        currentLabel = j;
                    }
                }
                //Check if the new lowest label is the same as the points original label
                if(currentLabel!=ptList[i].getLabel()) {
                    ptList[i].setLabel(currentLabel);
                    labelChange++;
                }
            }
            //Free the memory
            delete []dist;
        }

        //Function to convert the points into a 2D array image of the points
        void pointsToImage(){
            for(int i = 0; i<numPoints; i++){
                imageArray[ptList[i].getX()][ptList[i].getY()] = ptList[i].getLabel();
            }
        }

        //Function to print out the points on a file
        void printPoints(std::ofstream& output){
            static int count = 0;
            output << "Points after " << count << " iteration: " << std::endl;
            for(int i = 0; i<numPoints; i++){
                output << ptList[i].getX() << " " << ptList[i].getY() << " " << ptList[i].getLabel() << std::endl;
            }
            count++;
        }
        
        //Function to print out the imageArray of points
        void printImage(std::ofstream& output){
            static int count = 0;
            output << "Groups after " << count << " iteration: " << std::endl;
            for(int i = 0; i < numRows; i++){
                for(int j = 0 ; j< numCols; j++){
                    if(imageArray[i][j]>0) output << imageArray[i][j];
                    else output << " ";
                }
                output << std::endl;
            }
            count++;
        }

};

int main(int argc, char** argv){
    /*
    * Opens an input and outout files
    * Declare the needed variables for the program
    */
    std::ifstream input;
    std::ofstream output, output2;
    int K, nr, nc, np;
    input.open(argv[1]);
    output.open(argv[2]);
    output2.open(argv[3]);
    //Prompt user for K value
    std::cout << "Enter the K number:\n";
    std::cin >> K;

    //Read in the number of rows, columns, and points from input file
    input >> nr;
    input >> nc;
    input >> np;

    //Create an instance of the KMeans class
    K_Mean kMean(K, nr, nc, np);

    kMean.loadPtList(input);
    
    //This loops runs as long as the labels keep changing or a Max of 2*K times
    int i =0;
    while(kMean.getLabelChange()>0 && i<2*K){
        kMean.pointsToImage();
        kMean.printPoints(output);
        kMean.printImage(output2);
        kMean.computeCentoid();
        kMean.clusterCheck();
        i++;
    }

    input.close();
    output.close();
    output2.close();
}
