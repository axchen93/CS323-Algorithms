import java.io.*;

class BinTreeNode{
    private String chStr;
    private int prob;
    private String code;
    BinTreeNode next, left, right;

    BinTreeNode(){
        chStr = null;
        prob = 0;
        code = null;
        next = left = right = null;
    }

    BinTreeNode(String c, int p){
        chStr = c;
        prob = p;
        code = null;
        next = left = right = null;
    }

    public String getChStr(){
        return chStr;
    }

    public int getProb(){
        return prob;
    }

    public String getCode(){
        return code;
    }

    public BinTreeNode getLeft(){
        return left;
    }

    public BinTreeNode getRight(){
        return right;
    }

    public BinTreeNode getNext(){
        return next;        
    }

    public void setCode(String c){
        code = c;
    }

    public void setLeft(BinTreeNode T){
        left = T;
    }

    public void setRight(BinTreeNode T){
        right = T;
    }
    
    public void setNext(BinTreeNode T){  
        next = T;      
    }

    public String toString(){
        String ans = "(\"" + chStr + "\", " + prob + ", ";
        if(next==null) ans += "NULL)";
        else ans += ("\"" + next.getChStr() + "\")");
        return ans;
    }

    public void printNode(PrintWriter output4){
        if(this == null){
            output4.println("NULL");
            return;
        }
        output4.print("(" + chStr + ", " + prob + ", ");
        if(code == null) output4.print("NULL, ");
        else output4.print(code + ", ");
        if(next == null) output4.print("NULL, ");
        else output4.print(next.getChStr() + ", ");
        if(left == null) output4.print("NULL, ");
        else output4.print(left.getChStr() + ", ");
        if(right == null) output4.print("NULL)");
        else output4.print(right.getChStr() + ")");

        output4.println();
    }
}