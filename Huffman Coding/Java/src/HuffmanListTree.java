import java.util.Scanner;
import java.io.*;
class HuffmanListTree{
    private BinTreeNode listHead, root;

    HuffmanListTree(){
        BinTreeNode dummy = new BinTreeNode("dummy", 0);
        listHead = dummy;
        root = null;
    }

    HuffmanListTree(BinTreeNode T){
        BinTreeNode dummy = new BinTreeNode("dummy", 0);
        listHead = dummy;
        listHead.setNext(T);
        root = null;
    }

    public void setListHead(BinTreeNode T){
        listHead = T;
    }

    public void setRoot(BinTreeNode T){
        root = T;
    }

    public BinTreeNode getRoot(){
        return root;
    }

    public BinTreeNode getListHead(){
        return listHead;
    }

    public void constructLinkedList(Scanner input, PrintWriter output){
        String chStr;
        int prob;
        while(input.hasNext()){
            chStr = input.next();
            prob = input.nextInt();
            BinTreeNode spot = findSpot(prob);
            BinTreeNode newNode = new BinTreeNode(chStr, prob);
            insertNode(spot, newNode);
            printList(output);
        }
    }

    public void constructBinTree(PrintWriter output){
        while(listHead.getNext().getNext()!=null){
            BinTreeNode first = listHead.getNext();
            BinTreeNode second  = first.getNext();

            String chStr = first.getChStr() + second.getChStr();
            int prob = first.getProb() + second.getProb();

            BinTreeNode newNode = new BinTreeNode(chStr, prob);
            newNode.setLeft(first);
            newNode.setRight(second);

            BinTreeNode spot = findSpot(prob);
            insertNode(spot, newNode);

            listHead.setNext(second.getNext());

            newNode.printNode(output);
            printList(output);
        }
        root = listHead.getNext();
    }

    public void constructCode(BinTreeNode T, String code, PrintWriter output){
        if(T == null){
            System.out.println("Empty Tree");
            System.exit(0);
        }
        if(isLeaf(T)){
            T.setCode(code);
            output.println(T.getChStr() + "- Code: " + T.getCode());
            return;
        }
        constructCode(T.getLeft(), code + "0", output);
        constructCode(T.getRight(), code + "1", output);
    }
    private boolean isLeaf(BinTreeNode T){
        return (T.getLeft()==null) && (T.getRight()==null);
    }

    private BinTreeNode findSpot(int x){
        BinTreeNode spot = listHead;
        while(spot.getNext()!=null && spot.getNext().getProb() < x)
            spot = spot.getNext();
        return spot;
    }

    private void insertNode(BinTreeNode spot, BinTreeNode newNode){
        newNode.setNext(spot.getNext());
        spot.setNext(newNode);
    }

    private void printList(PrintWriter output){
        BinTreeNode current = listHead;
        output.print("Listhead ---> " + current.toString());
        current = current.getNext();
        while(current != null){
            output.print(" ---> " + current.toString());
            current = current.getNext();
        }
        output.print("---> NULL\n");
    }

    public void preOrder(BinTreeNode T, PrintWriter output){
        if(T==null) return;
        T.printNode(output);
        preOrder(T.getLeft(), output);
        preOrder(T.getRight(), output);
    }

    public void inOrder(BinTreeNode T, PrintWriter output){
        if(T==null) return;
        preOrder(T.getLeft(), output);
        T.printNode(output);
        preOrder(T.getRight(), output);
    }

    public void postOrder(BinTreeNode T, PrintWriter output){
        if(T==null) return;
        preOrder(T.getLeft(), output);
        preOrder(T.getRight(), output);
        T.printNode(output);
    }
}