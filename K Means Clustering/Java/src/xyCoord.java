class xyCoord{
    private int x;
    private int y;
    private int label;

    xyCoord(){
        x = -1;
        y = -1;
        label = -1;
    }

    xyCoord(int x, int y){
        this.x = x;
        this.y = y;
        label = -1;
    }

    xyCoord(int x, int y, int z){
        this.x = x;
        this.y = y;
        label = z;
    }

    public int getX(){
        return x;
    }

    public int getY(){
        return y;
    }

    public int getLabel(){
        return label;
    }
}