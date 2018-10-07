import java.util.Scanner;
import java.io.*;
class HuffmanCoding{
    public static void main(String args[]){
        try{
            Scanner input = new Scanner(new FileReader(args[0]));
            PrintWriter output1 = new PrintWriter(args[1]);
            PrintWriter output2 = new PrintWriter(args[2]);
            PrintWriter output3 = new PrintWriter(args[3]);
            PrintWriter output4 = new PrintWriter(args[4]);

            HuffmanListTree huffman = new HuffmanListTree();

            huffman.constructLinkedList(input, output1);
            huffman.constructBinTree(output2);
            huffman.constructCode(huffman.getRoot(), "", output3);

            output4.println("Preorder:");
            huffman.preOrder(huffman.getRoot(), output4);
            output4.println("\nInorder:");
            huffman.inOrder(huffman.getRoot(), output4);
            output4.println("\nPostorder:");
            huffman.postOrder(huffman.getRoot(), output4);

            input.close();
            output1.close();
            output2.close();
            output3.close();
            output4.close();
        }catch(Exception e){}
    }
}