
import java.io.PrintWriter;
import java.util.Scanner;

class HeapSort{
     private int rootIndex;
     private int parentIndex;
     private int leftChildIndex;
     private int rightChildIndex;
     private int minChildIndex;
     private int size;
     private int heapArr[];

     HeapSort(int size){
         heapArr = new int[size+1];
         heapArr[0] = 0;
         rootIndex = 1;
         parentIndex = 1;
         leftChildIndex = rootIndex*2;
         rightChildIndex = rootIndex*2 + 1;
         minChildIndex = 1;
         this.size = 0;
     }
     
    public static int countData(Scanner inFile){
        int counter = 0;
        while(inFile.hasNextInt()){
            inFile.nextInt();
            counter++;
        }
        return counter;
    }

    public void buildHeap(Scanner inFile, PrintWriter output1){
        while(inFile.hasNextInt()){
            int current = inFile.nextInt();
            insertData(current);
            size++;
            bubbleUp(heapArr[0]);
            printHeap(output1);
        }
     }

    public void deleteHeap(PrintWriter output, PrintWriter output2){
        while(!isEmpty()){
            int current  = getRoot();
            output2.print(current + " ");
            replaceRoot();
            bubbleDown(rootIndex);
            printHeap(output);
        }
    }

    private void bubbleUp(int index){
        if(isRoot(index)) return;
        parentIndex = index/2;
        int childData = heapArr[index];
        int parentData = heapArr[parentIndex];
        if(childData>=parentData) return;
        swapData(index, parentIndex);
        bubbleUp(parentIndex);
    }

    private void bubbleDown(int index){
        if(isLeaf(index)) return;
        leftChildIndex = index*2;
        rightChildIndex = leftChildIndex;
        if(rightChildIndex+1<=size) rightChildIndex = index*2 + 1;
        minChildIndex = findMin(leftChildIndex, rightChildIndex);
        if(heapArr[index]<=heapArr[minChildIndex]) return;
        swapData(index, minChildIndex);
        bubbleDown(minChildIndex);
    }

    private void swapData(int x, int y){
        int temp = heapArr[x];
        heapArr[x] = heapArr[y];
        heapArr[y] = temp;
    }

    private void insertData(int x){
        heapArr[0]++;
        heapArr[heapArr[0]] = x;
    }

    private int findMin(int left, int right){
        if(heapArr[left]<=heapArr[right]) return left;
        return right;
    }
    private void replaceRoot(){
        heapArr[rootIndex] = heapArr[size];
        heapArr[size] = 0;
        size--;
        heapArr[0]--;
    }

    private int getRoot(){
        return heapArr[rootIndex];
    }

    private boolean isRoot(int index){
        return index<=1;
    }

    private boolean isLeaf(int index){
        return (index*2) > size;
    }

    private boolean isEmpty(){
        return size == 0;
    }
    
    private void printHeap(PrintWriter output){
        for(int i = 0; i<heapArr.length && heapArr[i]!=0; i++){
            output.print(heapArr[i] + " ");
        }
        output.println();
    }

}