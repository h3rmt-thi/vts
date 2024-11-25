public class FigurenThreads {
    public void startThreads() throws InterruptedException {
        MyFigur f = new MyFigur();
        Schreiber s = new Schreiber(f);
        Leser l = new Leser(f);

        s.setDaemon(true);
        l.setDaemon(true);

        s.start();
        l.start();

        // dont join writer thread
        l.join();
    }

    public static void main(String[] args) throws InterruptedException {
        FigurenThreads ft = new FigurenThreads();
        ft.startThreads();
    }
}
