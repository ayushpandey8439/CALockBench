package worker;

public class worker implements Runnable{
    private Thread t;
    private boolean exit = false;
    private int id;
    public worker(int Id){
        id=Id;
        System.out.println(id);
    }
    public void exit(){
        this.exit = true;
    }

    @Override
    public void run() {
        while(!this.exit){
//            System.out.println(id+ " Running");
        }
    }
}
