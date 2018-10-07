class Points{
    private int x;
    private int y;
    private int label;

    Points(){
        x = -1;
        y = -1;
        label = -1;
    }

    Points(int x, int y){
        this.x = x;
        this.y = y;
        label = -1;
    }

    Points(int x, int y, int z){
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

    public void setLabel(int z){
        label = z;
    }
}
