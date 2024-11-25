import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.time.LocalDateTime;

public class DaytimeImpl extends UnicastRemoteObject implements Daytime {
    protected DaytimeImpl() throws RemoteException {
        // only required as super also throws RemoteException
    }

    @Override
    public String getDayTime() throws RemoteException {
        System.out.println("Received request for time");
        return LocalDateTime.now().toString();
    }
}