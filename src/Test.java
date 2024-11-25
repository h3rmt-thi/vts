public class Test {
    public static void main(String[] args) {
        UniqueId uid = new UniqueId("id.dat");
        try {
            uid.init(10_000);
            for (int i = 0; i < 5; i++)
                new Thread(() -> {
                    try {
                        for (int j = 0; j < 10; j++)
                            System.out.println(uid.getNext());
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }).start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
