class Node{
    private int data, timeReq;
    private Node next;

    public Node(int x, int s){
        data = x;
        timeReq = s;
        next = null;
    }

    public void setNext(Node s){
        next = s;
    }

    public int getData(){
        return data;
    }

    public int getTime(){
        return timeReq;
    }

    public Node getNext(){
        return next;
    }
}