import java.rmi.Remote;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class DaytimeServer {
    public static void main(String[] args) throws Exception {
        Remote remote = new DaytimeImpl();
        Registry registry = LocateRegistry.createRegistry(8080);
        registry.rebind("time", remote);
        System.out.println("TimerServer gestartet ...");
    }
}