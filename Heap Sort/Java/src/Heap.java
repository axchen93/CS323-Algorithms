import java.io.*;
import java.util.Scanner;
class Heap{
    public static void main(String args[]){
        try{
            Scanner inFile = new Scanner(new FileReader(args[0]));
            PrintWriter output1 = new PrintWriter(args[1]);
            PrintWriter output2 = new PrintWriter(args[2]);

            int size = HeapSort.countData(inFile);
            inFile.close();

            HeapSort heap = new HeapSort(size);

            inFile = new Scanner(new FileReader(args[0]));
            heap.buildHeap(inFile, output1);
            heap.deleteHeap(output1, output2);
            inFile.close();
            output1.close();
            output2.close();
        }catch(Exception e){}
        
    }
}