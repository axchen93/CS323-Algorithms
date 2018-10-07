import java.util.Scanner;
import java.io.*;
class LinkedList{
    private Node head;
    private int size;

    public LinkedList(){
        head = null;
        size = 0;
    }

    public boolean isEmpty(){
        return size == 0;
    }

    public void addNode(Node n){
        if(head == null){
            head = n;
            size++;
            return;
        }
        int nTime = n.getTime();
        int headTime = head.getTime();
        if( nTime <= headTime ){
            n.setNext(head);
            head = n;
            size++;
            return;
        }
        Node temp = head, prev = head;
        while(temp.getNext()!=null && (nTime > temp.getTime())){
            prev = temp;
            temp = temp.getNext();
        }
        if(nTime <= temp.getTime()){
            prev.setNext(n);
            n.setNext(temp);
        }else{
            n.setNext(temp.getNext());
            temp.setNext(n);
        }
        size++;
    }

    public Node removeHead(){
        if(head == null) return null;
        Node temp = head;
        head = head.getNext();
        temp.setNext(null);
        size--;
        return temp;
    }

    public void to_String(){
        System.out.println("Open LinkedListQueue");
        Node temp = head;
        while(temp!=null){
            System.out.print(temp.getData() + "--->");
            temp = temp.getNext();
        }
        System.out.println();
    }
}