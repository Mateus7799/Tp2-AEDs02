import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

class Player {
    String id;
    String name;
    String height;
    String weight;
    String college;
    String born;
    String birthCity;
    String birthState;

    public Player(String id, String name, String height, String weight, String college, String born, String birthCity, String birthState) {
        this.id = id;
        this.name = name;
        this.height = height;
        this.weight = weight;
        this.college = college;
        this.born = born;
        this.birthCity = birthCity;
        this.birthState = birthState;
    }

    @Override
    public String toString() {
        return String.format("[Id %s Player %s height %s weight %s born %s collage %s birth city %s birth state %s]",
                id, name, height, weight, born, college, birthCity, birthState);
    }
}

public class PlayerHeapsort {
    private static int comparisons = 0;
    private static int movements = 0;

    private static void heapify(ArrayList<Player> arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && Integer.parseInt(arr.get(l).height) > Integer.parseInt(arr.get(largest).height)) {
            largest = l;
        }
        if (r < n && Integer.parseInt(arr.get(r).height) > Integer.parseInt(arr.get(largest).height)) {
            largest = r;
        }
        comparisons += 2;

        if (largest != i) {
            Player temp = arr.get(i);
            arr.set(i, arr.get(largest));
            arr.set(largest, temp);
            movements += 3;
            heapify(arr, n, largest);
        }
    }

    private static void heapSort(ArrayList<Player> arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            Player temp = arr.get(0);
            arr.set(0, arr.get(i));
            arr.set(i, temp);
            movements += 3;

            heapify(arr, i, 0);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("/tmp/players.csv"));
        PrintWriter writer = new PrintWriter(new FileWriter("808360_heapsort.txt"));

        ArrayList<Player> players = new ArrayList<>();
        String line = reader.readLine(); // ignore first line

        while ((line = reader.readLine()) != null && !line.equals("FIM")) {
            String[] data = line.split(",");
            players.add(new Player(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]));
        }
        reader.close();

        heapSort(players);

        for (Player player : players) {
            System.out.println(player.toString());
        }

        writer.print("808360\t" + comparisons + "\t" + movements + "\t" + System.currentTimeMillis());
        writer.close();
    }
}
