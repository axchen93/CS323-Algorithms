import java.util.Scanner;
import java.io.*;

class Scheduler{
    public static void main(String args[]){
        try{
            Scanner input1 = new Scanner(new FileReader(args[0]));
            Scanner input2 = new Scanner(new FileReader(args[1]));
            PrintWriter output = new PrintWriter(args[2]);
            
            Scheduling sch = new Scheduling(input1, input2);
            sch.run(output);

            input1.close();
            input2.close();
            output.close();
        }catch(Exception e){}
        


    }
}