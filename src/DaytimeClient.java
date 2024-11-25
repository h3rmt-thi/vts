import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class DaytimeClient {
    public static void main(String[] args) {
        if (args.length != 1) {
            throw new IllegalArgumentException("Usage: java DaytimeClient <host>");
        }
        String host = args[0];
        try {
            System.out.println("Local starttime is: \t" + java.time.LocalDateTime.now());
            Registry registry = LocateRegistry.getRegistry(host, 8080);
            Daytime remote = (Daytime) registry.lookup("time");
            String received = remote.getDayTime();
            System.out.println("Received time is: \t\t" + received);
            System.out.println("Local endtime is: \t\t" + java.time.LocalDateTime.now());
        } catch (Exception e) {
            System.err.println("Error: " + e);
        }
    }
}